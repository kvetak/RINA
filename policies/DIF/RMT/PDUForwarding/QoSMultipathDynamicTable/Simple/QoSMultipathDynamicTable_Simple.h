// The MIT License (MIT)

//

// Copyright (c) 2014-2016 Brno University of Technology, PRISTINE project

//

// Permission is hereby granted, free of charge, to any person obtaining a copy

// of this software and associated documentation files (the "Software"), to deal

// in the Software without restriction, including without limitation the rights

// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell

// copies of the Software, and to permit persons to whom the Software is

// furnished to do so, subject to the following conditions:

//

// The above copyright notice and this permission notice shall be included in

// all copies or substantial portions of the Software.

//

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR

// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,

// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE

// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER

// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,

// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN

// THE SOFTWARE.



#pragma once



#include <QoSMultipathDynamicTable.h>



namespace QoSMultipathDynamicTable_Simple {



using namespace std;

using namespace QoSMultipathDynamicTable;



struct cEntry {

    RMTPort * p;

    int reqBW;

    string QoS;

    simtime_t t;

    string dst;

    int SrcCepId;

    cEntry(){

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

    UsedBW(){

        bw=0;

    }

};



typedef map<string, UsedBW> BWport; //map<QoSid, UsedBW>;

typedef map<RMTPort *, BWport> BWinfo; //map<port, BWport>;



struct BWcontrol {

    BWinfo BW;

    long getTotalBW(RMTPort * port){

        long total=0;

        for(auto it : BW[port]){

            total += it.second.bw;

        }

        return total;

    }

    int getBWbyQoS(RMTPort * port, string QoS){

        return BW[port][QoS].bw;

    }

    void addBW (RMTPort * port, string QoS, int bw){

        BW[port][QoS].bw+=bw;

    }

    void removeBW (RMTPort * port, string QoS, int bw){

        BW[port][QoS].bw-=bw;

    }

    void removePort (RMTPort * port){

        BW.erase(port);

    }

};



struct Movement {

    RMTPort * org; //Origin port of the flow

    RMTPort * dst; //Destination port of the flow

    int flow;

    int reqBW;

    string qos;

    Movement(RMTPort * Org, RMTPort * Dst, int Flow, int ReqBW, string QoS){

        org = Org;

        dst = Dst;

        flow = Flow;

        reqBW = ReqBW;

        qos = QoS;

    }

};



struct RerouteInfo{

    vector<Movement> movements;

    map<RMTPort *, int> ports; //map<port, BW>



    void addMov(RMTPort * org, RMTPort * dst, int flow, int reqBW, string qos){

       Movement mov(org, dst, flow, reqBW, qos);

       movements.push_back(mov);

    }



    RerouteInfo();

    RerouteInfo(vector<entryT> Ports){

        for (auto it : Ports){

            ports[it.p]=it.BW;

        }

    }

};



struct orderedList{

    list<cEntry*> List;

    void addElement (cEntry* entry){

        if (List.empty()){

            List.push_front(entry);

        }

        else{

            for(list<cEntry*>::iterator it=List.begin(); it!=List.end(); it++){

                if(entry->reqBW >= (*it)->reqBW){

                    List.insert(it, entry);

                    break;

                }

            }

            List.push_back(entry);

        }

    }

    void erraseElement (cEntry* entry){

        for(list<cEntry*>::iterator it=List.begin(); it!=List.end(); it++){

            if(entry == (*it)){

                List.erase(it);

            }

        }

    }

};

class QoSMultipathDynamicTable_Simple: public iQoSMultipathDynamicTable {



public:

    vector<RMTPort * > lookup(const PDU * pdu);

    vector<RMTPort * > lookup(const Address &dst, const string& qos);



    string toString();



    void finish();



    void addReplace(const string &addr, vector<entryT> ports);



protected:

    //unsigned short counter;

    cMessage * timeOutMsg = new cMessage("Clean Forwarding Cache");

    cMessage * recalcWeightMsg = new cMessage("Recalcule Weights");



    map<string, map<int, cEntry>> cache; //map<dst, map<flowidentifier(SrcCepId), entry>>

    map<RMTPort *, double> weights; //map<port, usage>

    BWcontrol BWControl;

    double cleanCache_t;

    double recalcule_t;

    orderedList orderedCache;



    map<string, vector<entryT> > table;
    map<int, simtime_t> dropedFlows; //map<flowId, time>



    void onMainPolicyInit();

    void onSetPort(RMTPort * p, const int bw);

    void preReplacePort(RMTPort * oldP, RMTPort * newP, const int bw);



    void handleMessage(cMessage * msg);



    RMTPort * portLookup(const string& dst, const string& qos);

    RMTPort * rerouteFlows(const vector<entryT>& ports, const string& dst, const int& bw, const string& qos);

    static bool compareDecresing(const entryT &i, const entryT &j);

    static bool compareAscending(const entryT &i, const entryT &j);

    void AplyReroute(const RerouteInfo &info, const string& dst);

    bool isBetterPort(const entryT * port1, const entryT * port2, const string& qos);

    bool isBetterPort(const entryT * port1, const entryT * port2);

    //vector<cEntry> OrganiceFlows(map<string, map<int, cEntry>> &flows);

    bool SameNextHop(string dst1, string dst2);

    unsigned int WeightedRandom(vector<entryT> &possibles, vector<double> &weights);

    void recalcule();

};



}

