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

#include <omnetpp.h>
#include "DIF/RMT/Scheduler/RMTSchedulingBase.h"
#include <map>
#include <set>

namespace IterativeScheduling {

using namespace std;


    class IterativeScheduling : public RMTSchedulingBase {
        public:
            void addQueue(RMTPort* port, RMTQueue * q);
            void removeQueue(RMTPort* port, RMTQueue * q);

            void finish();
        private:
            void processQueues(RMTPort* port, RMTQueueType direction);

        protected:
            map<RMTPort*, set<RMTQueue *> > queues;
            map<RMTPort*, set<RMTQueue *>::iterator> lastQ;
    };
}

