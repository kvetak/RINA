//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
// 

#ifndef SimpleDV_H_
#define SimpleDV_H_

#include <IntSimpleRouting.h>

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
typedef std::map<unsigned short, neighMetric> qosNeighMetric;
typedef neighMetric::iterator neighMetricIt;
typedef qosNeighMetric::iterator qosNeighMetricIt;

typedef std::map<std::string, rtEntry> tTable;
typedef std::map<unsigned short, tTable> rtTable;
typedef tTable::iterator tTableIt;
typedef rtTable::iterator rtTableIt;



class RoutingUpdate : public IntRoutingUpdate {
public:
    RoutingUpdate(const Address &_addr, const std::string &_src, const unsigned short &_qos);

    std::string getSrc();
    unsigned short getQoS();

    void addEntry(rtEntry);

    entriesIt entriesBegin();
    entriesIt entriesEnd();

protected:
    std::string src;
    unsigned short qos;
    entriesL entries;
};

class SimpleDV: public IntSimpleRouting {
public:
    //Process a Routing Update, return true => inform FWDG of the update
    bool processUpdate(const IntRoutingUpdate * update);


    //Flow inserted/removed
    void insertFlow(const Address &addr, const std::string &dst, const unsigned short &qos, const unsigned short &metric);
    void removeFlow(const Address &addr, const std::string &dst, const unsigned short &qos);

    //Get Changes
    entries2Next getChanges();
    entries2Next getAll();

    void handleMessage(cMessage *msg);
    void finish();

protected:
    // Called after initialize
    void onIni();

private:
    unsigned short infMetric;
    std::string myAddr;
    qosNeighMetric neig;
    rtTable table;

    entries2Next changes;
};

}

#endif /* SimpleDV_H_ */
