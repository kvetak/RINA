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
 * @file RcvrAckPolicyLG.cc
 * @author Marcel Marek (imarek@fit.vutbr.cz)
 * @date May 3, 2015
 * @brief This is an example policy class implementing LG RcvrAck behavior
 * @detail
 */

#include "DIF/EFCP/DTCP/RcvrAck/RcvrAckPolicyLG/RcvrAckPolicyLG.h"

const char * ECN_MARKED_DATA = "ECN_MARKED_DATA";

Register_Class(RcvrAckPolicyLG);

RcvrAckPolicyLG::RcvrAckPolicyLG()
{
}

RcvrAckPolicyLG::~RcvrAckPolicyLG()
{
}

void RcvrAckPolicyLG::initialize() {
    sigStatECNMarked = registerSignal(ECN_MARKED_DATA);
}


bool RcvrAckPolicyLG::run(DTPState* dtpState, DTCPState* dtcpState)
{
    Enter_Method("RcvrAckPolicyLG");

    DTP* dtp = getRINAModule<DTP*>(this, 1, { MOD_DTP });

    unsigned int seqNum;
    seqNum = dtpState->getRcvLeftWinEdge();


    // Send Ack/Flow Control PDU with LWE and RWE
    AckFlowPDU* ackFlowPdu = new AckFlowPDU();
    dtp->setPDUHeader(ackFlowPdu);
    ackFlowPdu->setSeqNum(dtcpState->getNextSndCtrlSeqNum());

    ackFlowPdu->setAckNackSeqNum(seqNum);

    dtp->fillFlowControlPDU(ackFlowPdu);

    if(dtpState->isEcnSet()) {
        ackFlowPdu->setFlags(ackFlowPdu->getFlags() | ECN_FLAG);
        emit(sigStatECNMarked, seqNum);
    }

    dtp->sendToRMT(ackFlowPdu);


    return false;
}
