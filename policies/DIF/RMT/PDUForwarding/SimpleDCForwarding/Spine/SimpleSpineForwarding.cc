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

#include "DIF/RMT/PDUForwarding/SimpleDCForwarding/Spine/SimpleSpineForwarding.h"
#include <sstream>
#include "Common/Utils.h"

namespace NSPSimpleDC {

    Register_Class(SimpleSpineForwarding);

    using namespace std;

    sFWDEntry::sFWDEntry() : entryType(0), inverseStorage(false) {}


    void SimpleSpineForwarding::onPolicyInit() {
        upCount = par("upCount").longValue();
        if(upCount < 0) { upCount = 0; }

        downCount = par("downCount").longValue();
        if(downCount < 0) { downCount = 0; }

        portsArray = new Port[upCount+downCount];
        for(int i = 0; i<upCount+downCount; i++) { portsArray[i] = nullptr; }
    }

    vector<Port> SimpleSpineForwarding::search(const DCAddr & n_addr) {
        if(Im == n_addr) { return vector<Port>(); }
        if(n_addr.type < 0 || n_addr.type > 3) {
            cerr << "Invalid dst addr ("<<n_addr<< ")" << endl;
            return vector<Port>();
        }

        auto r = table.find(n_addr);
        if(r != table.end()) {
            auto & e = r->second;
            if(e.entryType == 0) { return vector<Port>(); }

            vector<Port> ret;

            int i = (e.entryType != 2)? 0: upCount;
            int j = (e.entryType != 1)? upCount+downCount: downCount;
            for(; i<j; i++) {
                Port p = portsArray[i];
                if(e.inverseStorage == (e.ports.find(p) == e.ports.end()) ) {
                    ret.push_back(p);
                }
            }
            return ret;
        }

        switch(n_addr.type) {
            case 0:
            case 1:
                if(n_addr.a < downCount
                        && portsArray[upCount+n_addr.a] != nullptr) {
                    vector<Port> ret;
                    ret.push_back(portsArray[upCount+n_addr.a]);
                    return ret;
                } else { cerr << "!!!" << endl; }
                break;
            case 2:
                return downV;
            case 3:
                if(n_addr.b == Im.a) {
                    if(n_addr.a < upCount
                            && portsArray[n_addr.a] != nullptr) {
                        vector<Port> ret;
                        ret.push_back(portsArray[n_addr.a]);
                        return ret;
                    } else { cerr << "!!!" << endl; }
                } else {
                    return downV;
                }
        }
        return vector<Port>();
    }

    bool SimpleSpineForwarding::setNeigh(const DCAddr & n_addr, Port port) {
        bool invalid = false;
        switch(n_addr.type){
            case 1 :
                if(n_addr.b != Im.a || n_addr.a >= downCount) {
                    invalid = true;
                } break;
            case 3 :
                if(n_addr.b != Im.a || n_addr.a >= upCount) {
                    invalid = true;
                } break;
            default:
                invalid = true;
        }

        if(invalid) {
            cerr << "Invalid neighbour ("<<n_addr<< ") found for Spine " << Im<<endl;
            return false;
        }

        Port t ;
        if(n_addr.type == 1){
            t = portsArray[upCount+n_addr.a];
            if(t == port) { return true; }
            portsArray[upCount+n_addr.a] = port;
        } else {
            t = portsArray[n_addr.a];
            if(t == port) { return true; }
            portsArray[n_addr.a] = port;
        }

        upV.clear();
        downV.clear();
        bothV.clear();
        for(int i = 0; i<upCount; i++) {
            Port pt = portsArray[i];
            if(pt!= nullptr) {
                upV.push_back(pt);
                bothV.push_back(pt);
            }
        }
        for(int i = 0; i<downCount; i++) {
            Port pt = portsArray[upCount+i];
            if(pt!= nullptr) {
                downV.push_back(pt);
                bothV.push_back(pt);
            }
        }


        for(auto & e : table) {
            if(!e.second.ports.empty()) {
                if(e.second.ports.find(t) != e.second.ports.end()) {
                    e.second.ports.erase(t);
                    if(port != nullptr) {
                        e.second.ports.insert(port);
                    }
                }
            }
        }
        refreshCache (t, port);
        return true;
    }

