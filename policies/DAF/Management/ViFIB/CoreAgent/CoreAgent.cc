#include "CoreAgent.h"

#include <string>
#include <list>
#include "Utils.h"
#include "RINASignals.h"

using namespace std;

namespace ViFIB {

Define_Module(CoreAgent);

CoreAgent::CoreAgent() {}

void CoreAgent::initialize() {
    clientId = "";

    cModule * Node = this->getModuleByPath("^.^.^");

    //Init pointers
    initPointers();
    //Source info
    initNamingInfo();
    //Setup signals
    initSignalsAndListeners();
    //Init QoSRequirements
    initQoSRequiremets();

    sig2master = registerSignal(SIG_VAR_ViFIB_Slave2Master);
    Node->subscribe(SIG_VAR_ViFIB_Master2Slave, this);
}

void CoreAgent::receiveSignal(cComponent *src, simsignal_t id, cObject *obj){
    if(_masterMessage * msg = dynamic_cast<_masterMessage*>(obj)){
        if(msg->zoneId == clientId){
            sendData(FlowObject, msg);
        }
    }
}

void CoreAgent::handleMessage(cMessage *msg) { action(msg, true); }
void CoreAgent::processMRead(CDAPMessage* msg) { action(msg, false); }
void CoreAgent::processMReadR(CDAPMessage* msg) { action(msg, false); }


void CoreAgent::action(cMessage *msg, bool del) {
    if(msg->isSelfMessage()){
        //????
    } else {
        if(masterHello * m = dynamic_cast<masterHello*>(msg)){
            clientId = m->zoneId;
            emit(sig2master, m);
            del = false;
        } else if(masterNewBorder * m = dynamic_cast<masterNewBorder*>(msg)){
            emit(sig2master, m);
        }
    }

    if(del) { delete msg; }
}

}
