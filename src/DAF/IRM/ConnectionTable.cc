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

#include "DAF/IRM/ConnectionTable.h"

Define_Module(ConnectionTable);

void ConnectionTable::initialize()
{
    WATCH_LIST(ConTable);
}

std::string ConnectionTable::info() const {
    std::ostringstream os;
    os << "id=" << this->getId() << endl;
    /*
    for(TCTConstIter it = ConTable.begin(); it != ConTable.end(); ++it )
    {
        ConnectionTableEntry cte = *it;
        os << cte << endl;
    }
    */
    return os.str();
}

void ConnectionTable::insertNew(Flow* flow) {
    Enter_Method("insertNew()");
    this->insert(ConnectionTableEntry(flow));
}

void ConnectionTable::insert(const ConnectionTableEntry& entry) {
    Enter_Method("insert()");
    ConTable.push_back(entry);
}

void ConnectionTable::remove() {
}

ConnectionTableEntry* ConnectionTable::findEntryByAPNI(const APNamingInfo& apni) {
    for(TCTIter it = ConTable.begin(); it != ConTable.end(); ++it) {
        if ( it->getApni() == apni )
            return &(*it);
    }
    return NULL;
}

ConnectionTableEntry* ConnectionTable::findEntryByFlow(Flow* flow) {
    return findEntryByAPNI(flow->getSrcApni());
}

bool ConnectionTable::setSouthGates(Flow* flow, cGate* sIn, cGate* sOut) {
    ConnectionTableEntry* cte = findEntryByAPNI(flow->getSrcApni());
    if (cte) {
        cte->setSouthGateIn(sIn);
        cte->setSouthGateOut(sOut);
        return true;
    }
    else
        return false;
}

bool ConnectionTable::setNorthGates(Flow* flow, cGate* nIn, cGate* nOut) {
    ConnectionTableEntry* cte = findEntryByAPNI(flow->getSrcApni());
    if (cte) {
        cte->setNorthGateIn(nIn);
        cte->setNorthGateOut(nOut);
        return true;
    }
    else
        return false;
}

bool ConnectionTable::setFa(Flow* flow, FABase* fa) {
    ConnectionTableEntry* cte = findEntryByAPNI(flow->getSrcApni());
    if (cte) {
        cte->setFlowAlloc(fa);
        return true;
    }
    else
        return false;
}

cGate* ConnectionTable::findOutputGate(cGate* input, bool& isGoingUp) {
    for(TCTIter it = ConTable.begin(); it != ConTable.end(); ++it) {
        if ( it->getNorthGateIn() == input ) {
            isGoingUp = false;
            return it->getSouthGateOut();
        }
        if ( it->getSouthGateIn() == input ) {
            isGoingUp = true;
            return it->getNorthGateOut();
        }
    }
    return NULL;
}

bool ConnectionTable::setStatus(Flow* flow, ConnectionTableEntry::ConnectionStatus status) {
    ConnectionTableEntry* cte = findEntryByAPNI(flow->getSrcApni());
    if (cte) {
        cte->setConStatus(status);
        return true;
    }
    else
        return false;
}

void ConnectionTable::handleMessage(cMessage *msg)
{

}

FABase* ConnectionTable::getFa(Flow* flow) {
    ConnectionTableEntry* cte = findEntryByAPNI(flow->getSrcApni());
    return cte ? cte->getFlowAlloc() : NULL;
}

ConnectionTableEntry::ConnectionStatus ConnectionTable::getStatus(Flow* flow) {
    ConnectionTableEntry* cte = findEntryByAPNI(flow->getSrcApni());
    if (cte) {
        return cte->getConStatus();
    }
    return ConnectionTableEntry::CON_NIL;
}
