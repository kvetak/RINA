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
#define PDU_HEADER_LEN 10
#include "Address.h"
#include "APN.h"
#include "ConnectionId.h"
//#include "UserDataField.h"

//typedef cMessage* cMessagePtr;
//typedef cObject* cObjectPtr;
//typedef UserDataField* UserDataFieldPtr;

}}
class noncobject Address;
class noncobject APN;
class noncobject ConnectionId;
//class noncobject cMessagePtr;
//class noncobject cObjectPtr;





enum PDUType{
    	EFCP_PDU 				= 0x8000;
    	DATA_TRANSFER_PDU 		= 0x8001;
    	CONTROL_ACK_PDU 		= 0x8003;
        ACK_ONLY_PDU 			= 0x8804;
        NACK_ONLY_PDU 			= 0x8805;
        SELECT_ACK_PDU 			= 0x8806;
        SELECT_NACK_PDU 		= 0x8807;
        FLOW_ONLY_PDU 			= 0x8808;
        ACK_FLOW_PDU 			= 0x880C;
        NACK_FLOW_PDU 			= 0x880D;
        SELECT_ACK_FLOW_PDU 	= 0x880E;
        SELECT_NACK_FLOW_PDU 	= 0x880F;

}

enum PDUTypeBits{
    	PDU_NACK_BIT	= 0x01;
    	PDU_SEL_BIT		= 0x02;
    	PDU_ACK_BIT		= 0x04;
    	PDU_FC_BIT		= 0x08;
}

//TODO A1
enum FLAGS{
}



packet PDU {
    @customize(true);
    string displayString;
    unsigned int version = 1;
    Address srcAddr;
    Address dstAddr;
    APN srcApn; 
    APN dstApn;  
    ConnectionId connId;
    int type enum(PDUType);
    int flags = 0; //8bits
    unsigned int pduLen = PDU_HEADER_LEN;
    unsigned int seqNum;
//    cObject userData; //unsigned char []? string?
//    unsigned char userData[];
//    cMessagePtr mUserData;
    
    
    
}

//packet DataTransferPDU extends PDU{
//    type = DATA_TRANSFER_PDU;
//    
//}





