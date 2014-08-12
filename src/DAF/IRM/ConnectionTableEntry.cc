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

#include <ConnectionTableEntry.h>

ConnectionTableEntry::ConnectionTableEntry()
    :  FlowObject(NULL), conStatus(UNKNOWN),
       northGateIn(NULL), northGateOut(NULL),
       southGateIn(NULL), southGateOut(NULL),
       FlowAlloc(NULL)
{
}

ConnectionTableEntry::ConnectionTableEntry(Flow* flow)
    :  FlowObject(flow), conStatus(FLOWPENDING),
       northGateIn(NULL), northGateOut(NULL),
       southGateIn(NULL), southGateOut(NULL),
       FlowAlloc(NULL)
{
}

ConnectionTableEntry::ConnectionTableEntry(Flow* flow, cGate* nIn, cGate* nOut)
:  FlowObject(flow), conStatus(FLOWPENDING),
   northGateIn(nIn), northGateOut(nOut),
   southGateIn(NULL), southGateOut(NULL),
   FlowAlloc(NULL)
{
}

ConnectionTableEntry::~ConnectionTableEntry() {
    this->FlowObject = NULL;
    this->conStatus = UNKNOWN;
    this->northGateIn = NULL;
    this->northGateOut = NULL;
    this->southGateIn = NULL;
    this->southGateOut = NULL;
    this->FlowAlloc = NULL;
}

std::string ConnectionTableEntry::info() const {
    std::stringstream os;
    if (FlowObject)
        os << FlowObject->info() << "\n";
    if (FlowAlloc)
        os << "FA path: " << FlowAlloc->getFullPath() << "\n";
    if (northGateIn && northGateOut)
        os << "northIn: " << this->northGateIn->getName() << "[" << this->northGateIn->getIndex() << "]"
           << "\tnorthOut: " << this->northGateOut->getName() << "[" << this->northGateIn->getIndex() << "]\n";
    if (southGateIn && southGateOut)
        os << "southIn: " << this->southGateIn->getName()
           << "\tsouthOut: " << this->southGateOut->getName() << "\n";
    os << "status: " << this->getConnectionStatusString();
    return os.str();
}

std::string ConnectionTableEntry::getConnectionStatusString() const {
    switch(this->conStatus)
    {
        case NIL:               return "NULL";
        case FLOWPENDING:       return "flowpending";
        case CONNECTPENDING:    return "connectpending";
        case AUTHENTICATING:    return "authenticating";
        case ESTABLISHED:       return "established";
        case RELEASING:         return "releasing";
        case UNKNOWN:
        default:                return "UNKNOWN";
    }
}

void ConnectionTableEntry::setConStatus(ConnectionStatus conStatus) {
    this->conStatus = conStatus;
}

std::ostream& operator <<(std::ostream& os, const ConnectionTableEntry& cte) {
    return os << cte.info();
}

FABase* ConnectionTableEntry::getFlowAlloc() const {
    return FlowAlloc;
}

void ConnectionTableEntry::setFlowAlloc(FABase* flowAlloc) {
    FlowAlloc = flowAlloc;
}

Flow* ConnectionTableEntry::getFlowObject() const {
    return FlowObject;
}

void ConnectionTableEntry::setFlowObject(Flow* flowObject) {
    FlowObject = flowObject;
}

cGate* ConnectionTableEntry::getNorthGateIn() const {
    return northGateIn;
}

void ConnectionTableEntry::setNorthGateIn(cGate* northGateIn) {
    this->northGateIn = northGateIn;
}

cGate* ConnectionTableEntry::getNorthGateOut() const {
    return northGateOut;
}

void ConnectionTableEntry::setNorthGateOut(cGate* northGateOut) {
    this->northGateOut = northGateOut;
}

cGate* ConnectionTableEntry::getSouthGateIn() const {
    return southGateIn;
}

void ConnectionTableEntry::setSouthGateIn(cGate* southGateIn) {
    this->southGateIn = southGateIn;
}

cGate* ConnectionTableEntry::getSouthGateOut() const {
    return southGateOut;
}

void ConnectionTableEntry::setSouthGateOut(cGate* southGateOut) {
    this->southGateOut = southGateOut;
}
