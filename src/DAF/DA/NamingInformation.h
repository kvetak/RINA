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

#ifndef __RINA_NAMINGINFORMATION_H_
#define __RINA_NAMINGINFORMATION_H_

#include <omnetpp.h>
//RINASim libraries
#include "DAF/DA/NamingInformationEntry.h"
#include "Common/ExternConsts.h"

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

    void udateDisplayString();

};

#endif
