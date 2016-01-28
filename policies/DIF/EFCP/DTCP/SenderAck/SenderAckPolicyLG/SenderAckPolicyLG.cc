// The MIT License (MIT)
//
// Copyright (c) 2014-2016 Brno University of Technology, PRISTINE project
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
/**
 * @file SenderAckPolicyLG.cc
 * @author Marcel Marek (imarek@fit.vutbr.cz)
 * @date May 3, 2015
 * @brief This is an example policy class implementing LG SenderAck behavior
 * @detail
 */

#include "SenderAckPolicyLG.h"
#include "DTCP.h"

const char * ECN_MARKED_CTRL = "ECN_MARKED_CTRL";
const char * APPR_LOAD = "APPR_LOAD";

Register_Class(SenderAckPolicyLG);

SenderAckPolicyLG::SenderAckPolicyLG()
{
    load = 0;
    lastLoad = 0;
    gamma = 0.05;
    gamma1 = 0.05;
    gamma2 = 0.5;
//    gamma = 0.05;
//    gamma1 = 0.05;
//    gamma2 = 0.05;
    state = 1;
}

SenderAckPolicyLG::~SenderAckPolicyLG()
{
}

double SenderAckPolicyLG::getLoad() {
    return load;
}

void SenderAckPolicyLG::initialize() {
    sigStatECNMarked = registerSignal(ECN_MARKED_CTRL);
    sigStatApprLoad = registerSignal(APPR_LOAD);

    txControlPolicyLG = getRINAModule<TxControlPolicyLG*>(this, 1, {"txControlPolicy"});
}

bool SenderAckPolicyLG::run(DTPState* dtpState, DTCPState* dtcpState)
{
    Enter_Method("SenderAckPolicyLG");

    //  defaultAction(dtpState, dtcpState);
//    DTCP* dtcp = getRINAModule<DTCP*>(this, 1, {MOD_DTCP});
    /* Default */
    unsigned int endSeqNum = ((NAckPDU*)dtpState->getCurrentPdu())->getAckNackSeqNum();
    unsigned int startSeqNum = endSeqNum;
    bool startTrue = false;
    double lastECN = 0;

    int count = 0;

    std::vector<DTCPRxExpiryTimer*>* rxQ = dtcpState->getRxQ();
    std::vector<DTCPRxExpiryTimer*>::iterator it;

    for (unsigned int index = 0; index < rxQ->size(); )
    {
        DTCPRxExpiryTimer* timer = rxQ->at(index);
        unsigned int seqNum =(timer->getPdu())->getSeqNum();

        if ((seqNum >= startSeqNum || startTrue) && seqNum <= endSeqNum)
        {
            dtcpState->deleteRxTimer(seqNum);
            count++;

            continue;
        }
        index++;
    }
    //update SendLeftWindowEdge
    dtcpState->updateSndLWE(endSeqNum + 1);


    if(endSeqNum >= 2) {
        lastLoad = load;
        if(((NAckPDU*)dtpState->getCurrentPdu())->getFlags() & 0x01) {
            lastECN = 1;
            emit(sigStatECNMarked, ((NAckPDU*)dtpState->getCurrentPdu())->getSeqNum());
            if(load == 0) {
                load = 1;
                state = 2;
                gamma = gamma2;
            } else
                load = (1 - gamma) * load + gamma * 1;
        } else
            load = (1 - gamma) * load + gamma * 0;
    }

    if(state == 2 && lastLoad < load && lastLoad != 0) {
        state = 3;
        gamma = gamma1;
    }

    emit(sigStatApprLoad, load);

    txControlPolicyLG->updateRate(load, count, lastECN);
    dtcpState->setClosedWindow(false);

    return false;
}
