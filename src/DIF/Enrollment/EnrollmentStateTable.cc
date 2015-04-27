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

#include "EnrollmentStateTable.h"

Define_Module(EnrollmentStateTable);

void EnrollmentStateTable::initialize()
{
    WATCH_LIST(StateTable);
}

void EnrollmentStateTable::insert(EnrollmentStateTableEntry entry) {
    StateTable.push_back(entry);
}

EnrollmentStateTableEntry* EnrollmentStateTable::findEntryByDstAPN(const APN& apn) {
    for(EnrollStateTableIter it = StateTable.begin(); it != StateTable.end(); ++it) {
        EnrollmentStateTableEntry est = *it;
        if (est.getFlow()->getDstAddr().getApname() == apn)
            return &(*it);
    }
    return NULL;
}

void EnrollmentStateTable::handleMessage(cMessage *msg)
{

}
