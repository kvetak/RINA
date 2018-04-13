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

#include "DIF/RMT/PDUForwarding/SimpleDCForwarding/SimpleDCForwarding.h"
#include <sstream>
#include "Common/Utils.h"

namespace NSPSimpleDC {

    using namespace std;

    vector<Port> iSimpleDCForwarding::lookup(const PDU * pdu) {

        //Search cache

        string saddr = pdu->getDstAddr().getIpcAddress().getName();
        DCAddr n_addr = DCAddr(saddr);

        PDU * p = const_cast<PDU*>(pdu);
        p->setHopCount(p->getHopCount()+1);
        if(p->getHopCount()> 15) {
            return vector<Port>();
        }

        if(n_addr.type < 0) {  return vector<Port >(); }

        vector<Port> possible = search(n_addr);
        vector<Port> ret;
        if(possible.size() > 0) {
            int k = omnetpp::intuniform(omnetpp::getEnvir()->getRNG(0), 0, possible.size()-1);
            ret.push_back(possible[k]);
        }


        return ret;
    }

    vector<Port> iSimpleDCForwarding::lookup(const Address & dst, const std::string & qos) {
        string saddr = dst.getIpcAddress().getName();
        DCAddr n_addr = DCAddr(saddr);

        if(n_addr.type < 0) {  return vector<Port>(); }

        vector<Port> possible = search(n_addr);
        vector<Port> ret;
        if(possible.size() > 0) {
            int k = omnetpp::intuniform(omnetpp::getEnvir()->getRNG(0), 0, possible.size()-1);
            ret.push_back(possible[k]);
        }
        return ret;
    }


    void iSimpleDCForwarding::setNodeInfo(const string & n_addr) {
        Im = DCAddr(n_addr);
    }

    void iSimpleDCForwarding::setNodeInfo(const int & type, const int & a, const int & b) {
        Im = DCAddr(type, a, b);
    }


    string iSimpleDCForwarding::toString() {
        return "";
    }

    void iSimpleDCForwarding::refreshCache(Port oldP, Port newP){}
    void iSimpleDCForwarding::refreshCache(const DCAddr & addr){}
}
