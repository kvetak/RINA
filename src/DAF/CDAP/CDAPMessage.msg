//
// Copyright � 2014 PRISTINE Consortium (http://ict-pristine.eu)
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
    #include "Common/APNamingInfo.h"
    #include "Common/Address.h"
    typedef cObject* ObjectPtr;
}}

class noncobject Address;
class noncobject APNamingInfo;
class noncobject ObjectPtr;

//Message operation codes
enum opCode_t {
    UNKNOWN = 0;
	M_CONNECT = 1;
	M_CONNECT_R = 2;
	M_RELEASE = 3;
	M_RELEASE_R = 4;
	M_CREATE = 5;
	M_CREATE_R = 6;
	M_DELETE = 7;
	M_DELETE_R = 8;
	M_READ = 9;
	M_READ_R = 10;
	M_CANCELREAD = 11;
	M_CANCELREAD_R = 12;
	M_WRITE = 13;
	M_WRITE_R = 14;
	M_START = 15;
	M_START_R = 16;
	M_STOP = 17;
	M_STOP_R = 18;
//	M_INACTIV = 19;
//	M_UNABLE_MAINTAIN = 20;
//	M_STOP_SENDING = 21;
//	M_START_SENDING = 22;
}

// Values for the flags field.
enum flagValues_t {
	F_SYNC = 1;						// set on READ/WRITE to request synchronous r/w
	F_RD_INCOMPLETE = 2;			// set on all but final reply to an M_READ
}

struct objVal_t {					// value of an object
	uint32	intval;
	int32	sintval;
	uint64	int64val;
	int64	sint64val;
	string	strval;
//	char	byteval;				// arbitrary structure or message
	float 	floatval;
	double 	doubleval;
}

// CDAP-reserved authentication types are 0-99 and >1000
// Authentication types 100-1000 are reserved for private application use.
enum authTypes_t {
	AUTH_NONE = 0;					// No authentication
	AUTH_PASSWD = 1;				// User name and password provided
	AUTH_SSHRSA = 2;				// SSH RSA (version 1 or 2)
	AUTH_SSHDSA = 3;				// SSH DSA (version 2 only)
}

enum resultVal_t {
	R_CLASSNOTFOUND = -5;
	R_OBJBADINST = -4;
	R_OBJNOTFOUND = -3;
	R_OS_ERR = -2;
	R_FAIL = -1;
	R_SUCCESS = 0;
	R_SYNC_UNIMP = 1;
	R_FILTER_FALSE = 2;
	R_FILTER_MIXED = 3;
}

// Supported abstract syntax types
enum absSyntax_t {
	GPB = 0x08;
}

// Reserved authentication fields 1-99, >1000 are reserved for CDAP future use.
// Authentication type values 100-1000 are reserved for private application use.
struct authValue_t {
	string authName;			// Authentication name
	string authPassword;		// Authentication password
	string authOther;			// Additional authentication information
};

// General structure holding operation return value and potentionaly its verbal
// explanation for debugging purposes
//Magical length is 8 B
struct result_t {        
    string resultReason;	//Additional explanation of resultValue
    int32 resultValue;		//The result of an operation, indicating its success, partial success in the case of synchronized operations, or reason for failure.
}

// General structure holding authentication related information
// Magic length is 17 B
struct auth_t {
    unsigned char authType enum(authTypes_t);	//Authentication type
    authValue_t authValue;						//Relevant authentication data
}

// General structures for holding naming information regarding requestor/responder
// Magic length is 64 B 
struct naming_t {
	string AEInst;			//AE instance-id							
	string AEName;			//AE name				
	string ApInst;			//AP instance-id				
	string ApName;			//AP name				    
}

struct object_t {
    string objectClass;		//Object class (e.g. flow, string, int)
    string objectName;		//Unambiguous object name
    int objectInstance;     //Synonym to class+name concatenation
    ObjectPtr objectVal;	//Actual object
}

// Magical Header lengths
enum headerBitLengths {        
    hdrInt32 	= 32;
    hdrFiltr	= 128;
    hdrResult	= 132;
    hdrAuth 	= 136;
    hdrNaming 	= 512;
}

//////////////////////////////////////////////
//CDAP general messages
//////////////////////////////////////////////
packet CDAPMessage {
    string displayString;
    unsigned int headerBitLength = 160; //in bits
    Address srcAddr;
    Address dstAddr;
    schedulingPriority = -1;
    int32 opCode enum(opCode_t);
    int32 invokeID;	
}

//////////////////////////////////////////////
//CDAP M_CONNECT(_R) messages
//////////////////////////////////////////////

packet CDAP_M_Connect extends CDAPMessage {	
	displayString = "b=15,15,oval,#0066CC,#0066CC,0";
	opCode enum(opCode_t) = M_CONNECT;
	headerBitLength = (2+3)*hdrInt32 + hdrAuth + 2*hdrNaming;
		
	int32 flags enum(flagValues_t);
	int32 version;		
	int32 absSyntax enum(absSyntax_t);	
	
	auth_t auth;		
	APNamingInfo src;
	APNamingInfo dst;
}

