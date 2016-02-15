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


#include "RuleExceptionsRT.h"

namespace RERtDC {



    nodeNeig::nodeNeig() :
        status(false), timestamp(-1), tempUpdate(nullptr) {}

    void nodeNeig::init(DCAddr _n_addr, Address _addr) {
        n_addr = _n_addr;
        addr = _addr;
        status = false;
        timestamp = -1;
        tempUpdate = new LinksUpdate(addr);
    }

    LinksUpdate * nodeNeig::popUpdate() {
        LinksUpdate * t = tempUpdate;
        tempUpdate = new LinksUpdate(addr);
        return t;
    }

    void nodeNeig::addInfo(const linkInfo & li) {
        tempUpdate->addOrReplaceUpdate(li);
    }

    void nodeNeig::addInfo(const vector<linkInfo> & lli) {
        for(const linkInfo & li : lli) {
            tempUpdate->addOrReplaceUpdate(li);
        }
    }

    bool nodeNeig::emptyUpdate() {
        return tempUpdate->empty();
    }

    RuleExceptionsRT::RuleExceptionsRT() {
        myNeis = nullptr;
    }

    RuleExceptionsRT::~RuleExceptionsRT() {
        if(myNeis != nullptr) { delete[] myNeis; }
    }

    portId RuleExceptionsRT::getNeiId(Address addr) {
        return getNeiId(DCAddr(addr.getIpcAddress().getName()));
    }

    void RuleExceptionsRT::onPolicyInit() {
        Im = DCAddr(getModuleByPath("^")->par("ipcAddress").stringValue());

        nPod = par("nPod").longValue();
        nTor = par("nTor").longValue();
        nFab = par("nFab").longValue();
        nSpine = par("nSpine").longValue();
        nEdgeP = par("nEdgeP").longValue();

        startMyNeis();

        clean = new cMessage("Cleaning ok info");
        start = new cMessage("Start updates");

        oldAfter = par("oldAfter").longValue();
        expiresAfter = par("expiresAfter").longValue();
        double starttime = par("starttime").doubleValue();

        if(starttime < 0) { starttime = 0; }
        if(oldAfter < 0) { oldAfter = 0; }
        if(expiresAfter < oldAfter) { expiresAfter = oldAfter; }

        scheduleAt(simTime() + starttime, start);
        scheduleAt(simTime() + starttime + expiresAfter/1000.0, clean);
    }

    void RuleExceptionsRT::insertNeighbour(const Address &addr, const DCAddr &dst) {
        Enter_Method_Silent();
        portId p = getNeiId(dst);
        if(p >= myNeisSize) {
            cerr << "Invalid neighbour "<< dst << " added at " << Im << endl;
            endSimulation();
            return;
        }

        auto & n = myNeis[p];
        n.timestamp = simTime().dbl()*1000;

        if(n.status) { return; }


        linkInfo li(linkId(Im, dst), true, n.timestamp);
        n.status = true;
        if(start == nullptr) {
            addToUpdates(li);
            for (auto &ls : linksStatus) {
                n.addInfo(ls.second);
            }
            Update();
        } else {
            linksStatus[li.link] = li;
        }
    }

    void RuleExceptionsRT::removeNeighbour(const Address &addr, const DCAddr &dst) {
        Enter_Method_Silent();
        portId p = getNeiId(dst);
        if(p >= myNeisSize) {
            cerr << "Invalid neighbour "<< dst << " removed at " << Im << endl;
            endSimulation();
            return;
        }

        auto & n = myNeis[p];
        n.timestamp = simTime().dbl()*1000;

        if(!n.status) { return; }

        linkInfo li(linkId(Im, dst), false, n.timestamp);
        n.status = false;
        if(start == nullptr) {
            addToUpdates(li);
            for (auto &ls : linksStatus) {
                n.addInfo(ls.second);
            }
            Update();
        } else {
            linksStatus[li.link] = li;
        }

    }

