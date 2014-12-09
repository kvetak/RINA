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

//
// TODO generated message class
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
  DTP_RX_EXPIRY_TIMER = 3;
//  DTP_WINDOW_TIMER = 4;
  DTP_SENDING_RATE_TIMER = 5;
  DTP_A_TIMER = 6;
  
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


message RxExpiryTimer extends DTPTimers{
    type = DTP_RX_EXPIRY_TIMER;
    DTPDU_p pdu = NULL;
    unsigned int expiryCount = 0;
    double sent = 0;
}

//message WindowTimer extends DTPTimers{
//    type = DTP_WINDOW_TIMER;
//}

//message SendingRateTimer extends DTPTimers{
//	type = DTP_SENDING_RATE_TIMER;   
//}

message ATimer extends DTPTimers{
 	type = DTP_A_TIMER;   
 	DTPDU_p pdu = NULL;
}


