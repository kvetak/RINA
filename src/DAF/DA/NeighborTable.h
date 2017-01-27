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

#ifndef __RINA_NEIGHBORTABLE_H_
#define __RINA_NEIGHBORTABLE_H_

#include <omnetpp.h>
//RINASim libraries
#include "DAF/DA/NeighborTableEntry.h"
#include "Common/ExternConsts.h"

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

private:
    void updateDisplayString();
};

#endif
