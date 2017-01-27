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
#include "DIF/EFCP/DTP/DataTransferPDU.h"
typedef DataTransferPDU* DTPDU_p;
}}
class noncobject DTPDU_p;


enum DTCPTimerType
{
//  DTCP_WINDOW_TIMER = 1;
  DTCP_RX_EXPIRY_TIMER = 2;
  DTCP_SENDING_RATE_TIMER = 3;
  DTCP_RENDEZVOUS_TIMER = 4;
  DTCP_REL_C_PDU_TIMER = 5;
//  DTCP_SND_RENDEZ_TIMER = 6;
//  DTCP_RCV_RENDEZ_TIMER = 7;
}
message DTCPTimers {
	int type enum(DTCPTimerType);
}

//message WindowTimer extends DTCPTimers{
//    type = DTCP_WINDOW_TIMER;
//}


message DTCPRxExpiryTimer extends DTCPTimers{
    type = DTCP_RX_EXPIRY_TIMER;
    DTPDU_p pdu = NULL;
    unsigned int expiryCount = 0;
    double sent = 0;
}

message DTCPSendingRateTimer extends DTCPTimers{
  type = DTCP_SENDING_RATE_TIMER;
}

message DTCPRendezvousTimer extends DTCPTimers{
  type = DTCP_RENDEZVOUS_TIMER;
  unsigned int seqNum = 0;
  unsigned int counter = 0;
    
}

message DTCPReliableControlPDUTimer extends DTCPTimers{
  type = DTCP_REL_C_PDU_TIMER;  
}

//message DTCPSndRendezTimer extends DTCPTimers{
//  type = DTCP_SND_RENDEZ_TIMER;
//  unsigned int seqNum = 0;  
//}