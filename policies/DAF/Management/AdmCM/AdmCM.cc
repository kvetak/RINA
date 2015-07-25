#include "AdmCM.h"

Define_Module(AdmCM);

#include <string>
#include <list>
#include "Utils.h"

#include "RA.h"
#include "AdminMsgs.h"

using namespace std;

void AdmCM::initialize(){
    AdmT::initialize();

    sig = registerSignal("LISTENER_MASTER");
    this->getParentModule()->getParentModule()->getParentModule()->subscribe("LISTENER_SLAVE", this);
}

void AdmCM::action(cMessage *msg, bool del) {
    if(msg->isSelfMessage()){
        if ( !strcmp(msg->getName(), TIM_CONNECT) ) {
            onConnect();
        } else if ( !strcmp(msg->getName(), TIM_STARTFLOWS) ) {
            onSFlows();
        } else if ( !strcmp(msg->getName(), TIM_HELLO) ) {
            onSayHello();
        }
    } else {
        if(HelloMsg * m = dynamic_cast<HelloMsg*>(msg)){
            src = m->src;
            dif = m->dif;
            emit(sig, m);
        } else if(reqFlowMsg * m = dynamic_cast<reqFlowMsg*>(msg)){
            if(m->src == src && m->dif == dif) {
                sendData(FlowObject, m);
            } else if(m->src == par("src").stdstringValue() && m->dif == par("DIF").stdstringValue()) {
                allocateFlows(m->dif, par("src").stdstringValue(), m->flowsDstAppName);
            }
        } else if(reqDelFlowMsg * m = dynamic_cast<reqDelFlowMsg*>(msg)){
            if(m->src == src && m->dif == dif) {
                sendData(FlowObject, m);
            } else if(m->src == par("src").stdstringValue() && m->dif == par("DIF").stdstringValue()) {
                deallocateFlows(m->dif, par("src").stdstringValue(), m->flowsDstAppName);
            }
        }
    }
    if(del) { delete msg; }
}

void AdmCM::receiveSignal(cComponent *_src, simsignal_t id, cObject *obj) {
    if(reqFlowMsg * m = dynamic_cast<reqFlowMsg*>(obj)){
        if(m->src == src && m->dif == dif) {
            sendData(FlowObject, m);
        } else if(m->src == par("src").stdstringValue() && m->dif == par("DIF").stdstringValue()) {
            allocateFlows(m->dif, par("src").stdstringValue(), m->flowsDstAppName);
        }
    } else if(reqDelFlowMsg * m = dynamic_cast<reqDelFlowMsg*>(obj)){
        if(m->src == src && m->dif == dif) {
            sendData(FlowObject, m);
        } else if(m->src == par("src").stdstringValue() && m->dif == par("DIF").stdstringValue()) {
            deallocateFlows(m->dif, par("src").stdstringValue(), m->flowsDstAppName);
        }
    }

}
