#include "ManagementAgent.h"

#include <string>
#include <list>
#include "Utils.h"
#include "RINASignals.h"

using namespace std;

namespace ViFIB {

Define_Module(ManagementAgent);

ManagementAgent::ManagementAgent() {}

void ManagementAgent::initialize() {
    clientId = "";

    cModule * Node = this->getParentModule()->getParentModule()->getParentModule();

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

void ManagementAgent::receiveSignal(cComponent *src, simsignal_t id, cObject *obj){
    if(_vifibMessage * msg = dynamic_cast<_vifibMessage*>(obj)){
        if(msg->VifibId == clientId){
            sendData(FlowObject, msg);
        }
    }
}

void ManagementAgent::handleMessage(cMessage *msg) { action(msg, true); }
void ManagementAgent::processMRead(CDAPMessage* msg) { action(msg, false); }
void ManagementAgent::processMReadR(CDAPMessage* msg) { action(msg, false); }


void ManagementAgent::action(cMessage *msg, bool del) {
    if(vifibHello * m = dynamic_cast<vifibHello*>(msg)){
        clientId = m->VifibId;
        emit(sig2master, m);
        del = false;
    }
    if(del) { delete msg; }
}

}
