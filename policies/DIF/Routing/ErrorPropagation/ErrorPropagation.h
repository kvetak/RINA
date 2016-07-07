#pragma once

#include <IntRouting.h>

#include <map>

using namespace std;


class ErrorPropagationMsg : public IntRoutingUpdate {
public:
    ErrorPropagationMsg(bool st, string lk, double t);

    bool status;
    string link;
    double timestamp;
};

class ChangeMsg : public cMessage {
public:
    ChangeMsg(string l);
    string link;
};

class ErrorPropagation: public IntRouting {
public:
    //Process a Routing Update, return true => inform FWDG of the update
    virtual bool processUpdate(IntRoutingUpdate * update) = 0;

    //Flow inserted/removed
    void onFlow(const Address &addr, string flowName);
    void offFlow(const Address &addr, string flowName);

protected:
    void handleMessage(cMessage * msg);
    void onPolicyInit();

    double timeout, refreshTime, propagateDelay;
    map<string, bool> linksStatus;
    set<string> downLinks, upLinks;
    map<string, double> linkTime, updateTime;

};
