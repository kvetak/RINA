#pragma once

#include <omnetpp.h>
#include <queue>
#include <ConnectionId.h>
#include <Address.h>

using namespace std;

struct OF_Flow {
    double interPDU;
    int pduSize;
    int flowId;
    int secN;
    long remaining;

    OF_Flow(int _flowId) : flowId(_flowId) {};

    void set(double R, int _pduSize, long _remaining) {
        pduSize = _pduSize;
        secN = 0;
        remaining = _remaining;
        interPDU = _pduSize / R;
    }
};

struct OF_FlowSet {
    vector<OF_Flow>  flows;
    int method;

    string dst;
    string QoS;
    int N, cN;
    double minR, maxR;
    double minD, maxD;
    double minW, maxW;
    int pduMin, pduMax;

    OF_FlowSet(){}

    OF_FlowSet(int & flowId, int _method, string _dst, string _QoS, int _N, double R, double D, double K, int _pduMin, int _pduMax) :
        method(_method), dst(_dst), QoS(_QoS), pduMin(_pduMin), pduMax(_pduMax) {
        minR = R*(1.0-K);
        maxR = R*(1.0+K);
        minD = D*(1.0-K);
        maxD = D*(1.0+K);
        double W = D/_N;
        minW = W*(1.0-K);
        maxW = W*(1.0+K);

        N = 1 + 2*(int) ceil(maxD/minW);
        cN = N;

        for(int i = 0; i < N; i++) {
            flows.push_back(OF_Flow(flowId++));
        }
    }

    double startNext() {
        cN++;
        if(cN >= N) { cN = 0; }

        OF_Flow & f = flows[cN];
        double fR;
        int fPduSize;
        long fRemaining;
        double W;

        switch (method) {
            case 0:
            default:
                fR = uniform( minR, maxR);
                fPduSize = intuniform(pduMin, pduMax);
                fRemaining = (long) (uniform(minD, maxD)*fR);
                W = uniform(minW, maxW);
                break;
        }

        f.set(fR, fPduSize, fRemaining);

        return W;
    }

};

class OF_FlowNext_Msg : public cMessage {
public:
    int fset;
    OF_FlowNext_Msg(int _fset) : cMessage ("OF : Start Flow"), fset(_fset) {}
};
class OF_PDUNext_Msg : public cMessage {
public:
    int fset, findex;
    OF_PDUNext_Msg(int _fset, int _findex) : cMessage ("OF : Send PDU"), fset(_fset), findex(_findex) {}
};
class OF_IRed : public cMessage {
public:
    OF_IRed() : cMessage ("OF : InfReady") {}
};

class MlONOFInj : public cSimpleModule {
  protected:
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);

    simsignal_t signal;

    double fin;
    vector<OF_FlowSet> flowSets;

    string src, dif;
    ConnectionId connID;
    Address srcAddr, dstAddr;

    queue<cPacket*> q;

    int maxSimult, curSimult;
    double wPerBit;

};
