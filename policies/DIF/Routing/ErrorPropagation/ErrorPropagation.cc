#include "ErrorPropagation.h"

ErrorPropagationMsg::ErrorPropagationMsg(bool st, string lk, double t):
    status(st), link(lk), timestamp(t) {}

ChangeMsg::ChangeMsg(string lk):
        link(lk) {}

bool ErrorPropagation::processUpdate(IntRoutingUpdate * update){
    ErrorPropagationMsg * up = dynamic_cast<ErrorPropagationMsg * >(update);
    string & l = up->link;
    bool st = up->status;
    double t = up->timestamp;

    bool sendUpdate = false;
    bool informChange = false;

    //Not one of my links!!
    if(linksStatus.find(l) == linksStatus.end()) {
        //currently Off?
        if(updateTime.find(l) == updateTime.end()) { return false; }
        double cT = updateTime[l];

        //Old update
        if(cT >= t) { return false; }
        updateTime[l] = t;
        sendUpdate = true;

        if(st){ // Now ON
            //Change Off->On
            if(downLinks.find(l) != downLinks.end()) {
                informChange = true;
                downLinks.erase(l);
                upLinks.insert(l);
            }
        } else {
            //Change On->Off
            if(upLinks.find(l) != upLinks.end()) {
                informChange = true;
                upLinks.erase(l);
                downLinks.insert(l);
            }
        }
    }

    if(sendUpdate) {
        scheduleAt(simTime()+propagateDelay, new ChangeMsg(l));
    }

    return informChange;
}

void ErrorPropagation::onFlow(const Address &addr, string flowName) {}

void ErrorPropagation::offFlow(const Address &addr, string flowName){}

void ErrorPropagation::handleMessage(cMessage * msg){}

void ErrorPropagation::onPolicyInit(){}
