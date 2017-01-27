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
#include "DIF/RMT/Monitor/ModularMonitor/SM_Burst/SM_Burst.h"

#include <string>
#include <map>
#include <vector>
#include <list>

namespace MM_maxDelayLimited_Out {

using namespace std;
using namespace ModularMonitor;

class MM_maxDelayLimited_Out : public Int_MM_Out_Module
{
    public:
    ~MM_maxDelayLimited_Out();
        void finish();

        void pduInsertered(RMTQueue *, RMTPort *);
        void pduDropped(RMTQueue *, const cPacket *, RMTPort *);
        void pduReleased(RMTQueue *, RMTPort *);
        void queueCreated(RMTQueue *, RMTPort *);

        RMTQueue * getnextQueue(RMTPort *);
        simtime_t  getnextTime(RMTPort *);

    protected:
        map<string , simtime_t> queueName2Delay;
        int defaultMaxDel;
        map<RMTQueue * , simtime_t> queueDelay;

        map<string , double> queueName2Multip;
        map<RMTQueue * , double> queueMultip;


        map<string , simtime_t> queueName2BurstTime;
        map<string , unsigned int> queueName2BurstSize;

        map<RMTPort* , set<RMTQueue*> > portQueues;
        map<RMTQueue* , list<simtime_t> > queueInTime;
        map<RMTQueue* , SM_Burst > queueBurstCount;

        void initialize();
};

}
