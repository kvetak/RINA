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

#pragma once

#include "DIF/RMT/Monitor/ModularMonitor/Int_MM_Out_Module.h"

#include <string>
#include <map>
#include <vector>
#include <list>

namespace MM_psDQ_Out {

using namespace std;

struct UrgProb {
    double prob;
    int urg;

    UrgProb(double, int);
};

struct DegradList {
    int start;
    vector<UrgProb> urgList;

    DegradList(double);
};

struct QueueConfig {
    string id;
    int defPriority;
    double rate;
    vector<DegradList> degradLists;

    QueueConfig();
    QueueConfig(string, int);
};

struct QueueData {
    int count;
    list<simtime_t> cOutTimes;
    map<int, int> countUrg;
    int lastUrgency;


    map<int, int> countUrgstats;

    QueueData();
};

class MM_psDQ_Out : public Int_MM_Out_Module
{
    public:
    ~MM_psDQ_Out();
        void finish();

        void pduInsertered(RMTQueue *, RMTPort *);
        void pduDropped(RMTQueue *, const cPacket *, RMTPort *);
        void pduReleased(RMTQueue *, RMTPort *);
        void queueCreated(RMTQueue *, RMTPort *);

        RMTQueue * getnextQueue(RMTPort *);
        simtime_t  getnextTime(RMTPort *);

    protected:
        map<string, QueueConfig> queuesConf;
        map<RMTQueue *, QueueConfig *> queueConf;
        map<RMTQueue *, QueueData> queueData;

      //  map<string , int> queueName2Priority;
        int defaultPriority;
        int maxPriority;
      //  map<RMTQueue * , int> queuePriority;
      //  map<int, double> prioritySkip;

        map<RMTPort* , set<RMTQueue*> > portQueues;
        map<RMTPort* , int > portCount;

        void initialize();
};

}
