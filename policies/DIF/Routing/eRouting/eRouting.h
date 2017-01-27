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
#include <map>
#include "DIF/Routing/eRouting/eLink.h"

using namespace std;


typedef uint32_t lseq_t;


struct update_t {
    lseq_t s;
    bool status;
    simtime_t t;

    update_t() {
        s = 0;
        status = true;
        t = 0.0;
    }
};


struct nei_info {
    update_t status;
    Address dst;
    map<elink_t, update_t> pending;
};

class LinkHello : public IntRoutingUpdate {
public:
    elink_t link;
    lseq_t s;
};

class statusUpdate : public IntRoutingUpdate {
public:
    map<elink_t, update_t> info;
};


struct nodesStatus {
    vector<elink_t> ownFailures;
    vector<elink_t> othersFailures;
};

class eRouting: public IntRouting {
public:
    virtual void finish();
    virtual bool processUpdate(IntRoutingUpdate * update);
    virtual void handleMessage(cMessage *msg);

    void registerLink(const elink_t & e, const Address & n);
    void onLink(const elink_t & e);
    void offLink(const elink_t & e);

    nodesStatus getProblems();

protected:
    virtual void onPolicyInit();

    void sendUpdates();

    bool firstUpdate;
    cMessage * updateTimer, * clearCacheTimer;
    double cacheTime, updateDelay;
    set<Address> neis;
    map<elink_t, nei_info> links;

    map<elink_t, update_t> linksInfo;
};
