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

cplusplus {{
#include "Common/PDU.h"
}}
packet PDU;

packet ControlPDU extends PDU{
    type = -1;
//    unsigned int controlSeqNum;
}


packet NAckPDU extends ControlPDU{
    unsigned int ackNackSeqNum;
    
}
packet FlowControlPDU extends NAckPDU {
    unsigned int rcvRightWinEdge;
	unsigned int rcvRate;
    unsigned long timeUnit;
    unsigned int sndLeftWinEdge;
    unsigned int sndRightWinEdge;
    unsigned int sndRate;
}



packet AckOnlyPDU extends NAckPDU{
    type = ACK_ONLY_PDU;
}

packet NackOnlyPDU extends NAckPDU{
    type = NACK_ONLY_PDU;
}

packet AckFlowPDU extends FlowControlPDU{
    type = ACK_FLOW_PDU;
}

packet NackFlowPDU extends FlowControlPDU{
    type = NACK_FLOW_PDU;
}

packet FlowControlOnlyPDU extends FlowControlPDU{
    type = FLOW_ONLY_PDU;
}


packet SelectiveNAckFlow extends FlowControlPDU{
    unsigned int newLeftWinEdge;
    
    
    unsigned int nackListLen;
    unsigned int nackList [];
}

packet SelectiveAckFlowPDU extends SelectiveNAckFlow{
    type = SELECT_ACK_FLOW_PDU;
}

packet SelectiveNackFlowPDU extends SelectiveNAckFlow{
    type = SELECT_NACK_FLOW_PDU;
}

packet SelectiveAckPDU extends SelectiveNAckFlow{
    type = SELECT_ACK_PDU;
}

packet SelectiveNackPDU extends SelectiveNAckFlow{
    type = SELECT_NACK_PDU;
}

packet ControlAckPDU extends ControlPDU{
    type = CONTROL_ACK_PDU;
    
	unsigned int lastCtrlSeqNumRcv;
	unsigned int rcvLeftWinEdge;
	unsigned int rcvRightWinEdge;
	unsigned int sndLeftWinEdge;
	unsigned int sndRightWinEdge;
	unsigned int rcvRate;
}

packet RendezvousPDU extends ControlAckPDU{
    type = RENDEZVOUS_PDU;
    
    unsigned int rendezSeqNum;
    
}
