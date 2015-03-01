//
// Copyright © 2014 - 2015 PRISTINE Consortium (http://ict-pristine.eu)
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

#include <NM1FlowTableItem.h>

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
        case CON_NIL:               return "NULL";
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


FABase* NM1FlowTableItem::getFaBase() const
{
    return fa;
}

RMTPort* NM1FlowTableItem::getRmtPort() const
{
    return rmtPort;
}


const RMTQueues& NM1FlowTableItem::getRmtInputQueues() const
{
    return rmtPort->getInputQueues();
}


const RMTQueues& NM1FlowTableItem::getRmtOutputQueues() const
{
    return rmtPort->getOutputQueues();
}


std::string NM1FlowTableItem::getGateName() const
{
    return gateName;
}



