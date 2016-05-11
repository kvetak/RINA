#include <map>
#include <string>
#include <vector>

#include "RMTPort.h"



namespace MultipathStructs {

using namespace std;


struct entryT {
    RMTPort * p;
    int BW;
    entryT(){
        p = nullptr;
        BW = 0;
    }
    entryT(RMTPort * _p, int _bw){
        p = _p;
        BW = _bw;
    }
};

struct cEntry {

    RMTPort * p;

    int reqBW;

    string QoS;

    simtime_t t;

    string dst;

    int SrcCepId;

    cEntry() {

        p = nullptr;

        reqBW = 0;

        t = 0;

        QoS = "null";

        dst = "null";

        SrcCepId = 0;

    }

};

struct UsedBW {

    int bw;

    UsedBW() {

        bw = 0;

    }

};

typedef map<string, UsedBW> BWport; //map<QoSid, UsedBW>;

typedef map<RMTPort *, BWport> BWinfo; //map<port, BWport>;

struct BWcontrol {

    BWinfo BW;

    long getTotalBW(RMTPort * port) {

        long total = 0;

        for (auto it : BW[port]) {

            total += it.second.bw;

        }

        return total;

    }

    int getBWbyQoS(RMTPort * port, string QoS) {

        return BW[port][QoS].bw;

    }

    void addBW(RMTPort * port, string QoS, int bw) {

        BW[port][QoS].bw += bw;

    }

    void removeBW(RMTPort * port, string QoS, int bw) {

        BW[port][QoS].bw -= bw;

    }

    void removePort(RMTPort * port) {

        BW.erase(port);

    }

};

struct Movement {

    RMTPort * org; //Origin port of the flow

    RMTPort * dst; //Destination port of the flow

    int flow;

    int reqBW;

    string qos;

    Movement(RMTPort * Org, RMTPort * Dst, int Flow, int ReqBW, string QoS) {

        org = Org;

        dst = Dst;

        flow = Flow;

        reqBW = ReqBW;

        qos = QoS;

    }

};

struct RerouteInfo {

    vector<Movement> movements;

    map<RMTPort *, int> ports; //map<port, BW>

    void addMov(RMTPort * org, RMTPort * dst, int flow, int reqBW, string qos) {

        Movement mov(org, dst, flow, reqBW, qos);

        movements.push_back(mov);

    }

    RerouteInfo();

    RerouteInfo(vector<entryT> Ports) {

        for (auto it : Ports) {

            ports[it.p] = it.BW;

        }

    }

};

struct orderedList {

    list<cEntry*> List;

    void addElement(cEntry* entry) {

        if (List.empty()) {

            List.push_front(entry);

        }

        else {

            for (list<cEntry*>::iterator it = List.begin(); it != List.end();
                    it++) {

                if (entry->reqBW >= (*it)->reqBW) {

                    List.insert(it, entry);

                    break;

                }

            }

            List.push_back(entry);

        }

    }

    void erraseElement(cEntry* entry) {

        for (list<cEntry*>::iterator it = List.begin(); it != List.end();
                it++) {

            if (entry == (*it)) {

                List.erase(it);

            }

        }

    }

};

typedef map<string, vector<entryT> > Routingtable;
typedef map<string, map<RMTPort *, double>> SchedulerInfo;
typedef map<RMTPort *, string> NeighboursInfo;

struct RegisterInfo{

    string nodeId;
    Routingtable routingInfo;
    SchedulerInfo schedulerInfo;
    NeighboursInfo neighboursInfo;
    string nodePath;

    RegisterInfo(){
        nodeId ="";
        nodePath = "";
    }

};

struct Rsv_ReqInfo{
    string nodeIdOrg;
    string nodeIdDst;
    string qos;
    int flowId;

    Rsv_ReqInfo(){
            nodeIdOrg ="";
            nodeIdDst = "";
            qos = "";
            flowId = -1;
        }
};

struct RsvInfo{
    cEntry entry;
};

struct AckInfo{
    int flowID;

    AckInfo(){
        flowID = -1;
    }
};

struct MonConfigInfo{
    double SchedulerMonFrec;
    double ForwardingMonFrec;
    double LinksMonFrec;
    double SchedulerMonThres;

    MonConfigInfo(){
        SchedulerMonFrec = 0;
        ForwardingMonFrec = 0;
        LinksMonFrec = 0;
        SchedulerMonThres = 0.0;
    }
};

struct MonitorParamInfo{
    string nodeId;
    Routingtable* routingInfo;
    SchedulerInfo* schedulerInfo;
    NeighboursInfo* neighboursInfo;
    MonitorParamInfo(){
        nodeId ="";
        routingInfo = nullptr;
        schedulerInfo = nullptr;
        neighboursInfo = nullptr;
    }
};


class MonitorMsg : public cMessage {
public:
    string type;
    RegisterInfo regInfo;
    Rsv_ReqInfo rsv_ReqInfo;
    RsvInfo rsvInfo;
    AckInfo ackInfo;
    MonConfigInfo monConfigInfo;
    MonitorParamInfo monitorParamInfo;
};

}
