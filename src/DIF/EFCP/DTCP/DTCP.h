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
 * DTCP.h
 *
 *  Created on: Apr 17, 2014
 *      Author: Marcel Marek
 */

#ifndef DTCP_H_
#define DTCP_H_

#include <omnetpp.h>

//#include "DIF/EFCP/DTCP/RXControl.h"
#include "DIF/EFCP/DTCP/DTCPState.h"
#include "DIF/EFCP/DTP/DTPState.h"
#include "DIF/EFCP/DTP/DTP.h"
#include "DIF/EFCP/EFCP_defs.h"
#include "DIF/EFCP/DTCP/ControlPDU_m.h"
#include "DIF/EFCP/DTCP/DTCPTimers_m.h"

/* Policies */
#include "DIF/EFCP/DTCP/ECN/ECNPolicyBase.h"
#include "DIF/EFCP/DTCP/RcvrFC/RcvrFCPolicyBase.h"
#include "DIF/EFCP/DTCP/RcvrAck/RcvrAckPolicyBase.h"
#include "DIF/EFCP/DTCP/ReceivingFC/ReceivingFCPolicyBase.h"
#include "DIF/EFCP/DTCP/SendingAck/SendingAckPolicyBase.h"
#include "DIF/EFCP/DTCP/LostControlPDU/LostControlPDUPolicyBase.h"
#include "DIF/EFCP/DTCP/RcvrControlAck/RcvrControlAckPolicyBase.h"
#include "DIF/EFCP/DTCP/SenderAck/SenderAckPolicyBase.h"
#include "DIF/EFCP/DTCP/SndFCOverrun/SndFCOverrunPolicyBase.h"
#include "DIF/EFCP/DTCP/RcvFCOverrun/RcvFCOverrunPolicyBase.h"
#include "DIF/EFCP/DTCP/NoOverridePeak/NoOverridePeakPolicyBase.h"
#include "DIF/EFCP/DTCP/TxControl/TxControlPolicyBase.h"
#include "DIF/EFCP/DTCP/NoRateSlowDown/NoRateSlowDownPolicyBase.h"
#include "DIF/EFCP/DTCP/ReconcileFC/ReconcileFCPolicyBase.h"
#include "DIF/EFCP/DTCP/RateReduction/RateReductionPolicyBase.h"
#include "DIF/EFCP/DTCP/ECNSlowDown/ECNSlowDownPolicyBase.h"
#include "DIF/EFCP/DTCP/RxTimerExpiry/RxTimerExpiryPolicyBase.h"

class DTP;

class DTCP: public cSimpleModule {
    friend class DTP;
  private:

    DTP* dtp;
    DTCPState *dtcpState;
//    FlowControl* flowControl;
//    RXControl* rxControl;

    ECNPolicyBase* ecnPolicy;
    ECNSlowDownPolicyBase* ecnSlowDownPolicy;
    RcvrFCPolicyBase* rcvrFCPolicy;
    RcvrAckPolicyBase* rcvrAckPolicy;
    ReceivingFCPolicyBase* receivingFCPolicy;
    SendingAckPolicyBase* sendingAckPolicy;
    LostControlPDUPolicyBase* lostControlPDUPolicy;
    RcvrControlAckPolicyBase* rcvrControlAckPolicy;
    SenderAckPolicyBase* senderAckPolicy;
    SndFCOverrunPolicyBase* sndFcOverrunPolicy;
    RcvFCOverrunPolicyBase* rcvFcOverrunPolicy;
    NoOverridePeakPolicyBase* noOverridePeakPolicy;
    TxControlPolicyBase* txControlPolicy;
    NoRateSlowDownPolicyBase* noRateSlowDownPolicy;
    ReconcileFCPolicyBase* reconcileFCPolicy;
    RateReductionPolicyBase* rateReductionPolicy;
    RxTimerExpiryPolicyBase* rxTimerExpiryPolicy;



    /*Timers*/
//    WindowTimer* windowTimer;
    DTCPSendingRateTimer sendingRateTimer;

    void schedule(DTCPTimers *timer, double time = 0.0);
//    void resetWindowTimer();

    void sendAckPDU();
    void flushAllQueuesAndPrepareToDie();

    void handleSendingRateTimer(DTCPSendingRateTimer* timer);
    void handleRendezvousTimer(DTCPRendezvousTimer* rendezTimer);
    void startReliableCPDUTimer();
    void stopReliableCPDUTimer();


public:
    void deleteRxTimer(unsigned int seqNum);
    DTCP();
    virtual ~DTCP();

    void setDTP(DTP* dtp);

    DTCPState* getDTCPState() const;


//    void handleWindowTimer(WindowTimer* timer);
    void handleDTCPRxExpiryTimer(DTCPRxExpiryTimer* timer);


    void updateRcvRtWinEdge(DTPState* dtpState);

    unsigned int getNextSndCtrlSeqNum();
    unsigned int getLastCtrlSeqNumRcv();
    void setLastCtrlSeqnumRcvd(unsigned int ctrlSeqNum);


