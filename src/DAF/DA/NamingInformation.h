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

#ifndef __RINA_NAMINGINFORMATION_H_
#define __RINA_NAMINGINFORMATION_H_

#include <omnetpp.h>
//RINASim libraries
#include "NamingInformationEntry.h"
#include "ExternConsts.h"

typedef std::list<NamingInformationEntry> NamingInformations;
typedef NamingInformations::iterator NamingItem;
typedef NamingInformations::const_iterator NamingCItem;

//Constants
extern const char*   ELEM_NAMINGTABLE;
extern const char*   ELEM_SYNONYM;

class NamingInformation : public cSimpleModule
{
  public:

    void addNamingEntry(const APN& apn);
    NamingInformationEntry* findNamingEntryByApn(const APN& apn);
    NamingInformationEntry* findNamingEntryBySynonym(const APN& synonym);
    const APN* findApnBySynonym(const APN& synonym);
    const APNList findAllApnNames(const APN& apn);
    void addNewSynonym(const APN& apn, const APN& synonym);
    void removeNamingEntry(const APN& apn);

  protected:
    NamingInformations NamingInfoTable;

    virtual void initialize();
    virtual void handleMessage(cMessage *msg);

    void parseConfig(cXMLElement* config);

};

#endif
