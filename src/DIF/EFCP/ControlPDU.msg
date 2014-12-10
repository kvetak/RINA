//
// Copyright © 2014 PRISTINE Consortium (http://ict-pristine.eu)
// 
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
// 

cplusplus {{
#include "PDU.h"
}}
message PDU;

message ControlPDU extends PDU{
    type = -1;
//    unsigned int controlSeqNum;
}

message FlowControlPDU extends ControlPDU {
    unsigned int newRightWinEdge;
	unsigned int newRate;
    unsigned long timeUnit;
    unsigned int myLeftWinEdge;
    unsigned int myRightWinEdge;
    unsigned int myRcvRate;
}

message NAckPDU extends ControlPDU{
    unsigned int ackNackSeqNum;
    
}

message AckOnlyPDU extends NAckPDU{
    type = ACK_ONLY_PDU;
}

message NackOnlyPDU extends NAckPDU{
    type = NACK_ONLY_PDU;
}
message NAck extends NAckPDU{
    
}

message NAckFlow extends FlowControlPDU{
    unsigned int ackNackSeqNum;
}

message AckFlowPDU extends NAckFlow{
    type = ACK_FLOW_PDU;
}

message NackFlowPDU extends NAckFlow{
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