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

#include "DIF/RMT/PDUForwarding/QoSTable/QoSTable.h"


Register_Class(QoSTable::QoSTable);

namespace QoSTable {

using namespace std;

#include <sstream>

// Lookup function, return a list of RMTPorts to forward a PDU/Address+qos.
vector<RMTPort * > QoSTable::lookup(const PDU * pdu){
    return lookup(pdu->getDstAddr(), pdu->getConnId().getQoSId());
}
vector<RMTPort * > QoSTable::lookup(const Address &dst, const std::string &qos){
    vector<RMTPort* > ret;
    string dstAddr = dst.getIpcAddress().getName();

    ret = lookupInt(dstAddr, qos);

    if(ret.empty() && !qos.compare(VAL_MGMTQOSID) ) {
        for(QoSFWDTableIt qIt = table.begin(); qIt != table.end(); qIt++){
            ret = lookupInt(dstAddr, qIt->first);
            if(!ret.empty()) { return ret; }
        }
    }

    return ret;
}

vector<RMTPort * > QoSTable::lookupInt(const string &dst, const std::string &qos){
    vector<RMTPort* > ret;
    FWDTableIt it = table[qos].find(dst);
    if(it != table[qos].end()){
        ret.push_back(it->second);
    }
    return ret;
}

// Returns a representation of the Forwarding Knowledge
string QoSTable::toString(){
    std::ostringstream os;

    os << this->getFullPath()<<endl;

    for(QoSFWDTableIt qIt = table.begin(); qIt != table.end(); qIt++){
        os << "\tQoS : " <<qIt->first << endl;
        for(FWDTableIt tIt = qIt->second.begin(); tIt != qIt->second.end(); tIt++){
            os << "\t\t" <<tIt->first << "  ->  " <<tIt->second->getFullPath() << endl;
        }
    }


    return os.str();
}

//Insert/Remove an entry
void QoSTable::insert(const Address &addr, const std::string &qos, RMTPort * port){
    insert(addr.getIpcAddress().getName(), qos, port);
}
void QoSTable::remove(const Address &addr, const std::string &qos){
    remove(addr.getIpcAddress().getName(), qos);
}
void QoSTable::insert(const string &addr, const std::string &qos, RMTPort * port){
    table[qos][addr] = port;
}
void QoSTable::remove(const string &addr, const std::string &qos){
    table[qos].erase(addr);
    if(table[qos].empty()){
        table.erase(qos);
    }
}
void QoSTable::clean(){
    table.clear();
}


// Called after initialize
void QoSTable::onPolicyInit(){}

void QoSTable::finish(){
    if(par("printAtEnd").boolValue()){
        EV << toString() <<endl;
    }
}

}
