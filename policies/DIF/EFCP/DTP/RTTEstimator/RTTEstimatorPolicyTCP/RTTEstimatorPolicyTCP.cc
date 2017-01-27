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

#include "DIF/EFCP/DTP/RTTEstimator/RTTEstimatorPolicyTCP/RTTEstimatorPolicyTCP.h"
Register_Class(RTTEstimatorPolicyTCP);
RTTEstimatorPolicyTCP::RTTEstimatorPolicyTCP() {
    // TODO Auto-generated constructor stub
    state = STATE_FIRST;
    k = 4;
    G = 0.1;
    RTO = 1;

    sigStatTCPRTO = registerSignal("TCP_RTO");
}

RTTEstimatorPolicyTCP::~RTTEstimatorPolicyTCP() {
    // TODO Auto-generated destructor stub
}

bool RTTEstimatorPolicyTCP::run(DTPState* dtpState, DTCPState* dtcpState)
{
    double alpha = 0.125;
    double beta = 0.25;
    double newRtt = 0;
    /* Calculating RTT */
    ControlPDU* pdu = (ControlPDU*) dtpState->getCurrentPdu();
    if (pdu->getType() & PDU_SEL_BIT) {

    } else {
        if (pdu->getType() & PDU_ACK_BIT) {
            unsigned int seqNum = ((AckOnlyPDU*) pdu)->getAckNackSeqNum();
            std::vector<DTCPRxExpiryTimer*>* pduQ =
                    dtcpState->getRxQ();
            std::vector<DTCPRxExpiryTimer*>::iterator it;
            bool foundAck = false;
            for (it = pduQ->begin(); it != pduQ->end(); ++it) {
                if ((*it)->getPdu()->getSeqNum() == seqNum) {
                    foundAck = true;
                    double now = simTime().dbl();
                    double sent = (*it)->getSent();
                    newRtt = now - sent;

                    newRtt = floor(newRtt * 1000000000);
                    newRtt = newRtt / 1000000000;

                }
            }
            if (!foundAck) {
                EV
                << "RTTEstimator: Did not find PDU on RxQ to compare times."
                << endl;
                return false;
            }

        } else {

        }
    }
    EV << "Current RTT: " << newRtt << endl;
    /* End */

    if(state == STATE_FIRST) {
        RTTVar = newRtt / 2;
        SRTT = newRtt;
        state = STATE_NEXT;
    } else {
        double t = SRTT - newRtt;
        if( t < 0 )
            t *= -1;
        RTTVar = (1 - beta) * RTTVar + beta * t;
        SRTT = (1 - alpha) * SRTT + alpha * newRtt;
    }
    RTO = SRTT + std::max(G, k * RTTVar);

    if(RTO < 1)
        RTO = 1;

    dtpState->setRtt(newRtt);
//    dtcpState->RTO = RTO;

    emit(sigStatTCPRTO, RTO);

    return false;
}
