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
    :  conStatus(UNKNOWN), AppEntity(NULL),
       //FlowObject(NULL),
       northGateIn(NULL), northGateOut(NULL),
       southGateIn(NULL), southGateOut(NULL)
{
}

ConnectionTableEntry::ConnectionTableEntry(AEBase* nae) : AppEntity(nae) {
    northGateIn = nae->gate("dataOut")->getPathEndGate();
    northGateOut = nae->gate("dataIn")->getPathStartGate();
    southGateIn = NULL;
    southGateOut = NULL;
}

ConnectionTableEntry::ConnectionTableEntry(AEBase* nae, cGate* norI, cGate* norO)
    : AppEntity(nae), northGateIn(norI), northGateOut(norO)
{
    southGateIn = NULL;
    southGateOut = NULL;
    //FlowObject = NULL;
}

ConnectionTableEntry::ConnectionTableEntry(AEBase* nae, cGate* norI, cGate* norO, cGate* souI, cGate* souO)
    : AppEntity(nae), northGateIn(norI), northGateOut(norO), southGateIn(souI), southGateOut(souO)
{
    //FlowObject = NULL;
}

ConnectionTableEntry::~ConnectionTableEntry() {
    this->AppEntity = NULL;
    //this->FlowObject = NULL;
    this->conStatus = UNKNOWN;
    this->northGateIn = NULL;
    this->northGateOut = NULL;
    this->southGateIn = NULL;
    this->southGateOut = NULL;
}

std::string ConnectionTableEntry::info() const {
    std::stringstream os;
    //FIXME: Veseli
    //if (AppEntity->getF)
    //    os << *(AppEntity->getFlow()) << "\n";
    //else
    //    os << *(AppEntity->getApni()) << "\n";
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

AEBase* ConnectionTableEntry::getAppEntity() const {
    return AppEntity;
}

void ConnectionTableEntry::setAppEntity(AEBase* appEntity) {
    AppEntity = appEntity;
}

const cGate* ConnectionTableEntry::getNorthGateIn() const {
    return northGateIn;
}

void ConnectionTableEntry::setNorthGateIn(cGate* northGateIn) {
    this->northGateIn = northGateIn;
}

const cGate* ConnectionTableEntry::getNorthGateOut() const {
    return northGateOut;
}

void ConnectionTableEntry::setNorthGateOut(cGate* northGateOut) {
    this->northGateOut = northGateOut;
}

const cGate* ConnectionTableEntry::getSouthGateIn() const {
    return southGateIn;
}

void ConnectionTableEntry::setSouthGateIn(cGate* southGateIn) {
    this->southGateIn = southGateIn;
}

const cGate* ConnectionTableEntry::getSouthGateOut() const {
    return southGateOut;
}

void ConnectionTableEntry::setSouthGateOut(cGate* southGateOut) {
    this->southGateOut = southGateOut;
}