packet CDAP_M_Connect_R extends CDAPMessage {
	displayString = "b=15,15,oval,#0099FF,#0099FF,0";
	opCode enum(opCode_t) = M_CONNECT_R;	
	headerBitLength = (2+3)*hdrInt32 + hdrAuth + 2*hdrNaming + hdrResult;
	
	int32 flags enum(flagValues_t);
	int32 version;		
	int32 absSyntax enum(absSyntax_t);
	
	result_t result;	
	
	auth_t auth;		
	APNamingInfo src;
	APNamingInfo dst;
}

//////////////////////////////////////////////
//CDAP M_RELEASE(_R) messages
//////////////////////////////////////////////

packet CDAP_M_Release extends CDAPMessage {
	displayString = "b=15,15,oval,#993399,#993399,0";    
	opCode enum(opCode_t) = M_RELEASE;
	headerBitLength = (2+2)*hdrInt32;	
		
	int32 flags enum(flagValues_t);
	int32 version;
}

packet CDAP_M_Release_R extends CDAPMessage {
	displayString = "b=15,15,oval,#9966CC,#9966CC,0";
	opCode enum(opCode_t) = M_RELEASE_R;
	headerBitLength = (2+2)*hdrInt32 + hdrResult;
			
	int32 flags enum(flagValues_t);
	int32 version;
	
	result_t result;	
}

//////////////////////////////////////////////
//CDAP M_CREATE(_R) messages
//////////////////////////////////////////////

packet CDAP_M_Create extends CDAPMessage {
	displayString = "b=15,15,oval,#FFEE00,#FFEE00,0";
	opCode enum(opCode_t) = M_CREATE;	
	headerBitLength = (2+3)*hdrInt32 + hdrFiltr;
	
	int32 flags enum(flagValues_t);
	int32 version;
		
	object_t objectItem;
	
	int32 scope;
	string filter;	
}

packet CDAP_M_Create_R extends CDAPMessage {
	displayString = "b=15,15,oval,#FFFF66,#FFFF66,0";
  	opCode enum(opCode_t) = M_CREATE_R;
	headerBitLength = (2+2)*hdrInt32 + hdrResult + hdrFiltr;
	
	int32 flags enum(flagValues_t);
	int32 version;	
		
	object_t objectItem;	
	
	string filter;
	
	result_t result;		
}

//////////////////////////////////////////////
//CDAP M_DELETE(_R) messages
//////////////////////////////////////////////

packet CDAP_M_Delete extends CDAPMessage {
	displayString = "b=15,15,oval,#CC6633,#CC6633,0";    
	opCode enum(opCode_t) = M_DELETE;
	headerBitLength = (2+3)*hdrInt32 + hdrFiltr;
		
	int32 flags enum(flagValues_t);
	int32 version;
		
	object_t objectItem;
	
	int32 scope;
	string filter;		
}

packet CDAP_M_Delete_R extends CDAPMessage {
	displayString = "b=15,15,oval,#CC9966,#CC9966,0";
	opCode enum(opCode_t) = M_DELETE_R;	
	headerBitLength = (2+2)*hdrInt32 + hdrResult + hdrFiltr;
	
	int32 flags enum(flagValues_t);
	int32 version;
			
	object_t objectItem;
	
	string filter;
	
	result_t result;			
}

//////////////////////////////////////////////
//CDAP M_READ(_R) messages
//////////////////////////////////////////////

packet CDAP_M_Read extends CDAPMessage {
	displayString = "b=15,15,oval,#33CCCC,#33CCCC,0"; 
	opCode enum(opCode_t) = M_READ;	
	headerBitLength = (2+3)*hdrInt32 + hdrFiltr;
		
	int32 flags enum(flagValues_t);
	int32 version;
		
	object_t objectItem;
	
	int32 scope;
	string filter;			
}

packet CDAP_M_Read_R extends CDAPMessage {
	displayString = "b=15,15,oval,#33FFCC,#33FFCC,0";
	opCode enum(opCode_t) = M_READ_R;	
	headerBitLength = (2+2)*hdrInt32 + hdrResult + hdrFiltr;
	
	int32 flags enum(flagValues_t);
	int32 version;
			
	object_t objectItem;
	
	string filter;
	
	result_t result;
}

//////////////////////////////////////////////
//CDAP M_CANCELREAD(_R) messages
//////////////////////////////////////////////

packet CDAP_M_CancelRead extends CDAPMessage {
	displayString = "b=15,15,oval,#333366,#333366,0";
	opCode enum(opCode_t) = M_CANCELREAD;	
	headerBitLength = (2+2)*hdrInt32 + hdrResult;
	
	int32 flags enum(flagValues_t);
	int32 version;

	result_t result;	
}

