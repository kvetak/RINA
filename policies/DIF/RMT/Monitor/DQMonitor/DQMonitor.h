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

#ifndef DQMonitor_H_
#define DQMonitor_H_

#include "SmartMonitor.h"

#include "dlCUInfo.h"

#include <string>
#include <map>
#include <vector>
#include <list>

namespace DQMonitor {

using namespace std;

typedef std::map<std::string, L> lRepo;
typedef std::map<std::string, C> cRepo;
typedef std::map<std::string, U> uRepo;
typedef std::map<std::string, dlCUInfo> cuRepo;


typedef std::map<RMTQueue*, dlCUInfo*> queue2CU;


typedef list<RMTQueue*> QueuesList;
typedef map<RMTPort*, RMTQueue* > port2Queue;
typedef map<RMTPort*, QueuesList > port2Queues;

/*
typedef cuRepo::iterator cuRepoiterator;



typedef std::map<int, QueuesList> PriorityQueuesList;
typedef PriorityQueuesList::iterator PQListIterator;
typedef PriorityQueuesList::reverse_iterator PQListRIterator;

typedef std::map<RMTPort*, PriorityQueuesList> Port2PQ;
*/

class DQMonitor : public SmartMonitor
{
public:
    void onPolicyInit();
    void postPDUInsertion(RMTQueue* queue);
    void onMessageDrop(RMTQueue* queue, const cPacket* pdu);
    void postQueueCreation(RMTQueue* queue);

//    int getInCount(RMTPort* port);
//    int getInThreshold(RMTQueue * queue);

    double getInDropProb(RMTQueue * queue);
    RMTQueue* getNextInput(RMTPort* port);
    simtime_t getNextInputTime(RMTPort* port);

//    int getOutCount(RMTPort* port);
//    int getOutThreshold(RMTQueue * queue);

    double getOutDropProb(RMTQueue * queue);
    RMTQueue* getNextOutput(RMTPort* port);

  protected:
    lRepo Ls;
    cRepo Cs;
    uRepo Us;
    cuRepo CUs;
    queue2CU Q2CU;

    map< RMTPort*, map<L*, list<simtime_t> > > LTimes;
    map< RMTPort*, map<L*, list<simtime_t> > > SpaceTimes;
    map< RMTPort*, simtime_t> nextServe;

    map< RMTPort*, map<L*, list<RMTQueue*> > > LQueues;

    map< RMTQueue*, list<simtime_t> > UTimes;
    map< RMTQueue*, int > lastUrgency;

    map< RMTPort*, map<int, list<RMTQueue*> > > UQueues;

    map<RMTPort*, unsigned int > outC;

    void parseL(cXMLElement* xml);
    void parseC(cXMLElement* xml);
    void parseU(cXMLElement* xml);
};

}

#endif /* SIMPLEMONITOR_H_ */
