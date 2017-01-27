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

#include "DIF/RMT/PDUForwarding/NeiTable/NeiTable.h"
#include <iostream>

Register_Class(NeiTable);


using namespace std;

#include <sstream>

void NeiTable::initialize()
{
    //Inits
    //initSignalsAndListeners();

    sigStatPDUFTLENGTH = registerSignal(SIG_STAT_PDUFT_LENGTH);
    // Display active policy name.
    cDisplayString& disp = getDisplayString();
    disp.setTagArg("t", 1, "t");
    disp.setTagArg("t", 0, getClassName());
    onPolicyInit();
}

// Lookup function, return a list of RMTPorts to forward a PDU/Address+qos.
vector<RMTPort *> NeiTable::lookup(const PDU * pdu) {
    return lookup(pdu->getDstAddr(), pdu->getConnId().getQoSId());
}
vector<RMTPort *> NeiTable::lookup(const Address &dst, const std::string&qos) {
    vector<RMTPort*> ret;
    if(dst.getIpcAddress().getName() == "") { return ret; }

    auto p = table[dst.getIpcAddress().getName()][qos];
    if(p) { ret.push_back(p); }
    else if(qos == QoSCube::MANAGEMENT.getQosId()) {
        for(auto q_p : table[dst.getIpcAddress().getName()]) {
            if(q_p.second != nullptr) {
                ret.push_back(q_p.second);
                break;
            }
        }
    }


    return ret;
}
// Returns a representation of the Forwarding Knowledge
string NeiTable::toString()
{
    std::ostringstream os;

    os << this->getName() << endl;
    for(auto dst_q_p : table) {
        os << "\t" << dst_q_p.first << endl;
        for(auto q_p : dst_q_p.second) {
            if(q_p.second) {
                os << "\t\t->(" << q_p.first << " , " << q_p.second->getFullPath()
                    << ")" << endl;
            } else {
                os << "\t\t->(" << q_p.first << " , null)" << endl;
            }
        }
    }
    return os.str();
}
void NeiTable::insert(const string &addr, const std::string&qos, RMTPort * port) {
    table[addr][qos] = port;
    emit(sigStatPDUFTLENGTH, (long) table.size());
}
void NeiTable::remove(const string &addr, const std::string&qos) {
    table[addr].erase(qos);
    if (table[addr].empty())
    {
        table.erase(addr);
    }

    emit(sigStatPDUFTLENGTH, (long) table.size());
}
// Called after initialize
void NeiTable::onPolicyInit(){}
void NeiTable::initSignalsAndListeners()
{
    sigStatPDUFTLENGTH = registerSignal(SIG_STAT_PDUFT_LENGTH);
}
void NeiTable::finish()
{
    if (par("printAtEnd").boolValue())
    {
        EV << toString() << endl;
    }
}

