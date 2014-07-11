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

#include "FlowTable.h"

Define_Module(FlowTable);

void FlowTable::initialize()
{
    WATCH(FlowTab);
}

std::string FlowTable::info() const {
    std::stringstream os;
    for(TFTIter it = FlowTab.begin(); it != FlowTab.end(); ++it )
        os << it->first << it->second << endl;
    return os.str();
}

void FlowTable::handleMessage(cMessage *msg)
{

}

std::ostream& operator<< (std::ostream& os, const FlowTable& ft) {
    return os << ft.info();
}

std::ostream& operator<< (std::ostream& os, const TFlowTable& ft) {
    for(TFTIter it = ft.begin(); it != ft.end(); ++it )
    {
        os << it->first << it->second << endl;
    }
    return os;
}

std::ostream& operator<< (std::ostream& os, const TFlowTableEntry& fte) {
    return os << fte.first << "\n" << fte.second << endl;
}
