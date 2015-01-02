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
:   flow(flow), fa(fa), rmtPort(port), gateName(gateName)
{
}

NM1FlowTableItem::~NM1FlowTableItem() {

}

std::string NM1FlowTableItem::info() const {
    std::ostringstream os;

    if (flow != NULL)
    {
        os << flow->info() << endl;
    }
    if (fa != NULL)
    {
        os << "FA path: " << fa->getFullPath() << "\n";
    }
//    if (rmtOutputQueue != NULL)
//    {
//        os << "output RMT queue: " << rmtOutputQueue->getName() << "\n";
//    }
//    if (rmtInputQueue != NULL)
//    {
//        os << "input RMT queue: " << rmtInputQueue->getName();
//    }
    return os.str();
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