    bool RuleExceptionsRT::processUpdate(IntRoutingUpdate * update) {
        LinksUpdate * u = dynamic_cast<LinksUpdate*>(update);
        if(u == nullptr) {
            cerr << "Invalid update message received" << endl;
            endSimulation();
            return false;
        }

        bool changes = false;
        long tnow = simTime().dbl()*1000;
        long lold = tnow - oldAfter;
        long texpiration = tnow + expiresAfter;

        for(auto & l : u->linksStatus) {

            if(l.link.src == DCAddr()) {
                cerr << "At " << Im << ", received invalid link info from "<< u->getSource() << endl;
                endSimulation();
                return false;
            }

            if(l.link.src == Im || l.link.dst == Im) {
                portId p = myNeisSize;
                if(l.link.src == Im) { p = getNeiId(l.link.dst); }
                else { p = getNeiId(l.link.src); }

                if(p < myNeisSize) {
                    auto & n = myNeis[p];
                    if(n.timestamp < l.timestamp && l.status == n.status) {
                        //Updated timestamp for own link?? -> syncronize
                        n.timestamp = l.timestamp;
                        n.status = l.status;

                        addToUpdates(l);
                    } else if(!l.status && n.status && n.timestamp < texpiration) {
                        n.timestamp = tnow;
                        l.timestamp = tnow;
                        l.status = true;

                        //Re-Ok if received invalid own link-info
                        addToUpdates(l);
                    }
                }
                continue;
            }

            linkInfo & ls = linksStatus[l.link];
            ls.link = l.link;

            if(ls.timestamp > l.timestamp) { continue; }

            if(ls.timestamp == l.timestamp ) {
                if(ls.status && !l.status) {

                    ls.status = false;

                    //Received ko info with same timestamp as ok info
                    addToUpdates(l);
                    changes = true;
                }
                continue;
            }

            ls.timestamp = l.timestamp;
            if(l.status) {
                if(ls.status) {
                    if(l.timestamp  > lold) {
                        //Received ok info with newer timestamp, within propagation time
                        addToUpdates(l);
                    }
                } else {
                    ls.status = true;
                    //Received ok info of currently ko node
                    addToUpdates(l);
                    changes = true;
                }
            } else {
                if(ls.status) {
                    ls.status = false;
                    //Received ko info of currently ok node
                    addToUpdates(l);
                    changes = true;
                } else {
                    //Received ko info with newer timestamp
                    addToUpdates(l);
                }
            }
        }

        if(start == nullptr) { Update(); }
        return changes;
    }

    void RuleExceptionsRT::finish() {
        if(!par("printAtEnd").boolValue()){ return; }

        cout << "Routing at "<< Im << endl;

        cout << "\tMy links status:" <<endl;
        for(portId i = 0; i < myNeisSize; i++) {
            auto & n = myNeis[i];
            cout << "\t\t" << "Dst : " << n.n_addr;
            if(n.status) {
                cout << " | correct";
            } else {
                cout << " | failure";
            }
            cout << "   ("<<n.timestamp<<")" <<endl;
        }

        cout << "\tKnown failures:" <<endl;
        for(auto & ls : linksStatus) {
            if(!ls.second.status) {
                cout << "\t\t" << ls.first.src << " -> " << ls.first.dst;
                cout << " | Down at " << ls.second.timestamp << endl;
            }
        }
        cout << endl;

    }


    void RuleExceptionsRT::handleMessage(cMessage * msg) {
        if(msg == clean) {
            cleanOK();
            scheduleAt(simTime()+expiresAfter/1000.0, msg);
        } else if(msg == start) {
            delete start;
            start = nullptr;
            FirstUpdate();
        } else {
            cerr << "Unknown message" << endl;
            delete msg;
            endSimulation();
        }
    }


    void RuleExceptionsRT::cleanOK() {
        long lim = simTime().dbl()*1000 - expiresAfter;
        auto it = linksStatus.begin();
        while(it != linksStatus.end()) {
            if(it->second.status && it->second.timestamp < lim) {
                it = linksStatus.erase(it);
            } else { it++; }
        }
    }

