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

#include "DIF/RMT/PDUForwarding/MiniTable/MiniTable.h"


Register_Class(MiniTable::MiniTable);

namespace MiniTable {

using namespace std;

#include <sstream>

// Lookup function, return a list of RMTPorts to forward a PDU/Address+qos.
vector<RMTPort * > MiniTable::lookup(const PDU * pdu){
    vector<RMTPort* > ret;
    string dstAddr = pdu->getDstAddr().getIpcAddress().getName();
    FWDTableIt it = table.find(dstAddr);

    if(it != table.end()){
        ret.push_back(it->second);
    } else {
        std::cout << this->getFullPath()<<endl;
        std::cout << pdu->getDstAddr() << " not found "<<endl;
        std::cout << toString() <<endl;
    }

    return ret;
}
vector<RMTPort * > MiniTable::lookup(const Address &dst, const std::string& qos){

    vector<RMTPort* > ret;
    string dstAddr = dst.getIpcAddress().getName();
    FWDTableIt it = table.find(dstAddr);

    if(it != table.end()){
        ret.push_back(it->second);
    }

    return ret;
}

// Returns a representation of the Forwarding Knowledge
string MiniTable::toString(){
    std::ostringstream os;

    os << this->getFullPath()<<endl;
    for(FWDTableIt tIt = table.begin(); tIt != table.end(); tIt++){
        os << "\t" <<tIt->first << "  ->  " <<tIt->second->getFullPath() << endl;
    }

    return os.str();
}

//Insert/Remove an entry
void MiniTable::insert(const Address &addr, RMTPort * port){

    insert(addr.getIpcAddress().getName(), port);
}
void MiniTable::remove(const Address &addr){
    remove(addr.getIpcAddress().getName());
}
void MiniTable::insert(const string &addr, RMTPort * port){

    table[addr] = port;
}
void MiniTable::remove(const string &addr){
    table.erase(addr);
}
void MiniTable::clean(){
    table.clear();
}


// Called after initialize
void MiniTable::onPolicyInit(){}

void MiniTable::finish(){
    if(par("printAtEnd").boolValue()){
        EV << toString() <<endl;
    }
}

}
