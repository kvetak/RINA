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

#ifndef __RINA_NEIGHBORTABLE_H_
#define __RINA_NEIGHBORTABLE_H_

#include <omnetpp.h>
//RINASim libraries
#include "NeighborTableEntry.h"
#include "ExternConsts.h"

typedef std::list<NeighborTableEntry> NeighborEntries;
typedef NeighborEntries::iterator NeiEntryItem;
typedef NeighborEntries::const_iterator NeiEntryCItem;

//Constants
extern const char*   ELEM_NEIGHTAB;
extern const char*   ELEM_NEIGHBOR;

class NeighborTable : public cSimpleModule
{
  public:
    void addNeighborEntry(const APN& apn);
    NeighborTableEntry* findNeighborEntryByApn(const APN& apn);
    const APNList* findNeighborsByApn(const APN& apn);
    const APNList* findApnsByNeighbor(const APN& neighbor);
    void addNewNeighbor(const APN& apn, const APN& neighbor);
    void removeNeighborEntry(const APN& apn);
  protected:
    NeighborEntries NeiTable;

    virtual void initialize();
    virtual void handleMessage(cMessage *msg);

    void parseConfig(cXMLElement* config);

};

#endif
