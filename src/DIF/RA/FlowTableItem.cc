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

#include <FlowTableItem.h>

FlowTableItem::FlowTableItem(Flow* flow, FABase* fa, cGate* rmtPort)
:   flow(flow), fa(fa), rmtPort(rmtPort)
{
}

FlowTableItem::~FlowTableItem() {

}

std::string FlowTableItem::info() const {
    std::ostringstream os;

    if (flow != NULL)
    {
        os << flow->info() << endl;
    }
    if (fa != NULL)
    {
        os << "FA path: " << fa->getFullPath() << "\n";
    }
    return os.str();
}


std::ostream& operator <<(std::ostream& os, const FlowTableItem& cte) {
    return os << cte.info();
}

Flow* FlowTableItem::getFlow() const
{
    return flow;
}

FABase* FlowTableItem::getFaBase() const
{
    return fa;
}

cGate* FlowTableItem::getRmtPort() const
{
    return rmtPort;
}
