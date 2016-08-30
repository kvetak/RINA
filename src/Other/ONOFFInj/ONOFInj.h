#pragma once

#include "OFClasses.h"

#include <omnetpp.h>
#include <queue>
#include <memory>

#include <ConnectionId.h>
#include <Address.h>
#include <RMTPort.h>

#include "ONOFInj.h"
#include "OFMessages.h"
#include "MultipathStructs.h"

using namespace MultipathStructs;
using namespace std;

class ONOFInj : public cSimpleModule {
public :
    //Receive data from other node
    void receiveData(const string & _src, const string & _qos, shared_ptr<Inj_data> data);

    //Generate PDU
    Inj_PDU * genPDU(const pduReq & req);

    //N-1 ports
    void setPort(const string & dst, const string & qos, RMTPort * p) { ports[dst][qos] = p; }
    bool portReady(string dst, string qos) {
        RMTPort * p = ports[dst][qos];
        return (p != nullptr && p->isOutputReady());
    }
    map<string, map<string, RMTPort * > > ports;

    //PDU header
    int header;

    //Infection end time
    double fin;

    //Start flows timer
    cMessage iniFlows;

    //Node info
    string src, dif;
    ConnectionId connID;
    Address srcAddr, dstAddr;

    //Id for next created flow
    //int nextFlowId;

    //Flows
    map<int, sender_t *> senders;
    map<string, map<int, client_t *> > clients;
    map<string, map<int, server_t *> > servers;

    //stats
    long long received, sent;

    long long sentAct, sentRet, sentSRt, sentActk;

    virtual void initialize();
    virtual void handleMessage(cMessage *msg);
    void finish();

    void startFlows();

    server_t * createServer(string dst, string qos, int flow);
};
/*
    ;


    int nextFlowId;
    map<int, voiceOF *> vFlows;
    map<string, map<int, clientOF *> > cFlows;
    map<string, map<int, serverOF *> > sFlows;




    void actVoice(actTimer * m, voiceOF * f);
    void actClient(actTimer * m, clientOF * f);
    void actServer(actTimer * m, serverOF * f);

    void retClient(retransTimer * m, clientOF * f);
    void retServer(retransTimer * m, serverOF * f);

    void selRetServer(selretransTimer * m, serverOF * f);

    void rackClient(ackTimer * m, clientOF * f);
    void rackServer(ackTimer * m, serverOF * f);
};
*/
