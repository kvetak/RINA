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


#include "DIF/Routing/DCRouting/IntDCRouting.h"

namespace NSPSimpleDC {

    linkId::linkId():
            src(DCAddr()), dst(DCAddr()){}
    linkId::linkId(const DCAddr &_src, const DCAddr &_dst) {
        if(_src.type < _dst.type) {
            src =_src;
            dst =_dst;
        } else {
            src =_dst;
            dst =_src;
        }
    }

    bool linkId::operator<(const linkId & o) const {
        if(src < o.src) { return true; }
        if(o.src < src) { return false; }
        if(dst < o.dst) { return true; }

        return false;
    }

    bool linkId::operator==(const linkId & o) const {
        return src==o.src && dst==o.dst;
    }

    bool linkId::operator!=(const linkId & o) const {
        return src!=o.src || dst!=o.dst;
    }


    linkInfo::linkInfo():
        link(), status(false), timestamp(-1){}

    linkInfo::linkInfo(const linkId &_link, const bool &_status, const simtime_t &_timestamp):
                link(_link), status(_status), timestamp(_timestamp){}

    LinksUpdate * LinksUpdate::toDst(Address dst) {
        LinksUpdate * ret = new LinksUpdate();
        ret->dstAddr = dst;
        ret->linksStatus = linksStatus;
        return ret;
    }


    tableNode::tableNode() : d(99) {}
    tableNode::tableNode(const linkId * n) : d(1) {
        L.insert(n);
    }

    void tableNode::insert (set<const linkId *> Ls) {
        L.insert(Ls.begin(), Ls.end());
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
            for(const auto & linkData : linksOk) {
                if(linkData.second.link.src == DCAddr()) {
                    cerr << "Invalid link in ok list" << endl;
                    continue;
                }
                update.linksStatus.push_back(linkData.second);
            }
            for(const auto & linkData : linksKo) {
                if(linkData.second.link.src == DCAddr()) {
                    cerr << "Invalid link in ko list" << endl;
                    continue;
                }
                update.linksStatus.push_back(linkData.second);
            }

            if(!update.linksStatus.empty()) {
                for(const auto & n : activeNeighbours) {
                    sendUpdate(update.toDst(n));
                }
            }

            sched = nullptr;
            delete msg;
        } else  if(msg == start) {
            LinksUpdate update;
            for(const auto & linkData : linksKo) {
                if(linkData.second.link.src == DCAddr()) {
                    cerr << "Start - Invalid link in ko list" << endl;
                    continue;
                }
                update.linksStatus.push_back(linkData.second);
            }

            if(!update.linksStatus.empty()) {
                for(const auto & n : activeNeighbours) {
                    sendUpdate(update.toDst(n));
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

        string myAddr = getModuleByPath("^")->par("ipcAddress").stringValue();
        Im = DCAddr(myAddr);

        clean = nullptr;
        start = new cMessage("Start updates");
        sched = nullptr;

        pods = par("pods").longValue();
        torXpod = par("torXpod").longValue();
        fabricXpod = par("fabricXpod").longValue();
        spineXfabric = par("spineXfabric").longValue();
        edgeSets = par("edgeSets").longValue();
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

       // cout << "I'm " << Im << ", received update from "<< u->getSource() <<endl;

        bool changes = false;

        for(const auto l : u->linksStatus) {
            auto ml = myLinks.find(l.link);
            if(ml != myLinks.end()) {
                if(l.status == false
                        && ml->second.status
                        && ml->second.timestamp < (simTime()-expiration)) {
                    ml->second.timestamp = simTime();
                    changes = true;
                }
                continue;
            }

            if(l.link.src == DCAddr(-1,0,0)) {
                cerr << "At " << Im << ", received invalid link info from "<< u->getSource() << endl;
                continue;
            }

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
                        tI.link = l.link;
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
                        tI.link = l.link;
                        tI.timestamp = l.timestamp;
                        changes = true;
                    }
                }
            }
        }

        scheduleClean();

