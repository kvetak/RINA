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
 * @file DTCPTxControlPolicyTCPTahoe.cc
 * @author
 * @date Jan 9, 2015
 * @brief
 * @detail
 */
#include <DTCPTxControlPolicyTCPTahoe.h>
Register_Class(DTCPTxControlPolicyTCPTahoe);
DTCPTxControlPolicyTCPTahoe::DTCPTxControlPolicyTCPTahoe() {
    // TODO Auto-generated constructor stub
    ssthresh = MAX_SSTHRESH;
    state = STATE_STARTING_SLOW_START;
    rxSent = 0;
    ackRcvd = 0;
    snd_cwnd = RST_WND;
}

DTCPTxControlPolicyTCPTahoe::~DTCPTxControlPolicyTCPTahoe() {
    // TODO Auto-generated destructor stub
}

void DTCPTxControlPolicyTCPTahoe::initialize(int step)
{
    if(step == 0){
        sigStatTCPTahoeCWND = registerSignal("TCP_Tahoe_CWND");
    }
}

bool DTCPTxControlPolicyTCPTahoe::run(DTPState* dtpState, DTCPState* dtcpState)
{
    uint32 sendCredit = 0;

    if( state != STATE_STARTING_SLOW_START ) {
        if( dtcpState->ackRcvd > ackRcvd ) {
            uint32 n = 0;
            n = dtcpState->ackRcvd - ackRcvd;
            ackRcvd = dtcpState->ackRcvd;

            if(state == STATE_SLOW_START && n > 10)
                n = n ; //5;

            if(snd_cwnd >= ssthresh)
                state = STATE_CNG_AVOID;

            int old_cwnd = snd_cwnd;

            for (uint32 i = 0; i < n; i++) {       // Appropriate Byte Counting
                if(state == STATE_SLOW_START)
                    snd_cwnd += 1;
                if(state == STATE_CNG_AVOID)
                    snd_cwnd += 1 / snd_cwnd; // snd_cwnd += SMSS * SMSS / snd_cwnd;
            }

            sendCredit = snd_cwnd - old_cwnd + n;
        }

        if( dtcpState->getRxSent() >  rxSent) {
            ssthresh = std::max(int(snd_cwnd / 2), 2);
            state = STATE_SLOW_START;
            snd_cwnd = RST_WND;
            rxSent = dtcpState->getRxSent();

            sendCredit = snd_cwnd;
        }
    } else {
        state = STATE_SLOW_START;
        sendCredit = snd_cwnd;
    }

    if(sendCredit > 0)
        emit(sigStatTCPTahoeCWND, snd_cwnd);

    // -------------  adding packets to send queue
    std::vector<DataTransferPDU*>::iterator it;
    PDUQ_t* pduQ = NULL;
    uint32 sentNo = 1;

    for(int i = 1; i <= 2; i++) {
        if (dtcpState->getClosedWinQueLen() > 0) {
            pduQ = dtcpState->getClosedWindowQ();
        } else
            pduQ = dtpState->getGeneratedPDUQ();

        for (it = pduQ->begin(); it != pduQ->end() && (*it)->getSeqNum() <= dtcpState->getSenderRightWinEdge() && sentNo <= sendCredit; sentNo++) {
            dtpState->pushBackToPostablePDUQ((*it));
            it = pduQ->erase(it);
        }
    }

    dtcpState->setClosedWindow(true);
//    if (!dtpState->getGeneratedPDUQ()->empty() || dtcpState->getClosedWinQueLen() >= dtcpState->getMaxClosedWinQueLen() || (sentNo > sendCredit) ) {
//        dtcpState->setClosedWindow(true);
//    }

    return false;
}
