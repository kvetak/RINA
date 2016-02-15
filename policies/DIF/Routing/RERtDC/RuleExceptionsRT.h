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

#include <IntRouting.h>

#include "DCAddr.h"
#include "DCLinkInfo.h"
#include "DCLinkUpdate.h"
#include "DC_Defines.h"
#include "RawExceptions.h"


#include <vector>
#include <set>
#include <map>
#include <queue>

namespace RERtDC {

using namespace std;
using namespace NSPSimpleDC;
using namespace REFwdDC;



struct nodeNeig {
    DCAddr n_addr;
    Address addr;
    bool status;
    long timestamp;

    LinksUpdate * tempUpdate;

    nodeNeig();
    void init(DCAddr _n_addr, Address _addr);

    LinksUpdate * popUpdate();
    void addInfo(const linkInfo & li);
    void addInfo(const vector<linkInfo> & lli);
    bool emptyUpdate();
};

class RuleExceptionsRT: public IntRouting {
public:

    RuleExceptionsRT();
    virtual ~RuleExceptionsRT();

    //Process a Routing Update, return true => inform FWDG of the update
    bool processUpdate(IntRoutingUpdate * update);

    //Flow inserted/removed
    void insertNeighbour(const Address &addr, const DCAddr &dst);
    void removeNeighbour(const Address &addr, const DCAddr &dst);

    virtual RawExceptionsList getExceptions() = 0;

protected:
    DCAddr Im;

    nodeNeig * myNeis;
    portId myNeisSize;

    map<linkId, linkInfo> linksStatus;

    void onPolicyInit();
    void finish();
    virtual void handleMessage(cMessage * msg);

    virtual void startMyNeis() = 0;
    virtual portId getNeiId(Address addr);
    virtual portId getNeiId(DCAddr addr) = 0;


    cMessage * clean, * start;
    unsigned int nPod, nTor, nFab, nSpine, nEdgeP;
    long oldAfter, expiresAfter;

    void cleanOK();
    void FirstUpdate();
    void Update();

    void addToUpdates(linkInfo li);



    bool preparseFailures();
    void clearParsedFailures();

    Addr2setDCAddr problemsUp, problemsDown;
    uchar2setuchar deadToR, deadPodFabric, deadSpineFabric, deadSpineDown, deadSpineUp, deadEdge;
};
}
