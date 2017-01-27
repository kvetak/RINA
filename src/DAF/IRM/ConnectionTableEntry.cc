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

#include "DAF/IRM/ConnectionTableEntry.h"

ConnectionTableEntry::ConnectionTableEntry()
    :  //FlowObject(NULL)
       apni(APNamingInfo()), conStatus(CON_ERROR),
       northGateIn(NULL), northGateOut(NULL),
       southGateIn(NULL), southGateOut(NULL),
       FlowAlloc(NULL)
{
}

ConnectionTableEntry::ConnectionTableEntry(Flow* flow)
    :  conStatus(CON_FLOWPENDING),
       northGateIn(NULL), northGateOut(NULL),
       southGateIn(NULL), southGateOut(NULL),
       FlowAlloc(NULL)
{
    apni = flow->getSrcApni();
}

ConnectionTableEntry::~ConnectionTableEntry() {
    //this->FlowObject = NULL;
    this->conStatus = CON_ERROR;
    this->northGateIn = NULL;
    this->northGateOut = NULL;
    this->southGateIn = NULL;
    this->southGateOut = NULL;
    this->FlowAlloc = NULL;
}

std::string ConnectionTableEntry::info() const {
    std::ostringstream os;
    os << apni.info() << "\n";
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
        case CON_NIL:               return "NULL";
        case CON_FLOWPENDING:       return "flow pending";
        case CON_CONNECTPENDING:    return "connect pending";
        case CON_AUTHENTICATING:    return "authenticating";
        case CON_ESTABLISHED:       return "established";
        case CON_RELEASING:         return "releasing";
        case CON_ERROR:
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

cModule* ConnectionTableEntry::getIpc() const {
    return FlowAlloc->getModuleByPath("^.^");
}

const APNamingInfo& ConnectionTableEntry::getApni() const {
    return apni;
}

void ConnectionTableEntry::setApni(const APNamingInfo& apni) {
    this->apni = apni;
}

ConnectionTableEntry::ConnectionStatus ConnectionTableEntry::getConStatus() const {
    return conStatus;
}
