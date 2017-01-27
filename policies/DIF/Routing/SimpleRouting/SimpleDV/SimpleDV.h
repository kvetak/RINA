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

#ifndef SimpleDV_H_
#define SimpleDV_H_

#include "DIF/Routing/SimpleRouting/IntSimpleRouting.h"

namespace SimpleDV {

struct rtEntry {
    std::string addr;
    unsigned short metric;
    rtEntry(){
        addr = "";
        metric = UINT16_MAX;
    }
    rtEntry(const std::string &_addr, const unsigned short &_metric){
        addr = _addr;
        metric = _metric;
    }
};

typedef std::vector<rtEntry> entriesL;
typedef std::vector<rtEntry>::iterator entriesIt;

typedef std::map<Address, unsigned short> neighMetric;
typedef std::map<std::string, neighMetric> qosNeighMetric;
typedef neighMetric::iterator neighMetricIt;
typedef qosNeighMetric::iterator qosNeighMetricIt;

typedef std::map<std::string, rtEntry> tTable;
typedef std::map<std::string, tTable> rtTable;
typedef tTable::iterator tTableIt;
typedef rtTable::iterator rtTableIt;



class RoutingUpdate : public IntRoutingUpdate {
public:
    RoutingUpdate(const Address &_addr, const std::string &_src, const std::string& _qos);

    std::string getSrc();
    std::string getQoS();

    void addEntry(rtEntry);

    entriesIt entriesBegin();
    entriesIt entriesEnd();

protected:
    std::string src;
    std::string qos;
    entriesL entries;
};

class SimpleDV: public IntSimpleRouting {
public:
    //Process a Routing Update, return true => inform FWDG of the update
    bool processUpdate(IntRoutingUpdate * update);


    //Flow inserted/removed
    void insertFlow(const Address &addr, const std::string &dst, const std::string& qos, const unsigned short &metric);
    void removeFlow(const Address &addr, const std::string &dst, const std::string& qos);


    //Get Changes
    entries2Next getChanges();
    entries2Next getAll();

    void handleMessage(cMessage *msg);
    void finish();

protected:
    // Called after initialize
    void onPolicyInit();

private:
    unsigned short infMetric;
    std::string myAddr;
    qosNeighMetric neig;
    rtTable table;

    entries2Next changes;

    bool scheduledUpdate;
    void scheduleUpdate();
};

}

#endif /* SimpleDV_H_ */
