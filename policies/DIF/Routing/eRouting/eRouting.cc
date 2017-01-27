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

#include "DIF/Routing/eRouting/eRouting.h"

Register_Class(eRouting);

void eRouting::onPolicyInit() {
    cacheTime = par("cacheTime").doubleValue();
    updateDelay = par("updateDelay").doubleValue();

    updateTimer = new cMessage("Send Update");
    clearCacheTimer = new cMessage("Clear Cache");
    if(cacheTime > 0.0) { scheduleAt(simTime()+cacheTime, clearCacheTimer); }
}

void eRouting::finish() {
    IntRouting::finish();

    cancelAndDelete(clearCacheTimer);
    cancelAndDelete(updateTimer);

    if(par("printAtEnd").boolValue()) {

        cout << hex;
        cout << "eRouting at "<< myAddress<<endl;
        cout << "  Registered neighbours :"<<endl;
        for(auto & k : links) {
            cout <<"    "
                    << k.second.dst << "["<<(k.first)<<"]"
                    << " status "<< (k.second.status.status? "ON":"OFF")
                    << " - seq# "<< to_string(k.second.status.s)
                    << " / At "<< k.second.status.t
                    << endl;
        }
        cout << "  Stored info :"<<endl;
        for(auto & k : linksInfo) {
            cout <<"    "
                    << "["<<(k.first)<<"]"
                    << " status "<< (k.second.status? "ON":"OFF")
                    << " - seq# "<< to_string(k.second.s)
                    << " / At "<< k.second.t
                    << endl;
        }
        cout << dec;
    }
}

bool eRouting::processUpdate(IntRoutingUpdate * update) {
    bool changes = false;

    if(LinkHello * u = dynamic_cast<LinkHello*>(update)) {
        update_t & c = links[u->link].status;
        c.status = true;
        c.t = simTime();

        if(c.s < u->s) { c.s = u->s; }

        for(auto & k : links) {
            if(k.first == u->link) { continue; }
            k.second.pending[u->link] = c;
        }
        if(! updateTimer->isScheduled()) { scheduleAt(simTime()+updateDelay, updateTimer); };

    } else if(statusUpdate * u = dynamic_cast<statusUpdate*>(update)) {
        // received status update
        bool needUpdate = false;

        simtime_t tLimit = simTime() - cacheTime;
        for(auto & s : u->info) {
            const elink_t & link = s.first;
            update_t & ne = s.second; // new status

            if(links.find(link) != links.end()) {
                simtime_t refLimit = simTime() - cacheTime/2.0;
                nei_info & ce = links[link]; // current status -- no lo que sale ahora!!!!!!!!
                // Update of owned link
                if(ce.status.status != ne.status && ce.status.t < refLimit) {
                    // Received old update of owned link with incorrect status and last update more than cacheTime/2 ago -> refresh link info
                    // refresh(link);
                }
                continue;
            }
            if(s.second.s <= 1 && s.second.status) { continue; } // First update of link in ON
            if(s.second.status && s.second.t < tLimit) { continue; } // Old ON update


            update_t & ce = linksInfo[link]; // current status -- no lo que sale ahora!!!!!!!!

            if(ne.s < ce.s) { continue; } // Current stored seq# bigger


            bool addToUpdates = false;
            if(ce.s == 0) {
                // Currently not stored update!! -> New info
                addToUpdates = true;
                ce = ne;
                if(!ne.status) { changes = true; }
            } else if( ce.s == ne.s ) {
                // Same seq# as already stored -> check both status == and update internal only
                if(ce.status != ne.status) { error("Received same seq# for ON and OFF messages for the same link!!!!"); }
                ce = ne;
            } else {
                // Newer seq# -> Changed info or refresh?
                if(ce.status != ne.status) { changes = true; }
                ce = ne;
                addToUpdates = true;
            }
            if(addToUpdates) {
                for(auto & k : links) {
                    if(k.first == link) { continue; } // Do not inform a link update using the same link (should not append anyway)
                    k.second.pending[link] = ce;
                }
                needUpdate = true;
            }
        }


        if(needUpdate && ! updateTimer->isScheduled()) { scheduleAt(simTime()+updateDelay, updateTimer); };
    }
    return changes;
}

void eRouting::handleMessage(cMessage *msg) {
    if(msg == updateTimer) {
        sendUpdates();
    } else if ( msg == clearCacheTimer ) {
        //Clear cache
        vector<elink_t> old;
        simtime_t oT = simTime()-cacheTime;
        for(auto & l : linksInfo) {
            if(l.second.status && l.second.t < oT) { old.push_back(l.first); }
        }
        for(auto & l : old) { linksInfo.erase(l); }
        scheduleAt(simTime()+cacheTime, clearCacheTimer);
    }
}


void eRouting::registerLink(const elink_t & e, const Address & n) {
    links[e].dst = n;
    links[e].status.status = false;
}

void eRouting::onLink(const elink_t & e) {
    update_t & c = links[e].status;
    c.status = true;
    c.s++;

    //Add all KO links to info to update to nei

    LinkHello * l = new LinkHello();
    l->setDestination(links[e].dst);
    l->link = e;
    l->s = c.s;
    sendUpdate(l);
}

void eRouting::offLink(const elink_t & e) {
    nei_info & n = links[e];
    update_t & c = n.status;
    c.status = false;
    c.s++;
    c.t = simTime();

    for(auto &  k : links) {
        if(k.first == e) { continue; }
        k.second.pending[e] = c;
    }

    if(! updateTimer->isScheduled()) { scheduleAt(simTime()+updateDelay, updateTimer); };
}

void eRouting::sendUpdates() {
    for(auto & k : links) {
        if(! k.second.status.status) { continue; }
        if(k.second.pending.empty()) { continue; }

        statusUpdate * u = new statusUpdate();
        u->setDestination(k.second.dst);
        u->info = k.second.pending;
        k.second.pending.clear();

        sendUpdate(u);
    }

}


nodesStatus eRouting::getProblems(){
    nodesStatus ret;
    for(auto & k : links) {
        if(!k.second.status.status) { ret.ownFailures.push_back(k.first); }
    }
    for(auto & k : linksInfo) {
        if(!k.second.status) { ret.othersFailures.push_back(k.first); }
    }
    return ret;
}
