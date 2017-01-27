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
 * DV.cc
 *
 *  Created on: Mar 23, 2015
 *      Author: gaixas1
 */

#include "DIF/Routing/DomainRouting/DV/DV.h"
#include "DIF/Routing/DomainRouting/Routing.h"

namespace DMRnmsDV {

using namespace DMRnms;
using namespace std;

DVUpdate::DVUpdate(const Address &_addr, const string &_domain)
    :RoutingUpdate(_addr, _domain){}

void DVUpdate::addEntry(rtEntry _e) {
    entries.push_back(_e);
}

entriesIt DVUpdate::entriesBegin() {
    return entries.begin();
}

entriesIt DVUpdate::entriesEnd() {
    return entries.end();
}


DV::DV(Routing * parent, const Address &_nAddr, const string &_domain, const string &_addr)
    :rModule(parent, _nAddr,_domain, _addr) {
    infMetric = 32;
    scheduledUpdate = false;
    myAddrSet.insert(_addr);
}

bool DV::processUpdate(RoutingUpdate * update){
    // Cast update to known type
    DVUpdate * up = dynamic_cast<DVUpdate*>(update);
    if(up == NULL) { return false; }

    // Check I'm not the src
    Address src = up->getSource();
    if(src == myNAddress){ return false; }


    for(entriesIt newE = up->entriesBegin(); newE!= up->entriesEnd(); newE++){
        // Not consider entries to myself or my aliasses
        if(myAddrSet.find(newE->addr) != myAddrSet.end()){ continue; }

        tEntry * oldE = &table[newE->addr];
        bool entryChanged = false;

        if(oldE->addr == src){
            if(oldE->metric == newE->metric){
                oldE->metric = newE->metric;
            }
        } else if(oldE->metric >= newE->metric){
            oldE->addr = src;
            oldE->metric = newE->metric;
            entryChanged = true;
        }

        if(oldE->metric >= infMetric){
            changes[newE->addr] = Address();
            table.erase(newE->addr);
        } else if(entryChanged){
            changes[newE->addr] = src;
            changedEntries.insert(newE->addr);
        }
    }

    if(! changes.empty()) {
        scheduleUpdate();
        return true;
    } else {
        return false;
    }
}

void DV::addFlow(const Address &_nAddr, const std::string &_addr, const unsigned short &_metric){
    nei[_nAddr] = _metric;

    tEntry * oldE = &table[_addr];
    bool entryChangedDst = false, entryChanged = false;
    if(oldE->addr == _nAddr){
        if(oldE->metric != _metric){
            oldE->metric = _metric;
            entryChanged = true;
        }
    } else if (oldE->metric >= _metric) {
        oldE->addr = _nAddr;
        oldE->metric = _metric;
        entryChanged = true;
        entryChangedDst = true;
    }

    if(oldE->metric >= infMetric){
        changes[_addr] = Address();
        table.erase(_addr);
    } else {
        if(entryChanged){
            changedEntries.insert(_addr);
        }
        if(entryChangedDst){
            changes[_addr] = _nAddr;
        }
    }

    scheduleUpdate();
}

void DV::removeFlow(const Address &_nAddr, const std::string &_addr){
    nei.erase(_nAddr);

    for(tTableIt it = table.begin(); it != table.end();){
        tEntry * oldE = &it->second;
        tTableIt actIt = it++;

        if(oldE->addr == _nAddr){
            table.erase(actIt);
            changedEntries.insert(_addr);
            changes[_addr] = Address();
        }
    }

    scheduleUpdate();
}

void DV::addAddr(const std::string &_addr){
    myAddrSet.insert(_addr);
}

void DV::removeAddr(const std::string &_addr){
    myAddrSet.erase(_addr);
}

void DV::setInfMetric(const unsigned short &inf){
    infMetric = inf;
}

dmNxt DV::getChanges(){
    dmNxt ret(domain, changes);
    changes.clear();
    return ret;
}

dmNxt DV::getAll() {
    dmNxt ret(domain);

    for(tTableIt it = table.begin(); it != table.end(); it++){
        if(it->second.metric < infMetric){
            ret.entries[it->first] = it->second.addr;
        } else {
            ret.entries[it->first] = Address();
        }
    }

    changes.clear();
    return ret;
}

void DV::handleMessage(cMessage *msg){
    if(msg->isSelfMessage()){

        //iterate all Neighbour
        for(neighMetricIt itN = nei.begin(); itN != nei.end(); itN++){
            //New Update to Neighbour
            DVUpdate * update = new DVUpdate(itN->first, domain);

            //Populate the update
            for(sSetIt cIt = changedEntries.begin(); cIt != changedEntries.end(); cIt++){
                tEntry * rt = &table[*cIt];
                update->addEntry(
                        rtEntry(*cIt, rt->metric + itN->second)
                        );
            }

            //Add our entries
            update->addEntry(rtEntry(myAddr, itN->second));
            for(sSetIt mIt = myAddrSet.begin(); mIt != myAddrSet.end(); mIt++){
                update->addEntry(rtEntry(*mIt, itN->second));
            }

            parent->chSendUpdate(update);
        }

        changedEntries.clear();
        scheduledUpdate = false;
    }
    delete msg;
}


void DV::scheduleUpdate(){
    if(!scheduledUpdate){
        scheduledUpdate = true;
        scheduleAt(1, new cMessage("Time2Update"));
    }
}

} /* namespace DomainRouting */
