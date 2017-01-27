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

#include "DIF/RMT/Monitor/ModularMonitor/Int_MM_Drop_Module.h"

#include <string>
#include <map>
#include <vector>
#include <list>

namespace MM_PDQ_Drop {

using namespace std;


struct Threshold {
    int limit;
    double prob;

    Threshold(int, double);
};

struct QueueConfig {
    string id;
    int absThreshold;
    vector<Threshold> thresholdList;

    QueueConfig();
    QueueConfig(string, int);
};

class MM_PDQ_Drop : public Int_MM_Drop_Module
{
    public:
        ~MM_PDQ_Drop();

        void pduInsertered(RMTQueue *, RMTPort *);
        void pduDropped(RMTQueue *, const cPacket *, RMTPort *);
        void pduReleased(RMTQueue *, RMTPort *);
        void queueCreated(RMTQueue *, RMTPort *);

        double getDropProbability(RMTQueue *, RMTPort *);

        void finish();
    protected:
        map<string, QueueConfig> queuesConf;
        map<RMTQueue *, QueueConfig *> queueConf;

        map<RMTPort* , set<RMTQueue*> > portQueues;
        map<RMTPort * , int> portCount;

        int defaultThreshold;

        void initialize();
};

}
