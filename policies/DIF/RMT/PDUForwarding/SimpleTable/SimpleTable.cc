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

#include "DIF/RMT/PDUForwarding/SimpleTable/SimpleTable.h"
#include <iostream>

Register_Class(SimpleTable::SimpleTable);

namespace SimpleTable {

using namespace std;

#include <sstream>

void SimpleTable::initialize()
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
vector<RMTPort *> SimpleTable::lookup(const PDU * pdu)
{
    return lookup(pdu->getDstAddr(), pdu->getConnId().getQoSId());
}
vector<RMTPort *> SimpleTable::lookup(const Address &dst, const std::string&qos)
{
    vector<RMTPort*> ret;
    string dstAddr = dst.getIpcAddress().getName();
    qos2Port * t = &table[dstAddr];

    if (t->empty())
    {
        return ret;
    }
    if (t->find(qos) != t->end())
    {
        ret.push_back((*t)[qos]);
    }
    else if (!qos.compare(VAL_MGMTQOSID) && t->size() > 0)
    {
        ret.push_back(t->begin()->second);
    }
    if (ret.empty())
    {
        if (t->find(ANY_QOS) != t->end())
        {
           // ret.push_back((*t)[ANY_QOS]);
        }
    }
    return ret;
}
// Returns a representation of the Forwarding Knowledge
string SimpleTable::toString()
{
    std::ostringstream os;

    os << this->getFullPath() << endl;
    for (FWDTableIt tIt = table.begin(); tIt != table.end(); tIt++)
    {
        os << "\t" << tIt->first << endl;
        for (qos2PortIt qIt = tIt->second.begin(); qIt != tIt->second.end();
                qIt++)
        {
            os << "\t\t->(" << qIt->first << " , " << qIt->second->getFullPath()
                    << ")" << endl;
        }
    }
    return os.str();
}
//Insert/Remove an entry
void SimpleTable::insert(const Address &addr, const std::string&qos,
        RMTPort * port)
{
    insert(addr.getIpcAddress().getName(), qos, port);
    emit(sigStatPDUFTLENGTH, (long) table.size());
}
void SimpleTable::remove(const Address &addr, const std::string&qos)
{
    remove(addr.getIpcAddress().getName(), qos);
    emit(sigStatPDUFTLENGTH, (long) table.size());
}
void SimpleTable::insert(const string &addr, const std::string&qos,
        RMTPort * port)
{
    table[addr][qos] = port;
    emit(sigStatPDUFTLENGTH, (long) table.size());
}
void SimpleTable::remove(const string &addr, const std::string&qos)
{
    table[addr].erase(qos);
    if (table[addr].empty())
    {
        table.erase(addr);
    }

    emit(sigStatPDUFTLENGTH, (long) table.size());
}
//Insert/Remove a mini entry
void SimpleTable::insert(const Address &addr, RMTPort * port)
{
    insert(addr.getIpcAddress().getName(), port);
    emit(sigStatPDUFTLENGTH, (long) table.size());
}
void SimpleTable::remove(const Address &addr)
{
    remove(addr.getIpcAddress().getName());
    emit(sigStatPDUFTLENGTH, (long) table.size());
}
void SimpleTable::insert(const string &addr, RMTPort * port)
{
    table[addr][ANY_QOS] = port;
    emit(sigStatPDUFTLENGTH, (long) table.size());
}
void SimpleTable::remove(const string &addr)
{
    table[addr].erase(ANY_QOS);
    if (table[addr].empty())
    {
        table.erase(addr);
    }
    emit(sigStatPDUFTLENGTH, (long) table.size());
}
// Called after initialize
void SimpleTable::onPolicyInit(){}
void SimpleTable::initSignalsAndListeners()
{
    sigStatPDUFTLENGTH = registerSignal(SIG_STAT_PDUFT_LENGTH);
}
void SimpleTable::finish()
{
    if (par("printAtEnd").boolValue())
    {
        EV << toString() << endl;
    }
}
}
