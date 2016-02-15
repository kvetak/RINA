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


#include "GDC_RT_iface.h"

namespace GDC {
    using namespace std;

    nodeNeig::nodeNeig() :
        status(false), timestamp(-1), tempUpdate(nullptr) {}

    void nodeNeig::init(const Addr & _n_addr, const Address & _addr) {
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

    iface_RT::iface_RT() {
        myNeis = nullptr;
    }

    iface_RT::~iface_RT() {
        if(myNeis != nullptr) { delete[] myNeis; }
    }

    ushort iface_RT::getNeiId(const Address & addr) {
        return getNeiId(Addr(addr.getIpcAddress().getName()));
    }

    void iface_RT::onPolicyInit() {
        Im = Addr(getModuleByPath("^")->par("ipcAddress").stringValue());

        nSpines = par("nSpines").longValue();
        nPod = par("nPod").longValue();
        nEdgeP = par("nEdgeP").longValue();
        nFab = par("nFab").longValue();
        nTor = par("nTor").longValue();
        nEdge = par("nEdge").longValue();

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

    void iface_RT::insertNeighbour(const Address &addr, const Addr &dst) {
        Enter_Method_Silent();
        ushort p = getNeiId(dst);
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

    void iface_RT::removeNeighbour(const Address &addr, const Addr &dst) {
        Enter_Method_Silent();
        ushort p = getNeiId(dst);
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

    bool iface_RT::processUpdate(IntRoutingUpdate * update) {
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

            if(l.link.src == Addr()) {
                cerr << "At " << Im << ", received invalid link info from "<< u->getSource() << endl;
                endSimulation();
                return false;
            }

            if(l.link.src == Im || l.link.dst == Im) {
                ushort p = myNeisSize;
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

    void iface_RT::finish() {
        if(!par("printAtEnd").boolValue()){ return; }

        cout << "Routing at "<< Im << endl;

        cout << "\tMy links status:" <<endl;
        for(ushort i = 0; i < myNeisSize; i++) {
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


    void iface_RT::handleMessage(cMessage * msg) {
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


    void iface_RT::cleanOK() {
        long lim = simTime().dbl()*1000 - expiresAfter;
        auto it = linksStatus.begin();
        while(it != linksStatus.end()) {
            if(it->second.status && it->second.timestamp < lim) {
                it = linksStatus.erase(it);
            } else { it++; }
        }
    }

    void iface_RT::FirstUpdate() {
        vector<linkInfo> myErrors;
        for (ushort i = 0; i< myNeisSize; i++) {
            auto &n = myNeis[i];
            if(!n.status) {
                myErrors.push_back(linkInfo(linkId(Im, n.n_addr), false, n.timestamp));
            }
        }

        for (ushort i = 0; i< myNeisSize; i++) {
            auto &n = myNeis[i];
            n.addInfo(myErrors);
            if(n.status && !n.emptyUpdate()) {
                LinksUpdate * up = n.popUpdate();
                sendUpdate(up);
            }
        }
    }
    void iface_RT::Update() {
        for (ushort i = 0; i< myNeisSize; i++) {
            auto &n = myNeis[i];
            if(n.status && !n.emptyUpdate()) {
                LinksUpdate * up = n.popUpdate();
                sendUpdate(up);
            }
        }
    }

    void iface_RT::addToUpdates(linkInfo li) {
        linksStatus[li.link] = li;
        for (ushort i = 0; i< myNeisSize; i++) {
            auto &n = myNeis[i];
            n.addInfo(li);
        }
    }



    bool iface_RT::preparseFailures() {
        clearParsedFailures();

        if(linksStatus.empty()) { return false; }

        for(auto & ls : linksStatus) {
            if(!ls.second.status) {
                parseFailure(ls.first.src, ls.first.dst);
                parseFailure(ls.first.dst, ls.first.src);
            }
        }
        return true;
    }

    void iface_RT::parseFailure(const Addr & src, const Addr & dst) {
        if(src.a == 0) {
            setAddr & fails = R0Fails[src];
            fails.insert(dst);
            R0GroupedFailures[Im.b][dst.a].insert(dst.b);
            if((ushort)fails.size() >= nFab*(nPod+nEdgeP)) {
                R0Dead.insert(src);
            }
        } else if(src.b <= nFab){
            if(dst.a == 0) {
                setAddr & fails = R1FailsUp[src];
                fails.insert(dst);
                if(fails.size() == nSpines) {
                    R1DeadUp.insert(src);
                    setuchar & ds = groupDeadsUp[src.a];
                    ds.insert(src.b);
                    if(ds.size() == nFab) { unreachGroup.insert(src.a); }
                }
            } else {
                setAddr & fails = R1FailsDown[src];
                fails.insert(dst);
                if(fails.size() == nTor) {
                    R1DeadDown.insert(src);
                }
            }
        } else {
            setAddr & fails = R2Fails[src];
            fails.insert(dst);
            R2GroupedFailures[src.a][src.b].insert(dst.b);
            if(fails.size() >= nFab) {
                R2Dead.insert(src);
            }
            groupProb.insert(src.a);
        }
    }

    void iface_RT::clearParsedFailures() {
        R0Fails.clear();
        R1FailsUp.clear();
        R1FailsDown.clear();
        R2Fails.clear();

        R0Dead.clear();
        R1DeadUp.clear();
        R1DeadDown.clear();
        R2Dead.clear();

        groupDeadsUp.clear();
        groupProb.clear();
        unreachGroup.clear();
    }

    bool iface_RT::fullSet(const setuchar & sa, const setuchar &sb, const ushort size) {
        ushort sza = sa.size();
        ushort szb = sb.size();
        if(sza + szb < size ) { return false; }
        if(sza == 0 || szb == 0) { return true; }
        setuchar sj = sa;
        sj.insert(sb.begin(), sb.end());
        return sj.size() >= size;
    }
    bool iface_RT::fullSet(const setAddr & sa, const setAddr &sb, const ushort size) {
        ushort sza = sa.size();
        ushort szb = sb.size();
        if(sza + szb < size ) { return false; }
        if(sza == 0 || szb == 0) { return true; }
        setAddr sj = sa;
        sj.insert(sb.begin(), sb.end());
        return sj.size() >= size;
    }

}
