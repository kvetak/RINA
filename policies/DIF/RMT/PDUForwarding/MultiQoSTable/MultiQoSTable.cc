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

#include <MultiQoSTable/MultiQoSTable.h>


Register_Class(MultiQoSTable::MultiQoSTable);

namespace MultiQoSTable {

using namespace std;

#include <sstream>

// Lookup function, return a list of RMTPorts to forward a PDU/Address+qos.
vector<RMTPort * > MultiQoSTable::lookup(const PDU * pdu){
    return lookup(pdu->getDstAddr(), pdu->getConnId().getQoSId());
}
vector<RMTPort * > MultiQoSTable::lookup(const Address &dst, const std::string& qos){

    vector<RMTPort* > ret;

    string dstAddr = dst.getIpcAddress().getName();

    //Why empty lookup?
    if(dstAddr == "") { return ret; }

    auto it = table[qos].find(dstAddr);

    if(it != table[qos].end()){
        int i = intuniform(0, it->second.size()-1);
        ret.push_back(it->second.at(i));
    }

    if(ret.empty()) {
        if(qos == QoSCube::MANAGEMENT.getQosId()) {
            for(auto qosT : table) {
                ret = lookup(dst, qosT.first);
                if(!ret.empty()) { break; }
            }
        }
    }

    if(ret.empty()) {
    //    cout << "NOT FOUND "<< dst <<  " +  QoS " << qos <<endl;
    //    cout << "\tAT " << this->getFullPath() << endl;
    }

    return ret;
}

// Returns a representation of the Forwarding Knowledge
string MultiQoSTable::toString(){
    std::ostringstream os;

    os << this->getName()<<endl;
    for(const auto &qosTable : table) {
        os << "\tQoS :" << qosTable.first << endl;
        for(const auto & entry : qosTable.second) {
            os << "\t\tQoS :" << entry.first << "  ->  ";
            for(RMTPort * p : entry.second){
                os << p->getFullPath() << "   ";
            }
            os << endl;
        }
    }
    return os.str();
}

//Insert/Remove an entry
void MultiQoSTable::addReplace(const std::string &addr, const std::string &qosId, std::vector<RMTPort * > ports) {
    if(ports.empty()){
        table[qosId].erase(addr);
    } else {
        table[qosId][addr] = ports;
    }
}

// Called after initialize
void MultiQoSTable::onPolicyInit(){}

void MultiQoSTable::finish(){
    if(par("printAtEnd").boolValue()){
        EV << "-----------------" << endl;
        EV << "Forwarding table::" << endl;
        EV << toString() <<endl;
        EV << "-----------------" << endl;
    }
}

}
