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

/*
 * LS.cc
 *
 *  Created on: Mar 23, 2015
 *      Author: gaixas1
 */

#include "DIF/Routing/DomainRouting/LS/LS.h"
#include "DIF/Routing/DomainRouting/Routing.h"

namespace DMRnmsLS {

using namespace DMRnms;
using namespace std;



LSUpdate::LSUpdate(const Address &_addr, const string &_domain)
    :RoutingUpdate(_addr, _domain){}


void LSUpdate::addEntry(const std::string & _addr, linksU _neig) {
    entries[_addr] = _neig;
}
void LSUpdate::setEntries(linksSt _entries) {
    entries = _entries;
}

linksStIt LSUpdate::entriesBegin() {
    return entries.begin();
}

linksStIt LSUpdate::entriesEnd() {
    return entries.end();
}


LS::LS(Routing * parent, const Address &_nAddr, const string &_domain, const string &_addr)
    :rModule(parent, _nAddr, _domain, _addr) {
    scheduledUpdate = false;
    secId = 1;
}

bool LS::processUpdate(RoutingUpdate * update){
    // Cast update to known type
    LSUpdate * up = dynamic_cast<LSUpdate*>(update);
    if(up == NULL) { return false; }

    for(linksStIt it = up->entriesBegin(); it != up->entriesEnd(); it++){
        string node = it->first;
        if(netState[node].sId < it->second.sId){
            netState[node] = it->second;
            changed.insert(node);
        }
    }

    if(! changed.empty()) {
        scheduleUpdate();
        return true;
    } else {
        return false;
    }
}

void LS::addFlow(const Address &_nAddr, const std::string &_addr, const unsigned short &_metric){
    nei[_nAddr] = _metric;
    neigTable[_addr] = _nAddr;

    changed.insert(myAddr);
    secId++;

    linksU * myEntry = &(netState[myAddr]);
    myEntry->sId = secId;
    myEntry->links[_addr] = _metric;

    scheduleUpdate();
}

void LS::removeFlow(const Address &_nAddr, const std::string &_addr){
    nei.erase(_nAddr);
    neigTable.erase(_addr);

    changed.insert(myAddr);
    secId++;

    linksU * myEntry = &(netState[myAddr]);
    myEntry->sId = secId;
    myEntry->links.erase(_addr);

    scheduleUpdate();
}

void LS::addAddr(const std::string &_addr){
    myAddrSet.insert(_addr);

    secId++;

    linksU * myEntry = &(netState[myAddr]);
    myEntry->sId = secId;
    myEntry->links[_addr] = 0;

    scheduleUpdate();
}

void LS::removeAddr(const std::string &_addr){
    myAddrSet.erase(_addr);

    secId++;

    linksU * myEntry = &(netState[myAddr]);
    myEntry->sId = secId;
    myEntry->links.erase(_addr);

    scheduleUpdate();
}

void LS::setInfMetric(const unsigned short &inf){}

dmNxt LS::getChanges(){
    dmNxt ret(domain);

    TreeNode t = constructTree();
    for(TreeNodeIt it = t.chl.begin(); it != t.chl.end(); it++){
        ret.entries[(*it)->addr] = neigTable[(*it)->addr];
        addRecursive(ret.entries, neigTable[(*it)->addr], *it);
    }

    s2A tmp = ret.entries;

    for(s2AIt tIt = currentTable.begin(); tIt != currentTable.end(); tIt++){
        if(ret.entries[tIt->first] == tIt->second){
            ret.entries.erase(tIt->first);
        }
    }

    currentTable = tmp;

    return ret;
}

dmNxt LS::getAll() {
    dmNxt ret(domain);

    TreeNode t = constructTree();
    for(TreeNodeIt it = t.chl.begin(); it != t.chl.end(); it++){
        ret.entries[(*it)->addr] = neigTable[(*it)->addr];
        addRecursive(ret.entries, neigTable[(*it)->addr], *it);
    }

    currentTable = ret.entries;
    return ret;
}

void LS::handleMessage(cMessage *msg){
    if(msg->isSelfMessage()){
        //get Changes
        linksSt _entries = getChangedEntries ();

        //iterate all Neighbour
        for(neighMetricIt itN = nei.begin(); itN != nei.end(); itN++){
            //New Update to Neighbour
            LSUpdate * update = new LSUpdate(itN->first, domain);

            //Populate the update
            update->setEntries(_entries);

            parent->chSendUpdate(update);
        }

        changed.clear();
        scheduledUpdate = false;
    }
    delete msg;
}


void LS::scheduleUpdate(){
    if(!scheduledUpdate){
        scheduledUpdate = true;
        scheduleAt(1, new cMessage("Time2Update"));
    }
}



linksSt LS::getChangedEntries () {
    linksSt ret;
    for(sSetIt it = changed.begin(); it != changed.end(); it++){
        ret[*it] = netState[*it];
    }
    return ret;
}


TreeNode LS::constructTree() {
    TreeNode t(myAddr, 0);
    s2m added;
    added[myAddr] = 0;

    wMap waiting;
    s2m * links = &(netState[myAddr].links);
    for(s2mIt it = links->begin(); it !=links->end(); it++){
        waiting[it->first] = psT(&t, it->second);
    }


    while(!waiting.empty()){
        unsigned short min = UINT16_MAX;
        sList mins;

        for (wMapIt it = waiting.begin(); it != waiting.end(); it++){
            if(it->second.metric < min){
                min = it->second.metric;
                mins.clear();
            }
            if(it->second.metric == min){
                mins.push_back(it->first);
            }
        }

        while(!mins.empty()){
            string addr = mins.back();
            mins.pop_back();

            psT ps = waiting[addr];
            waiting.erase(addr);

            TreeNode * nt = new TreeNode(addr, ps.metric);
            ps.p->chl.insert(nt);

            added[addr] = ps.metric;

            links = &(netState[addr].links);

            for(s2mIt it = links->begin(); it !=links->end(); it++){
                string daddr = it->first;
                if(added.find(daddr) == added.end()){
                    wMapIt eI = waiting.find(daddr);
                    if(eI == waiting.end()){
                        waiting[daddr] = psT(nt, ps.metric + it->second);
                    } else if(eI->second.metric > ps.metric + it->second){
                        eI->second.metric = ps.metric + it->second;
                        eI->second.p = nt;
                    }
                }
            }
        }
    }

    return t;
}

void LS::addRecursive(s2A &ret, const Address &next, TreeNode * t) {
    for(TreeNodeIt it = t->chl.begin(); it != t->chl.end(); it++){
        ret[(*it)->addr] = next;
        addRecursive(ret, next, *it);
    }
}



} /* namespace DomainRouting */
