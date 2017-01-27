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

#include "DIF/RMT/MaxQueue/REDUpstreamNotifier/REDUpstreamNotifier.h"

Define_Module(REDUpstreamNotifier);

void REDUpstreamNotifier::onPolicyInit()
{
    sigStatUpstreamNotifierSeqNum = registerSignal("REDUpstreamNotifierSeqNum");
}

bool REDUpstreamNotifier::run(RMTQueue* queue)
{
    // simple version:
    // Send out the notification when an output (N-1)-port is overflowing.
    double notifyProb = 0;
    double len = queue->getLength();
    double thrLen = queue->getThreshLength();
    double maxLen = queue->getMaxLength();

    if(len >= maxLen)
        notifyProb = 1;

    if ((len < maxLen) && (len >= thrLen) ) {
        notifyProb = 1 / (maxLen - thrLen) * (len - thrLen);
    }

    const double rand = dblrand();
    if(rand < notifyProb){
        if (queue->getType() == RMTQueue::OUTPUT)
        { // (N-1)-port output queues are filling up => stop accepting more PDUs
            PDU_Base* pdu = (PDU_Base*)queue->getLastPDU();
            notifySenderOfCongestion(queue->getLastPDU());
            emit(sigStatUpstreamNotifierSeqNum, pdu->getSeqNum());
        }
    }

    return false;
}

