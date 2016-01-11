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

//

cplusplus {{
#include "DataTransferPDU.h"
typedef DataTransferPDU* DTPDU_p;
}}
class noncobject DTPDU_p;

enum DTPTimerType
{
  DTP_SENDER_INACTIVITY_TIMER = 1;
  DTP_RCVR_INACTIVITY_TIMER = 2;   
//  DTP_RX_EXPIRY_TIMER = 3;
//  DTP_WINDOW_TIMER = 4;
//  DTP_SENDING_RATE_TIMER = 5;
  DTP_A_TIMER = 6;
//  DTCP_SND_RENDEZ_TIMER = 7;
  DTP_INTERRUPTER_TIMER = 8;
//  DTP_DELIMITING_TIMER = 9;
  
}

enum InterrupterActionType
{
  INTERRUPTER_ZERO_RCV_CREDIT = 1;
  INTERRUPTER_INFLATE_RCV_CREDIT = 2;   

  
}
message DTPTimers {
	int type enum(DTPTimerType);
}

message InactivityTimer extends DTPTimers{
 
}

message SenderInactivityTimer extends InactivityTimer{
    type = DTP_SENDER_INACTIVITY_TIMER;
}

message RcvrInactivityTimer extends InactivityTimer{
    type = DTP_RCVR_INACTIVITY_TIMER;
}

//message DelimitingTimer extends DTPTimers{
//    type = DTP_DELIMITING_TIMER;
//}

//message RxExpiryTimer extends DTPTimers{
//    type = DTP_RX_EXPIRY_TIMER;
//    DTPDU_p pdu = NULL;
//    unsigned int expiryCount = 0;
//    double sent = 0;
//}

//message WindowTimer extends DTPTimers{
//    type = DTP_WINDOW_TIMER;
//}

//message SendingRateTimer extends DTPTimers{
//	type = DTP_SENDING_RATE_TIMER;   
//}

message ATimer extends DTPTimers{
 	type = DTP_A_TIMER;   
 	DTPDU_p pdu = NULL;
 	unsigned int seqNum;
}

message TheInterrupterTimer extends DTPTimers{
 type = DTP_INTERRUPTER_TIMER;
 int action enum(InterrupterActionType);
}


