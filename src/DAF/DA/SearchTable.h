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

#ifndef __RINA_SEARCHTABLE_H_
#define __RINA_SEARCHTABLE_H_

#include <omnetpp.h>
#include "DAF/DA/SearchTableEntry.h"
#include "Common/ExternConsts.h"

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

private:
    void updateDisplayString();
};

#endif
