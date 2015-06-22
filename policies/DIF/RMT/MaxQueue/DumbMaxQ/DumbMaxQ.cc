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

#include <DumbMaxQ.h>


Define_Module(DumbMaxQ);

void DumbMaxQ::onPolicyInit()
{
    monitor = dynamic_cast<SmartMonitor*>(qMonPolicy);
    if (monitor == NULL)
    {
        EV << "!!! DumbMaxQ has to be used in conjecture with SmartMonitor!" << endl;
    }
}

bool DumbMaxQ::run(RMTQueue* queue)
{
    bool drop = false;
    double dp;
    switch (queue->getType()) {
        case RMTQueue::INPUT: dp = monitor->getInDropProb(queue); break;
        case RMTQueue::OUTPUT: dp = monitor->getOutDropProb(queue); break;
    }

    if( dp <= 0 ) { return false; }
    if( dp >= 1 ) { drop = true; }
    else { drop = dp >= uniform(0,1); }

    if(drop) {
        std::string qos = ((PDU*)queue->getLastPDU())->getConnId().getQoSId();
        if(queue->getType() == RMTQueue::INPUT){
            dropIn[qos]++;
        } else {
            dropOut[qos]++;
        }
    }

    return drop;
}


void  DumbMaxQ::finish(){
    if(!dropIn.empty() || !dropOut.empty()) {
        EV << "--------"<< endl;
        EV << "At " << getFullPath()<< endl;
        std::map<std::string, unsigned int>::iterator it;

        if(!dropIn.empty() ) {
            EV << "On input:" <<endl;
            for(it = dropIn.begin(); it!= dropIn.end(); it++){
                EV << "QoS " << it->first << " - Dropped "<< it->second << endl;
            }
        }

        if(!dropOut.empty() ) {
            EV << "On output:" <<endl;
            for(it = dropOut.begin(); it!= dropOut.end(); it++){
                EV << "QoS " << it->first << " - Dropped "<< it->second << endl;
            }
        }
        EV << "--------"<< endl;
    }
}
