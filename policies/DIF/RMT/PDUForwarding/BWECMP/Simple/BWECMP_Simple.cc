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

#include "BWECMP_Simple.h"
#include <sstream>


Register_Class(BWECMP_Simple::BWECMP_Simple);

namespace BWECMP_Simple {

using namespace std;
using namespace BWECMP;


cEntry::cEntry(): p(nullptr), t(0) {}


void BWECMP_Simple::onMainPolicyInit() {
    cleanCache_t = par("cleanCache_t").doubleValue();
    if(cleanCache_t > 0) {
        scheduleAt(simTime() + cleanCache_t, new cMessage("Clean Forwarding Cache"));
    }
}

vector<RMTPort * > BWECMP_Simple::lookup(const PDU * pdu){
    RMTPort * next = nullptr;
    string dstAddr = pdu->getDstAddr().getIpcAddress().getName();

    cEntry * e = &cache[dstAddr][pdu->getConnId().getDstCepId()];

    next = e->p;
    if(next == nullptr) {
        next = portLookup(dstAddr, pdu->getConnId().getQoSId());
        e->p = next;
    }

    vector<RMTPort *> ret;
    if(next != nullptr) {
        ret.push_back(next);
        e->t = simTime();
    } else {
        cache[dstAddr].erase(pdu->getConnId().getDstCepId());
        if(cache[dstAddr].empty()) { cache.erase(dstAddr); }
    }


    return ret;
}

vector<RMTPort * > BWECMP_Simple::lookup(const Address &dst, const std::string& qos){
    RMTPort * next = nullptr;
    vector<RMTPort *> ret;

    string dstAddr = dst.getIpcAddress().getName();

    if(dstAddr == "") { return ret; }

    next = portLookup(dstAddr, qos);

    if(next != nullptr) { ret.push_back(next); }


    return ret;
}

RMTPort * BWECMP_Simple::portLookup(const string& dst, const string& qos) {
    if(dst == "") { return nullptr; }
    int reqBW = QoS_BWreq[qos];
    vector<entryT> * entries = & table[dst];

    vector<entryT> possibles;

    int count = 0;
    for(const entryT & e : *entries) {
        if(e.BW >= reqBW) {
            count += e.BW;
            possibles.push_back(e);
        }
    }

    if(possibles.empty()) { return nullptr; }

    int r = intuniform(0, count);
    for(const entryT & e : possibles) {
        if(r<e.BW) { return e.p; }
        else { r -= e.BW; }
    }

    error("Entries found but none returned");
    return nullptr;
}


void BWECMP_Simple::onSetPort(RMTPort * p, const int bw) {
    if(bw > 0) { return; }

    for(auto it = cache.begin(); it!= cache.end();) {
        for(auto it2 = it->second.begin(); it2!= it->second.end();) {
            if(it2->second.p == p) {
                auto tIt = it2;
                it2++;
                it->second.erase(tIt);
            } else { it2++; }
        }
        if(it->second.empty()) {
            auto tIt = it;
            it++;
            cache.erase(tIt);
        } else { it++; }
    }
}

void BWECMP_Simple::preReplacePort(RMTPort * oldP, RMTPort * newP, const int bw) {
    onSetPort(oldP, 0);

    for(auto & dst : table) {
        for(auto & e : dst.second) {
            if(e.p == oldP) { e.p = newP; }
        }
    }
}

void BWECMP_Simple::handleMessage(cMessage * msg) {
    simtime_t limT = simTime()-2*cleanCache_t;
    for(auto it = cache.begin(); it!= cache.end();) {
        for(auto it2 = it->second.begin(); it2!= it->second.end();) {
            if(it2->second.t < limT) {
                auto tIt = it2;
                it2++;
                it->second.erase(tIt);
            } else { it2++; }
        }
        if(it->second.empty()) {
            auto tIt = it;
            it++;
            cache.erase(tIt);
        } else { it++; }
    }

    scheduleAt(simTime() + cleanCache_t, msg);
}

void BWECMP_Simple::addReplace(const string &addr, vector<entryT> ports) {
    if(addr == "") { return; }

    if(ports.empty()) {
        cache.erase(addr);
        table.erase(addr);
        return;
    }

    for(entryT & e : table[addr]) {
        bool found = false;
        for(entryT & n : ports) {
            if(e.p == n.p) { found = true; }
        }
        if(!found) {
            for(auto it2 = cache[addr].begin(); it2!= cache[addr].end();) {
                if(it2->second.p == e.p) {
                    auto tIt = it2;
                    it2++;
                    cache[addr].erase(tIt);
                } else { it2++; }
            }
        }
    }
    if(cache[addr].empty()) { cache.erase(addr); }

    table[addr] = ports;
}


// Returns a representation of the Forwarding Knowledge
string BWECMP_Simple::toString(){
    std::ostringstream os;
    os << this->getFullName()<<endl;
    for(const auto & dst : table) {
        os << "\t" << dst.first << "  ->  " << endl;
        for(auto e : dst.second) {
            os << "\t\t" << e.BW << " : "<< e.p->getFullPath() << endl;
        }
    }

    return os.str();
}

void BWECMP_Simple::finish(){
    if(par("printAtEnd").boolValue()){
        EV << "-----------------" << endl;
        EV << "Forwarding table::" << endl;
        EV << toString() <<endl;
        EV << "-----------------" << endl;
    }
}

}
