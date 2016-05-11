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

#include "QoSMultipathMonitor_Simple.h"
#include <sstream>
#include <algorithm>
#include <vector>


Register_Class(QoSMultipathMonitor_Simple::QoSMultipathMonitor_Simple);

namespace QoSMultipathMonitor_Simple {

using namespace std;
using namespace QoSMultipathMonitor;


void QoSMultipathMonitor_Simple::onMainPolicyInit() {

    recalcule_t = par("recalcule_t").doubleValue();
    counter = 0;

    scheduleAt(simTime() + recalcule_t, recalcWeightMsg);
}

vector<RMTPort * > QoSMultipathMonitor_Simple::lookup(const PDU * pdu){
    RMTPort * next = nullptr;
    string dstAddr = pdu->getDstAddr().getIpcAddress().getName();

    cEntry * e = &cache[dstAddr][pdu->getConnId().getSrcCepId()];

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

//Not Used
vector<RMTPort * > QoSMultipathMonitor_Simple::lookup(const Address &dst, const std::string& qos){
    RMTPort * next = nullptr;
    vector<RMTPort *> ret;

    string dstAddr = dst.getIpcAddress().getName();

    if(dstAddr == "") { return ret; }

    next = portLookup(dstAddr, qos);

    if(next != nullptr) { ret.push_back(next); }


    return ret;
}

RMTPort * QoSMultipathMonitor_Simple::portLookup(const string& dst, const string& qos) {
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

void QoSMultipathMonitor_Simple::onSetPort(RMTPort * p, const int bw) {
    if(bw > 0) {
        return;
    }

    for(auto it = cache.begin(); it!= cache.end();) {
        for(auto it2 = it->second.begin(); it2!= it->second.end();) {
            if(it2->second.p == p) {
                auto tIt = it2;
                it2++;
                orderedCache.erraseElement(&(tIt->second));
                it->second.erase(tIt);
            } else { it2++; }
        }
        if(it->second.empty()) {
            auto tIt = it;
            it++;
            cache.erase(tIt);
        } else { it++; }
    }
    //BWControl.erase(p);
    BWControl.removePort(p);
}

void QoSMultipathMonitor_Simple::preReplacePort(RMTPort * oldP, RMTPort * newP, const int bw) {
    onSetPort(oldP, 0);

    for(auto & dst : table) {
        for(auto & e : dst.second) {
            if(e.p == oldP) { e.p = newP; }
        }
    }
}

void QoSMultipathMonitor_Simple::handleMessage(cMessage * msg) {

    if (msg == recalcWeightMsg){
        recalcule();
        scheduleAt(simTime() + recalcule_t, msg);
    }
}

//Insert/Remove an entry
void QoSMultipathMonitor_Simple::addReplace(const string &addr, vector<entryT> ports) {
    if(addr == "") {
        return;
    }

    if(ports.empty()) {
        for(auto it = cache[addr].begin(); it!= cache[addr].end();) {
            BWControl.removeBW(it->second.p, it->second.QoS, it->second.reqBW);
        }
        cache.erase(addr);
        table.erase(addr);
        return;
    }

    for(entryT & e : table[addr]) {
        bool found = false;
        for(entryT & n : ports) {
            if(e.p == n.p) {
                found = true;
            }
        }
        if(!found) {
            for(auto it2 = cache[addr].begin(); it2!= cache[addr].end();) {
                if(it2->second.p == e.p) {
                    auto tIt = it2;
                    it2++;
                    BWControl.removeBW(tIt->second.p, tIt->second.QoS, tIt->second.reqBW);
                    orderedCache.erraseElement(&(tIt->second));
                    cache[addr].erase(tIt);
                } else {
                    it2++;
                }
            }
        }
    }
    if(cache[addr].empty()) {
        cache.erase(addr);
    }

    table[addr] = ports;

//    //update informatión in manager
//    MonitorMsg* msg = new MonitorMsg();
//    string id = getFullPath();
//    int pos1 = id.find(".")+1;
//    int pos2 = id.find(".",pos1);
//    id=id.substr(pos1, pos2-pos1);
//    msg->regInfo.nodeId=id;
//    msg->type="Register_Node";
//    msg->regInfo.routingInfo=&table;
//    msg->regInfo.portInfo=&Port_avBW;
//    cModule *targetModule = getModuleByPath("InfecteedMultipathFatTree.fullPathMonitor");
//    take(msg);
//    sendDirect(msg, targetModule, "radioIn");

}

void QoSMultipathMonitor_Simple::recalcule(){
    for(auto it : QoS_BWreq){

        for(auto it2 : Port_avBW){
            list <unsigned short> aux = mon->getStats(it2.first, it.first);
            double mean = 0;
            for(auto it3 : aux){
                mean = mean + it3;
            }
            if(aux.size()== 0){
                mean = 1.0;
            }
            else if(mean == 0)
            {
                mean = 1.0;
            }
            else{
                mean = (double)aux.size()/(mean);//inverse of median
                if(mean > 1.0){
                    mean = 1.0;
                }

            }
            weights[it.first][it2.first] = mean;
        }
    }
}

// Returns a representation of the Forwarding Knowledge
string QoSMultipathMonitor_Simple::toString(){
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

void QoSMultipathMonitor_Simple::setFlow(cEntry entry){
    cache[entry.dst][entry.SrcCepId]=entry;
}

void QoSMultipathMonitor_Simple::removeFlow(cEntry entry){
    cache[entry.dst].erase(entry.SrcCepId);
    if(cache[entry.dst].size()==0){
        cache.erase(entry.dst);
    }
}

void QoSMultipathMonitor_Simple::finish(){
    if(par("printAtEnd").boolValue()){
        EV << "-----------------" << endl;
        EV << "Forwarding table::" << endl;
        EV << toString() <<endl;
        EV << "-----------------" << endl;
        EV << "Cache table::" << endl;
        map<RMTPort *, int> counter;
        for(auto it : Port_avBW){
            counter[it.first]=0;
        }
        for (auto it : cache){
        EV << it.first << endl;
            for(auto it2 : it.second){
                EV << "Flujo : " << it2.first << endl;
                EV << "Puerto: " << it2.second.p->getFullPath() << endl;
                EV << "QoS: " << it2.second.QoS << endl;
                EV << "BW    : " << it2.second.reqBW << endl <<endl;
                counter[it2.second.p] = counter[it2.second.p]+1;
            }
            EV << "-----------------" << endl;
        }
        for(auto it3 : Port_avBW){
            EV  << it3.first->getFullPath() << " : " << counter[it3.first] << endl;
        }
        EV << toString() <<endl;
        EV << "-----------------" << endl;
    }
}

Routingtable* QoSMultipathMonitor_Simple::getRoutingTable(){
    return &table;
}

SchedulerInfo* QoSMultipathMonitor_Simple::getSchedulerInfo(){
    recalcule();
    return &weights;
}


}