    void SimpleSpineForwarding::setDst(const DCAddr & n_addr, const set<DCAddr> & next) {
        if(n_addr == Im) { return; }

        if(n_addr.type < 0 || n_addr.type > 3) {
            cerr << "Invalid dst addr ("<<n_addr<< ")" << endl;
            return;
        }

        int S = next.size();

        if(S == 0) {
            table[n_addr] = sFWDEntry();
            return;
        }

        set<int> upIds, downIds;
        for(const auto & n : next) {
            if(n.type == 1) {
                downIds.insert(n.a);
            } else if(n.type == 3) {
                upIds.insert(n.a);
            }
        }
        int upS = upIds.size();
        int downS = downIds.size();

        if(upS == 0 && downS == 0) {
            table[n_addr] = sFWDEntry();
            return;
        }

        bool defaultEntry = false;
        switch(n_addr.type) {
            case 0:
            case 1:
                if(n_addr.a < downCount
                        && upS == 0
                        && downS == 1
                        && portsArray[upCount+n_addr.a]) {
                    defaultEntry = true;
                } break;
            case 2:
                if(downS == downCount
                        && upS == 0) {
                    defaultEntry = true;
                } break;
            case 3:
                if(n_addr.b == Im.a) {
                    if(n_addr.a < upCount
                            && portsArray[n_addr.a] != nullptr) {
                        defaultEntry = true;
                    }
                } else if(downS == downCount
                        && upS == 0) {
                    defaultEntry = true;
                }
        }

        if(defaultEntry) {
            table.erase(n_addr);
        } else if(upS > 0) {
            if(downS > 0) {
                table[n_addr] = getFWDEntryBOTH(upIds, downIds);
            } else {
                table[n_addr] = getFWDEntryUP(upIds);
            }
        } else {
            table[n_addr] = getFWDEntryDOWN(downIds);
        }

        refreshCache (n_addr);
    }

    sFWDEntry SimpleSpineForwarding::getFWDEntryUP(const set<int> & pIds) {
        sFWDEntry ret;
        ret.entryType = 1;
        ret.inverseStorage = ((int)pIds.size()*2 > upCount);

        for(int i = 0; i< upCount; i++) {
            if(ret.inverseStorage == (pIds.find(i) == pIds.end())) {
                ret.ports.insert(portsArray[i]);
            }
        }
        return ret;
    }

    sFWDEntry SimpleSpineForwarding::getFWDEntryDOWN(const set<int> & pIds) {
        sFWDEntry ret;
        ret.entryType = 2;
        ret.inverseStorage = ((int)pIds.size()*2 > downCount);

        for(int i = 0; i< downCount; i++) {
            if(ret.inverseStorage == (pIds.find(i) == pIds.end())) {
                ret.ports.insert(portsArray[upCount+i]);
            }
        }

        return ret;
    }

    sFWDEntry SimpleSpineForwarding::getFWDEntryBOTH(const set<int> & pIdsU, const set<int> & pIdsD) {
        sFWDEntry ret;
        ret.entryType = 3;
        ret.inverseStorage = (int)(pIdsU.size()*2 + pIdsD.size()*2 ) > (upCount+downCount);

        for(int i = 0; i< upCount; i++) {
            if(ret.inverseStorage == (pIdsU.find(i) == pIdsU.end())) {
                ret.ports.insert(portsArray[i]);
            }
        }
        for(int i = 0; i< downCount; i++) {
            if(ret.inverseStorage == (pIdsD.find(i) == pIdsD.end())) {
                ret.ports.insert(portsArray[upCount+i]);
            }
        }
        return ret;
    }

    void SimpleSpineForwarding::finish() {
        if(par("printAtEnd").boolValue()) {
            cout << "-----------------------" << endl;
            cout << "SimpleSpineForwarding at "<< endl;
            cout << " " << getFullPath() << endl;

            cout << "I'm Spine "<< Im << endl;
            if(upCount > 0) {
                cout << "\tUp neighbours:" << endl;
                for(int i = 0; i < upCount; i++) {
                    cout << "\t\t2."<<Im.b<<"."<<i<<"  ->  Status "<< (portsArray[i]!=nullptr? "ON":"OFF") << endl;
                }
            }
            if(downCount > 0) {
                cout << "\tDown neighbours:" << endl;
                for(int i = 0; i < downCount; i++) {
                    cout << "\t\t0."<<Im.a<<"."<<i<<"  ->  Status "<< (portsArray[upCount+i]!=nullptr? "ON":"OFF") << endl;
                }
            }
            if(table.empty()) {
                cout << "\tNo entries stored" << endl;
            } else {
                cout << "Stored entries " << table.size() << endl;
                for(auto & e : table) {
                    cout <<"\t\t"<< e.first << " -- ";
                    if(e.second.entryType == 0) {
                        cout << "Unreachable";
                    } else {
                        switch (e.second.entryType) {
                            case 1: cout <<"UP - ";break;
                            case 2: cout <<"DOWN - ";break;
                            case 3: cout <<"BOTH - ";break;
                        }
                        if(e.second.inverseStorage) {
                            cout << "(inverse) ";
                        }
                        cout << e.second.ports.size() << " stored ports:";
                    }
                    cout << endl;
                    for(auto &k : e.second.ports) {
                        cout << "\t\t\t" << k->getFullPath() << endl;
                    }
                }
            }
        }

        delete portsArray;
    }

}
