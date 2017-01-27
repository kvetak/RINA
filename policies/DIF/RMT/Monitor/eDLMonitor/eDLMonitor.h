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

#ifndef eDLMonitor_H_
#define eDLMonitor_H_

#include "DIF/RMT/Monitor/SmartMonitor/SmartMonitor.h"

#include <string>
#include <map>
#include <vector>
#include <list>

namespace eDLMonitor {

using namespace std;

typedef list<RMTQueue*> QueuesList;
typedef map<RMTPort*, RMTQueue* > port2Queue;
typedef map<RMTPort*, QueuesList > port2Queues;
typedef map<RMTPort*, unsigned int > port2Count;

typedef map<int, double> i2d;

struct dlCUInfo {
    std::string CUId, queue;
    int urgency;
    int threshold;
    double dropProb;
    int absThreshold;

    dlCUInfo();
    dlCUInfo(std::string id);
    dlCUInfo(std::string id, std::string _queue, int urg, int thre, double dropP, int absThre);
};

typedef std::map<std::string, dlCUInfo> cuRepo;
typedef cuRepo::iterator cuRepoiterator;

typedef std::map<RMTQueue*, std::string> queue2CU;


typedef std::map<int, QueuesList> PriorityQueuesList;
typedef PriorityQueuesList::iterator PQListIterator;
typedef PriorityQueuesList::reverse_iterator PQListRIterator;

typedef std::map<RMTPort*, PriorityQueuesList> Port2PQ;

class eDLMonitor : public SmartMonitor
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
    cuRepo CUs;
    queue2CU Q2CU;

    port2Queues inQ;
    Port2PQ outQs;

    port2Count inC, outC, lastInsertedUrgency;
    i2d probs;
};

}

#endif /* SIMPLEMONITOR_H_ */
