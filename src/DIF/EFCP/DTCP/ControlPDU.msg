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
#include "PDU.h"
}}
message PDU;

message ControlPDU extends PDU{
    type = -1;
//    unsigned int controlSeqNum;
}


message NAckPDU extends ControlPDU{
    unsigned int ackNackSeqNum;
    
}
message FlowControlPDU extends NAckPDU {
    unsigned int newRightWinEdge;
	unsigned int newRate;
    unsigned long timeUnit;
    unsigned int myLeftWinEdge;
    unsigned int myRightWinEdge;
    unsigned int myRcvRate;
}



message AckOnlyPDU extends NAckPDU{
    type = ACK_ONLY_PDU;
}

message NackOnlyPDU extends NAckPDU{
    type = NACK_ONLY_PDU;
}

message AckFlowPDU extends FlowControlPDU{
    type = ACK_FLOW_PDU;
}

message NackFlowPDU extends FlowControlPDU{
    type = NACK_FLOW_PDU;
}

message FlowControlOnlyPDU extends FlowControlPDU{
    type = FLOW_ONLY_PDU;
}


message SelectiveNAckFlow extends FlowControlPDU{
    unsigned int newLeftWinEdge;
    
    
    unsigned int nackListLen;
    unsigned int nackList [];
}

message SelectiveAckFlowPDU extends SelectiveNAckFlow{
    type = SELECT_ACK_FLOW_PDU;
}

message SelectiveNackFlowPDU extends SelectiveNAckFlow{
    type = SELECT_NACK_FLOW_PDU;
}

message SelectiveAckPDU extends SelectiveNAckFlow{
    type = SELECT_ACK_PDU;
}

message SelectiveNackPDU extends SelectiveNAckFlow{
    type = SELECT_NACK_PDU;
}

message ControlAckPDU extends ControlPDU{
    type = CONTROL_ACK_PDU;
    
	unsigned int lastCtrlSeqNumRcv;
	unsigned int sndLtWinEdge;
	unsigned int sndRtWinEdge;
	unsigned int myLtWinEdge;
	unsigned int myRtWinEdge;
	unsigned int myRcvRate;
}