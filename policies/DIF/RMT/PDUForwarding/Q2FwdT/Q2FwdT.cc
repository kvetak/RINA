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

#include "DIF/RMT/PDUForwarding/Q2FwdT/Q2FwdT.h"

#include <sstream>

Register_Class(Q2FwdT);

vPorts Q2FwdT::lookup(const PDU * pdu) {
    vPorts ret;
/*
    cout << pdu->getSrcAddr().getIpcAddress() << " -> "<< pdu->getDstAddr().getIpcAddress()
            << " | "<< pdu->getConnId().getQoSId()<<endl;
*/
    port_t p = search(pdu->getDstAddr().getIpcAddress().getName(), pdu->getConnId().getQoSId());
    if(p != nullptr) { ret.push_back(p); }
    return ret;
}

vPorts Q2FwdT::lookup(const Address &dst, const std::string& qos) {
    vPorts ret;
    port_t p = search(dst.getIpcAddress().getName(), qos);
    if(p != nullptr) { ret.push_back(p); }
    return ret;
}

port_t Q2FwdT::search(const string & _raddr, const string & _qos) {
    if(_raddr == "" || _qos == "") { return nullptr; }

    int addr = stoi(_raddr);
    int T = Q2T[_qos];
    return Tables[T][addr];
}

void Q2FwdT::iniStructs(const map<string, int> & _Q2T, const int & _nT, const int & _Ts) {
    Q2T = _Q2T;
    Tables = vector<vPorts>(_nT, vPorts(_Ts, nullptr));
}

void Q2FwdT::setTentry(const int & _T, const int & _addr, port_t _p) {
    Tables[_T][_addr] = _p;
}
void Q2FwdT::setTable(const int & _T, const vPorts & _cont) {
    Tables[_T] = _cont;
}
void Q2FwdT::setQ2T(const map<string, int> & _Q2T) {
    Q2T = _Q2T;
}

string Q2FwdT::toString(){
    std::ostringstream os;

    os << "-------------"<<endl;
    os << "Forwarding at "<< getFullPath()<<endl;
    os << "QoS to Table:"<<endl;
    for(auto QT : Q2T) {
        os << "    QoS : "<<QT.first << " -> Table : " << QT.second <<endl;
    }
    for(unsigned int i = 0; i< Tables.size(); i++) {
        os << "Table "<<i <<endl;
        const vPorts & T = Tables[i];
        for(unsigned int j = 0; j < T.size(); j++) {
            port_t p = T[j];
            if(p != nullptr) {
                os << "    Addr : "<< j << " -> Port : "<< T[j]->getFullPath()<<endl;
            } else {
                os << "    Addr : "<< j << " -> Port : null"<<endl;
            }
        }
    }
    os << "-------------"<<endl<<endl;

    return os.str();
}

void Q2FwdT::finish() {
    if(par("printAtEnd").boolValue()) {
        cout << "-------------"<<endl;
        cout << "Forwarding at "<< getFullPath()<<endl;
        cout << "QoS to Table:"<<endl;
        for(auto QT : Q2T) {
            cout << "    QoS : "<<QT.first << " -> Table : " << QT.second <<endl;
        }
        for(unsigned int i = 0; i< Tables.size(); i++) {
            cout << "Table "<<i <<endl;
            const vPorts & T = Tables[i];
            for(unsigned int j = 0; j < T.size(); j++) {
                port_t p = T[j];
                if(p != nullptr) {
                    cout << "    Addr : "<< j << " -> Port : "<< T[j]->getFullPath()<<endl;
                } else {
                    cout << "    Addr : "<< j << " -> Port : null"<<endl;
                }
            }
        }
        cout << "-------------"<<endl<<endl;
    }
}
