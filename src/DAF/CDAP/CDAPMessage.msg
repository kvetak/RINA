//
// Copyright © 2014 PRISTINE Consortium (http://ict-pristine.eu)
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
	F_SYNC = 1;								// set on READ/WRITE to request synchronous r/w
	F_RD_INCOMPLETE = 2;					// set on all but final reply to an M_READ
}

struct objVal_t {							// value of an object
	uint32	intval;
	int32	sintval;
	uint64	int64val;
	int64	sint64val;
	string	strval;
//	char	byteval;			// arbitrary structure or message
	float 	floatval;
	double 	doubleval;
}

// CDAP-reserved authentication types are 0-99 and >1000
// Authentication types 100-1000 are reserved for private application use.
enum authTypes_t {
	AUTH_NONE = 0;							// No authentication
	AUTH_PASSWD = 1;						// User name and password provided
	AUTH_SSHRSA = 2;						// SSH RSA (version 1 or 2)
	AUTH_SSHDSA = 3;						// SSH DSA (version 2 only)
}

// Reserved authentication fields 1-99, >1000 are reserved for CDAP future use.
// Authentication type values 100-1000 are reserved for private application use.
struct authValue_t {
	string authName;			// Authentication name
	string authPassword;		// Authentication password
	string authOther;			// Additional authentication information
};

struct result_t {        
    string resultReason;		//Additional explanation of resultValue
    int resultValue;			//The result of an operation, indicating its success, partial success in the case of synchronized operations, or reason for failure.
}

struct auth_t {
    unsigned char authType enum(authTypes_t);
    authValue_t authValue;
}

struct naming_t {
	string AEInst;							
	string AEName;							
	string ApInst;							
	string ApName;							    
}

struct object_t {
    string objectClass;
    int objectInstance;
    string objectName;
    cObject objectVal;
}

message CDAP_General_Message {
	uint32 absSyntax;							// Abstract Syntax of messages, see text.
	unsigned char opCode enum(opCode_t);		// op Code.
	uint32 invokeID;							// Invoke ID, omitted if no reply desired.
	unsigned char flags enum(flagValues_t);		// misc. flags
	string objClass;							// Name of the object class of objName
	string objName;								// Object name, unique in its class
	uint64 objInst;								// Unique object instance
	objVal_t objValue;							// value of object in read/write/etc.
	uint32 result; 								// result of operation, 0 == success
	uint32 scope;								// scope of READ/WRITE operation
//	char[] filter;								// filter script
	unsigned char authMech enum(authTypes_t);	// Authentication mechanism
	authValue_t authValue;						// Authentication information
	string destAEInst;							// Destination AE Instance name
	string destAEName;							// Destination AE name
	string destApInst;							// Destination Application Instance name
	string destApName;							// Destination Application name
	string srcAEInst;							// Source AE Instance name
	string srcAEName;							// Source AE name
	string srcApInst;							// Source Application Instance name
	string srcApName;							// Source Application name
	string resultReason;						// further explanation of result
	int64 version;								// For application use - RIB/class version.
}

message CDAP_M_Connect {	
	unsigned char opCode enum(opCode_t) = M_CONNECT;
	int invokeID;	
	unsigned char flags enum(flagValues_t);
	int version;		
	int absSyntax;	
	auth_t auth;	
	naming_t src;
	naming_t dst;
}

message CDAP_M_Connect_R {
	unsigned char opCode enum(opCode_t) = M_CONNECT_R;
	int invokeID;	
	unsigned char flags enum(flagValues_t);
	int version;		
	result_t result;		   
	int absSyntax;	
	auth_t auth;	
	naming_t src;
	naming_t dst;
}

message CDAP_M_Release {
	unsigned char opCode enum(opCode_t) = M_RELEASE;
	int invokeID;	
	unsigned char flags enum(flagValues_t);
	int version;
}

message CDAP_M_Release_R {
	unsigned char opCode enum(opCode_t) = M_RELEASE_R;	
	int invokeID;	
	unsigned char flags enum(flagValues_t);
	int version;
	result_t result;	
}

message CDAP_M_Create {
	unsigned char opCode enum(opCode_t) = M_CREATE;
	int invokeID;	
	unsigned char flags enum(flagValues_t);
	int version;	
	object_t object;
	int scope;
	int filter;	
}

message CDAP_M_Create_R {
	unsigned char opCode enum(opCode_t) = M_CREATE_R;
	int invokeID;	
	unsigned char flags enum(flagValues_t);
	int version;	
	result_t result;
	object_t object;	
	int filter;		
}

message CDAP_M_Delete {
	unsigned char opCode enum(opCode_t) = M_DELETE;
	int invokeID;	
	unsigned char flags enum(flagValues_t);
	int version;	
	object_t object;
	int scope;
	int filter;		
}

message CDAP_M_Delete_R {
	unsigned char opCode enum(opCode_t) = M_DELETE_R;
	int invokeID;	
	unsigned char flags enum(flagValues_t);
	int version;	
	result_t result;
	object_t object;
	int filter;		
}

message CDAP_M_Read {
	unsigned char opCode enum(opCode_t) = M_READ;
	int invokeID;	
	unsigned char flags enum(flagValues_t);
	int version;
	object_t object;
	int scope;
	int filter;			
}

message CDAP_M_Read_R {
	unsigned char opCode enum(opCode_t) = M_READ_R;
	int invokeID;	
	unsigned char flags enum(flagValues_t);
	int version;	
	result_t result;
	object_t object;
	int filter;		
}

message CDAP_M_CancelRead {
	unsigned char opCode enum(opCode_t) = M_CANCELREAD;
	int invokeID;	
	unsigned char flags enum(flagValues_t);
	int version;
	result_t result;
}

message CDAP_M_CancelRead_R {
	unsigned char opCode enum(opCode_t) = M_CANCELREAD_R;
	int invokeID;	
	unsigned char flags enum(flagValues_t);
	int version;	
	result_t result;	
}

message CDAP_M_Write {
	unsigned char opCode enum(opCode_t) = M_WRITE;
	int invokeID;	
	unsigned char flags enum(flagValues_t);
	int version;
	object_t object;
	int scope;
	int filter;					
}

message CDAP_M_WRITE_R {
	unsigned char opCode enum(opCode_t) = M_WRITE_R;
	int invokeID;	
	unsigned char flags enum(flagValues_t);
	int version;	
	result_t result;
	object_t object;
	int filter;			
}

message CDAP_M_Start {
	unsigned char opCode enum(opCode_t) = M_START;
	int invokeID;	
	unsigned char flags enum(flagValues_t);
	int version;
	object_t object;
	int scope;
	int filter;		
}

message CDAP_M_Start_R {
	unsigned char opCode enum(opCode_t) = M_START_R;
	int invokeID;	
	unsigned char flags enum(flagValues_t);
	int version;	
	result_t result;
	object_t object;
	int filter;		
}

message CDAP_M_Stop {
	unsigned char opCode enum(opCode_t) = M_STOP;
	int invokeID;	
	unsigned char flags enum(flagValues_t);
	int version;	
	object_t object;
	int scope;
	int filter;		
	
}

message CDAP_M_Stop_R {
	unsigned char opCode enum(opCode_t) = M_STOP_R;
	int invokeID;	
	unsigned char flags enum(flagValues_t);
	int version;	
	result_t result;
	object_t object;
	int filter;			
}
