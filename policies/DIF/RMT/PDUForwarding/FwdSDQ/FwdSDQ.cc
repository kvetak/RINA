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

#include <FwdSDQ/FwdSDQ.h>

#include <sstream>

Register_Class(FwdSDQ);

vPorts FwdSDQ::lookup(const PDU * pdu) {
    vPorts ret;

    string src = pdu->getSrcAddr().getIpcAddress().getName();
    string dst = pdu->getDstAddr().getIpcAddress().getName();
    string qos = pdu->getConnId().getQoSId();

    port_t p = nullptr;

    p = search(src, dst, qos);
    if (p == nullptr) {
        p = search("-", dst, qos);
    }
    if (p == nullptr) {
        p = search(src, dst, "-");
    }
    if (p == nullptr) {
        p = search("-", dst, "-");
    }

    if (p != nullptr) {
        ret.push_back(p);
    }

    return ret;
}

vPorts FwdSDQ::lookup(const Address &dst, const std::string& qos) {
    vPorts ret;

    string dst_s = dst.getIpcAddress().getName();

    port_t p = nullptr;

    p = search("-", dst_s, qos);
    if (p == nullptr) {
        p = search("-", dst_s, "-");
    }

    if (p != nullptr) {
        ret.push_back(p);
    }
    return ret;
}

port_t FwdSDQ::search(const string & src, const string & dst,const string & qos) {
    return table[src][dst][qos];
}

void FwdSDQ::add(const string & src, const string & dst,const string & qos, port_t p) {
    table[src][dst][qos] = p;
    table["-"][dst][qos] = p;
    table[src][dst]["-"] = p;
    table["-"][dst]["-"] = p;
}


string FwdSDQ::toString() {
    std::ostringstream os;

    os << "-------------" << endl;
    os << "Forwarding at " << getFullPath() << endl;
    for(auto srcT : table) {
        os << "SRC :: "<< srcT.first <<endl;
        for(auto dstT : srcT.second) {
            os << "\tDST :: "<< dstT.first <<endl;
            for(auto qosT : dstT.second) {
                os << "\t\tQoS :: "<< qosT.first << " -> ";
                if(qosT.second != nullptr) {
                    os<< qosT.second->getFullPath();
                } else {
                    os<< "null";
                }
                os <<endl;
            }
        }
    }
    os << "-------------" << endl << endl;

    return os.str();
}

void FwdSDQ::finish() {
    if (par("printAtEnd").boolValue()) {
        cout << toString() << endl;
    }
}
