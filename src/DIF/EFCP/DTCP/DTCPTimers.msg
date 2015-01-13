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

cplusplus {{
#include "DataTransferPDU.h"
typedef DataTransferPDU* DTPDU_p;
}}
class noncobject DTPDU_p;


enum DTCPTimerType
{
  DTCP_WINDOW_TIMER = 1;
  DTCP_RX_EXPIRY_TIMER = 2;
  
}
message DTCPTimers {
	int type enum(DTCPTimerType);
}

message WindowTimer extends DTCPTimers{
    type = DTCP_WINDOW_TIMER;
}


message DTCPRxExpiryTimer extends DTCPTimers{
    type = DTCP_RX_EXPIRY_TIMER;
    DTPDU_p pdu = NULL;
    unsigned int expiryCount = 0;
    double sent = 0;
}