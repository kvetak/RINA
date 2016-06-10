#include "Agent.h"

#include "FAI.h"
#include "otMessages.h"
#include "sRA.h"

Define_Module(Agent);

Agent::Agent() {}

void Agent::initialize() {
    Enter_Method_Silent();
    EV << "Holas"<<endl;
    EV << "Listening signal agentRequest at :"<< this->getParentModule()->getFullPath()<<endl;
    this->getParentModule()->subscribe("agentRequest", this);

    EV << "I'm "<<this->getParentModule()->par("ipcAddress").stdstringValue()<<endl;
    helloMsg * m = new helloMsg(this->getParentModule()->par("ipcAddress").stdstringValue(), this);
    send(m, "maIo$o");
}

void Agent::receiveSignal(cComponent *source, simsignal_t signalID, cObject *obj) {
    Enter_Method_Silent();
    EV << "Received Signal!!" << endl;

    FAI * fai = dynamic_cast<FAI *>(obj);
    if(fai != nullptr) {
        Flow * f = fai->getFlow();
        flowsFais[f] = fai;

        EV << "Flow from "<< f->getSrcAddr() << " to "<< f->getDstAddr()<<endl;
        requestMsg * m = new requestMsg(this, f);
        send(m, "maIo$o");
    }
}

void Agent::handleMessage(cMessage *m) {
    EV << "Received Message!!" << endl;
    if(responseMsg * msg = dynamic_cast<responseMsg*>(m)) {
        std::string src = msg->f->getSrcAddr().getIpcAddress().getName();
        std::string dst = msg->f->getDstAddr().getIpcAddress().getName();
        EV << "New Flow allocated from "<< src <<"  to " << dst<< " At index "<< msg->gateIndex <<endl;


        getRINAModule<sRA*>(this, 1, {MOD_RESALLOC, MOD_RA})->AddNM1Flow(msg->f, msg->gateIndex);

        if(msg->f->getSrcAddr().getIpcAddress().getName() == this->getParentModule()->par("ipcAddress").stdstringValue()) {
            EV << "I'm source"<<endl;
            flowsFais[msg->f]->receiveAllocateRequest();
        }
    }
    delete m;
}
