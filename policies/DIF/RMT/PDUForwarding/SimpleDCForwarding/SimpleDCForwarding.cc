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

#include "SimpleDCForwarding.h"
#include <sstream>
#include "Utils.h"

namespace NSPSimpleDC {

    Register_Class(SimpleDCForwarding);

    using namespace std;


    DCAddr::DCAddr(): type(-1), a(0), b(0){}

    DCAddr::DCAddr(const int & _type, const int & _a, const int & _b):
            type(_type), a(_a), b(_b){}

    DCAddr::DCAddr(const string & s_addr) {
        vector<string> s_vec = split(s_addr, '.');
        type = atoi(s_vec[0].c_str());
        a = atoi(s_vec[1].c_str());
        b = atoi(s_vec[2].c_str());
    }

    bool DCAddr::operator<( const DCAddr & o ) const {
        if(type < o.type) { return true; }
        if(type > o.type) { return false;}

        if(a < o.a) { return true; }
        if(a > o.a) { return false;}

        if(b < o.b) { return true; }

        return false;
    }

    bool DCAddr::operator==( const DCAddr & o ) const {
        return (type == o.type && a == o.a && b == o.b);
    }

    FWDEntry::FWDEntry() : inverse(false), toUp(false) {}


    vector<RMTPort * > SimpleDCForwarding::lookup(const PDU * pdu) {
        vector<RMTPort * > possible = search(DCAddr(pdu->getDstAddr().getIpcAddress().getName()));
        vector<RMTPort * > ret;
        if(possible.size() > 0) {
            int k = intuniform(0, possible.size()-1);
            ret.push_back(possible[k]);
        }
        return ret;
    }

    vector<RMTPort * > SimpleDCForwarding::lookup(const Address & dst, const std::string & qos) {
        vector<RMTPort * > possible = search(DCAddr(dst.getIpcAddress().getName()));
        vector<RMTPort * > ret;
        if(possible.size() > 0) {
            int k = intuniform(0, possible.size()-1);
            ret.push_back(possible[k]);
        }
        return ret;
    }


    vector<RMTPort * > SimpleDCForwarding::search(const DCAddr & n_addr) {
        auto r = table.find(n_addr);
        if(r != table.end()) {
            vector<RMTPort * > ret;
            FWDEntry & e = r->second;
            if(e.inverse) {
                if(e.toUp) {
                    for(auto p : upV) {
                        if(e.ports.find(p) == e.ports.end()) {
                            ret.push_back(p);
                        }
                    }
                } else {
                    for(auto p : downV) {
                        if(e.ports.find(p) == e.ports.end()) {
                            ret.push_back(p);
                        }
                    }
                }
            } else {
                for(auto p : e.ports) {
                    ret.push_back(p);
                }
            }
        }

        if(Im == n_addr) { return vector<RMTPort * >(); }

        //This only if best paths are available!!
        switch(Im.type) {
            case 0:
                /*
                 * TOR > X
                 * X:AG same rack : direct
                 *  otherwise UP
                 * default UP
                 */
                if(n_addr.type == 1 && n_addr.a == Im.a) {
                    auto t = upN.find(n_addr.b);
                    if(t != upN.end()) {
                        vector<RMTPort * > ret;
                        ret.push_back(t->second);
                        return ret;
                    }
                }
                return upV;
            case 1:
                /*
                 * AG > X
                 * X:TOR
                 *  same rack : direct
                 *  otherwise : UP
                 * X:AG
                 *  same rack : DOWN
                 *  same Spine-set : UP
                 *  otherwise : ANY
                 * X:Spine
                 *  same Spine-set : direct
                 *  otherwise : DOWN
                 */
                switch(n_addr.type) {
                    case 0 :
                        if(n_addr.a == Im.a) {
                            auto t = downN.find(n_addr.b);
                            if(t != downN.end()) {
                                vector<RMTPort * > ret;
                                ret.push_back(t->second);
                                return ret;
                            }
                        }
                        return upV;
                    case 1 :
                        if(n_addr.a == Im.a && !downV.empty()) {
                            return downV;
                        } else if(n_addr.b == Im.b && !upV.empty()) {
                            return upV;
                        }
                        return allV;
                    case 2 :
                        if(n_addr.a == Im.b) {
                            auto t = upN.find(n_addr.b);
                            if(t != upN.end()) {
                                vector<RMTPort * > ret;
                                ret.push_back(t->second);
                                return ret;
                            }
                        }
                        return downV;

                }
            case 2:
                /*
                 * Spine > X
                 * X:TOR
                 *  direct to rack AG
                 * X:AG
                 *  same Spine-set : direct
                 *  direct to rack AG
                 * default : DOWN
                 */
                if(n_addr.type != 2) {
                    auto t = downN.find(n_addr.a);
                    if(t != downN.end()) {
                        vector<RMTPort * > ret;
                        ret.push_back(t->second);
                        return ret;
                    }
                }
                return downV;
        }
        return vector<RMTPort * >();
    }

