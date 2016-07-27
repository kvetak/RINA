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


class FailureTest : public cSimpleModule {
public:
    void initialize();
    void finish();
    void handleMessage(cMessage * msg);


    static FailureTest * instance;

    void registerLink(const string & link, FailureNode * owner);

protected:
    set<string> dead, alive;
    map<string, vector<FailureNode *> > link2Nodes;

    cMessage * killTimer, * resurrectTimer;
    unsigned int c;

};

