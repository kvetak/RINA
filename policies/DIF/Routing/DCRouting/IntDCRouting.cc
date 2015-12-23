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


#include "IntDCRouting.h"

namespace NSPSimpleDC {

    linkId::linkId():
            type(-1), pod(-1), src(-1), dst(-1){}
    linkId::linkId(const int &_type, const int &_pod, const int &_src, const int &_dst):
            type(_type), pod(_pod), src(_src), dst(_dst){}

    bool linkId::operator<(const linkId & o) const {
        if(type < o.type) { return true; }
        if(type > o.type) { return false; }

        if(src < o.src) { return true; }
        if(src > o.src) { return false; }

        if(dst < o.dst) { return true; }
        return false;
    }

    bool linkId::operator==(const linkId & o) const {
        return type==o.type && src==o.src && dst==o.dst;
    }


    linkInfo::linkInfo():
        link(), status(false), timestamp(simTime()){}

    linkInfo::linkInfo(const linkId &_link, const bool &_status, const simtime_t &_timestamp):
                link(_link), status(_status), timestamp(_timestamp){}

    LinksUpdate * LinksUpdate::toDst(Address dst) {
        LinksUpdate * ret = new LinksUpdate();
        ret->dstAddr = dst;
        ret->linksStatus = linksStatus;
        return ret;
    }

    void IntDCRouting::handleMessage(cMessage * msg) {
        if(msg == clean) {
            if(linksOk.empty()) {
                clean = nullptr;
                delete msg;
            } else {
                scheduleAt(simTime() + expiration, clean);
            }
        } else if(msg == sched) {
            LinksUpdate update;
            for(const auto & linkData : myLinks) {
                if(!linkData.second.status) {
                    update.linksStatus.push_back(linkData.second);
                }
            }
            for(const auto & linkData : linksOk) {
                if(!linkData.second.status) {
                    update.linksStatus.push_back(linkData.second);
                }
            }
            for(const auto & linkData : linksKo) {
                if(!linkData.second.status) {
                    update.linksStatus.push_back(linkData.second);
                }
            }

            if(!update.linksStatus.empty()) {
                for(const auto & n : activeNeighbours) {
                    sendUpdate(update->toDst(n));
                }
            }

            sched = nullptr;
            delete msg;
        } else  if(msg == start) {
            LinksUpdate update;
            for(const auto & linkData : myLinks) {
                if(!linkData.second.status) {
                    update.linksStatus.push_back(linkData.second);
                }
            }
            if(!update.linksStatus.empty()) {
                for(const auto & n : activeNeighbours) {
                    sendUpdate(update->toDst(n));
                }
            }

            start = nullptr;
            delete msg;
        } else {
            cerr << "Unknown message" << endl;
            delete msg;
        }
    }

    void IntDCRouting::onPolicyInit() {
        Im = DCAddr(par("myAddr").stdstringValue());

        clean = nullptr;
        start = new cMessage("Start updates");
        sched = nullptr;

        pods = par("pods").longValue();
        torXpod = par("torXpod").longValue();
        fabricXpod = par("fabricXpod").longValue();
        spineXfabric = par("spineXfabric").longValue();
        updateWait = par("updateWait").doubleValue();
        expiration = par("expiration").doubleValue();
        double starttime = par("starttime").doubleValue();

        scheduleAt(simTime() + starttime, start);

        startMyLinks();
    }

    bool IntDCRouting::processUpdate(IntRoutingUpdate * update) {
        LinksUpdate * u = dynamic_cast<LinksUpdate*>(update);
        if(u == nullptr) {
            cerr << "Invalid update message received" << endl;
            return false;
        }

        bool changes = false;

        for(const auto l : u->linksStatus) {
            if(myLinks.find(l.link) != myLinks.end()) { continue; }

            if(l.status) {
                if(linksKo.find(l.link) != linksKo.end()) {
                    linkInfo & tI = linksKo[l.link];
                    if(tI.timestamp < l.timestamp) {
                        linksOk[l.link] = l;
                        linksKo.erase(l.link);
                        changes = true;
                    }
                } else  if(l.timestamp > simTime() + expiration) {
                    linkInfo & tI = linksOk[l.link];
                    if(tI.timestamp < l.timestamp) {
                        tI.timestamp = l.timestamp;
                        changes = true;
                    }
                }
            } else {
                if(linksOk.find(l.link) != linksOk.end()) {
                    linkInfo & tI = linksOk[l.link];
                    if(tI.timestamp < l.timestamp) {
                        linksKo[l.link] = l;
                        linksOk.erase(l.link);
                        changes = true;
                    }
                } else {
                    linkInfo & tI = linksKo[l.link];
                    if(tI.timestamp < l.timestamp) {
                        tI.timestamp = l.timestamp;
                        changes = true;
                    }
                }
            }
        }

        if(changes) {
            scheduleUpdate();
        }
        scheduleClean();
    }

    void IntDCRouting::insertNeighbour(const Address &addr, const std::string &dst) {
        activeNeighbours.insert(addr);
        activeNeigh(dst);
    }

    void IntDCRouting::removeNeighbour(const Address &addr, const std::string &dst) {
        activeNeighbours.erase(addr);
        inactiveNeigh(dst);
    }

    void IntDCRouting::scheduleUpdate() {
        if(start == nullptr && sched == nullptr) {
            sched = new cMessage("Scheduled update");
            scheduleAt(simTime()+updateWait, sched);
        }
    }
    void IntDCRouting::scheduleClean() {
        if(clean == nullptr) {
            clean = new cMessage("Scheduled clean");
            scheduleAt(simTime()+expiration, clean);
        }
    }
}
