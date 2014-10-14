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

#include "SearchTable.h"

//Constants
const char*   ELEM_SEARCHTAB    = "SearchTable";
const char*   ELEM_PEER         = "Peer";

Define_Module(SearchTable);

void SearchTable::initialize()
{
    //Parse XML config
    parseConfig(par(PAR_CONFIGDATA).xmlValue());

    //Init watchers
    WATCH_LIST(SrchTable);
}

SearchTableEntry* SearchTable::findSearchEntryByApn(const APN& apn) {
    for (SearchItem it = SrchTable.begin(); it != SrchTable.end(); ++it) {
        if (it->getApn() == apn)
            return &(*it);
    }
    return NULL;
}

void SearchTable::handleMessage(cMessage *msg)
{
    // TODO - Generated method body
}

void SearchTable::addSearchEntry(const APN& apn) {
    SrchTable.push_back(SearchTableEntry(apn));
}

const APNList* SearchTable::findPeersByApn(const APN& apn) {
    SearchTableEntry* entry = findSearchEntryByApn(apn);
    return entry ? &(entry->getPeers()) : NULL;
}

void SearchTable::addNewPeerDa(const APN& apn, const APN& peer) {
    findSearchEntryByApn(apn)->addPeer(peer);
}

void SearchTable::removeSearchEntry(const APN& apn) {
    SrchTable.remove(*(findSearchEntryByApn(apn)));
}

void SearchTable::parseConfig(cXMLElement* config) {
}
