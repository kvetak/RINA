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

#include <wocIMultiQoSTable/wocIMultiQoSTable.h>
#include "InfectionSignals.h"


Register_Class(wocIMultiQoSTable::wocIMultiQoSTable);

namespace wocIMultiQoSTable {

using namespace std;

#include <sstream>

// Lookup function, return a list of RMTPorts to forward a PDU/Address+qos.
vector<RMTPort * > wocIMultiQoSTable::lookup(const PDU * pdu){

    string dstAddr = pdu->getDstAddr().getIpcAddress().getName();
    string srcAddr = pdu->getSrcAddr().getIpcAddress().getName();

    RMTPort * r = search(dstAddr, pdu->getConnId().getQoSId());
    vector<RMTPort * > ret;
    if(r != nullptr) {
        ret.push_back(r);
    }

    return ret;
}

vector<RMTPort * > wocIMultiQoSTable::lookup(const Address &dst, const std::string& qos){

    string dstAddr = dst.getIpcAddress().getName();

    vector<RMTPort* > ret;

    RMTPort * next = search(dstAddr, qos);

    if(next != nullptr) {
        ret.push_back(next);
    }

    return ret;
}

// Returns a representation of the Forwarding Knowledge
string wocIMultiQoSTable::toString(){
    std::ostringstream os;

    os << this->getName()<<endl;
    for(const auto &qosTable : table) {
        os << "\tQoS :" << qosTable.first << endl;
        for(const auto & entry : qosTable.second) {
            os << "\t\tQoS :" << entry.first << "  ->  ";
            for(RMTPort * p : entry.second){
                os << p->getParentModule()->getName() << "   ";

            }
            os << endl;
        }
    }


    return os.str();
}


RMTPort * wocIMultiQoSTable::search(const string & dst, const string & qos) {

    if(qos != QoSCube::MANAGEMENT.getQosId()) {
        vector<RMTPort*> & vR = table[qos][dst];
        int pS = vR.size();
        if(pS <= 0) { return nullptr; }
        if(pS == 1) { return vR.front(); }

        int k = intuniform(0, pS-1);
        return vR[k];
    } else {
        return search(dst, MA2QoS);
    }
}

//Insert/Remove an entry
void wocIMultiQoSTable::addReplace(const std::string &addr, const std::string &qosId, std::vector<RMTPort * > ports) {
    vector<RMTPort*> old;

    for(RMTPort * p : table[qosId][addr]) {
        bool found = false;
        for(RMTPort * p2 : ports) {
            if(p == p2) { found = true; break; }
        }
        if(!found) { old.push_back(p); }
    }

    if(ports.empty()){
        table[qosId].erase(addr);
    } else {
        table[qosId][addr] = ports;
    }
}

void wocIMultiQoSTable::setPortDelay(RMTPort* port, double delay) {
    portDelay[port] = delay;
}

// Called after initialize
void wocIMultiQoSTable::onPolicyInit(){
    MA2QoS = par("MA2QoS").stdstringValue();
    if(MA2QoS == "") { error("Management to QoS must be set."); }
}

void wocIMultiQoSTable::finish(){
    if(par("printAtEnd").boolValue()){
        EV << "-----------------" << endl;
        EV << this->getFullPath() << endl;
            EV << "Forwarding table::" << endl;
            EV << toString() <<endl;
        EV << "-----------------" << endl;
    }
}

}
