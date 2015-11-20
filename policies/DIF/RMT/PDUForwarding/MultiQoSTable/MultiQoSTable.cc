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


FlowIdent::FlowIdent(const string & _qosId, const string & _srcAddr, const string & _dstAddr, const int & _srcCepId, const int & _dstCepId) :
    qosId(_qosId), srcAddr(_srcAddr), dstAddr(_dstAddr), srcCepId(_srcCepId), dstCepId(_dstCepId){}

bool FlowIdent::operator<( const FlowIdent & o ) const {
    if(srcCepId < o.srcCepId) { return true; }
    if(srcCepId > o.srcCepId) { return false; }

    if(dstCepId < o.dstCepId) { return true; }
    if(dstCepId > o.dstCepId) { return false; }

    if(qosId < o.qosId) { return true; }
    if(qosId > o.qosId) { return false; }

    if(dstAddr < o.dstAddr) { return true; }
    if(dstAddr > o.dstAddr) { return false; }

    return srcAddr < o.srcAddr;
}

CacheData::CacheData(RMTPort *  _next, const simtime_t & _expiration) :
        next(_next), expiration(_expiration) {}
CacheData::CacheData() :
    next(nullptr), expiration(0.0) {}

// Lookup function, return a list of RMTPorts to forward a PDU/Address+qos.
vector<RMTPort * > MultiQoSTable::lookup(const PDU * pdu){

    string dstAddr = pdu->getDstAddr().getIpcAddress().getName();
    string srcAddr = pdu->getSrcAddr().getIpcAddress().getName();

    const ConnectionId & cId = pdu->getConnId();
    FlowIdent fId = FlowIdent(cId.getQoSId(), srcAddr, dstAddr, cId.getSrcCepId(), cId.getDstCepId());

    CacheData & cd = cache[fId];

    simtime_t ex = simTime() + exTime;

    if(cd.next == nullptr || cd.expiration < ex) {
        cd.next = search(dstAddr, fId.qosId);
    }

    vector<RMTPort * > ret;
    if(cd.next != nullptr) {
        ret.push_back(cd.next);
        cd.expiration = ex;
    } else {
        cache.erase(fId);
    }

    return ret;
}
vector<RMTPort * > MultiQoSTable::lookup(const Address &dst, const std::string& qos){

    string dstAddr = dst.getIpcAddress().getName();

    vector<RMTPort* > ret;

    RMTPort * next = search(dstAddr, qos);

    if(next != nullptr) {
        ret.push_back(next);
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
                os << p->getParentModule()->getName() << "   ";

            }
            os << endl;
        }
    }


    os << "\tCache : "<<endl;
    for(const auto &ent : cache) {
        os << "\t\t :";
        os << "("<< ent.first.srcAddr << "."<< ent.first.srcCepId << ")";
        os << " -> ";
        os << "("<< ent.first.dstAddr << "."<< ent.first.dstCepId << ")";
        os << " ["<< ent.first.qosId << "]";
        os << " >> "<<endl;
        os << "\t\t\t" << ent.second.next->getParentModule()->getName();
        os << "\t\t\tExpires " << ent.second.expiration;
        os << endl;
    }
    return os.str();
}


RMTPort * MultiQoSTable::search(const string & dst, const string & qos) {

    if(qos != QoSCube::MANAGEMENT.getQosId()) {
        vector<RMTPort*> & vR = table[qos][dst];
        int pS = vR.size();
        if(pS <= 0) { return nullptr; }
        if(pS == 1) { return vR.front(); }

        int k = intuniform(0, pS);
        return vR[k];
    } else {
        return search(dst, MA2QoS);
    }
}

//Insert/Remove an entry
void MultiQoSTable::addReplace(const std::string &addr, const std::string &qosId, std::vector<RMTPort * > ports) {

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

    for(RMTPort * p : old) {
        for(auto it = cache.begin(); it != cache.end();) {
            auto itB = it++;
            if(it->second.next == p && it->first.dstAddr == addr && it->first.qosId == qosId) {
                cache.erase(itB);
            }
        }
    }
}

// Called after initialize
void MultiQoSTable::onPolicyInit(){
    MA2QoS = par("MA2QoS").stdstringValue();
    if(MA2QoS == "") { error("Management to QoS must be set."); }
    exTime = par("exTime").doubleValue();
}

void MultiQoSTable::finish(){
    if(par("printAtEnd").boolValue()){
        EV << "-----------------" << endl;
        EV << this->getFullPath() << endl;
        EV << "Forwarding table::" << endl;
        EV << toString() <<endl;
        EV << "-----------------" << endl;
    }
}

}
