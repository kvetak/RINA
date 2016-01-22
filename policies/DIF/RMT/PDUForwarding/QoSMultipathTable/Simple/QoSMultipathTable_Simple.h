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

#include <QoSMultipathTable.h>

namespace QoSMultipathTable_Simple {

using namespace std;
using namespace QoSMultipathTable;

struct cEntry {
    RMTPort * p;
    int reqBW;
    simtime_t t;
    cEntry();
};

struct UsedBW {
    int bw;
    UsedBW(){
        bw=0;
    }
};

struct Movement {
    RMTPort * org; //Origin port of the flow
    RMTPort * dst; //Destination port of the flow
    int flow;
    int reqBW;
    Movement(RMTPort * Org, RMTPort * Dst, int Flow, int ReqBW){
        org = Org;
        dst = Dst;
        flow = Flow;
        reqBW = ReqBW;
    }
};

struct RerouteInfo{
    vector<Movement> movements;
    map<RMTPort *, int> ports; //map<port, BW>

    void addMov(RMTPort * org, RMTPort * dst, int flow, int reqBW){
       Movement mov(org, dst, flow, reqBW);
       movements.push_back(mov);
    }

    RerouteInfo();
    RerouteInfo(vector<entryT> Ports){
        for (auto it : Ports){
            ports[it.p]=it.BW;
        }
    }
};
class QoSMultipathTable_Simple: public iQoSMultipathTable {

public:
    vector<RMTPort * > lookup(const PDU * pdu);
    vector<RMTPort * > lookup(const Address &dst, const string& qos);

    string toString();

    void finish();

    void addReplace(const string &addr, vector<entryT> ports);

protected:
    map<string, map<int, cEntry>> cache;
    map<RMTPort *, UsedBW> BWControl; //map<port, UsedBW>;
    double cleanCache_t;

    map<string, vector<entryT> > table;

    void onMainPolicyInit();
    void onSetPort(RMTPort * p, const int bw);
    void preReplacePort(RMTPort * oldP, RMTPort * newP, const int bw);

    void handleMessage(cMessage * msg);

    RMTPort * portLookup(const string& dst, const string& qos);
    RMTPort * rerouteFlows(const vector<entryT>& ports, const string& dst, const int& bw);
    static bool compareDecresing(const entryT &i, const entryT &j);
    static bool compareAscending(const entryT &i, const entryT &j);
    void AplyReroute(const RerouteInfo &info, const string& dst);
    bool isBetterPort(const entryT * port1, const entryT * port2);
};

}
