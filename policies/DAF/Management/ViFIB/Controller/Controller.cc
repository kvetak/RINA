#include "Controller.h"

#include <string>
#include <list>
#include "Utils.h"
#include "RINASignals.h"

using namespace std;

namespace ViFIB {

Define_Module(Controller);

Controller::AddedFlowListener::AddedFlowListener(Controller * p) : parent(p) {}
void Controller::AddedFlowListener::receiveSignal(cComponent *src, simsignal_t id, cObject *obj){
    //Flow * f;
    //Do something - get flow
    //parent->addedFlow(f);
}

Controller::RemovedFlowListener::RemovedFlowListener(Controller * p) : parent(p) {}
void Controller::RemovedFlowListener::receiveSignal(cComponent *src, simsignal_t id, cObject *obj){
    //Flow * f;
    //Do something - get flow
    //parent->removedFlow(f);
}


Controller::Controller() {
    //Consts
    TIM_CONNECT    = "StartCommunication";
    TIM_STARTFLOWS = "StartFlows";
    TIM_HELLO = "SayHello";

    PAR_DSTAPNAME       = "dstApName";
    PAR_DSTAPINSTANCE   = "dstApInstance";
    PAR_DSTAENAME       = "dstAeName";
    PAR_DSTAEINSTANCE   = "dstAeInstance";
}

void Controller::initialize() {
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

    dir = getRINAModule<Directory*>(this, 3, {MOD_DIFALLOC, MOD_DA});

    baseIPC =  getModuleByPath(par("baseIPC").stringValue());
    substrateAddr = baseIPC->par("apName").stdstringValue();
    vifibId = par("vifibId").stdstringValue();
    imBorder = false;

    Node->subscribe(SIG_VAR_AddedFlow, new AddedFlowListener(this));
    Node->subscribe(SIG_VAR_RemovedFlow, new RemovedFlowListener(this));
}

void Controller::onConnect(){
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

void Controller::handleMessage(cMessage *msg) { action(msg, true); }
void Controller::processMRead(CDAPMessage* msg) { action(msg, false); }
void Controller::processMReadR(CDAPMessage* msg) { action(msg, false); }


void Controller::action(cMessage *msg, bool del) {
    if(msg->isSelfMessage()){
        if ( !strcmp(msg->getName(), TIM_HELLO) ) {
            sendData(FlowObject, new vifibHello(vifibId, substrateAddr));
        }
    } else {
        if(vifibIniValues * m = dynamic_cast<vifibIniValues*>(msg)){
            if(m->VifibId != vifibId) { error("Received message to another ViFIB node!!"); }
            if(m->isBorder) {
                createVifiBIPC_Double(m->cloudAddr, m->cloudDIF, m->backboneAddr, m->backboneDIF);
            } else {
                createVifiBIPC_Simple(m->cloudAddr, m->cloudDIF);
            }
        } else if(vifibConnect * m = dynamic_cast<vifibConnect*>(msg)){
            if(m->VifibId != vifibId) { error("Received message to another ViFIB node!!"); }
            for(auto entry : m->dsts) {
                if(entry.border_id == "") {
                    connectTo(entry.cloud_id, entry.location, false);
                } else  {
                    connectTo(entry.border_id, entry.location, true);
                }
            }
        } else if(vifibDisconnect * m = dynamic_cast<vifibDisconnect*>(msg)){
            if(m->VifibId != vifibId) { error("Received message to another ViFIB node!!"); }
            for(auto entry : m->dsts) {
                disconnectFrom(entry);
            }
        }
    }

    if(del) { delete msg; }
}


void Controller::connectTo(string dstAddr, string dstLocation, int border) {
    if(flows.find(dstAddr) != flows.end()) { return; }

    DAP dif = border ? DAP(backboneDIF) : DAP(cloudDIF);

    if (!DifAllocator->isDifLocal(dif)) { error( "Local CS does not have any IPC in DIF"); }

    //Retrieve DIF's local IPC member
    cModule* targetIpc = DifAllocator->getDifMember(dif);

    RA * ra = dynamic_cast<RA*>(targetIpc->getSubmodule(MOD_RESALLOC)->getSubmodule(MOD_RA));
    if(!ra) { error( "Local IPC RA not found"); }


    string dst = dstAddr;
    if(border){  dst.append("_").append(backboneDIF); }
    else { dst.append("_").append(cloudDIF); }

    APNamingInfo dstAPN = APNamingInfo(APN(dst.c_str()));
    APNamingInfo srcAPN = border ? backboneAPN : cloudAPN;


    dir->addDirEntry(dstAPN.getApn());
    dir->addNewDif(dstAPN.getApn(), Address(dstLocation));

    Flow * flow   = new Flow(srcAPN, dstAPN);

    if (flow->isManagementFlow()) {
        ra->createNFlow(flow);
    } else {
        ra->createNM1Flow(flow);
    }

    flows[dstAddr] = flow;
}

void Controller::disconnectFrom(string dstAddr) {
    if(flows.find(dstAddr) == flows.end()) { return; }

    Flow * f = flows[dstAddr];
    flows.erase(dstAddr);

    //Do the disconnection here!!
    cout << *f<<endl;
}

void Controller::createVifiBIPC_Simple(string cloudAddr, string cloudDIF) {
    imBorder = false;
    this->cloudAddr = cloudAddr;
    this->cloudDIF = cloudDIF;

    string tcloudAPN = cloudAddr;
    tcloudAPN.append("_").append(cloudDIF);
    cloudAPN = APNamingInfo(APN(tcloudAPN.c_str()));

    dir->addDirEntry(cloudAPN.getApn());
    dir->addNewDif(cloudAPN.getApn(), Address(substrateAddr));


    cModule * node = this->getModuleByPath("^.^.^");
    cModuleType* ipcType = cModuleType::get("rina.src.DIF.IPCProcess");

    cModule *cloudIPC = ipcType->create("CloudIPC", node);
    cloudIPC->par("ipcAddress").setStringValue(cloudAddr);
    cloudIPC->par("difName").setStringValue(cloudDIF);

    cGate * modIn, * modOut, * baseIn, * baseOut;

    cloudIPC->setGateSize("southIo", 1);
    modIn = cloudIPC->gateHalf("southIo", cGate::INPUT, 0);
    modOut = cloudIPC->gateHalf("southIo", cGate::OUTPUT, 0);

    baseIPC->setGateSize("northIo", baseIPC->gateSize("northIo")+1);
    baseIn = baseIPC->gateHalf("northIo", cGate::INPUT, baseIPC->gateSize("northIo")-1);
    baseOut = baseIPC->gateHalf("northIo", cGate::OUTPUT, baseIPC->gateSize("northIo")-1);

    baseOut->connectTo(modIn);
    modOut->connectTo(baseIn);

    baseOut->connectTo(modIn);
    modOut->connectTo(baseIn);

    cloudIPC->finalizeParameters();
    cloudIPC->par("routingPolicyName").setStringValue("TDomainRouting");
    cloudIPC->buildInside();

    cloudIPC->getSubmodule(MOD_POL_ROUTING)->par("printAtEnd").setBoolValue(par("printAtEnd").boolValue());

    cModule * modgen, * modfor;

    cloudIPC->getSubmodule(MOD_RESALLOC)->getSubmodule(MOD_PDUFWDGEN)->deleteModule();
    modgen = cModuleType::get("rina.policies.DIF.RA.PDUFG.HierarchicalGenerator.HierarchicalGenerator")
        ->create(MOD_PDUFWDGEN, cloudIPC->getSubmodule(MOD_RESALLOC));

    cloudIPC->getSubmodule(MOD_RELAYANDMUX)->getSubmodule(MOD_POL_RMT_PDUFWD)->deleteModule();
    modfor = cModuleType::get("rina.policies.DIF.RMT.PDUForwarding.HierarchicalTable.HierarchicalTable")
        ->create(MOD_POL_RMT_PDUFWD, cloudIPC->getSubmodule(MOD_RELAYANDMUX));

    modfor->finalizeParameters();
    modgen->finalizeParameters();

    modfor->buildInside();
    modgen->buildInside();

    cloudIPC->scheduleStart(simTime());
    cloudIPC->callInitialize();
}

void Controller::createVifiBIPC_Double(string cloudAddr, string cloudDIF, string backboneAddr, string backboneDIF) {
    imBorder = true;
    this->cloudAddr = cloudAddr;
    this->cloudDIF = cloudDIF;
    this->backboneAddr = backboneAddr;
    this->backboneDIF = backboneDIF;

    string tcloudAPN = cloudAddr;
    tcloudAPN.append("_").append(cloudDIF);
    cloudAPN = APNamingInfo(APN(tcloudAPN.c_str()));

    string tbackboneAPN = cloudAddr;
    tbackboneAPN.append("_").append(cloudDIF);
    backboneAPN = APNamingInfo(APN(tbackboneAPN.c_str()));

    dir->addDirEntry(cloudAPN.getApn());
    dir->addNewDif(cloudAPN.getApn(), Address(substrateAddr));
    dir->addNewDif(cloudAPN.getApn(), Address(backboneAPN.getApn().getName()));

    dir->addDirEntry(backboneAPN.getApn());
    dir->addNewDif(backboneAPN.getApn(), Address(substrateAddr));


    cModule * node = this->getModuleByPath("^.^.^");
    cModuleType* ipcType = cModuleType::get("rina.src.DIF.IPCProcess");

    cGate * modIn, * modOut, * baseIn, * baseOut;
    cModule * modgen, * modfor;

    cModule *backboneIPC = ipcType->create("BackboneIPC", node);
    backboneIPC->par("ipcAddress").setStringValue(backboneAddr);
    backboneIPC->par("difName").setStringValue(backboneDIF);


    backboneIPC->setGateSize("southIo", 1);
    modIn = backboneIPC->gateHalf("southIo", cGate::INPUT, 0);
    modOut = backboneIPC->gateHalf("southIo", cGate::OUTPUT, 0);

    baseIPC->setGateSize("northIo", baseIPC->gateSize("northIo")+1);
    baseIn = baseIPC->gateHalf("northIo", cGate::INPUT, baseIPC->gateSize("northIo")-1);
    baseOut = baseIPC->gateHalf("northIo", cGate::OUTPUT, baseIPC->gateSize("northIo")-1);

    baseOut->connectTo(modIn);
    modOut->connectTo(baseIn);

    backboneIPC->finalizeParameters();
    backboneIPC->par("routingPolicyName").setStringValue("TDomainRouting");
    backboneIPC->buildInside();

    backboneIPC->getSubmodule(MOD_POL_ROUTING)->par("printAtEnd").setBoolValue(par("printAtEnd").boolValue());


    backboneIPC->getSubmodule(MOD_RESALLOC)->getSubmodule(MOD_PDUFWDGEN)->deleteModule();
    modgen = cModuleType::get("rina.policies.DIF.RA.PDUFG.HierarchicalGenerator.HierarchicalGenerator")
        ->create(MOD_PDUFWDGEN, backboneIPC->getSubmodule(MOD_RESALLOC));

    backboneIPC->getSubmodule(MOD_RELAYANDMUX)->getSubmodule(MOD_POL_RMT_PDUFWD)->deleteModule();
    modfor = cModuleType::get("rina.policies.DIF.RMT.PDUForwarding.HierarchicalTable.HierarchicalTable")
        ->create(MOD_POL_RMT_PDUFWD, backboneIPC->getSubmodule(MOD_RELAYANDMUX));

    modfor->finalizeParameters();
    modgen->finalizeParameters();

    modfor->buildInside();
    modgen->buildInside();

    backboneIPC->scheduleStart(simTime());
    backboneIPC->callInitialize();

    cModule *cloudIPC = ipcType->create("CloudIPC", node);
    cloudIPC->par("ipcAddress").setStringValue(cloudAddr);
    cloudIPC->par("difName").setStringValue(cloudDIF);

    cloudIPC->setGateSize("southIo", 2);
    modIn = cloudIPC->gateHalf("southIo", cGate::INPUT, 0);
    modOut = cloudIPC->gateHalf("southIo", cGate::OUTPUT, 0);

    backboneIPC->setGateSize("northIo", 1);
    baseIn = backboneIPC->gateHalf("northIo", cGate::INPUT, 0);
    baseOut = backboneIPC->gateHalf("northIo", cGate::OUTPUT, 0);

    baseOut->connectTo(modIn);
    modOut->connectTo(baseIn);

    modIn = cloudIPC->gateHalf("southIo", cGate::INPUT, 1);
    modOut = cloudIPC->gateHalf("southIo", cGate::OUTPUT, 1);

    baseIPC->setGateSize("northIo", baseIPC->gateSize("northIo")+1);
    baseIn = baseIPC->gateHalf("northIo", cGate::INPUT, baseIPC->gateSize("northIo")-1);
    baseOut = baseIPC->gateHalf("northIo", cGate::OUTPUT, baseIPC->gateSize("northIo")-1);

    baseOut->connectTo(modIn);
    modOut->connectTo(baseIn);


    cloudIPC->finalizeParameters();
    cloudIPC->par("routingPolicyName").setStringValue("TDomainRouting");
    cloudIPC->buildInside();

    cloudIPC->getSubmodule(MOD_POL_ROUTING)->par("printAtEnd").setBoolValue(par("printAtEnd").boolValue());


    cloudIPC->getSubmodule(MOD_RESALLOC)->getSubmodule(MOD_PDUFWDGEN)->deleteModule();
    modgen = cModuleType::get("rina.policies.DIF.RA.PDUFG.HierarchicalGenerator.HierarchicalGenerator")
        ->create(MOD_PDUFWDGEN, cloudIPC->getSubmodule(MOD_RESALLOC));

    cloudIPC->getSubmodule(MOD_RELAYANDMUX)->getSubmodule(MOD_POL_RMT_PDUFWD)->deleteModule();
    modfor = cModuleType::get("rina.policies.DIF.RMT.PDUForwarding.HierarchicalTable.HierarchicalTable")
        ->create(MOD_POL_RMT_PDUFWD, cloudIPC->getSubmodule(MOD_RELAYANDMUX));

    modfor->finalizeParameters();
    modgen->finalizeParameters();

    modfor->buildInside();
    modgen->buildInside();

    cloudIPC->scheduleStart(simTime());
    cloudIPC->callInitialize();
}

void Controller::addedFlow(Flow*) {
    // ******** do something
}
void Controller::removedFlow(Flow*) {
    // ******** do something
}

}
