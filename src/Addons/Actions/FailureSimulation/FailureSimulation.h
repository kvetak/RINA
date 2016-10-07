#pragma once

#include <omnetpp.h>

#include <set>
#include <map>
#include <vector>

using namespace std;

class FailureNode {
public:
    virtual void killLink(const string & link) = 0;
    virtual void resurrectLink(const string &  link) = 0;
};


class FailureSimulation : public cSimpleModule {
public:
    void initialize();
    void finish();
    void handleMessage(cMessage * msg);


    static FailureSimulation * instance;

    void registerLink(const string & link, FailureNode * owner);

protected:
    set<string> dead, alive;
    map<string, vector<FailureNode *> > link2Nodes;

    cMessage * killTimer, * resurrectTimer;
    simtime_t interKill;
    unsigned int c;

};

