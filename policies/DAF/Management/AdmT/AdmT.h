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

using namespace std;

#include "AdminMsgs.h"


class AdmT : public AE
{
protected:

    const char* TIM_CONNECT;
    const char* TIM_STARTFLOWS;
    const char* TIM_HELLO;

    const char* PAR_DSTAPNAME;
    const char* PAR_DSTAPINSTANCE;
    const char* PAR_DSTAENAME;
    const char* PAR_DSTAEINSTANCE;

    std::string dstApName;
    std::string dstApInstance;
    std::string dstAeName;
    std::string dstAeInstance;

    DA * DifAllocator;

    map<string, Flow *> reqFlows;

    virtual void initialize();
    virtual void handleMessage(cMessage *msg);


    void onConnect();
    void onSFlows();
    void onSayHello();

    void allocateFlows(string dif, string src, vector<string> dstVec);

    void deallocateFlows(string dif, string src, vector<string> dstVec);

    void processMRead(CDAPMessage* msg);
    void processMReadR(CDAPMessage* msg);



    virtual void action(cMessage *msg, bool del);

public:
    AdmT();
};