    void RuleExceptionsRT::FirstUpdate() {
        vector<linkInfo> myErrors;
        for (portId i = 0; i< myNeisSize; i++) {
            auto &n = myNeis[i];
            if(!n.status) {
                myErrors.push_back(linkInfo(linkId(Im, n.n_addr), false, n.timestamp));
            }
        }

        for (portId i = 0; i< myNeisSize; i++) {
            auto &n = myNeis[i];
            n.addInfo(myErrors);
            if(n.status && !n.emptyUpdate()) {
                LinksUpdate * up = n.popUpdate();
                sendUpdate(up);
            }
        }
    }
    void RuleExceptionsRT::Update() {
        for (portId i = 0; i< myNeisSize; i++) {
            auto &n = myNeis[i];
            if(n.status && !n.emptyUpdate()) {
                LinksUpdate * up = n.popUpdate();
                sendUpdate(up);
            }
        }
    }

    void RuleExceptionsRT::addToUpdates(linkInfo li) {
        linksStatus[li.link] = li;
        for (portId i = 0; i< myNeisSize; i++) {
            auto &n = myNeis[i];
            n.addInfo(li);
        }
        //cout << "Added update at "<< Im << endl;
    }



    bool RuleExceptionsRT::preparseFailures() {
        int foundFails = 0;
        vector<linkId> failures;

        for(auto & ls : linksStatus) {
            if(!ls.second.status) {
                foundFails++;
                auto & lId = ls.first;
                failures.push_back(lId);
            }
        }

        if(foundFails <= 0) { return false; }

        vecuchar podProblemsCount(nPod, 0);
        vecuchar spineProblemsCount(nFab, 0);

        for(auto & f : failures) {
            problemsUp[f.src].insert(f.dst);
            problemsDown[f.dst].insert(f.src);

            if(f.src.type == TYPEID_ToR) { podProblemsCount[f.src.a]++; }
            if(f.src.type == TYPEID_Fabric) { spineProblemsCount[f.src.b]++; }
            if(f.src.type == TYPEID_Spine) { spineProblemsCount[f.src.a]++; }
        }


        Addr2setDCAddrIt it = problemsUp.begin();
        while(it != problemsUp.end()) {
            const DCAddr & n = it->first;
            unsigned int s = it->second.size();
            bool ers = false;
            switch (n.type){
                case TYPEID_ToR:
                    if(s == nFab){ deadToR[n.a].insert(n.b); ers = true; }
                    break;
                case TYPEID_Fabric:
                    if(s == nSpine){ deadSpineFabric[n.b].insert(n.a); ers = true; }
                    break;
                case TYPEID_Spine:
                    if(s == nEdgeP){ deadSpineUp[n.a].insert(n.b); ers = true; }
                    break;
                default : ers = true;
            }
            if(ers) { it = problemsUp.erase(it); }
            else { it++; }
        }
        it = problemsDown.begin();
        while(it != problemsDown.end()) {
            const DCAddr & n = it->first;
            unsigned int s = it->second.size();
            bool ers = false;
            switch (n.type){
                case TYPEID_Fabric:
                    if(s == nTor){ deadPodFabric[n.b].insert(n.a); ers = true; }
                    break;
                case TYPEID_Spine:
                    if(s == nPod){ deadSpineDown[n.a].insert(n.b); ers = true; }
                    break;
                case TYPEID_Edge:
                    if(s == nSpine){ deadEdge[n.b].insert(n.a); ers = true; }
                    break;
                default : ers = true;
            }
            if(ers) { it = problemsDown.erase(it); }
            else { it++; }
        }

        return true;
    }

    void RuleExceptionsRT::clearParsedFailures() {
        problemsUp.clear();
        problemsDown.clear();

        deadToR.clear();
        deadPodFabric.clear();
        deadSpineFabric.clear();
        deadSpineDown.clear();
        deadSpineUp.clear();
        deadEdge.clear();
    }
}