packet CDAP_M_CancelRead_R extends CDAPMessage {
	displayString = "b=15,15,oval,#333399,#333399,0";
	opCode enum(opCode_t) = M_CANCELREAD_R;
	headerBitLength = (2+2)*hdrInt32 + hdrResult;
	
	int32 flags enum(flagValues_t);
	int32 version;
	
	result_t result;		
}

//////////////////////////////////////////////
//CDAP M_WRITE(_R) messages
//////////////////////////////////////////////

packet CDAP_M_Write extends CDAPMessage {
	displayString = "b=15,15,oval,#CC9900,#CC9900,0";
	opCode enum(opCode_t) = M_WRITE;	
	headerBitLength = (2+3)*hdrInt32 + hdrFiltr;
		
	int32 flags enum(flagValues_t);
	int32 version;
		
	object_t objectItem;
	
	int32 scope;
	string filter;			
}

packet CDAP_M_Write_R extends CDAPMessage {
	displayString = "b=15,15,oval,#CC9933,#CC9933,0";
	opCode enum(opCode_t) = M_WRITE_R;	
	headerBitLength = (2+2)*hdrInt32 + hdrResult + hdrFiltr;
	
	int32 flags enum(flagValues_t);
	int32 version;
			
	object_t objectItem;
	
	string filter;
	
	result_t result;		
}

//////////////////////////////////////////////
//CDAP M_START(_R) messages
//////////////////////////////////////////////

packet CDAP_M_Start extends CDAPMessage {
	displayString = "b=15,15,oval,#99CC00,#99CC00,0";
	opCode enum(opCode_t) = M_START;	
	headerBitLength = (2+3)*hdrInt32 + hdrFiltr;
		
	int32 flags enum(flagValues_t);
	int32 version;
		
	object_t objectItem;
	
	int32 scope;
	string filter;			
}

packet CDAP_M_Start_R extends CDAPMessage {
	displayString = "b=15,15,oval,#99FF33,#99FF33,0";
	opCode enum(opCode_t) = M_START_R;
	headerBitLength = (2+2)*hdrInt32 + hdrResult + hdrFiltr;
	
	int32 flags enum(flagValues_t);
	int32 version;
			
	object_t objectItem;
	
	string filter;
	
	result_t result;		
}

//////////////////////////////////////////////
//CDAP M_STOP(_R) messages
//////////////////////////////////////////////

packet CDAP_M_Stop extends CDAPMessage {
	displayString = "b=15,15,oval,#FF3333,#FF3333,0";	
	opCode enum(opCode_t) = M_STOP;	
	headerBitLength = (2+3)*hdrInt32 + hdrFiltr;
		
	int32 flags enum(flagValues_t);
	int32 version;
		
	object_t objectItem;
	
	int32 scope;
	string filter;		
}

packet CDAP_M_Stop_R extends CDAPMessage {
	displayString = "b=15,15,oval,#FF6666,#FF6666,0";
	opCode enum(opCode_t) = M_STOP_R;	
	headerBitLength = (2+2)*hdrInt32 + hdrResult + hdrFiltr;
	
	int32 flags enum(flagValues_t);
	int32 version;
			
	object_t objectItem;
	
	string filter;
	
	result_t result;
}


//////////////////////////////////////////////////////
// To inform app (socket) about inactivity //////////
/////////////////////////////////////////////////////
//message CDAP_M_Inactiv extends CDAPMessage {
//    displayString = "b=15,15,oval,#FF0000,#FF0000,0";
//	opCode enum(opCode_t) = M_INACTIV;
//	int invokeID;	
//	unsigned char flags enum(flagValues_t);
//	int version;	
//	result_t result;
//	object_t object;
//	int filter;			
//}



//////////////////////////////////////////////////////
// To inform app (socket) about that we were unable //
// to maintain QoS parameters                       //
//////////////////////////////////////////////////////
//message CDAP_M_Unable_Maintain extends CDAPMessage {
//  displayString = "b=15,15,oval,#FF0000,#FF0000,0";
//	opCode enum(opCode_t) = M_UNABLE_MAINTAIN;
//	int invokeID;	
//	unsigned char flags enum(flagValues_t);
//	int version;	
//	result_t result;
//	object_t object;
//	int filter;			
//}


//////////////////////////////////////////////////////
// To inform app (socket) to STOP sending           //
//////////////////////////////////////////////////////
//message CDAP_M_STOP_SENDING extends CDAPMessage {
//    displayString = "b=15,15,oval,#FF0000,#FF0000,0";
//	opCode enum(opCode_t) = M_STOP_SENDING;
//}

//////////////////////////////////////////////////////
// To inform app (socket) to START sending again    //
//////////////////////////////////////////////////////
//message CDAP_M_START_SENDING extends CDAPMessage {
//    displayString = "b=15,15,oval,#FF0000,#FF0000,0";
//	opCode enum(opCode_t) = M_START_SENDING;
//}
