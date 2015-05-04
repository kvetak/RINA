//
// Copyright © 2014 PRISTINE Consortium (http://ict-pristine.eu)
//  
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public License
// as published by the Free Software Foundation; either version 3
// of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with this program; if not, see <http://www.gnu.org/licenses/>.
//
/*
 * DTCP.h
 *
 *  Created on: Apr 17, 2014
 *      Author: Marcel Marek
 */

#ifndef DTCP_H_
#define DTCP_H_

#include <omnetpp.h>
#include <csimplemodule.h>

//#include "RXControl.h"
#include "DTCPState.h"
#include "DTPState.h"
#include "DTP.h"
#include "EFCP_defs.h"
#include "ControlPDU_m.h"
#include "DTCPTimers_m.h"

/* Policies */
#include "DTCPECNPolicyBase.h"
#include "RcvrFCPolicyBase.h"
#include "RcvrAckPolicyBase.h"
#include "ReceivingFCPolicyBase.h"
#include "SendingAckPolicyBase.h"
#include "LostControlPDUPolicyBase.h"
#include "RcvrControlAckPolicyBase.h"
#include "SenderAckPolicyBase.h"
#include "DTCPFCOverrunPolicyBase.h"
#include "NoOverridePeakPolicyBase.h"
#include "TxControlPolicyBase.h"
#include "NoRateSlowDownPolicyBase.h"
#include "ReconcileFCPolicyBase.h"
#include "RateReductionPolicyBase.h"
#include "DTCPECNSlowDownPolicyBase.h"

class DTP;

class DTCP: public cSimpleModule {
    friend class DTP;
  private:

    DTP* dtp;
    DTCPState *dtcpState;
//    FlowControl* flowControl;
//    RXControl* rxControl;

    DTCPECNPolicyBase* ecnPolicy;
    RcvrFCPolicyBase* rcvrFCPolicy;
    RcvrAckPolicyBase* rcvrAckPolicy;
    ReceivingFCPolicyBase* receivingFCPolicy;
    SendingAckPolicyBase* sendingAckPolicy;
    LostControlPDUPolicyBase* lostControlPDUPolicy;
    RcvrControlAckPolicyBase* rcvrControlAckPolicy;
    SenderAckPolicyBase* senderAckPolicy;
    DTCPFCOverrunPolicyBase* fcOverrunPolicy;
    NoOverridePeakPolicyBase* noOverridePeakPolicy;
    TxControlPolicyBase* txControlPolicy;
    NoRateSlowDownPolicyBase* noRateSlowDownPolicy;
    ReconcileFCPolicyBase* reconcileFCPolicy;
    RateReductionPolicyBase* rateReductionPolicy;
    DTCPECNSlowDownPolicyBase* ecnSlowDownPolicy;


    /*Timers*/
    WindowTimer* windowTimer;
    DTCPSendingRateTimer sendingRateTimer;

    void schedule(DTCPTimers *timer, double time = 0.0);
    void resetWindowTimer();

    void sendAckPDU();
    void flushAllQueuesAndPrepareToDie();

    void handleSendingRateTimer(DTCPSendingRateTimer* timer);

public:

    DTCP();
    virtual ~DTCP();

    void setDTP(DTP* dtp);

    DTCPState* getDTCPState() const;


    void handleWindowTimer(WindowTimer* timer);
    void handleDTCPRxExpiryTimer(DTCPRxExpiryTimer* timer);


    void updateRcvRtWinEdge(DTPState* dtpState);

    unsigned int getNextSndCtrlSeqNum();
    unsigned int getLastCtrlSeqNumRcv();
    void setLastCtrlSeqnumRcvd(unsigned int ctrlSeqNum);


    void setSndRtWinEdge(unsigned int sndRtWinEdge);
    unsigned int getSndRtWinEdge();
    void setRcvRtWinEdge(unsigned int rcvRtWinEdge);
    unsigned int getRcvRtWinEdge();

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

    unsigned int getSendingRate() const;
    void setSendingRate(unsigned int sendingRate);

    unsigned int getRcvrRate() const;

    void incDupAcks();
    unsigned int getDupAcks() const;

    void incDupFC();
    unsigned int getDupFC() const;

    unsigned int getSenderLeftWinEdge() const;
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
    bool runFCOverrunPolicy(DTPState* dtpState);
    bool runNoOverridePeakPolicy(DTPState* dtpState);
    bool runTxControlPolicy(DTPState* dtpState, PDUQ_t* pduQ);
    bool runNoRateSlowDownPolicy(DTPState* dtpState);
    bool runReconcileFCPolicy(DTPState* dtpState);
    bool runRateReductionPolicy(DTPState* dtpState);
    bool runECNSlowDownPolicy(DTPState* dtpState);

    //TODO policies
    void runRxTimerExpiryPolicy(DTCPRxExpiryTimer* timer);




    void redrawGUI();
    cModule* createPolicyModule(const char* prefix, const char* name);
    bool isClosedWinQClosed();

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