    void SimpleDCForwarding::setNodeInfo(const int & type, const int & a, const int & b) {
        Im = DCAddr(type, a, b);
    }

    void SimpleDCForwarding::addNeigh(const string & s_addr, RMTPort* port) {
        DCAddr n_addr = DCAddr(s_addr);
        bool re_up = false;
        bool re_down = false;
        switch(Im.type) {
            case 0:
                if(n_addr.type != 1 || Im.a != n_addr.a) {
                    cerr << "Invalid neighbour ("<<s_addr<< ") found for TOR" << endl;
                    return;
                }
                upN[n_addr.a] = port;
                re_up = true;
                break;
            case 1:
                if( (n_addr.type != 0 || Im.a != n_addr.a)
                  &&(n_addr.type != 2 || Im.b != n_addr.a)) {
                    cerr << "Invalid neighbour ("<<s_addr<< ") found for AG" << endl;
                    return;
                }
                if(n_addr.type == 0) {
                    downN[n_addr.a] = port;
                    re_down = true;
                } else  {
                    upN[n_addr.a] = port;
                    re_up = true;
                }
                break;
            case 2:
                if(n_addr.type != 2 || Im.a != n_addr.b) {
                    cerr << "Invalid neighbour ("<<s_addr<< ") found for Spine" << endl;
                    return;
                }
                downN[n_addr.a] = port;
                re_down = true;
                break;
        }
        if(re_up || re_down) {
            upV.clear();
            downV.clear();
            allV.clear();
            for(auto idPort : upN) {
                upV.push_back(idPort.second);
                allV.push_back(idPort.second);
            }
            for(auto idPort : downN) {
                downV.push_back(idPort.second);
                allV.push_back(idPort.second);
            }
        }

    }

    void SimpleDCForwarding::removeNeigh(const string & s_addr, RMTPort* port) {
        DCAddr n_addr = DCAddr(s_addr);
        bool re_up = false;
        bool re_down = false;
        switch(Im.type) {
            case 0:
                if(n_addr.type != 1 || Im.a != n_addr.a) {
                    cerr << "Invalid neighbour ("<<s_addr<< ") found for TOR." << endl;
                    return;
                }
                upN.erase(n_addr.a);
                re_up = true;
                break;
            case 1:
                if( (n_addr.type != 0 || Im.a != n_addr.a)
                  &&(n_addr.type != 2 || Im.b != n_addr.a)) {
                    cerr << "Invalid neighbour ("<<s_addr<< ") found for AG." << endl;
                    return;
                }
                if(n_addr.type == 0) {
                    downN.erase(n_addr.b);
                    re_down = true;
                } else  {
                    upN.erase(n_addr.b);
                    re_up = true;
                }
                break;
            case 2:
                if(n_addr.type != 2 || Im.a != n_addr.b) {
                    cerr << "Invalid neighbour ("<<s_addr<< ") found for Spine." << endl;
                    return;
                }
                downN.erase(n_addr.a);
                re_down = true;
                break;
        }
        if(re_up || re_down) {
            upV.clear();
            downV.clear();
            allV.clear();
            for(auto idPort : upN) {
                upV.push_back(idPort.second);
                allV.push_back(idPort.second);
            }
            for(auto idPort : downN) {
                downV.push_back(idPort.second);
                allV.push_back(idPort.second);
            }
        }
    }

