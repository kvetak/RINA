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

#include "DIF/RMT/Scheduler/IterativeScheduling/IterativeScheduling.h"


namespace IterativeScheduling {

Define_Module(IterativeScheduling);

using namespace std;

    void IterativeScheduling::addQueue(RMTPort* port, RMTQueue * q) {
        queues[port].insert(q);
        if(queues[port].size() == 1) { lastQ[port] = queues[port].begin(); }
    }
    void IterativeScheduling::removeQueue(RMTPort* port, RMTQueue * q) {
        if(*lastQ[port] == q) { lastQ[port]++; }
        queues[port].erase(q);
        if(lastQ[port] == queues[port].end()) { lastQ[port] = queues[port].begin(); }
    }

    void IterativeScheduling::processQueues(RMTPort* port, RMTQueueType direction) {
        Enter_Method("processQueues()");

        switch(direction){
            case RMTQueue::INPUT:
                if (port->isInputReady() && port->getWaiting(RMTQueue::INPUT)) {
                    RMTQueue* inQ = port->getLongestQueue(RMTQueue::INPUT);
                    inQ->releasePDU();
                }
            break;
            case RMTQueue::OUTPUT:
                if (port->isOutputReady() && port->getWaiting(RMTQueue::OUTPUT)) {
                    for( int k = queues[port].size(); k > 0; k--) {
                        RMTQueue * outQ = *lastQ[port];
                        if(outQ && outQ->getLength() > 0) {
                            lastQ[port]++;
                            if(lastQ[port] == queues[port].end()) { lastQ[port] = queues[port].begin(); }
                            outQ->releasePDU();
                            return;
                        } else {
                            lastQ[port]++;
                            if(lastQ[port] == queues[port].end()) { lastQ[port] = queues[port].begin(); }
                        }
                    }
                }
        }
    }


    void IterativeScheduling::finish(){
        if(par("printAtEnd").boolValue()) {
            cout << "----------------" << endl;
            std::cout << "IterativeScheduling::finish" << endl;
            cout << getFullPath() << endl << endl;
            for(auto & pl : queues) {
                cout << pl.first->getFullPath() << endl;
                for(auto & q : pl.second) {
                    cout <<  "\t" << q->getFullPath() << endl;
                    cout <<  "\t\t" << q->getLength();
                    cout <<  " / " << q->getThreshLength() << endl;
                }
                auto it = lastQ[pl.first];
                if(it == pl.second.end()) {
                    cout << "\tCurrent : out of bounds" <<endl;
                } else {
                    cout << "\tCurrent : " << (*it)->getFullPath() <<endl;
                }
            }
            cout << "----------------" << endl;
        }
    }

}