    void setSndRtWinEdge(unsigned int sndRtWinEdge);
    unsigned int getSndRtWinEdge();
    void setRcvRtWinEdge(unsigned int rcvRtWinEdge);
    unsigned int getRcvRightWinEdge();

    unsigned int getRcvCredit();

    unsigned long getSendingTimeUnit();

    bool isSendingRateFullfilled() const;
    void setSendingRateFullfilled(bool rateFullfilled);

    void incRcvRtWinEdge();

    void nackPDU(unsigned int startSeqNum, unsigned int endSeqNum = 0);
    void ackPDU(unsigned int startSeqNum, unsigned int endSeqNum = 0);

    void pushBackToRxQ(DataTransferPDU* pdu);
    void clearRxQ();
    unsigned int getDataReXmitMax() const;

    unsigned int getPdusSentInTimeUnit() const;
    void setPdusSentInTimeUnit(unsigned int pdusSentInTimeUnit);
    void incPdusSentInTimeUnit();

    unsigned int getPdusRcvdInTimeUnit() const;


    unsigned int getSendingRate() const;
    void setSendingRate(unsigned int sendingRate);

    unsigned int getRcvrRate() const;

    void incDupAcks();
    unsigned int getDupAcks() const;

    void incDupFC();
    unsigned int getDupFC() const;

    unsigned int getSndLeftWinEdge() const;
    void setSenderLeftWinEdge(unsigned int senderLeftWinEdge);
    void updateSenderLWE(unsigned int seqNum);

    /* Run Policies */
    bool runECNPolicy(DTPState* dtpState);
    bool runRcvrFCPolicy(DTPState* dtpState);
    bool runRcvrAckPolicy(DTPState* dtpState);
    bool runReceivingFCPolicy(DTPState* dtpState);
    bool runSendingAckPolicy(DTPState* dtpState, ATimer* timer);
    bool runLostControlPDUPolicy(DTPState* dtpState);
    bool runRcvrControlAckPolicy(DTPState* dtpState);
    bool runSenderAckPolicy(DTPState* dtpState);
    bool runSndFCOverrunPolicy(DTPState* dtpState);
    bool runRcvFCOverrunPolicy(DTPState* dtpState);
    bool runNoOverridePeakPolicy(DTPState* dtpState);
    bool runTxControlPolicy(DTPState* dtpState, PDUQ_t* pduQ);
    bool runNoRateSlowDownPolicy(DTPState* dtpState);
    bool runReconcileFCPolicy(DTPState* dtpState);
    bool runRateReductionPolicy(DTPState* dtpState);
    bool runECNSlowDownPolicy(DTPState* dtpState);

    void runRxTimerExpiryPolicy(DTCPRxExpiryTimer* timer);




    void redrawGUI();
    cModule* createPolicyModule(const char* prefix, const char* name);
    bool isClosedWinQClosed();
    void scheduleRxTimerExpiry();
    void setSndFcOverrunPolicy(SndFCOverrunPolicyBase* sndFcOverrunPolicy);
    void setLostControlPduPolicy(LostControlPDUPolicyBase* lostControlPduPolicy);
    void setNoOverridePeakPolicy(NoOverridePeakPolicyBase* noOverridePeakPolicy);
    void setNoRateSlowDownPolicy(NoRateSlowDownPolicyBase* noRateSlowDownPolicy);
    void setRateReductionPolicy(RateReductionPolicyBase* rateReductionPolicy);
    void setRcvrAckPolicy(RcvrAckPolicyBase* rcvrAckPolicy);
    void setRcvrControlAckPolicy(RcvrControlAckPolicyBase* rcvrControlAckPolicy);
    void setRcvrFcPolicy(RcvrFCPolicyBase* rcvrFcPolicy);
    void setReceivingFcPolicy(ReceivingFCPolicyBase* receivingFcPolicy);
    void setReconcileFcPolicy(ReconcileFCPolicyBase* reconcileFcPolicy);
    void setRxTimerExpiryPolicy(RxTimerExpiryPolicyBase* rxTimerExpiryPolicy);
    void setSenderAckPolicy(SenderAckPolicyBase* senderAckPolicy);
    void setSendingAckPolicy(SendingAckPolicyBase* sendingAckPolicy);
    void setTxControlPolicy(TxControlPolicyBase* txControlPolicy);
    void setDtcpState(DTCPState* dtcpState);
    void setRcvFcOverrunPolicy(RcvFCOverrunPolicyBase* rcvFcOverrunPolicy);
    void setECNPolicy(ECNPolicyBase* ecnPolicy);
    void setECNSlowDownPolicy(ECNSlowDownPolicyBase* ecnSlowDownPolicy);
    void startRendezvousTimer();

  protected:
    virtual void handleMessage(cMessage *msg);
    virtual void initialize(int step);
    int numInitStages() const
    {
      return 2;
    }
    void initSignalsAndListeners();


    //Signals
    simsignal_t sigStatDTCPRxCount;
};

#endif /* DTCP_H_ */
