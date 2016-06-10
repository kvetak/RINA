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

#include <GironaFWD/GironaFWD.h>

Register_Class(GironaFWD);

vPorts GironaFWD::lookup(const PDU * pdu) {
    string d = pdu->getDstAddr().getIpcAddress().getName();

    vPorts possible = search(d);

    if(possible.size() < 2) { return possible; }
    else {
        vPorts ret;
        string s = pdu->getSrcAddr().getIpcAddress().getName();
        int sc = pdu->getConnId().getSrcCepId();
        int dc = pdu->getConnId().getDstCepId();
        ret.push_back(possible.at(hashFlow(s, d, sc, dc) % possible.size()));
        return ret;
    }
}

vPorts GironaFWD::lookup(const Address &dst, const std::string& qos) {
    string d = dst.getIpcAddress().getName();

    vPorts possible = search(d);

    if(possible.size() < 2) { return possible; }
    else {
        vPorts ret;
        ret.push_back(possible.at(hashFlow(myaddr, d, 0, 0) % possible.size()));
        return ret;
    }
}

vPorts GironaFWD::search(const string &dst) {
    vPorts ret;
    if(neis.find(dst) != neis.end()) { ret.push_back(neis[dst]); }
    /*
    string s = myaddr;
    string d = dst;
    string w = inverse(s, symbolLen) + d;
    string we = reduce(w, symbolLen);
    int e = getFirst(we, symbolLen);
    cout << e << endl;
    */
    return ret;
}

void GironaFWD::setNeighbour(const string & dst, const port_t port) {
    neis[dst] = port;
}

void GironaFWD::unsetNeighbour(const string & dst) {
    neis.erase(dst);
}

void GironaFWD::onPolicyInit() {
    myaddr = getModuleByPath("^.^")->par("ipcAddress").stringValue();
    symbolLen = par("symbolLen").longValue();
}

void GironaFWD::finish() {
}
