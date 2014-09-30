//
// Generated file, do not edit! Created by opp_msgc 4.5 from Common/PDU.msg.
//

#ifndef _PDU_M_H_
#define _PDU_M_H_

#include <omnetpp.h>

// opp_msgc version check
#define MSGC_VERSION 0x0405
#if (MSGC_VERSION!=OMNETPP_VERSION)
#    error Version mismatch! Probably this file was generated by an earlier version of opp_msgc: 'make clean' should help.
#endif

// cplusplus {{
#define PDU_HEADER_LEN 10
#include "APN.h"
#include "ConnectionId.h"
typedef cObject* cObjectPtr;
typedef cMessage* cMessagePtr;
// }}



/**
 * Enum generated from <tt>Common/PDU.msg</tt> by opp_msgc.
 * <pre>
 * enum PDUType{
 *     	EFCP_PDU 				= 0x8000;
 *     	DATA_TRANSFER_PDU 		= 0x8001;
 *     	CONTROL_ACK_PDU 		= 0x8003;
 *         ACK_ONLY_PDU 			= 0x8804;
 *         NACK_ONLY_PDU 			= 0x8805;
 *         SELECT_ACK_PDU 			= 0x8806;
 *         SELECT_NACK_PDU 		= 0x8807;
 *         FLOW_ONLY_PDU 			= 0x8808;
 *         ACK_FLOW_PDU 			= 0x880C;
 *         NACK_FLOW_PDU 			= 0x880D;
 *         SELECT_ACK_FLOW_PDU 	= 0x880E;
 *         SELECT_NACK_FLOW_PDU 	= 0x880F;
 *         
 *         
 *         
 * }
 * </pre>
 */
enum PDUType {
    EFCP_PDU = 0x8000,
    DATA_TRANSFER_PDU = 0x8001,
    CONTROL_ACK_PDU = 0x8003,
    ACK_ONLY_PDU = 0x8804,
    NACK_ONLY_PDU = 0x8805,
    SELECT_ACK_PDU = 0x8806,
    SELECT_NACK_PDU = 0x8807,
    FLOW_ONLY_PDU = 0x8808,
    ACK_FLOW_PDU = 0x880C,
    NACK_FLOW_PDU = 0x880D,
    SELECT_ACK_FLOW_PDU = 0x880E,
    SELECT_NACK_FLOW_PDU = 0x880F
};

/**
 * Enum generated from <tt>Common/PDU.msg</tt> by opp_msgc.
 * <pre>
 * enum FLAGS{
 * }
 * </pre>
 */
enum FLAGS {
};

/**
 * Class generated from <tt>Common/PDU.msg</tt> by opp_msgc.
 * <pre>
 * message PDU {
 *     @customize(true);
 *     unsigned int version = 1;
 *     APN dstAddr; 
 *     APN srcAddr;  
 *     ConnectionId connId;
 *     int type enum(PDUType);
 *     int flags = 0; 
 *     unsigned int pduLen = PDU_HEADER_LEN;
 *     unsigned int seqNum;
 * 
 *     unsigned char userData[];
 *     cMessagePtr mUserData;
 *     
 *     
 * }
 * </pre>
 *
 * PDU_Base is only useful if it gets subclassed, and PDU is derived from it.
 * The minimum code to be written for PDU is the following:
 *
 * <pre>
 * class PDU : public PDU_Base
 * {
 *   private:
 *     void copy(const PDU& other) { ... }

 *   public:
 *     PDU(const char *name=NULL, int kind=0) : PDU_Base(name,kind) {}
 *     PDU(const PDU& other) : PDU_Base(other) {copy(other);}
 *     PDU& operator=(const PDU& other) {if (this==&other) return *this; PDU_Base::operator=(other); copy(other); return *this;}
 *     virtual PDU *dup() const {return new PDU(*this);}
 *     // ADD CODE HERE to redefine and implement pure virtual functions from PDU_Base
 * };
 * </pre>
 *
 * The following should go into a .cc (.cpp) file:
 *
 * <pre>
 * Register_Class(PDU);
 * </pre>
 */
class PDU_Base : public ::cMessage
{
  protected:
    unsigned int version_var;
    APN dstAddr_var;
    APN srcAddr_var;
    ConnectionId connId_var;
    int type_var;
    int flags_var;
    unsigned int pduLen_var;
    unsigned int seqNum_var;
    unsigned char *userData_var; // array ptr
    unsigned int userData_arraysize;
    cMessagePtr mUserData_var;

  private:
    void copy(const PDU_Base& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const PDU_Base&);
    // make constructors protected to avoid instantiation
    PDU_Base(const char *name=NULL, int kind=0);
    PDU_Base(const PDU_Base& other);
    // make assignment operator protected to force the user override it
    PDU_Base& operator=(const PDU_Base& other);

  public:
    virtual ~PDU_Base();
    virtual PDU_Base *dup() const {throw cRuntimeError("You forgot to manually add a dup() function to class PDU");}
    virtual void parsimPack(cCommBuffer *b);
    virtual void parsimUnpack(cCommBuffer *b);

    // field getter/setter methods
    virtual unsigned int getVersion() const;
    virtual void setVersion(unsigned int version);
    virtual APN& getDstAddr();
    virtual const APN& getDstAddr() const {return const_cast<PDU_Base*>(this)->getDstAddr();}
    virtual void setDstAddr(const APN& dstAddr);
    virtual APN& getSrcAddr();
    virtual const APN& getSrcAddr() const {return const_cast<PDU_Base*>(this)->getSrcAddr();}
    virtual void setSrcAddr(const APN& srcAddr);
    virtual ConnectionId& getConnId();
    virtual const ConnectionId& getConnId() const {return const_cast<PDU_Base*>(this)->getConnId();}
    virtual void setConnId(const ConnectionId& connId);
    virtual int getType() const;
    virtual void setType(int type);
    virtual int getFlags() const;
    virtual void setFlags(int flags);
    virtual unsigned int getPduLen() const;
    virtual void setPduLen(unsigned int pduLen);
    virtual unsigned int getSeqNum() const;
    virtual void setSeqNum(unsigned int seqNum);
    virtual void setUserDataArraySize(unsigned int size);
    virtual unsigned int getUserDataArraySize() const;
    virtual unsigned char getUserData(unsigned int k) const;
    virtual void setUserData(unsigned int k, unsigned char userData);
    virtual cMessagePtr& getMUserData();
    virtual const cMessagePtr& getMUserData() const {return const_cast<PDU_Base*>(this)->getMUserData();}
    virtual void setMUserData(const cMessagePtr& mUserData);
};


#endif // _PDU_M_H_
