#pragma once

//Standard libraries
#include <omnetpp.h>

#include <string>
#include <map>

//RINASim libraries
#include "AE.h"
#include "RA.h"
#include "FA.h"
#include "DA.h"
#include "Directory.h"
#include "ViFIB/Graph.h"

using namespace std;

#include "ViFIB/Messages.h"

namespace ViFIB {

class Management : public AE, public cListener
{
protected:
    simsignal_t sig2slaves;

    const char* TIM_CONNECT;
    const char* TIM_STARTFLOWS;
    const char* TIM_HELLO;

    const char* PAR_DSTAPNAME;
    const char* PAR_DSTAPINSTANCE;
    const char* PAR_DSTAENAME;
    const char* PAR_DSTAEINSTANCE;

    const char* WAKE_UP;
    const char* ADD_UPDATE;
    const char* REMOVE_UPDATE;

    std::string dstApName;
    std::string dstApInstance;
    std::string dstAeName;
    std::string dstAeInstance;

    DA * DifAllocator;
    cModule * baseIPC;

    bool waiting;
    string zoneId;
    int maxBorders;
    int maxDiameter;
    int currentNodes, currentBorders;

    map<string, vifibInfo> clientsInfo;
    map<int, string> cAddr2Id;
    map<int, string> bAddr2Id;

    map<string, vector<miniInfo> > extBorders;

    map<string, vector<miniInfo> > bordersConnections;

    Graph<unsigned short> g;


    virtual void initialize();

    void onConnect();

    virtual void handleMessage(cMessage *msg);
    void processMRead(CDAPMessage* msg);
    void processMReadR(CDAPMessage* msg);

    virtual void receiveSignal(cComponent *src, simsignal_t id, cObject *obj);

    virtual void action(cMessage *msg, bool del);


    void improveNet(vector< Graph<unsigned short>::LinkAB > & newLinks);
    void propagate(vector< Graph<unsigned short>::LinkAB > & newLinks);

public:
    Management();
};

}
