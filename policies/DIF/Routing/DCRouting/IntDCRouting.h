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

#pragma once

#include "DIF/Routing/IntRouting.h"
#include <vector>
#include <set>
#include <map>
#include <queue>
#include "DIF/RMT/PDUForwarding/SimpleDCForwarding/DCAddr.h"

namespace NSPSimpleDC {

using namespace std;

struct linkId {
    /*
    * type - (src/dst)
    *      0   - (TOR/Fabric)
    *      1   - (Fabric/Spine)
    */
    DCAddr src, dst;

    linkId();
    linkId(const DCAddr &_src, const DCAddr &_dst);

    bool operator<(const linkId &o) const;
    bool operator==(const linkId & o) const;
    bool operator!=(const linkId & o) const;
};

struct linkInfo {
    /*
     * link
     *      Affected link
     *
     * status
     *      true    - link OK
     *      false   - link KO
     * timestamp
     *      last time the link state changed
     */
    linkId link;
    bool status;
    simtime_t timestamp;

    linkInfo();
    linkInfo(const linkId &_link, const bool &_status, const simtime_t &_timestamp);
};

struct tableNode {
    int d;
    set<const linkId *> L;
    tableNode();
    tableNode(const linkId * n);

    void insert (set<const linkId *> Ls);
};

class LinksUpdate : public IntRoutingUpdate {
    public:
        vector<linkInfo> linksStatus;

        LinksUpdate * toDst(Address dst);
};

struct rtEntry {
    DCAddr dst;
    set<DCAddr> next;
};

class IntDCRouting: public IntRouting {
public:
    //Process a Routing Update, return true => inform FWDG of the update
    bool processUpdate(IntRoutingUpdate * update);

    //Flow inserted/removed
    void insertNeighbour(const Address &addr, const DCAddr &dst);
    void removeNeighbour(const Address &addr, const DCAddr &dst);

    //Get Changes
    vector<rtEntry>  getChanges();
    vector<rtEntry>  getAll();

protected:
    DCAddr Im;

    cMessage * clean, * start, * sched;
    int pods, torXpod, fabricXpod, spineXfabric, edgeSets;
    simtime_t updateWait, expiration;

    map<linkId, linkInfo> myLinks, linksOk, linksKo;
    set<Address> activeNeighbours;

    map<DCAddr, set<const linkId *>> cache;

    // Called after initialize
    void onPolicyInit();

    //Used for cache cleaning
    virtual void handleMessage(cMessage * msg);


    virtual void activeNeigh(const DCAddr &dst) = 0;
    virtual void inactiveNeigh(const DCAddr &dst) = 0;

    virtual void printAtEnd() = 0;

    virtual void startMyLinks() = 0;
    void scheduleUpdate();
    void scheduleClean();

    map<DCAddr, tableNode> * computeTable();

    vector<DCAddr> getNeis(DCAddr);

    virtual set<DCAddr> getNotOptimalDst(map<DCAddr, tableNode> *  table) = 0;

    void finish();
};
}
