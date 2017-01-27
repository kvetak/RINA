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

#include "DIF/RMT/PDUForwarding/FloodMiniTable/FloodMiniTable.h"


Register_Class(FloodMiniTable::FloodMiniTable);

namespace FloodMiniTable {

using namespace std;

#include <sstream>

// Lookup function, return a list of RMTPorts to forward a PDU/Address+qos.
vector<RMTPort * > FloodMiniTable::lookup(const PDU * pdu){
    return lookup(pdu->getDstAddr(), pdu->getConnId().getQoSId());
}
vector<RMTPort * > FloodMiniTable::lookup(const Address &dst, const std::string& qos){

    vector<RMTPort* > ret;
    string dstAddr = dst.getIpcAddress().getName();
    FWDTableIt it = table.find(dstAddr);

    if(it != table.end()){
        for(RMTPort* p : it->second) {
            ret.push_back(p);
        }
    }

    return ret;
}

// Returns a representation of the Forwarding Knowledge
string FloodMiniTable::toString(){
    std::ostringstream os;

    os << this->getName()<<endl;
    for(FWDTableIt tIt = table.begin(); tIt != table.end(); tIt++){
        os << "\t" <<tIt->first << "  ->  ";
        for(RMTPort * p : tIt->second){
            os << p->getFullPath() << "   ";
        }
        os << endl;
    }

    return os.str();
}

//Insert/Remove an entry
void FloodMiniTable::addReplace(const std::string &addr, vector<RMTPort *> ports){
    if(ports.empty()){
        table.erase(addr);
    } else {
        table[addr] = ports;
    }
}

// Called after initialize
void FloodMiniTable::onPolicyInit(){}

void FloodMiniTable::finish(){
    if(par("printAtEnd").boolValue()){
        EV << "-----------------" << endl;
        EV << "Forwarding table::" << endl;
        EV << toString() <<endl;
        EV << "-----------------" << endl;
    }
}

}
