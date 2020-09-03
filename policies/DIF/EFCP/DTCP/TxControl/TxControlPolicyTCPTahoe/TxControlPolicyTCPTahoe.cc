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
/**
 * @file TxControlPolicyTCPTahoe.cc
 * @author
 * @date Jan 9, 2015
 * @brief
 * @detail
 */
#include "DIF/EFCP/DTCP/TxControl/TxControlPolicyTCPTahoe/TxControlPolicyTCPTahoe.h"
Register_Class(TxControlPolicyTCPTahoe);
TxControlPolicyTCPTahoe::TxControlPolicyTCPTahoe() {
    // TODO Auto-generated constructor stub
    ssthresh = MAX_SSTHRESH;
    state = STATE_STARTING_SLOW_START;
    rxSent = 0;
    ackRcvd = 0;
    snd_cwnd = RST_WND;
    flightSize = 0;
}

TxControlPolicyTCPTahoe::~TxControlPolicyTCPTahoe() {
    // TODO Auto-generated destructor stub
}

void TxControlPolicyTCPTahoe::initialize(int step)
{
    if(step == 0){
        sigStatTCPTahoeCWND = registerSignal("TCP_Tahoe_CWND");
    }
    packetSize = par("packetSize");
    ackPolicy = check_and_cast<SenderAckPolicyTCP *>(getModuleByPath("^.senderAckPolicy"));//^.^.efcp
}

void TxControlPolicyTCPTahoe::slowDown() {
    if((simTime().dbl() - lastSlowDownTime) > 2 * rtt ) {
        lastSlowDownTime = simTime().dbl();

        state = STATE_CNG_AVOID;
        snd_cwnd = std::max(int(snd_cwnd / 2), 2);
        ssthresh = snd_cwnd;
    }
}

bool TxControlPolicyTCPTahoe::run(DTPState* dtpState, DTCPState* dtcpState)
{
    int sendCredit = 0;
    double time = simTime().dbl();
    time = time + 1;
    rtt = dtpState->getRtt();

    if( state != STATE_STARTING_SLOW_START ) {
        if( ackPolicy->numOfAcked > ackRcvd ) {
            uint32_t n = 0;
            n = ackPolicy->numOfAcked - ackRcvd;
            flightSize -= n;
            ackRcvd = ackPolicy->numOfAcked;

            if(state == STATE_SLOW_START && n > 10)
            //FIXME: Vesely -> Marek: Resolve!
                n = 5 ; //5 instead of n = n;

            if(snd_cwnd >= ssthresh)
                state = STATE_CNG_AVOID;

//            int old_cwnd = snd_cwnd;

            for (uint32_t i = 0; i < n; i++) {       // Appropriate Byte Counting
                if(state == STATE_SLOW_START)
                    snd_cwnd += 1;
                if(state == STATE_CNG_AVOID)
                    snd_cwnd += 1 / snd_cwnd; // snd_cwnd += SMSS * SMSS / snd_cwnd;
            }

//            sendCredit = int(snd_cwnd) - old_cwnd + n;
            sendCredit = int(snd_cwnd) - flightSize;
        }

        if( dtcpState->getRxSent() >  rxSent) {
            rxSent = dtcpState->getRxSent();
            slowDown();
//            ssthresh = std::max(int(snd_cwnd / 2), 2);
//            state = STATE_SLOW_START;
//            snd_cwnd = RST_WND;
//            rxSent = dtcpState->getRxSent();
//
//            sendCredit = snd_cwnd;
        }
    } else {
        state = STATE_SLOW_START;
        sendCredit = snd_cwnd;
    }

    if(snd_cwnd > dtcpState->getRcvCredit())
        state = STATE_CNG_AVOID;

    emit(sigStatTCPTahoeCWND, snd_cwnd * packetSize);

    // -------------  adding packets to send queue
    std::vector<DataTransferPDU*>::iterator it;
    PDUQ_t* pduQ = NULL;
    int sentNo = 1;

    for(int i = 1; i <= 2; i++) {
        if (dtcpState->getClosedWinQueLen() > 0) {
            pduQ = dtcpState->getClosedWindowQ();
        } else
            pduQ = dtpState->getGeneratedPDUQ();

        for (it = pduQ->begin(); it != pduQ->end() && (*it)->getSeqNum() <= dtcpState->getSndRightWinEdge() && sentNo <= sendCredit; sentNo++) {
            dtpState->pushBackToPostablePDUQ((*it));
            flightSize++;
            it = pduQ->erase(it);
        }
    }

    if (!dtpState->getGeneratedPDUQ()->empty() || dtcpState->getClosedWinQueLen() >= dtcpState->getMaxClosedWinQueLen() || (sentNo > sendCredit) ) {
        dtcpState->setClosedWindow(true);
    }

    return false;
}
