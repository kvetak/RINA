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

#include "DAF/DA/NamingInformation.h"

//Constants
const char*   ELEM_NAMINGTABLE     = "NamingInfo";
const char*   ELEM_SYNONYM         = "Synonym";

Define_Module(NamingInformation);

void NamingInformation::initialize()
{
    //Parse XML config
    parseConfig(par(PAR_CONFIGDATA).xmlValue());

    udateDisplayString();
    //Init watchers
    WATCH_LIST(NamingInfoTable);
}

void NamingInformation::addNamingEntry(const APN& apn) {
    NamingInfoTable.push_back(NamingInformationEntry(apn));
}

NamingInformationEntry* NamingInformation::findNamingEntryByApn(const APN& apn) {
    for (NamingItem it = NamingInfoTable.begin(); it != NamingInfoTable.end(); ++it) {
        if (it->getApn() == apn)
            return &(*it);
    }
    return NULL;
}

void NamingInformation::addNewSynonym(const APN& apn, const APN& synonym) {
    findNamingEntryByApn(apn)->addSynonym(synonym);
}

void NamingInformation::removeNamingEntry(const APN& apn) {
    NamingInfoTable.remove(*(findNamingEntryByApn(apn)));
}

NamingInformationEntry* NamingInformation::findNamingEntryBySynonym(const APN& synonym) {
    for (NamingItem it = NamingInfoTable.begin(); it != NamingInfoTable.end(); ++it) {
        if (it->hasSynonym(synonym))
            return &(*it);
    }
    return NULL;

}

const APN* NamingInformation::findApnBySynonym(const APN& synonym) {
    NamingInformationEntry* entry = findNamingEntryBySynonym(synonym);
    return entry ? &(entry->getApn()) : NULL;
}

void NamingInformation::handleMessage(cMessage *msg)
{

}

const APNList NamingInformation::findAllApnNames(const APN& apn) {
    NamingInformationEntry* entry1 = findNamingEntryByApn(apn);
    NamingInformationEntry* entry2 = findNamingEntryBySynonym(apn);

    APNList result = APNList();
    //APN does not exist within NamingInfo
    if (entry1 == NULL && entry2 == NULL) {
        EV << "No NamingInfo thus considering " << apn << " as unique!" << endl;
        result.push_back(apn);
    }
    //APN without any synonyms
    else if (entry1 != NULL && entry2 == NULL) {
        result.push_back(apn);
    }
    //Found based on synonym
    else if (entry1 == NULL && entry2 != NULL) {
        result = entry2->getSynonyms();
        result.push_back(apn);
    }
    //Inconsistancy where two different NI are returned
    else {
        EV << "NamingInfo contains inconsistency" << endl
           << *entry1 << endl
           << *entry2 << endl;
    }
    return result;
}

void NamingInformation::parseConfig(cXMLElement* config) {
    cXMLElement* mainTag = NULL;
    if (config != NULL && config->hasChildren() && config->getFirstChildWithTag(ELEM_NAMINGTABLE))
        mainTag = config->getFirstChildWithTag(ELEM_NAMINGTABLE);
    else {
        EV << "configData parameter not initialized!" << endl;
        return;
    }


    cXMLElementList apnlist = mainTag->getChildrenByTagName(ELEM_APN);
    for (cXMLElementList::const_iterator it = apnlist.begin(); it != apnlist.end(); ++it) {
        cXMLElement* m = *it;

        if (!(m->getAttribute(ATTR_APN) && m->getFirstChildWithTag(ELEM_SYNONYM))) {
            EV << "\nError when parsing NaimingInfo record" << endl;
            continue;
        }

        APN newapn = APN(m->getAttribute(ATTR_APN));

        addNamingEntry(newapn);

        cXMLElementList synonymlist = m->getChildrenByTagName(ELEM_SYNONYM);
        for (cXMLElementList::const_iterator jt = synonymlist.begin(); jt != synonymlist.end(); ++jt) {
            cXMLElement* n = *jt;

            if (!(n->getAttribute(ATTR_APN))) {
                EV << "\nError when parsing Synonym record" << endl;
                continue;
            }

            addNewSynonym(newapn, APN(n->getAttribute(ATTR_APN)));
        }
    }
}

void NamingInformation::udateDisplayString() {
    //Update display string
    std::ostringstream description;
    description << NamingInfoTable.size() << " entries";
    this->getDisplayString().setTagArg("t", 0, description.str().c_str());
    this->getDisplayString().setTagArg("t", 1, "t");
}
