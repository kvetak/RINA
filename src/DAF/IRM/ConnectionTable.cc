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

#include "ConnectionTable.h"

Define_Module(ConnectionTable);

void ConnectionTable::initialize()
{
    WATCH_LIST(ConTable);
    //Insert info to the ConnectionTable

    //Scan all AEs in DAP and add them to table
    for (cModule::SubmoduleIterator i(this->getParentModule()); !i.end(); i++) {
        cModule *submodp = i();
        if (dynamic_cast<AEBase*>(submodp))
            insertNewAe(dynamic_cast<AEBase*>(submodp));
    }
}

std::string ConnectionTable::info() const {
    std::stringstream os;
    os << "id=" << this->getId() << endl;
    /*
    for(TCTConstIter it = ConTable.begin(); it != ConTable.end(); ++it )
    {
        ConnectionTableEntry cte = *it;
        os << cte << endl;
    }
    */
    return os.str();
}

void ConnectionTable::insert(const ConnectionTableEntry& entry) {
    Enter_Method("insert()");
    ConTable.push_back(entry);
}

void ConnectionTable::remove() {
}

ConnectionTableEntry* ConnectionTable::findEntryByAe(AEBase* ae) {
    for(TCTIter it = ConTable.begin(); it != ConTable.end(); ++it) {
        if (it->getAppEntity() == ae)
            return &(*it);
    }
    return NULL;
}

ConnectionTableEntry* ConnectionTable::findEntryByFlow(const Flow* flow) {
    for(TCTIter it = ConTable.begin(); it != ConTable.end(); ++it) {
        if ( it->getAppEntity()->isFlowUsed(flow) )
            return &(*it);
    }
    return NULL;
}

void ConnectionTable::insertNewAe(AEBase* ae) {
    ConnectionTableEntry* entry = new ConnectionTableEntry(ae);
    insert(*entry);
}

void ConnectionTable::handleMessage(cMessage *msg)
{

}