    void SimpleDCForwarding::addDst(const string & s_addr, const set<int> & upP, const set<int> & downP) {
        DCAddr n_addr = DCAddr(s_addr);
        if(n_addr == Im) { return; }
        if(n_addr.type < 0 || n_addr.type > 2) {
            cerr << "Invalid dst addr ("<<s_addr<< ") inserted." << endl;
        }

        int upPS = upP.size();
        int downPS = downP.size();
        int upNS = upN.size();
        int downNS = downN.size();

        if(upPS == 0 && downPS == 0) {
            table[n_addr] = FWDEntry();
            return;
        }

        switch(Im.type) {
            case 0:
                //Special case : TOR > same rack AG
                if(n_addr.type == 1 && n_addr.a == Im.a){
                    if(upP.find(n_addr.b) != upP.end()) {
                        //Direct link available
                        table.erase(n_addr);
                    } else {
                        //Secondary links available
                        table[n_addr] = getUpPorts(upP);
                    }
                    break;
                }
                if(upPS == upNS){
                    //All links available
                    table.erase(n_addr);
                } else {
                    //Some links available
                    table[n_addr] = getUpPorts(upP);
                }
                break;
            case 1:
                switch (n_addr.type) {
                    case 0:
                        if(n_addr.a == Im.a) {
                            //Special case : AG > same rack TOR
                            if(downP.find(n_addr.b) != downP.end()) {
                                //Direct link available
                                table.erase(n_addr);
                            } else {
                                //Secondary links available
                                table[n_addr] = getJoinPorts(upP, downP);
                            }
                        } else if(downPS > 0) {
                            //Secondary links (down) available
                            table[n_addr] = getJoinPorts(upP, downP);
                        } else if(upPS == upNS){
                            //All links available
                            table.erase(n_addr);
                        } else {
                            //Some links available
                            table[n_addr] = getUpPorts(upP);
                        }
                        break;
                    case 1 :
                        if(n_addr.a == Im.a) {
                            //Special case : AG > same rack AG
                            if(upPS != 0) {
                                //Secondary links (up) available
                                table[n_addr] = getJoinPorts(upP, downP);
                            } else if(downPS == downNS){
                                //All links available
                                table.erase(n_addr);
                            } else {
                                //Some links available
                                table[n_addr] = getDownPorts(downP);
                            }

                        } else if(n_addr.b == Im.b) {
                            //Special case : AG > same spine-set AG
                            if(downPS != 0) {
                                //Secondary links (down) available
                                table[n_addr] = getJoinPorts(upP, downP);
                            } else if(upPS == upNS){
                                //All links available
                                table.erase(n_addr);
                            } else {
                                //Some links available
                                table[n_addr] = getUpPorts(downP);
                            }
                        } else if(upPS == upNS && downPS == downPS){
                            table.erase(n_addr);
                        } else {
                            table[n_addr] = getJoinPorts(upP, downP);
                        }
                        break;
                    case 2 :
                        if(n_addr.a == Im.b) {
                            //Special case : AG > spine-set Spine
                            if(upP.find(n_addr.b) != upP.end()) {
                                //Direct link available
                                table.erase(n_addr);
                            } else {
                                //Secondary links available
                                table[n_addr] = getJoinPorts(upP, downP);
                            }
                        } else {
                            if(upNS != 0) {
                                //Secondary links available
                                table[n_addr] = getJoinPorts(upP, downP);
                            } else if(downPS == downNS) {
                                //All links available
                                table.erase(n_addr);
                            } else {
                                //Some links available
                                table[n_addr] = getDownPorts(upP);
                            }
                        }
                }
            case 2:
                if(n_addr.type == 2) {
                    if(downPS == downPS) {
                        //All links available
                        table.erase(n_addr);
                    } else {
                        //Some links available
                        table[n_addr] = getDownPorts(upP);
                    }
                } else {
                    if(downP.find(n_addr.a) != downP.end()) {
                        //Direct link to rack AG available
                        table.erase(n_addr);
                    } else {
                        //Secondary links available
                        table[n_addr] = getDownPorts(upP);
                    }
                }
                break;
        }
    }

    FWDEntry SimpleDCForwarding::getUpPorts(const set<int> & pIds) {
        FWDEntry ret;
        ret.inverse = (pIds.size()*2 > upN.size());

        if(!ret.inverse) {
            for(auto idPort : upN) {
                if(pIds.find(idPort.first) != pIds.end()) {
                    ret.ports.insert(idPort.second);
                }
            }
        } else {
            for(auto idPort : upN) {
                if(pIds.find(idPort.first) == pIds.end()) {
                    ret.ports.insert(idPort.second);
                }
            }
        }
        ret.toUp = true;
        return ret;
    }

    FWDEntry SimpleDCForwarding::getDownPorts(const set<int> & pIds){
        FWDEntry ret;
        ret.inverse = (pIds.size()*2 > downN.size());

        if(!ret.inverse) {
            for(auto idPort : downN) {
                if(pIds.find(idPort.first) != pIds.end()) {
                    ret.ports.insert(idPort.second);
                }
            }
        } else {
            for(auto idPort : downN) {
                if(pIds.find(idPort.first) == pIds.end()) {
                    ret.ports.insert(idPort.second);
                }
            }
        }
        return ret;
    }

    FWDEntry SimpleDCForwarding::getJoinPorts(const set<int> & upIds, const set<int> & downIds) {
        FWDEntry ret;
        for(auto idPort : upN) {
            if(upIds.find(idPort.first) != upIds.end()) {
                ret.ports.insert(idPort.second);
            }
        }
        for(auto idPort : downN) {
            if(downIds.find(idPort.first) == downIds.end()) {
                ret.ports.insert(idPort.second);
            }
        }
        return ret;
    }


    string SimpleDCForwarding::toString() {
        return "";
    }

    void SimpleDCForwarding::onPolicyInit(){}

    void SimpleDCForwarding::finish() {
        if(par("printAtEnd").boolValue()) {
            cout << table.size();
            for(auto & e : table) {
                cout << e.first.type << "." << e.first.a << "." << e.first.b << " -- " << e.second.ports.size() << endl;
            }
        }
    }

}
