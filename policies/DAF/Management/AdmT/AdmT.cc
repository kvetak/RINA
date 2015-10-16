#include "AdmT.h"
Define_Module(AdmT);

#include <string>
#include <list>
#include "Utils.h"

using namespace std;

AdmT::AdmT() {
    //Consts
    TIM_CONNECT    = "StartCommunication";
    TIM_STARTFLOWS = "StartFlows";
    TIM_HELLO = "SayHello";

    PAR_DSTAPNAME       = "dstApName";
    PAR_DSTAPINSTANCE   = "dstApInstance";
    PAR_DSTAENAME       = "dstAeName";
    PAR_DSTAEINSTANCE   = "dstAeInstance";
}

void AdmT::initialize()
{
    DifAllocator = getRINAModule<DA*>(this, 3, {MOD_DIFALLOC, MOD_DA});

    if (!DifAllocator)
        error("Pointer to DifAllocator is not initialized!");

    //Init pointers
    initPointers();
    //Source info
    initNamingInfo();
    //Setup signals
    initSignalsAndListeners();
    //Init QoSRequirements
    initQoSRequiremets();

    //Destination for flow
    dstApName     = this->par(PAR_DSTAPNAME).stringValue();
    dstApInstance = this->par(PAR_DSTAPINSTANCE).stringValue();
    dstAeName     = this->par(PAR_DSTAENAME).stringValue();
    dstAeInstance = this->par(PAR_DSTAEINSTANCE).stringValue();

    int connT = par("connectAt").doubleValue();
    if(connT >= 0) {
        scheduleAt(simTime()+connT, new cMessage(TIM_CONNECT));
    }

    int iniFT = par("startFlowsAt").doubleValue();
    if(iniFT >= 0) {
        scheduleAt(simTime()+iniFT, new cMessage(TIM_STARTFLOWS));
    }
}

void AdmT::handleMessage(cMessage *msg) { action(msg, true); }


void AdmT::onConnect(){
    //Prepare flow's source and destination
    APNamingInfo src = this->getApni();
    APNamingInfo dst = APNamingInfo( APN(this->dstApName), this->dstApInstance,
                                     this->dstAeName, this->dstAeInstance);

    //Create a flow
    FlowObject = new Flow(src, dst);
    FlowObject->setQosRequirements(this->getQoSRequirements());

    //Notify IRM about a new flow
    insertFlow();

    //Call flow allocation request
    sendAllocationRequest(FlowObject);

    int shT = par("sayHelloAfter").doubleValue();
    if(shT >= 1) {
        scheduleAt(simTime()+shT, new cMessage(TIM_HELLO));
    }
}


void AdmT::allocateFlows(string dif, string src, vector<string> dstVec){
    if(dif == "" || src == "" || dstVec.empty()) { return; }

    if (!DifAllocator->isDifLocal(DAP(dif))) {
        error( "Local CS does not have any IPC in DIF ");
    }

    //Retrieve DIF's local IPC member
    cModule* targetIpc = DifAllocator->getDifMember(DAP(dif));

    RA * ra = dynamic_cast<RA*>(targetIpc->getSubmodule(MOD_RESALLOC)->getSubmodule(MOD_RA));
    FA * fa = dynamic_cast<FA*>(targetIpc->getSubmodule(MOD_FLOWALLOC)->getSubmodule(MOD_FA));

    if(!ra) {
        error( "Local IPC RA not found");
    }
    if(!fa) {
        error( "Local IPC FA not found");
    }


    src.append("_").append(dif);

    for(string & dst : dstVec) {
        if(dst == "") { continue; }

        dst.append("_").append(dif);

        APNamingInfo srcAPN = APNamingInfo(APN(src.c_str()));
        APNamingInfo dstAPN = APNamingInfo(APN(dst.c_str()));

        Flow * flow   = new Flow(srcAPN, dstAPN);

        if (flow->isManagementFlow()) { // mgmt flow
            ra->createNFlow(flow);
        } else { // data flow
            ra->createNM1Flow(flow);
        }
        reqFlows[dst] = flow;
    }
}


void AdmT::deallocateFlows(string dif, string src, vector<string> dstVec){
    if(dif == "" || src == "" || dstVec.empty()) { return; }

    if (!DifAllocator->isDifLocal(DAP(dif))) {
        error( "Local CS does not have any IPC in DIF ");
    }

    //Retrieve DIF's local IPC member
    cModule* targetIpc = DifAllocator->getDifMember(DAP(dif));

    RA * ra = dynamic_cast<RA*>(targetIpc->getSubmodule(MOD_RESALLOC)->getSubmodule(MOD_RA));
    if(!ra) { error( "Local IPC RA not found"); }

    FA * fa = dynamic_cast<FA*>(targetIpc->getSubmodule(MOD_FLOWALLOC)->getSubmodule(MOD_FA));
    if(!fa) { error( "Local IPC FA not found"); }

    for(string & dst : dstVec) {
        if(dst == "") { continue; }


        dst.append("_").append(dif);

        if(reqFlows.find(dst) != reqFlows.end()) {
            //fa->receiveDeallocateRequest(reqFlows[dst]);
            //Irm->receiveDeallocationRequestFromAe(reqFlows[dst]);
            ra->removeNM1Flow(reqFlows[dst]);
            reqFlows.erase(dst);
        }

    }
}

void AdmT::onSFlows(){
    string dif = par("DIF").stdstringValue();
    string src = par("src").stdstringValue();
    string dsts = par("dsts").stdstringValue();
    vector<string> dstVec = split(dsts, ',');

    allocateFlows(dif, src, dstVec);
}

void AdmT::onSayHello(){
    //Create Hello messsage
    HelloMsg* hello = new HelloMsg(par("src").stdstringValue(), par("DIF").stdstringValue());

    //Send message
    sendData(FlowObject, hello);
}

void AdmT::processMRead(CDAPMessage* msg) { action(msg, false); }
void AdmT::processMReadR(CDAPMessage* msg) { action(msg, false); }


void AdmT::action(cMessage *msg, bool del) {
    if(msg->isSelfMessage()){
        if ( !strcmp(msg->getName(), TIM_CONNECT) ) {
            onConnect();
        } else if ( !strcmp(msg->getName(), TIM_STARTFLOWS) ) {
            onSFlows();
        } else if ( !strcmp(msg->getName(), TIM_HELLO) ) {
            onSayHello();
        }
    } else {
        if(reqFlowMsg * m = dynamic_cast<reqFlowMsg*>(msg)){
            if(m->src == par("src").stdstringValue() && m->dif == par("DIF").stdstringValue()) {
                allocateFlows(m->dif, par("src").stdstringValue(), m->flowsDstAppName);
            }
        } else if(reqDelFlowMsg * m = dynamic_cast<reqDelFlowMsg*>(msg)){
            if(m->src == par("src").stdstringValue() && m->dif == par("DIF").stdstringValue()) {
                deallocateFlows(m->dif, par("src").stdstringValue(), m->flowsDstAppName);
            }
        }
    }
    if(del) { delete msg; }
}
