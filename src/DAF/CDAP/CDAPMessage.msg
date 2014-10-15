//
// Copyright � 2014 PRISTINE Consortium (http://ict-pristine.eu)
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
    #include "Address.h"       
    typedef cObject* ObjectPtr;
}}

class noncobject Address;
class noncobject ObjectPtr;


//Message operation codes
enum opCode_t {
	M_CONNECT = 0;
	M_CONNECT_R = 1;
	M_RELEASE = 2;
	M_RELEASE_R = 3;
	M_CREATE = 4;
	M_CREATE_R = 5;
	M_DELETE = 6;
	M_DELETE_R = 7;
	M_READ = 8;
	M_READ_R = 9;
	M_CANCELREAD = 10;
	M_CANCELREAD_R = 11;
	M_WRITE = 12;
	M_WRITE_R = 13;
	M_START = 14;
	M_START_R = 15;
	M_STOP = 16;
	M_STOP_R = 17;
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
struct result_t {        
    string resultReason;	//Additional explanation of resultValue
    int resultValue;		//The result of an operation, indicating its success, partial success in the case of synchronized operations, or reason for failure.
}

// General structure holding authentication related information
struct auth_t {
    unsigned char authType enum(authTypes_t);	//Authentication type
    authValue_t authValue;						//Relevant authentication data
}

// General structures for holding naming information regarding requestor/responder
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

//////////////////////////////////////////////
//CDAP general messages
//////////////////////////////////////////////
message CDAPMessage {
    unsigned int size;
    int handle;
    Address dstAddr;  
}

//////////////////////////////////////////////
//CDAP M_CONNECT(_R) messages
//////////////////////////////////////////////

message CDAP_M_Connect extends CDAPMessage {	
	unsigned char opCode enum(opCode_t) = M_CONNECT;
	int invokeID;	
	unsigned char flags enum(flagValues_t);
	int version;		
	int absSyntax enum(absSyntax_t);	
	auth_t auth;	
	naming_t src;
	naming_t dst;
}

message CDAP_M_Connect_R extends CDAPMessage {
	unsigned char opCode enum(opCode_t) = M_CONNECT_R;
	int invokeID;	
	unsigned char flags enum(flagValues_t);
	int version;		
	result_t result;		   
	int absSyntax enum(absSyntax_t);	
	auth_t auth;	
	naming_t src;
	naming_t dst;
}

//////////////////////////////////////////////
//CDAP M_RELEASE(_R) messages
//////////////////////////////////////////////

message CDAP_M_Release extends CDAPMessage {
	unsigned char opCode enum(opCode_t) = M_RELEASE;
	int invokeID;	
	unsigned char flags enum(flagValues_t);
	int version;
}

message CDAP_M_Release_R extends CDAPMessage {
	unsigned char opCode enum(opCode_t) = M_RELEASE_R;	
	int invokeID;	
	unsigned char flags enum(flagValues_t);
	int version;
	result_t result;	
}

//////////////////////////////////////////////
//CDAP M_CREATE(_R) messages
//////////////////////////////////////////////

message CDAP_M_Create extends CDAPMessage {
	unsigned char opCode enum(opCode_t) = M_CREATE;
	int invokeID;	
	unsigned char flags enum(flagValues_t);
	int version;	
	object_t object;
	int scope;
	int filter;	
}

message CDAP_M_Create_R extends CDAPMessage {
	unsigned char opCode enum(opCode_t) = M_CREATE_R;
	int invokeID;	
	unsigned char flags enum(flagValues_t);
	int version;	
	result_t result;
	object_t object;	
	int filter;		
}

//////////////////////////////////////////////
//CDAP M_DELETE(_R) messages
//////////////////////////////////////////////

message CDAP_M_Delete extends CDAPMessage {
	unsigned char opCode enum(opCode_t) = M_DELETE;
	int invokeID;	
	unsigned char flags enum(flagValues_t);
	int version;	
	object_t object;
	int scope;
	int filter;		
}

message CDAP_M_Delete_R extends CDAPMessage {
	unsigned char opCode enum(opCode_t) = M_DELETE_R;
	int invokeID;	
	unsigned char flags enum(flagValues_t);
	int version;	
	result_t result;
	object_t object;
	int filter;			
}

//////////////////////////////////////////////
//CDAP M_READ(_R) messages
//////////////////////////////////////////////

message CDAP_M_Read extends CDAPMessage {
	unsigned char opCode enum(opCode_t) = M_READ;
	int invokeID;	
	unsigned char flags enum(flagValues_t);
	int version;
	object_t object;
	int scope;
	int filter;			
}

message CDAP_M_Read_R extends CDAPMessage {
	unsigned char opCode enum(opCode_t) = M_READ_R;
	int invokeID;	
	unsigned char flags enum(flagValues_t);
	int version;	
	result_t result;
	object_t object;
	int filter;		
}

//////////////////////////////////////////////
//CDAP M_CANCELREAD(_R) messages
//////////////////////////////////////////////

message CDAP_M_CancelRead extends CDAPMessage {
	unsigned char opCode enum(opCode_t) = M_CANCELREAD;
	int invokeID;	
	unsigned char flags enum(flagValues_t);
	int version;
	result_t result;
}

message CDAP_M_CancelRead_R extends CDAPMessage {
	unsigned char opCode enum(opCode_t) = M_CANCELREAD_R;
	int invokeID;	
	unsigned char flags enum(flagValues_t);
	int version;	
	result_t result;	
}

//////////////////////////////////////////////
//CDAP M_WRITE(_R) messages
//////////////////////////////////////////////

message CDAP_M_Write extends CDAPMessage {
	unsigned char opCode enum(opCode_t) = M_WRITE;
	int invokeID;	
	unsigned char flags enum(flagValues_t);
	int version;
	object_t object;
	int scope;
	int filter;					
}

message CDAP_M_Write_R extends CDAPMessage {
	unsigned char opCode enum(opCode_t) = M_WRITE_R;
	int invokeID;	
	unsigned char flags enum(flagValues_t);
	int version;	
	result_t result;
	object_t object;
	int filter;			
}

//////////////////////////////////////////////
//CDAP M_START(_R) messages
//////////////////////////////////////////////

message CDAP_M_Start extends CDAPMessage {
	unsigned char opCode enum(opCode_t) = M_START;
	int invokeID;	
	unsigned char flags enum(flagValues_t);
	int version;
	object_t object;
	int scope;
	int filter;		
}

message CDAP_M_Start_R extends CDAPMessage {
	unsigned char opCode enum(opCode_t) = M_START_R;
	int invokeID;	
	unsigned char flags enum(flagValues_t);
	int version;	
	result_t result;
	object_t object;
	int filter;		
}

//////////////////////////////////////////////
//CDAP M_STOP(_R) messages
//////////////////////////////////////////////

message CDAP_M_Stop extends CDAPMessage {
	unsigned char opCode enum(opCode_t) = M_STOP;
	int invokeID;	
	unsigned char flags enum(flagValues_t);
	int version;	
	object_t object;
	int scope;
	int filter;		
	
}

message CDAP_M_Stop_R extends CDAPMessage {
	unsigned char opCode enum(opCode_t) = M_STOP_R;
	int invokeID;	
	unsigned char flags enum(flagValues_t);
	int version;	
	result_t result;
	object_t object;
	int filter;			
}
