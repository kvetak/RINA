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



#include <QoSMultipathMonitor.h>




namespace QoSMultipathMonitor_Simple {



using namespace std;

using namespace QoSMultipathMonitor;

using namespace MultipathStructs;


class QoSMultipathMonitor_Simple: public iQoSMultipathMonitor {



public:

    vector<RMTPort * > lookup(const PDU * pdu);

    vector<RMTPort * > lookup(const Address &dst, const string& qos);

    Routingtable* getRoutingTable();
    SchedulerInfo* getSchedulerInfo();
    void setFlow(cEntry entry);
    void removeFlow(cEntry entry);


    string toString();



    void finish();



    void addReplace(const string &addr, vector<entryT> ports);



protected:

    unsigned short counter;

    cMessage * timeOutMsg = new cMessage("Clean Forwarding Cache");

    cMessage * recalcWeightMsg = new cMessage("Recalcule Weights");



    map<string, map<int, cEntry>> cache; //map<dst, map<flowidentifier(SrcCepId), entry>>

    map<RMTPort *, WeightInfo> weights; //map<qos, map<port, weight>>

    map<int, int> translateId; //map<flowid, flowidreal>

    BWcontrol BWControl;

    double cleanCache_t;

    double recalcule_t;

    orderedList orderedCache;



    //map<string, vector<entryT> > table;
    Routingtable table;

    RMTPort * portLookup(const string& dst, const string& qos);

    void onMainPolicyInit();

    void onSetPort(RMTPort * p, const int bw);

    void preReplacePort(RMTPort * oldP, RMTPort * newP, const int bw);





    void handleMessage(cMessage * msg);
    void recalcule();
    //vector<cEntry> OrganiceFlows(map<string, map<int, cEntry>> &flows);

};



}

