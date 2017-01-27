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

#ifndef __RINA_CONNECTIONTABLE_H_
#define __RINA_CONNECTIONTABLE_H_

//Standard libraries
#include <omnetpp.h>
//RINASim libraries
#include "ConnectionTableEntry.h"

typedef std::list<ConnectionTableEntry> TConTable;
typedef TConTable::iterator TCTIter;
typedef TConTable::const_iterator TCTConstIter;

class ConnectionTable : public cSimpleModule
{
  public:
    std::string info() const;

    void insertNew(Flow* flow);
    void insert(const ConnectionTableEntry& entry);
    void remove();

    ConnectionTableEntry* findEntryByFlow(Flow* flow);
    ConnectionTableEntry* findEntryByAPNI(const APNamingInfo& apni);

    cGate* findOutputGate(cGate* input, bool& isGoingUp);

    bool setSouthGates(Flow* flow, cGate* sIn, cGate* sOut);
    bool setNorthGates(Flow* flow, cGate* nIn, cGate* nOut);
    bool setFa(Flow* flow, FABase* fa);
    bool setStatus(Flow* flow, ConnectionTableEntry::ConnectionStatus status);
    ConnectionTableEntry::ConnectionStatus getStatus(Flow* flow);

    FABase* getFa(Flow* flow);

  protected:
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);

  private:
    TConTable ConTable;
};

#endif
