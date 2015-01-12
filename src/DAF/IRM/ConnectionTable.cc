//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
// 

#include "ConnectionTable.h"

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

void ConnectionTable::insertNew(Flow* flow, cGate* nIn, cGate* nOut) {
    Enter_Method("insertNew()");
    this->insert(ConnectionTableEntry(flow, nIn, nOut));
}

void ConnectionTable::insert(const ConnectionTableEntry& entry) {
    Enter_Method("insert()");
    ConTable.push_back(entry);
}

void ConnectionTable::remove() {
}

ConnectionTableEntry* ConnectionTable::findEntryByFlow(Flow* flow) {
    for(TCTIter it = ConTable.begin(); it != ConTable.end(); ++it) {
        //EV << "Comparing" << it->getFlowObject() << " and " << flow << endl;
        //EV << "=========NOVY=========\n" << it->getFlowObject()->info() << endl;
        //EV << "=========STARY=========\n" << flow->info() << endl;
        if ( *(it->getFlowObject()) == *flow )
            return &(*it);
    }
    return NULL;
}

bool ConnectionTable::setSouthGates(Flow* flow, cGate* sIn, cGate* sOut) {
    ConnectionTableEntry* cte = this->findEntryByFlow(flow);
    if (cte) {
        cte->setSouthGateIn(sIn);
        cte->setSouthGateOut(sOut);
        return true;
    }
    else
        return false;
}

bool ConnectionTable::setNorthGates(Flow* flow, cGate* nIn, cGate* nOut) {
    ConnectionTableEntry* cte = this->findEntryByFlow(flow);
    if (cte) {
        cte->setNorthGateIn(nIn);
        cte->setNorthGateOut(nOut);
        return true;
    }
    else
        return false;
}

bool ConnectionTable::setFa(Flow* flow, FABase* fa) {
    ConnectionTableEntry* cte = this->findEntryByFlow(flow);
    if (cte) {
        cte->setFlowAlloc(fa);
        return true;
    }
    else
        return false;
}

cGate* ConnectionTable::findOutputGate(cGate* input) {
    for(TCTIter it = ConTable.begin(); it != ConTable.end(); ++it) {
        if ( it->getNorthGateIn() == input )
            return it->getSouthGateOut();
        if ( it->getSouthGateIn() == input )
            return it->getNorthGateOut();
    }
    return NULL;
}

bool ConnectionTable::setStatus(Flow* flow, ConnectionTableEntry::ConnectionStatus status) {
    ConnectionTableEntry* cte = this->findEntryByFlow(flow);
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
    ConnectionTableEntry* cte = this->findEntryByFlow(flow);
    return cte ? cte->getFlowAlloc() : NULL;
}
