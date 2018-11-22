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

#include <RAFTFSM.h>

Define_Module(RAFTFSM);

void RAFTFSM::initialize() {
    this->rib = check_and_cast<RIBBase*>(getModuleByPath("^.^.^.rib.rib"));
}

void RAFTFSM::handleMessage(cMessage *msg) {

}

object_t* RAFTFSM::applyEntry(RAFTLogObj *entry) {
    object_t *obj = NULL;

    if (dynamic_cast<CDAP_M_Write*>(entry->entry)) {
        CDAP_M_Write* msg = check_and_cast<CDAP_M_Write*>(entry->entry);
        obj = this->rib->writeObj(0, &msg->getObjectItem());
    }
    else if (dynamic_cast<CDAP_M_Create*>(entry->entry)) {
        CDAP_M_Create* msg = check_and_cast<CDAP_M_Create*>(entry->entry);
        obj = this->rib->createObj(0, &msg->getObjectItem());
    }

    return obj;
}

