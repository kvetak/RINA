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

#include "QoSMultipathDynamicTable_Simple.h"
#include <sstream>
#include <algorithm>
#include <vector>


Register_Class(QoSMultipathDynamicTable_Simple::QoSMultipathDynamicTable_Simple);

namespace QoSMultipathDynamicTable_Simple {

using namespace std;
using namespace QoSMultipathDynamicTable;


//cEntry::cEntry(): p(nullptr), t(0), QoS("null") {}


void QoSMultipathDynamicTable_Simple::onMainPolicyInit() {
    cleanCache_t = par("cleanCache_t").doubleValue();
    recalcule_t = par("recalcule_t").doubleValue();
    counter = 0;

    if(cleanCache_t > 0) {
        scheduleAt(simTime() + cleanCache_t, timeOutMsg);
    }
    scheduleAt(simTime() + recalcule_t, recalcWeightMsg);
}

vector<RMTPort * > QoSMultipathDynamicTable_Simple::lookup(const PDU * pdu){
    counter ++;
    if (counter>=20){
       recalcule();
       counter=0;
    }
    RMTPort * next = nullptr;
    string dstAddr = pdu->getDstAddr().getIpcAddress().getName();

    cEntry * e = &cache[dstAddr][pdu->getConnId().getDstCepId()];

    string QoSid;
    if(par("QoSSpliter").boolValue()){
        QoSid = pdu->getConnId().getQoSId();
    }
    else{
        QoSid = "null";
    }

    next = e->p;

    if(next == nullptr) {
        next = portLookup(dstAddr, pdu->getConnId().getQoSId());
        if(next != nullptr){
            e->p = next;//Port inserted in cache
            e->reqBW = QoS_BWreq[pdu->getConnId().getQoSId()];
            e->QoS = QoSid;
            e->dst = dstAddr;
            e->DstCepId = pdu->getConnId().getDstCepId();
            orderedCache.addElement(e);
            string aux = pdu->getConnId().getQoSId();
            //BWControl[next].bw += QoS_BWreq[pdu->getConnId().getQoSId()];
            BWControl.addBW(next,QoSid,QoS_BWreq[pdu->getConnId().getQoSId()]);
        }
    }

    //Only for debug
  /*  EV << "Cache Final" << endl;
    for(auto it : cache[dstAddr]){
        EV << "Flujo : " << it.first << endl;
        EV << "Puerto: " << (int)it.second.p << endl;
        EV << "QoS: " << it.second.QoS << endl;
        EV << "BW    : " << it.second.reqBW << endl <<endl;
    }
    EV << endl << endl;*/
    //End of debug

    vector<RMTPort *> ret;
    if(next != nullptr) {
        ret.push_back(next);
        e->t = simTime();
    } else {
        //BWControl[(cache[dstAddr][pdu->getConnId().getDstCepId()]).p].bw -= (cache[dstAddr][pdu->getConnId().getDstCepId()]).reqBW;
        BWControl.removeBW(cache[dstAddr][pdu->getConnId().getDstCepId()].p,
                QoSid,
                cache[dstAddr][pdu->getConnId().getDstCepId()].reqBW);

        orderedCache.erraseElement(&cache[dstAddr][pdu->getConnId().getDstCepId()]);
        cache[dstAddr].erase(pdu->getConnId().getDstCepId());
        if(cache[dstAddr].empty()) {
            cache.erase(dstAddr);
        }
    }


    return ret;
}

//Not Used
vector<RMTPort * > QoSMultipathDynamicTable_Simple::lookup(const Address &dst, const std::string& qos){
    RMTPort * next = nullptr;
    vector<RMTPort *> ret;

    string dstAddr = dst.getIpcAddress().getName();

    if(dstAddr == "") { return ret; }

    next = portLookup(dstAddr, qos);

    if(next != nullptr) { ret.push_back(next); }


    return ret;
}

RMTPort * QoSMultipathDynamicTable_Simple::portLookup(const string& dst, const string& qos) {
    if(dst == "") {
        return nullptr;
    }
    string QoSid;
    if(par("QoSSpliter").boolValue()){
        QoSid = qos;
    }
    else{
        QoSid = "null";
    }
    int reqBW = QoS_BWreq[qos];
    vector<entryT> * entries = & table[dst];

    if (entries->empty()){
        return nullptr;
    }
    vector<entryT> possibles;

    int max = 0;
    RMTPort * bestOption = nullptr;

    for( entryT & e : *entries) {
        //UsedBW* BW = &BWControl[(e.p)];
        //if((e.BW - BW->bw) >= reqBW) {
        if(!par("DropIfNoBW").boolValue()){
            if((e.BW - BWControl.getBWbyQoS(e.p, qos)) > max){
                bestOption = e.p;
            }
        }
        if ((e.BW - BWControl.getTotalBW(e.p)) >= reqBW){
            possibles.push_back(e);
        }
    }


    if(possibles.empty()) {
        if(par("Reroute").boolValue()){
            long totalBW = 0;
                for (entryT & it : *entries)
                {
                   //totalBW += it.BW-BWControl[it.p].bw;
                    totalBW += it.BW-BWControl.getTotalBW(it.p);
                }
            if(totalBW >= reqBW){

                RMTPort * result = rerouteFlows(*entries, dst, reqBW, QoSid);
                if (result!=nullptr){
                    return result;
                }
                else{
                    if(!par("DropIfNoBW").boolValue()){
                        return bestOption;
                    }
                    else{
                        return nullptr;
                    }
                }
            }
            else{
                if(!par("DropIfNoBW").boolValue()){
                    return bestOption;
                }
                else{
                    return nullptr;
                }
            }
        }
        else{
            if(!par("DropIfNoBW").boolValue()){
                return bestOption;
            }
            else{
                return nullptr;
            }
        }
    }

    //int maxBW=0;
    if (weights.empty() || counter>=20){
        recalcule();
        counter=0;
    }
    entryT * exit = nullptr;
    vector<double> auxweight;
    long double sum = 0;
    if (weights.find(qos)!=weights.end())
    {
        for( entryT & e : possibles) {
            auxweight.insert(auxweight.end(),weights[qos][e.p]);
            sum = sum + weights[qos][e.p];
        }
        for(vector<double>::iterator it2 = auxweight.begin(); it2 != auxweight.end(); it2++){
            *it2 = (*it2)/sum;//Normalization
        }
        exit = &possibles[WeightedRandom(possibles, auxweight)];
    }
    else
    {
        exit = &possibles[(rand() % possibles.size())];
    }
    if (exit != nullptr)
    {
        return exit->p;
    }
    else
    {
        error("Entries found but none returned");
        return nullptr;
    }
}

RMTPort * QoSMultipathDynamicTable_Simple::rerouteFlows(const vector<entryT>& ports, const string& dst, const int& bw, const string& qos){

    vector<entryT> AvBWports; //ports with AVIABLE BandWith


    for(auto it : ports)
    {
        //entryT e(it.p,it.BW-BWControl[it.p].bw);
        entryT e(it.p,it.BW-BWControl.getTotalBW(it.p));
        AvBWports.push_back(e);
    }

    if(par("bigFlows").boolValue()){
        sort(AvBWports.begin(), AvBWports.end(), compareAscending);
    }
    else{
        sort(AvBWports.begin(), AvBWports.end(), compareDecresing);
    }

    //vector<cEntry> flows = OrganiceFlows(cache);
    for(auto p: AvBWports){
        RerouteInfo info(AvBWports);

        //for(auto it : cache[dst]){
        for(auto it : orderedCache.List){
            if((it->p==p.p) && (it->reqBW > 0) && SameNextHop(dst, it->dst)){
                //if flow can be rerouted
                entryT * auxPort = new entryT(NULL, 0);
                for (auto it2 : info.ports){
                        //if ((it2.second >= it.second.reqBW) && (it2.second > auxPort->BW)){
                    //if ((it2.second >= cache[dst][it].reqBW) && (isBetterPort(new entryT(it2.first, it2.second), auxPort))
                          //  && (it2.first != p.p)){
                    if ((it2.second >= it->reqBW) && (isBetterPort(new entryT(it2.first, it2.second), auxPort))
                            && (it2.first != p.p)){
                        auxPort->p = it2.first;
                        auxPort->BW = it2.second;
                    }
                }
                info.addMov(p.p, auxPort->p, it->DstCepId, it->reqBW, qos);
                info.ports[p.p]+=it->reqBW;
                info.ports[auxPort->p]-=it->reqBW;
                delete auxPort;

                if(info.ports[p.p] >= bw){
                    AplyReroute(info, dst);
                    return p.p;

                }
            }
        }
        info.movements.clear();
        info.ports.clear();
    }
    return nullptr;

}

unsigned int QoSMultipathDynamicTable_Simple::WeightedRandom(vector<entryT> &possibles, vector<double> &weight){

    unsigned int sum = 0;
    for (unsigned int i=0; i<weight.size(); i++){
        sum = sum + (int)(weight[i]*100);
    }
    if(sum == 0)
    {
        return 0;
    }
    int rnd = rand() % sum;
    for (unsigned int i=0; i<weight.size(); i++){
        if(rnd < (int)(weight[i]*100)){
            return i;
        }
        else{
            rnd =- (int)(weight[i]*100);
        }
    }
    return 0;//Never should end here
}

bool QoSMultipathDynamicTable_Simple::SameNextHop(string dst1, string dst2){

    if(dst1 == dst2){
        return true;
    }

    vector<entryT> * entries1 = & table[dst1];
    vector<entryT> * entries2 = & table[dst2];

    for (auto it1 : *entries1){
        for (auto it2 : *entries2){
            if(it1.p == it2.p){
                return true;
            }
        }
    }

    return false;
}

void QoSMultipathDynamicTable_Simple::AplyReroute(const RerouteInfo &info, const string& dst){

    for (auto it : info.movements){
        cache[dst][it.flow].p=it.dst;
        //BWControl[it.org].bw += it.reqBW;
        BWControl.addBW(it.org, it.qos, it.reqBW);
        //BWControl[it.dst].bw -= it.reqBW;
        BWControl.removeBW(it.dst, it.qos, it.reqBW);
    }
}

bool QoSMultipathDynamicTable_Simple::isBetterPort(const entryT * port1, const entryT * port2, const string& qos){
    if(port1 == nullptr)
    {
        return false;
    }
    else if(port2 == nullptr)
    {
        return true;
    }
    else{
        if(par("bigFlows").boolValue()){
            //return ((port1->BW-BWControl[port1->p].bw) < (port2->BW-BWControl[port2->p].bw));
            return ((port1->BW-BWControl.getBWbyQoS(port1->p, qos)) < (port2->BW-BWControl.getBWbyQoS(port2->p,qos)));
        }
        else{
            //return ((port1->BW-BWControl[port1->p].bw) > (port2->BW-BWControl[port2->p].bw));
            return ((port1->BW-BWControl.getBWbyQoS(port1->p, qos)) > (port2->BW-BWControl.getBWbyQoS(port2->p,qos)));
        }
    }

}

bool QoSMultipathDynamicTable_Simple::isBetterPort(const entryT * port1, const entryT * port2){
    if(port1 == nullptr)
    {
        return false;
    }
    else if(port2 == nullptr)
    {
        return true;
    }
    else{
        if(par("bigFlows").boolValue()){
            //return ((port1->BW-BWControl[port1->p].bw) < (port2->BW-BWControl[port2->p].bw));
            return ((port1->BW-BWControl.getTotalBW(port1->p)) < (port2->BW-BWControl.getTotalBW(port2->p)));
        }
        else{
            //return ((port1->BW-BWControl[port1->p].bw) > (port2->BW-BWControl[port2->p].bw));
            return ((port1->BW-BWControl.getTotalBW(port1->p)) > (port2->BW-BWControl.getTotalBW(port2->p)));
        }
    }

}

bool QoSMultipathDynamicTable_Simple::compareDecresing(const entryT &i, const entryT &j){
    return(i.BW > j.BW);//Decresing order
}

bool QoSMultipathDynamicTable_Simple::compareAscending(const entryT &i, const entryT &j){
    return(i.BW < j.BW);//Ascending order
}

void QoSMultipathDynamicTable_Simple::onSetPort(RMTPort * p, const int bw) {
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

void QoSMultipathDynamicTable_Simple::preReplacePort(RMTPort * oldP, RMTPort * newP, const int bw) {
    onSetPort(oldP, 0);

    for(auto & dst : table) {
        for(auto & e : dst.second) {
            if(e.p == oldP) { e.p = newP; }
        }
    }
}

void QoSMultipathDynamicTable_Simple::handleMessage(cMessage * msg) {

    if (msg == timeOutMsg){
        simtime_t limT = simTime()-2*cleanCache_t;
        for(auto it = cache.begin(); it!= cache.end();) {
            for(auto it2 = it->second.begin(); it2!= it->second.end();) {
                if(it2->second.t < limT) {
                    auto tIt = it2;
                    it2++;
                    //BWControl[tIt->second.p].bw -= tIt->second.reqBW;
                    BWControl.removeBW(tIt->second.p, tIt->second.QoS, tIt->second.reqBW);
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

        scheduleAt(simTime() + cleanCache_t, msg);
    }
    else if (msg == recalcWeightMsg){

//        for(auto it : QoS_BWreq){
//
//            for(auto it2 : Port_avBW){
//                list <unsigned short> aux = mon->getStats(it2.first, it.first);
//                double mean = 0;
//                for(auto it3 : aux){
//                    mean =+ it3;
//                }
//                if(aux.size()== 0 || mean == 0){
//                    mean = 0.01;
//                }
//                else{
//                    mean = aux.size()/(mean);//inverse of median
//                }
//                weights[it.first][it2.first]==mean;
//            }
//            //for(auto it2 : Port_avBW){
//            //    weights[it.first][it2.first]/sum;//Normalization
//            //}
//        }
        recalcule();
        scheduleAt(simTime() + recalcule_t, msg);
    }
}

void QoSMultipathDynamicTable_Simple::recalcule(){
    for(auto it : QoS_BWreq){

                for(auto it2 : Port_avBW){
                    list <unsigned short> aux = mon->getStats(it2.first, it.first);
                    double mean = 0;
                    for(auto it3 : aux){
                        mean =+ it3;
                    }
                    if(aux.size()== 0 || mean == 0){
                        mean = 0.01;
                    }
                    else{
                        mean = aux.size()/(mean);//inverse of median
                    }
                    weights[it.first][it2.first] = mean;
                }
                //for(auto it2 : Port_avBW){
                //    weights[it.first][it2.first]/sum;//Normalization
                //}
            }
}

//Insert/Remove an entry
void QoSMultipathDynamicTable_Simple::addReplace(const string &addr, vector<entryT> ports) {
    if(addr == "") {
        return;
    }

    if(ports.empty()) {
        for(auto it = cache[addr].begin(); it!= cache[addr].end();) {
                //BWControl[it->second.p].bw -= it->second.reqBW;
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
                    //BWControl[tIt->second.p].bw -= tIt->second.reqBW;
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
}


// Returns a representation of the Forwarding Knowledge
string QoSMultipathDynamicTable_Simple::toString(){
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

void QoSMultipathDynamicTable_Simple::finish(){
    if(par("printAtEnd").boolValue()){
        EV << "-----------------" << endl;
        EV << "Forwarding table::" << endl;
        EV << toString() <<endl;
        EV << "-----------------" << endl;
    }
}

}