        if(changes) {
            scheduleUpdate();
            return true;
        } else {
            return false;
        }
    }

    void IntDCRouting::insertNeighbour(const Address &addr, const DCAddr &dst) {
        Enter_Method_Silent();
        activeNeighbours.insert(addr);
        activeNeigh(dst);
    }

    void IntDCRouting::removeNeighbour(const Address &addr, const DCAddr &dst) {
        Enter_Method_Silent();
        activeNeighbours.erase(addr);
        inactiveNeigh(dst);
    }

    void IntDCRouting::scheduleUpdate() {
        Enter_Method_Silent();
        if(start == nullptr && sched == nullptr) {
            sched = new cMessage("Scheduled update");
            scheduleAt(simTime()+updateWait, sched);
        }
    }
    void IntDCRouting::scheduleClean() {
        Enter_Method_Silent();
        if(clean == nullptr) {
            clean = new cMessage("Scheduled clean");
            scheduleAt(simTime()+expiration, clean);
        }
    }


    map<DCAddr, tableNode> * IntDCRouting::computeTable() {
        map<DCAddr, tableNode> * table = new map<DCAddr, tableNode>();
        map<DCAddr, tableNode> & t = (*table);
        for(int p = 0; p < pods; p++) {
            for(int k = 0; k < torXpod; k++) {
                t[DCAddr(0, p, k)];
            }
            for(int f = 0; f < fabricXpod; f++) {
                t[DCAddr(1, p, f)];
            }
        }
        for(int f = 0; f < fabricXpod; f++) {
            for(int s = 0; s < spineXfabric; s++) {
                t[DCAddr(2, f, s)];
            }
        }
        for(int p = 0; p < edgeSets; p++) {
            for(int f = 0; f < fabricXpod; f++) {
                t[DCAddr(3, p, f)];
            }
        }

        queue<DCAddr> next;
        for(auto & l : myLinks) {
            if(l.second.status) {
                if(l.first.dst == Im) {
                    t[l.first.src] = tableNode( &(l.first) );
                    next.push(l.first.src);
                } else {
                    t[l.first.dst] = tableNode( &(l.first) );
                    next.push(l.first.dst);
                }
            }
        }

        while(!next.empty()) {
            auto n = next.front();
            next.pop();
            tableNode & tn = t[n];
            int tD = tn.d + 1;
            vector<DCAddr> neis = getNeis(n);
            for(auto &ni : neis) {
                tableNode & tni = t[ni];
                if(linksKo.find(linkId(n, ni)) != linksKo.end()) {
                    continue;
                }
                if(tni.d > tD) {
                    tni.d = tD;
                    tni.insert(tn.L);
                    next.push(ni);
                } else if(tni.d == tD) {
                    tni.insert(tn.L);
                }
            }
        }

        return table;
    }

    vector<DCAddr> IntDCRouting::getNeis(DCAddr n) {
        vector<DCAddr> ret;
        switch(n.type) {
            case 0 :
                for(int f = 0; f < fabricXpod; f++) {
                    ret.push_back( DCAddr(1, n.a, f) );
                }
                break;
            case 1 :
                for(int t = 0; t < torXpod; t++) {
                    ret.push_back( DCAddr(0, n.a, t) );
                }
                for(int s = 0; s < spineXfabric; s++) {
                    ret.push_back( DCAddr(2, n.b, s) );
                }
                break;
            case 2 :
                for(int p = 0; p < pods; p++) {
                    ret.push_back( DCAddr(1, p, n.a) );
                }
                for(int p = 0; p < edgeSets; p++) {
                    ret.push_back( DCAddr(3, p, n.a) );
                }
                break;
            case 3 :
                break;
        }

        return ret;
    }

    vector<rtEntry>  IntDCRouting::getChanges() {
        vector<rtEntry> ret;
        map<DCAddr, tableNode> * t = computeTable();
        set<DCAddr> no = getNotOptimalDst(t);

        for(auto it = cache.begin(); it!= cache.end();) {
            const DCAddr & n = it->first;
            auto noIt = no.find(n);
           bool save = false;
            auto &tn = (*t)[n];

            if(noIt == no.end()) {
                save = true;
                cache.erase(it++);
            } else if(it->second != tn.L) {
                save = true;
                it->second = tn.L;
                it++;
                no.erase(noIt);
            } else {
                it++;
                no.erase(noIt);
            }

           if(save){
                rtEntry e;
                e.dst = n;
                for(auto & nd : tn.L) {
                    if(nd->src == Im) {  e.next.insert(nd->dst); }
                    else { e.next.insert(nd->src); }
                }
                ret.push_back(e);
          }
        }

        for(auto & n : no) {
            auto & tn = (*t)[n];
            rtEntry e;
            e.dst = n;
            cache[n] = tn.L;
            for(auto & nd : tn.L) {
                if(nd->src == Im) {  e.next.insert(nd->dst); }
                else { e.next.insert(nd->src); }
            }
            ret.push_back(e);
        }
        return ret;
    }

    vector<rtEntry>  IntDCRouting::getAll() {
        vector<rtEntry> ret;
        map<DCAddr, tableNode> * t = computeTable();
        set<DCAddr> no = getNotOptimalDst(t);
        cache.clear();

        for(auto n : no) {
            auto &tn = (*t)[n];
            rtEntry e;
            e.dst = n;
            cache[n] = tn.L;
            for(auto & nd : tn.L) {
                if(nd->src == Im) {  e.next.insert(nd->dst); }
                else { e.next.insert(nd->src); }
            }
            ret.push_back(e);
        }
        return ret;
    }


    void IntDCRouting::finish() {
        if(par("printAtEnd").boolValue()) {
            cout << "-------------" <<endl;
            cout << "routing at "<< Im <<endl;
            if(par("printMyLinks").boolValue()) {
                cout << "-print links status" <<endl;
                for(auto e : myLinks) {
                    cout << "\t" << e.first.src << " -> " << e.first.dst
                            << " status : " << (e.second.status? "OK" : "KO") << endl;
                }
            }

            if(par("printKoList").boolValue()) {
                cout << "-print Ko List"<<endl;
                for(auto e : linksKo) {
                    cout << "\t" << e.first.src << " -> " << e.first.dst << " (@ "<<e.second.timestamp<<")" << endl;
                }
            }

            if(par("printFullTable").boolValue()) {
                cout << "-print Table"<<endl;
                map<DCAddr, tableNode> * t = computeTable();
                for(auto e : *t) {
                    cout << "\t" << e.first;
                    cout << "\t\t--distance : " << e.second.d << endl;
                    for(auto k : e.second.L) {
                        cout << "\t\t" << k->src << " -> " << k->dst << endl;
                    }
                }
                if(par("printNotOptimal").boolValue()) {
                    cout << "-print not optimal paths"<<endl;
                    set<DCAddr> no = getNotOptimalDst(t);
                    for(auto n : no) {
                        auto &tn = (*t)[n];
                        cout << "\t"<<n<<endl;
                        cout << "\t\t distance "<< tn.d<<endl;
                        for(auto & nd : tn.L) {
                            if(nd->src == Im) {
                                cout << "\t\t-> "<< nd->dst <<endl;
                            } else {
                                cout << "\t\t-> "<< nd->src <<endl;
                            }
                        }
                    }
                }
            } else if(par("printNotOptimal").boolValue()) {
                map<DCAddr, tableNode> * t = computeTable();
                cout << "-print not optimal paths"<<endl;
                set<DCAddr> no = getNotOptimalDst(t);
                for(auto n : no) {
                    auto &tn = (*t)[n];
                    cout << "\t"<<n<<endl;
                    cout << "\t\t distance "<< tn.d<<endl;
                    for(auto & nd : tn.L) {
                        if(nd->src == Im) {
                            cout << "\t\t-> "<< nd->dst <<endl;
                        } else {
                            cout << "\t\t-> "<< nd->src <<endl;
                        }
                    }
                }
            }



            printAtEnd();

            cout << "-------------" <<endl;
            cout << endl;
        }
    }
}
