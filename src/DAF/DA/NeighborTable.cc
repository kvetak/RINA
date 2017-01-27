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

#include "DAF/DA/NeighborTable.h"

//Constants
const char*   ELEM_NEIGHTAB        = "NeighborTable";
const char*   ELEM_NEIGHBOR        = "Neighbor";

Define_Module(NeighborTable);

void NeighborTable::updateDisplayString() {
    std::ostringstream description;
    description << NeiTable.size() << " entries";
    this->getDisplayString().setTagArg("t", 0, description.str().c_str());
    this->getDisplayString().setTagArg("t", 1, "t");
}

void NeighborTable::initialize()
{
    //Parse XML config
    parseConfig(par(PAR_CONFIGDATA).xmlValue());

    updateDisplayString();
    //Init watchers
    WATCH_LIST(NeiTable);
}

void NeighborTable::handleMessage(cMessage *msg)
{

}

void NeighborTable::addNeighborEntry(const APN& apn) {
    NeiTable.push_back(NeighborTableEntry(apn));
}

NeighborTableEntry* NeighborTable::findNeighborEntryByApn(const APN& apn) {
    for (NeiEntryItem it = NeiTable.begin(); it != NeiTable.end(); ++it) {
        if (it->getApn() == apn)
            return &(*it);
    }
    return NULL;
}

const APNList* NeighborTable::findNeighborsByApn(const APN& apn) {
    NeighborTableEntry* entry = findNeighborEntryByApn(apn);
    return entry ? &(entry->getNeigbors()) : NULL;
}

void NeighborTable::addNewNeighbor(const APN& apn, const APN& neighbor) {
    findNeighborEntryByApn(apn)->addNeighbor(neighbor);
}

void NeighborTable::removeNeighborEntry(const APN& apn) {
    NeiTable.remove(*(findNeighborEntryByApn(apn)));
}

const APNList* NeighborTable::findApnsByNeighbor(const APN& neighbor) {
    APNList* apnlist = new APNList();
    for (NeiEntryCItem it = NeiTable.begin(); it != NeiTable.end(); ++it) {
        if (it->hasNeighbor(neighbor)) {
            apnlist->push_back(it->getApn());
        }
    }
    return apnlist;
}

void NeighborTable::parseConfig(cXMLElement* config) {
    cXMLElement* mainTag = NULL;
    if (config != NULL && config->hasChildren() && config->getFirstChildWithTag(ELEM_NEIGHTAB))
        mainTag = config->getFirstChildWithTag(ELEM_NEIGHTAB);
    else {
        EV << "configData parameter not initialized!" << endl;
        return;
    }

    cXMLElementList apnlist = mainTag->getChildrenByTagName(ELEM_APN);
    for (cXMLElementList::const_iterator it = apnlist.begin(); it != apnlist.end(); ++it) {
        cXMLElement* m = *it;

        if (!(m->getAttribute(ATTR_APN) && m->getFirstChildWithTag(ELEM_NEIGHBOR))) {
            EV << "\nError when parsing NeighborTable record" << endl;
            continue;
        }

        APN newapn = APN(m->getAttribute(ATTR_APN));

        addNeighborEntry(newapn);

        cXMLElementList neighborlist = m->getChildrenByTagName(ELEM_NEIGHBOR);
        for (cXMLElementList::const_iterator jt = neighborlist.begin(); jt != neighborlist.end(); ++jt) {
            cXMLElement* n = *jt;

            if (!(n->getAttribute(ATTR_APN))) {
                EV << "\nError when parsing Synonym record" << endl;
                continue;
            }

            addNewNeighbor(newapn, APN(n->getAttribute(ATTR_APN)));
        }
    }


}
