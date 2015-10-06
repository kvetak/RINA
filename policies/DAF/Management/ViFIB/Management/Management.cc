#include "Management.h"

#include <string>
#include <list>
#include "Utils.h"
#include "RINASignals.h"

using namespace std;

namespace ViFIB {

Define_Module(Management);

Management::Management() {
    //Consts
    TIM_CONNECT    = "StartCommunication";
    TIM_STARTFLOWS = "StartFlows";
    TIM_HELLO = "SayHello";

    PAR_DSTAPNAME       = "dstApName";
    PAR_DSTAPINSTANCE   = "dstApInstance";
    PAR_DSTAENAME       = "dstAeName";
    PAR_DSTAEINSTANCE   = "dstAeInstance";

    WAKE_UP          = "WakeUp";
    ADD_UPDATE          = "UpdateAfterAdding";
    REMOVE_UPDATE       = "UpdateAfterRemoving";
}

void Management::initialize() {
    cModule * Node = this->getModuleByPath("^.^.^");


    DifAllocator = dynamic_cast<DA*>(Node->getSubmodule(MOD_DIFALLOC)->getSubmodule(MOD_DA));
    if (!DifAllocator) { error("Pointer to DifAllocator is not initialized!"); }

    //Init pointers
    initPointers();
    //Source info
    initNamingInfo();
    //Setup signals
    initSignalsAndListeners();
    //Init QoSRequirements
    initQoSRequiremets();

    //Destination of management agent
    dstApName     = this->par(PAR_DSTAPNAME).stringValue();
    dstApInstance = this->par(PAR_DSTAPINSTANCE).stringValue();
    dstAeName     = this->par(PAR_DSTAENAME).stringValue();
    dstAeInstance = this->par(PAR_DSTAEINSTANCE).stringValue();

    int connT = par("connectAt").doubleValue();
    if(connT >= 0) { scheduleAt(simTime()+connT, new cMessage(TIM_CONNECT)); }

    baseIPC =  getModuleByPath(par("baseIPC").stringValue());

    zoneId = par("zoneId").stdstringValue();
    maxBorders = this->par("maxBorders").longValue();
    maxDiameter = this->par("maxDiameter").longValue();
    currentNodes = 0;
    currentBorders = 0;

    sig2slaves = registerSignal(SIG_VAR_ViFIB_Master2Slave);
    Node->subscribe(SIG_VAR_ViFIB_Slave2Master, this);

    int waitUntil = par("waitUntil").longValue();
    if(waitUntil > 0) {
        waiting = true;
        scheduleAt(waitUntil, new cMessage(WAKE_UP));
    } else {
        waiting = false;
    }

}

void Management::onConnect(){
    //Prepare flow's source and destination
    APNamingInfo src = this->getApni();
    APNamingInfo dst = APNamingInfo( APN(this->dstApName), this->dstApInstance, this->dstAeName, this->dstAeInstance);

    //Create a flow
    FlowObject = new Flow(src, dst);
    FlowObject->setQosRequirements(this->getQoSRequirements());

    //Notify IRM about a new flow
    insertFlow();

    //Call flow allocation request
    sendAllocationRequest(FlowObject);

    int shT = par("sayHelloAfter").doubleValue();
    if(shT >= 1) { scheduleAt(simTime()+shT, new cMessage(TIM_HELLO)); }
}

void Management::handleMessage(cMessage *msg) { action(msg, true); }
void Management::processMRead(CDAPMessage* msg) { action(msg, false); }
void Management::processMReadR(CDAPMessage* msg) { action(msg, false); }

void Management::receiveSignal(cComponent *src, simsignal_t id, cObject *obj){
    if(cMessage * m = dynamic_cast<cMessage*>(obj)){ action(m, false); }
}

void Management::improveNet(vector< Graph<unsigned short>::LinkAB > & newLinks) {
    int diameter = g.computePaths();
    while(diameter > maxDiameter) {
        Graph<unsigned short>::LinkAB t = g.improve();
        if(t.metric > 0) {
            newLinks.push_back(t);
        }
        diameter = g.computePaths();
    }
}

void Management::propagate(vector< Graph<unsigned short>::LinkAB > & newLinks) {
    map<string, vifibConnect*> messages;

    for(auto link :newLinks) {
        if(messages[link.A] == NULL) { messages[link.A] = new vifibConnect(link.A); }
        messages[link.A]->dsts.push_back(clientsInfo[link.B]);

        if(messages[link.B] == NULL) { messages[link.B] = new vifibConnect(link.B); }
        messages[link.B]->dsts.push_back(clientsInfo[link.A]);
    }

    for(auto message : messages) {
        emit(sig2slaves, message.second);
    }
}

void Management::action(cMessage *msg, bool del) {
    if(msg->isSelfMessage()){
        if ( !strcmp(msg->getName(), WAKE_UP) ) {
            waiting = false;
            vector< Graph<unsigned short>::LinkAB > newLinks = g.addRandomLinks(clientsInfo.size());
            improveNet(newLinks);
            propagate(newLinks);
        } else if ( !strcmp(msg->getName(), ADD_UPDATE) ) {
            if(!waiting) {
                vector< Graph<unsigned short>::LinkAB > newLinks;
                improveNet(newLinks);
                propagate(newLinks);
            }
        } else if ( !strcmp(msg->getName(), REMOVE_UPDATE) ) {
            if(!waiting) {
                vector< Graph<unsigned short>::LinkAB > newLinks;
                improveNet(newLinks);
                propagate(newLinks);
            }
        }
    } else {
        if(dynamic_cast<_vifibMessage*>(msg)){
            if(vifibHello * m = dynamic_cast<vifibHello*>(msg)){
                vifibInfo * info = & clientsInfo[m->VifibId];
                if(info->location == "") {
                    info->location = m->location;
                    int cAddr = 1;
                    while(cAddr2Id[cAddr] != ""){ cAddr++; }
                    info->cloud_addr = cAddr;
                    info->cloud_id = to_string(cAddr);
                    currentNodes++;

                    if(currentBorders < maxBorders) {
                        info->isBorder = true;
                        int bAddr = 1;
                        while(bAddr2Id[bAddr] != ""){ bAddr++; }
                        info->border_addr = bAddr;
                        info->border_id = to_string(bAddr);
                        currentBorders++;
                    }

                    vifibIniValues * response;

                    if(info->isBorder){
                        bordersConnections[m->VifibId];
                        sendData(FlowObject, new masterNewBorder(zoneId, m->VifibId, info->border_id));
                        response = new vifibIniValues(m->VifibId, info->cloud_id, "Cloud", info->border_id, "Backbone");
                    } else {
                        response = new vifibIniValues(m->VifibId, info->cloud_id, "Cloud");
                    }
                    emit(sig2slaves, response);

                    g.addNode(m->VifibId);
                    scheduleAt(simTime(), new cMessage(ADD_UPDATE));

                }
            } else if(vifibBye * m = dynamic_cast<vifibBye*>(msg)){
                vifibInfo * info = & clientsInfo[m->VifibId];
                if(info->location != "") {
                    cAddr2Id.erase(info->cloud_addr);
                    if(info->isBorder){
                        bordersConnections.erase(m->VifibId);
                        // ************* Reallocate lost border <-> border connections

                        bAddr2Id.erase(info->border_addr);
                        sendData(FlowObject, new masteRemovedBorder(zoneId, m->VifibId, info->border_id));
                    }

                    g.removeNode(m->VifibId);
                    scheduleAt(simTime(), new cMessage(REMOVE_UPDATE));
                }
                clientsInfo.erase(m->VifibId);
            }
        } else if(dynamic_cast<_masterMessage*>(msg)){
            if(masteBordersList * m = dynamic_cast<masteBordersList*>(msg)){
                for(auto entry : m->borders){
                    if(entry.first != zoneId){
                        if(zoneId < entry.first){
                            // ************* Reconnect lost border <-> border and add new ones
                        }
                        extBorders[entry.first] = entry.second;
                    }
                }
            } else if(masterConenctTo * m = dynamic_cast<masterConenctTo*>(msg)){
                // ************* Conect borders <-> dstBorders, random, start at s(src), d(dst)
                if(currentBorders > 0 && extBorders[m->dstZone].size() > 0){
                    int s = intuniform(0, currentBorders-1);
                    int d = intuniform(0, extBorders[m->dstZone].size()-1);
                }
            }
        }
    }

    if(del) { delete msg; }
}

}
