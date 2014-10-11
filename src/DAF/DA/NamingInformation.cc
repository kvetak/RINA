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

#include "NamingInformation.h"

//Constants
const char*   ELEM_NAMINGTABLE     = "NamingInfo";
const char*   ELEM_SYNONYM         = "Synonym";

Define_Module(NamingInformation);

void NamingInformation::initialize()
{
    //Parse XML config
    parseConfig(par(PAR_CONFIGDATA).xmlValue());

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
