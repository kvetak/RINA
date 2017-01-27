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

#include "DAF/DA/SearchTable.h"

//Constants
const char*   ELEM_SEARCHTAB    = "SearchTable";
const char*   ELEM_PEER         = "Peer";

Define_Module(SearchTable);

void SearchTable::updateDisplayString() {
    std::ostringstream description;
    description << SrchTable.size() << " entries";
    this->getDisplayString().setTagArg("t", 0, description.str().c_str());
    this->getDisplayString().setTagArg("t", 1, "t");
}

void SearchTable::initialize()
{
    //Parse XML config
    parseConfig(par(PAR_CONFIGDATA).xmlValue());

    updateDisplayString();
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
