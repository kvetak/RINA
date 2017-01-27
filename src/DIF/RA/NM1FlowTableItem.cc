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

#include "DIF/RA/NM1FlowTableItem.h"

NM1FlowTableItem::NM1FlowTableItem(Flow* flow, FABase* fa, RMTPort* port, std::string gateName)
:   flow(flow), fa(fa), rmtPort(port), gateName(gateName), conStatus(CON_CONNECTPENDING)
{
}

NM1FlowTableItem::~NM1FlowTableItem() {

}

std::string NM1FlowTableItem::info() const {
    std::ostringstream os;


    os << flow->info() << endl;
    os << "FA path: " << fa->getFullPath() << endl;
    os << "status: " << getConnectionStatusString() << endl;
    os << "RMT port: " << rmtPort->getFullName() << endl;

    return os.str();
}

std::string NM1FlowTableItem::getConnectionStatusString() const {
    switch(this->conStatus)
    {
        case CON_NIL:               return "null";
        case CON_FLOWPENDING:       return "flowpending";
        case CON_CONNECTPENDING:    return "connectpending";
        case CON_AUTHENTICATING:    return "authenticating";
        case CON_ESTABLISHED:       return "established";
        case CON_RELEASING:         return "releasing";
        case CON_ERROR:
        default:                return "UNKNOWN";
    }
}


NM1FlowTableItem::ConnectionStatus NM1FlowTableItem::getConnectionStatus()
{
    return this->conStatus;
}

void NM1FlowTableItem::setConnectionStatus(ConnectionStatus conStatus) {
    this->conStatus = conStatus;
}

std::ostream& operator <<(std::ostream& os, const NM1FlowTableItem& cte) {
    return os << cte.info();
}

Flow* NM1FlowTableItem::getFlow() const
{
    return flow;
}


FABase* NM1FlowTableItem::getFABase() const
{
    return fa;
}

RMTPort* NM1FlowTableItem::getRMTPort() const
{
    return rmtPort;
}


const RMTQueues& NM1FlowTableItem::getRMTInputQueues() const
{
    return rmtPort->getInputQueues();
}


const RMTQueues& NM1FlowTableItem::getRMTOutputQueues() const
{
    return rmtPort->getOutputQueues();
}


std::string NM1FlowTableItem::getGateName() const
{
    return gateName;
}



