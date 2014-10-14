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

#ifndef __RINA_SEARCHTABLE_H_
#define __RINA_SEARCHTABLE_H_

#include <omnetpp.h>
#include "SearchTableEntry.h"
#include "ExternConsts.h"

typedef std::list<SearchTableEntry> SearchEntries;
typedef SearchEntries::iterator SearchItem;
typedef SearchEntries::const_iterator SearchCItem;

//Constants
extern const char*   ELEM_SEARCHTAB;
extern const char*   ELEM_PEER;


class SearchTable : public cSimpleModule
{
  public:
    void addSearchEntry(const APN& apn);
    SearchTableEntry* findSearchEntryByApn(const APN& apn);
    const APNList* findPeersByApn(const APN& apn);
    void addNewPeerDa(const APN& apn, const APN& peer);
    void removeSearchEntry(const APN& apn);
  protected:
    SearchEntries SrchTable;

    virtual void initialize();
    virtual void handleMessage(cMessage *msg);

    void parseConfig(cXMLElement* config);
};

#endif
