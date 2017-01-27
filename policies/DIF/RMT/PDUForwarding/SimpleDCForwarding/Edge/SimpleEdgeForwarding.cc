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

#include "DIF/RMT/PDUForwarding/SimpleDCForwarding/Edge/SimpleEdgeForwarding.h"
#include <sstream>
#include "Common/Utils.h"

namespace NSPSimpleDC {

    Register_Class(SimpleEdgeForwarding);

    using namespace std;

    eFWDEntry::eFWDEntry() : entryType(false), inverseStorage(false) {}


    void SimpleEdgeForwarding::onPolicyInit() {
        downCount = par("downCount").longValue();
        if(downCount < 0) { downCount = 0; }
        portsArray = new Port[downCount];
        for(int i = 0; i<downCount; i++) { portsArray[i] = nullptr; }
    }

    vector<Port> SimpleEdgeForwarding::search(const DCAddr & n_addr) {
        if(Im == n_addr) { return vector<Port>(); }
        if(n_addr.type < 0 || n_addr.type > 3) {
            cerr << "Invalid dst addr ("<<n_addr<< ")" << endl;
            return vector<Port>();
        }

        auto r = table.find(n_addr);
        if(r != table.end()) {
            auto & e = r->second;
            if(!e.entryType) { return vector<Port>(); }

            vector<Port> ret;
            for(int i = 0; i<downCount; i++) {
                Port p = portsArray[i];
                if(e.inverseStorage == (e.ports.find(p) == e.ports.end()) ) {
                    ret.push_back(p);
                }
            }
            return ret;
        }

        if(n_addr.type == 2 && n_addr.a == Im.b) {
            if(n_addr.b < downCount && portsArray[n_addr.b] != nullptr) {
                    vector<Port> ret;
                    ret.push_back(portsArray[n_addr.b]);
                    return ret;
            } else { cout << "!!! Invalid port to " << (n_addr.b) << "  at " << Im << endl; }
        }
        return downV;
    }


    bool SimpleEdgeForwarding::setNeigh(const DCAddr & n_addr, Port port) {
        if(n_addr.type != 2 || Im.b != n_addr.a || n_addr.b >= downCount) {
            cerr << "Invalid neighbour ("<<n_addr<< ") found for Edge " << Im<<endl;
            return false;
        }

        Port t = portsArray[n_addr.b];
        if(portsArray[n_addr.b] == port) { return true; }
        portsArray[n_addr.b] = port;


        downV.clear();
        for(int i = 0; i<downCount; i++) {
            if(portsArray[i]!= nullptr) {
                downV.push_back(portsArray[i]);
            }
        }


        for(auto & e : table) {
                if(e.second.ports.find(t) != e.second.ports.end()) {
                    e.second.ports.erase(t);
                    if(port != nullptr) {
                        e.second.ports.insert(port);
                    }
                }
        }
        refreshCache (t, port);
        return true;
    }

    void SimpleEdgeForwarding::setDst(const DCAddr & n_addr, const set<DCAddr> & next) {
        if(n_addr == Im) { return; }

        if(n_addr.type < 0 || n_addr.type > 3) {
            cerr << "Invalid dst addr ("<<n_addr<< ")" << endl;
            return;
        }

        int S = next.size();

        if(S == 0) {
            table[n_addr] = eFWDEntry();
            return;
        }

        set<int> pIds;
        for(const auto & n : next) {
            pIds.insert(n.b);
        }


        if(n_addr.type == 2 && n_addr.a == Im.b) {
            if(S == 1 && pIds.find(n_addr.b) != pIds.end()){
                table.erase(n_addr);
            } else {
                table[n_addr] = getFWDEntry(pIds);
            }
        } else if (S == downCount) {
            table.erase(n_addr);
        } else {
            table[n_addr] = getFWDEntry(pIds);
        }

        refreshCache (n_addr);
    }

    eFWDEntry SimpleEdgeForwarding::getFWDEntry(const set<int> & pIds) {
        eFWDEntry ret;
        ret.entryType = true;
        ret.inverseStorage = ((int)pIds.size()*2 > downCount);

        for(int i = 0; i< downCount; i++) {
            if(ret.inverseStorage == (pIds.find(i) == pIds.end())) {
                ret.ports.insert(portsArray[i]);
            }
        }
        return ret;
    }

    void SimpleEdgeForwarding::finish() {
        if(par("printAtEnd").boolValue()) {
            cout << "-----------------------" << endl;
            cout << "SimpleEdgeForwarding at "<< endl;
            cout << " " << getFullPath() << endl;

            cout << "I'm Edge "<< Im << endl;
            if(downCount > 0) {
                cout << "\tDown neighbours:" << endl;
                for(int i = 0; i < downCount; i++) {
                    cout << "\t\t1."<<Im.a<<"."<<i<<"  ->  Status "<< (portsArray[i]!=nullptr? "ON":"OFF") << endl;
                }
            }
            if(table.empty()) {
                cout << "\tNo entries stored" << endl;
            } else {
                cout << "Stored entries " << table.size() << endl;
                for(auto & e : table) {
                    cout <<"\t\t"<< e.first << " -- ";
                    if(e.second.entryType == false) {
                        cout << "Unreachable";
                    } else {
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
