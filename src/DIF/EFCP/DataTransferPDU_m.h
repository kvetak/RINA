//
// Generated file, do not edit! Created by opp_msgc 4.5 from DIF/EFCP/DataTransferPDU.msg.
//

#ifndef _DATATRANSFERPDU_M_H_
#define _DATATRANSFERPDU_M_H_

#include <omnetpp.h>

// opp_msgc version check
#define MSGC_VERSION 0x0405
#if (MSGC_VERSION!=OMNETPP_VERSION)
#    error Version mismatch! Probably this file was generated by an earlier version of opp_msgc: 'make clean' should help.
#endif

// cplusplus {{
#include "PDU.h"
// }}



/**
 * Class generated from <tt>DIF/EFCP/DataTransferPDU.msg</tt> by opp_msgc.
 * <pre>
 * packet DataTransferPDU extends PDU {
 *     type = DATA_TRANSFER_PDU;
 * }
 * </pre>
 */
class DataTransferPDU : public ::PDU
{
  protected:

  private:
    void copy(const DataTransferPDU& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const DataTransferPDU&);

  public:
    DataTransferPDU(const char *name=NULL, int kind=0);
    DataTransferPDU(const DataTransferPDU& other);
    virtual ~DataTransferPDU();
    DataTransferPDU& operator=(const DataTransferPDU& other);
    virtual DataTransferPDU *dup() const {return new DataTransferPDU(*this);}
    virtual void parsimPack(cCommBuffer *b);
    virtual void parsimUnpack(cCommBuffer *b);

    // field getter/setter methods
};

inline void doPacking(cCommBuffer *b, DataTransferPDU& obj) {obj.parsimPack(b);}
inline void doUnpacking(cCommBuffer *b, DataTransferPDU& obj) {obj.parsimUnpack(b);}


#endif // _DATATRANSFERPDU_M_H_
