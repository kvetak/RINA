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

#ifndef DLMonitor_H_
#define DLMonitor_H_

#include "RMTQMonitorBase.h"

#include <string>
#include <map>
#include <vector>
#include <list>

struct dlCUInfo {
    std::string CUId;
    int urgency;
    int threshold;

    dlCUInfo();
    dlCUInfo(std::string id);
    dlCUInfo(std::string id, int urg, int thre);
};

typedef std::map<std::string, dlCUInfo> cuRepo;
typedef cuRepo::iterator cuRepoiterator;

typedef std::pair<RMTPort*, std::string> portCU;

typedef std::map<RMTQueue*, std::string> queue2CU;

typedef std::map<RMTPort*, int> portVal;

typedef std::list<RMTQueue*> queuesList;
typedef std::map<int, queuesList> PriorityQueuesList;
typedef PriorityQueuesList::iterator PQListIterator;
typedef PriorityQueuesList::reverse_iterator PQListRIterator;

typedef std::map<RMTPort*, PriorityQueuesList> PortPQL;


class DLMonitor : public RMTQMonitorBase
{
  public:
    virtual void onPolicyInit();
    virtual void onMessageArrival(RMTQueue* queue);
    virtual void onMessageDeparture(RMTQueue* queue);
    virtual void onMessageDrop(RMTQueue* queue, const cPacket* pdu);
    virtual void postQueueCreation(RMTQueue* queue);

    virtual int getPortCount(RMTPort* port);
    virtual int getThreshold(RMTQueue* queue);
    virtual RMTQueue* getNextUrgentQ(RMTPort * port);



  protected:
    cuRepo CUs;
    queue2CU Q2CU;

    portVal count;
    portVal lastInsertedUrgency;
    PortPQL queues;
};

#endif /* SIMPLEMONITOR_H_ */
