//
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

#ifndef TKMonitor_H_
#define TKMonitor_H_

#include "DIF/RMT/Monitor/SmartMonitor/SmartMonitor.h"

#include <string>
#include <map>
#include <vector>
#include <list>

namespace TKMonitor {

using namespace std;

typedef list<RMTQueue*> QueuesList;
typedef map<RMTPort*, RMTQueue* > port2Queue;
typedef map<RMTPort*, QueuesList > port2Queues;
typedef map<RMTPort*, unsigned int > port2Count;



typedef set<RMTQueue*> QueuesSet;
typedef map<RMTPort*, QueuesSet > port2QueuesS;


struct TKInfo {
    string id;
    int tokensTic;
    int maxTokens;

    TKInfo();
    TKInfo(string _id);
    TKInfo(string _id, int _tokensTic, int _maxTokens);
};

typedef map<string, TKInfo> tkRepo;
typedef tkRepo::iterator tkRepoiterator;



typedef map<int, QueuesList> PriorityQueuesList;
typedef PriorityQueuesList::iterator PQListIterator;
typedef PriorityQueuesList::reverse_iterator PQListRIterator;

struct QTKStatus {
    TKInfo info;
    int tokens;
    int count;
    QTKStatus();
    QTKStatus(TKInfo _info);
};

typedef map<RMTQueue *, QTKStatus> QueueStatus;


class TKMonitor : public SmartMonitor
{
public:
    void onPolicyInit();
    void postPDUInsertion(RMTQueue* queue);
    void onMessageDrop(RMTQueue* queue, const cPacket* pdu);
    void postQueueCreation(RMTQueue* queue);

    RMTQueue* getNextInput(RMTPort* port);
    RMTQueue* getNextOutput(RMTPort* port);

    double getInDropProb(RMTQueue * queue);
    double getOutDropProb(RMTQueue * queue);

  protected:
    tkRepo TKs;
    QueueStatus Qs;
    port2QueuesS OutSet;

    port2Queues inQ;

    port2Count inC, outC;

    int tokensPDU;
};

}

#endif /* SIMPLEMONITOR_H_ */
