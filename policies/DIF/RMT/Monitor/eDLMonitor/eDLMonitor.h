//
// Copyright © 2014 - 2015 PRISTINE Consortium (http://ict-pristine.eu)
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

#ifndef eDLMonitor_H_
#define eDLMonitor_H_

#include "SmartMonitor.h"

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
    void onMessageArrival(RMTQueue* queue);
    void onMessageDeparture(RMTQueue* queue);
    void onMessageDrop(RMTQueue* queue, const cPacket* pdu);
    void postQueueCreation(RMTQueue* queue);

    int getInCount(RMTPort* port);
    int getInThreshold(RMTQueue * queue);
    RMTQueue* getNextInput(RMTPort* port);

    int getOutCount(RMTPort* port);
    int getOutThreshold(RMTQueue * queue);
    RMTQueue* getNextOutput(RMTPort* port);

    queueStat getInStat(RMTQueue * queue);
    queueStat getOutStat(RMTQueue * queue);

  protected:
    cuRepo CUs;
    queue2CU Q2CU;

    port2Queue inM, outM;
    port2Queues inQ;
    Port2PQ outQs;

    port2Count inC, outC, lastInsertedUrgency;
    i2d probs;
};

}

#endif /* SIMPLEMONITOR_H_ */
