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
/*
 * @file DTPState.h
 * @author Marcel Marek
 * @date Apr 28, 2014
 * @brief
 * @detail
 * EFCPSpec 8.5.2 DTP State - the DTSV
 */
#ifndef DTPSTATE_H_
#define DTPSTATE_H_

#include <omnetpp.h>
#include <cobject.h>
#include <queue>
#include <vector>
#include "EFCP_defs.h"
#include "DataTransferPDU.h"

#include "PDU.h"



typedef enum
{
  //NULL = 0,
  DTP_STATE_ACTIVE = 0x01,
  DTP_STATE_PORT_ID_TRANS = 0x10, //Port-id transition
} DTPStateState;


/*
 *
 */
class DTPState : public cSimpleModule {

private:
    PDU* currentPDU;

    /* These parameters can set smaller values of the DTAE constants
     * for a given flow. These must have values less than or equal
     * those defined for the DIF. */
    unsigned int maxFlowSDUSize;
    unsigned int maxFlowPDUSize;

    unsigned int seqNumRollOverThresh;
    int state;
    bool dtcpPresent; /*!<a Boolean that indicates whether this connection is using DTCP. */
    bool winBased; /*!< a Boolean that indicates whether window-based flow control is in use.*/
    bool rateBased; /*!<a Boolean indicates whether rate-based flow control is in use.*/
    bool rxPresent; /*!<a Boolean that indicates whether Retransmission Control (potentially with gaps) is in use*/

    /* Move to DTCPState! */



    PDUQ_t reassemblyPDUQ;
    PDUQ_t generatedPDUs;
    PDUQ_t postablePDUs;

    const QoSCube* qoSCube;

    bool partDeliv; /* Partial Delivery of SDUs is Allowed */
    bool incompDeliv; /* Delivery of Incomplete SDUs is Allowed */
    unsigned int rcvLeftWinEdge;
    unsigned int maxSeqNumRcvd;

    unsigned int nextSeqNumToSend;
    unsigned int lastSDUDelivered;
    //queue<PDU,seqNum> pduReassemblyQ

    /* Not in specs */
    unsigned int dropDup; //number of dropped duplicates (this variable is not mentioned in specs)

    /* Not defined in specs, but refered to */
    unsigned int lastSeqNumSent;

    /* Moved from DTCP-SV */
    bool setDRFFlag; // This Boolean indicates that the next PDU sent should have the DRF Flag set.
    double rtt;
    double mpl;



    /* new */
    bool ecnSet; //This variable gets set upon reception of DataTransfer PDU with ECN bit set and cleared upon reception of DataTransfer PDU with ECN bit cleared.
    bool blockingPort;

    void clearPDUQ(std::vector<DataTransferPDU*>* pduQ);
    void clearGeneratedPDUQ();
    void clearPostablePDUQ();

public:
    DTPState();
    virtual ~DTPState();

    void initDefaults();

    void incDropDup(){dropDup++;}
    unsigned int getDropDup() const;

    bool isFCPresent(){ return winBased || rateBased;}

    bool isDtcpPresent() const;
    void setDtcpPresent(bool dtcpPresent);
    bool isIncompDeliv() const;
    void setIncompDeliv(bool incompDeliv);
    unsigned int getMaxFlowPduSize() const;
    void setMaxFlowPduSize(unsigned int maxFlowPduSize);
    unsigned int getMaxFlowSduSize() const;
    void setMaxFlowSduSize(unsigned int maxFlowSduSize);
    unsigned int getMaxSeqNumRcvd() const;
    void setMaxSeqNumRcvd(unsigned int maxSeqNumRcvd);
    void incMaxSeqNumRcvd();
    void incRcvLeftWindowEdge();
    unsigned int getNextSeqNumToSend();
    unsigned int getNextSeqNumToSendWithoutIncrement();
    void setNextSeqNumToSend(unsigned int nextSeqNumToSend);
    void incNextSeqNumToSend();
    bool isPartDeliv() const;
    void setPartDeliv(bool partDeliv);
    bool isRateBased() const;
    void setRateBased(bool rateBased);
    bool isRateFullfilled() const;
    void setRateFullfilled(bool rateFullfilled);
    unsigned int getRcvLeftWinEdge() const;
    void setRcvLeftWinEdge(unsigned int rcvLeftWinEdge);
    bool isRxPresent() const;
    void setRxPresent(bool rxPresent);
    unsigned int getSeqNumRollOverThresh() const;
    void setSeqNumRollOverThresh(unsigned int seqNumRollOverThresh);
    int getState() const;
    void setState(int state);
    bool isWinBased() const;
    void setWinBased(bool winBased);
    bool isSetDrfFlag() const;
    void setSetDrfFlag(bool setDrfFlag);
    double getRtt() const;
    void setRtt(double rtt);

    unsigned int getLastCtrlSeqNumRcv();
    unsigned int getLastSeqNumSent() const;
    void setLastSeqNumSent(unsigned int lastSeqNumSent);
    bool isEcnSet() const;
    void setEcnSet(bool ecnSet);
    const PDU* getCurrentPdu() const;
    void setCurrentPdu(PDU* currentPdu);

    std::vector<DataTransferPDU*>* getReassemblyPDUQ();
    void pushBackToReassemblyPDUQ(DataTransferPDU* pdu);
    void addPDUToReassemblyQ(DataTransferPDU* pdu);
    void clearReassemblyPDUQ();

    PDUQ_t* getGeneratedPDUQ();
    void pushBackToGeneratedPDUQ(DataTransferPDU* pdu);

    PDUQ_t* getPostablePDUQ();
    void pushBackToPostablePDUQ(DataTransferPDU* pdu);
    const QoSCube* getQoSCube() const;
    void setQoSCube(const QoSCube*& qoSCube);
    unsigned int getLastSduDelivered() const;
    void setLastSduDelivered(unsigned int lastSduDelivered);

    void updateRcvLWE(unsigned int seqNum);
    void updateSndLWE();
    double getMPL() const;
    void setMpl(double mpl);
    bool isBlockingPort() const;
    void setBlockingPort(bool blockingPort);

protected:
  virtual void handleMessage(cMessage *msg);
  virtual void initialize(int step);
  int numInitStages() const { return 2;};
};

#endif /* DTPSTATE_H_ */
