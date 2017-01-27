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
#include <queue>
#include <vector>
#include "Common/Utils.h"
#include "DIF/EFCP/EFCP_defs.h"
#include "DIF/EFCP/DTP/DataTransferPDU.h"


#include "Common/PDU.h"

/* Dirty hacks */
#include "DIF/EFCP/DTP/DTPTimers_m.h"
/* End dirty hacks */



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

    /* Not defined in specs, but referred to */
    unsigned int lastSeqNumSent;

    /* Moved from DTCP-SV */
    bool setDRFFlag; // This Boolean indicates that the next PDU sent should have the DRF Flag set.
    double rtt;
    double mpl;



    /* new */
    bool ecnSet; //This variable gets set upon reception of DataTransfer PDU with ECN bit set and cleared upon reception of DataTransfer PDU with ECN bit cleared.
    bool blockingPort;

    /* Dirty hacks */
    /* This section contains temporary 'dirty hacks' variables to bypass obstacles.
     * They might and hopefully will be removed very soon, so do not depend on them.
     */
    ATimer* tmpAtimer;

    /* End Dirsty hacks */

    void clearPDUQ(std::vector<DataTransferPDU*>* pduQ);
    void clearGeneratedPDUQ();
    void clearPostablePDUQ();

public:
    DTPState();
    virtual ~DTPState();

    void initDefaults();

    void incDropDup(){dropDup++;}
    unsigned int getDropDup() const;

//    bool isFCPresent(){ return winBased || rateBased;}

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
//    bool isRateBased() const;
//    void setRateBased(bool rateBased);
    bool isRateFullfilled() const;
    void setRateFullfilled(bool rateFullfilled);
    unsigned int getRcvLeftWinEdge() const;
    void setRcvLeftWinEdge(unsigned int rcvLeftWinEdge);
//    bool isRxPresent() const;
//    void setRxPresent(bool rxPresent);
    unsigned int getSeqNumRollOverThresh() const;
    void setSeqNumRollOverThresh(unsigned int seqNumRollOverThresh);
    int getState() const;
    void setState(int state);
//    bool isWinBased() const;
//    void setWinBased(bool winBased);
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


    /* Dirty hacks */
    ATimer* getTmpAtimer() const;
    void setTmpAtimer(ATimer* tmpAtimer);
    void resetRcvVars();
    void resetSndVars();

//    double getDelimitDelay() const;
//    void setDelimitDelay(double delimitDelay);

    /* End dirty hacks */

protected:
  virtual void handleMessage(cMessage *msg);
  virtual void initialize(int step);
  int numInitStages() const { return 2;};
};

#endif /* DTPSTATE_H_ */
