#include "Core.h"

#include <string>
#include <list>
#include "Utils.h"
#include "RINASignals.h"

using namespace std;

namespace ViFIB {

Define_Module(Core);


Core::Core() {}

void Core::initialize() {
    cModule * Node = this->getParentModule()->getParentModule()->getParentModule();


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

    sig2slaves = registerSignal(SIG_VAR_ViFIB_Master2Slave);
    Node->subscribe(SIG_VAR_ViFIB_Slave2Master, this);
}

void Core::handleMessage(cMessage *msg) { action(msg, true); }
void Core::processMRead(CDAPMessage* msg) { action(msg, false); }
void Core::processMReadR(CDAPMessage* msg) { action(msg, false); }

void Core::receiveSignal(cComponent *src, simsignal_t id, cObject *obj){
    if(cMessage * m = dynamic_cast<cMessage*>(obj)){ action(m, false); }
}

void Core::action(cMessage *msg, bool del) {
    if(msg->isSelfMessage()){
        // ************* do something
    }

    if(del) { delete msg; }
}

}
