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

#ifndef DTP_H_
#define DTP_H_

#include <omnetpp.h>
#include <vector>

#include "Common/RINASignals.h"
#include "Common/ExternConsts.h"

#include "DTPState.h"
#include "DTPTimers_m.h"
#include "DTCP.h"
//#include "Common/PDU.h"
#include "DataTransferPDU.h"
#include "ControlPDU_m.h"
#include "Common/SDU.h"
#include "RMT.h"

#include "DIF/RA/RA.h"
#include "SDUData_m.h"

#include "Common/QueueInfo.h"


/* Policies */
#include "RcvrInactivityPolicyBase.h"
#include "SenderInactivityPolicyBase.h"
#include "InitialSeqNumPolicyBase.h"
#include "RTTEstimatorPolicyBase.h"

//#include "SDUs.h"

#define DEFAULT_INIT_SEQUENCE_NUMBER 1


class DTCP;

class DTP : public cSimpleModule
{

    friend class DTCP;
  private:

    unsigned int sduSeqNum;
    std::set<unsigned int> sequencingQ;
    int deletePdu;
    bool pduDroppingEnabled;
    bool rendezvousEnabled;

    DTPState* state; //state of this data-transfer
    DTCP* dtcp;
    const Flow* flow;

//    const QoSCube *qosCube;

    /* Policies */
    RcvrInactivityPolicyBase* rcvrInactivityPolicy;
    SenderInactivityPolicyBase* senderInactivityPolicy;
    InitialSeqNumPolicyBase* initialSeqNumPolicy;
    RTTEstimatorPolicyBase* rttEstimatorPolicy;

    /* Various queues */


    std::vector<UserDataField*> userDataFieldQOut;

    std::vector<ATimer*> aTimerQ;



    /* Timers */
    SenderInactivityTimer* senderInactivityTimer;
    RcvrInactivityTimer* rcvrInactivityTimer;


    /**************** Moved rateFulfilled to FC together with sendingRatetimer **************************/
    /* This timer should be in FlowControl, but since for some reason "rateFulfilled" is in DTState it is better available from here */
//    SendingRateTimer* sendingRateTimer;

//    WindowTimer* windowTimer;

    /* Gates */
    /* To FAI */
    cGate* northI;
    cGate* northO;

    /* To RMT */
    cGate* southI;
    cGate* southO;

    ConnectionId connId;

    /* Handle messages and timer */
//    void handleDTPRxExpiryTimer(RxExpiryTimer* timer);
//    void handleDTPSendingRateTimer(SendingRateTimer* timer);
//    void handleDTPWindowTimer(WindowTimer* timer);
    void handleDTPRcvrInactivityTimer(RcvrInactivityTimer* timer);
    void handleDTPSenderInactivityTimer(SenderInactivityTimer* timer);
    void handleDTPATimer(ATimer* timer);

//    void handleMsgFromDelimiting(Data* msg);
    void handleMsgFromUp(UserDataField* userDataField);
    void handleMsgFromRMT(PDU* msg);
    void handleDataTransferPDUFromRMT(DataTransferPDU* pdu);

    void handleQueueInfo(QueueInfo* queueInfo);

    /* Send */


    /** Delimits content of buffer from application */
    unsigned int delimit(SDUData* sduData);
    unsigned int delimitFromRMT(PDU *pdu, unsigned int len);


    /** Encapsulate all SDUs from sduQ into PDUs and put them in generated_PDU Queue */
    void generatePDUsnew();

    void trySendGenPDUs(std::vector<DataTransferPDU*>* pduQ);



    /** This method does SDU protection eg CRC*/
    void sduProtection(SDU *sdu);

    void getSDUFromQ(SDU *sdu);


    void setConnId(const ConnectionId& connId);

    /* Policies */


    /* Policy-related methods */
//    void runTxControlPolicy(std::vector<DataTransferPDU*>* pduQ);
//    void runNoRateSlowDownPolicy();
//    void runReconcileFlowControlPolicy();

//    void runRateReductionPolicy();
//    void runRxTimerExpiryPolicy(RxExpiryTimer* timer);
    void runRcvrInactivityTimerPolicy();
    void runSenderInactivityTimerPolicy();
    void runRTTEstimatorPolicy();





    unsigned int getFlowControlRightWinEdge();

    /* This method SHOULD return amount of time to wait before retransmission attempt */
    double getRxTime();

    unsigned int getAllowableGap();



    void flushReassemblyPDUQ();
    void clearRxQ();
    void clearClosedWindowQ();

    void generateDTPDU(UserDataField* userDataField);

    void schedule(DTPTimers* timer, double time =0.0);

//    void handleSDUs(CDAPMessage* cdap);

    void initGates();

    bool commonRcvControl(ControlPDU* pdu);



    void sendAckOnlyPDU(unsigned int seqNum);
    bool setDRFInPDU(bool override);

    void redrawGUI();
    void addPDUToReassemblyQ(DataTransferPDU* pdu);



    void rcvrBufferStateChange();
    bool isDuplicate(unsigned int seqNum);
    void notifyAboutInactivity();


    void notifyStartSending();
    void handleControlPDUFromRMT(ControlPDU* pdu);

    double getATime();
    void fillControlAckPDU(ControlAckPDU* ctrlAckPdu);
    void fillRendezvousPDU(RendezvousPDU* rendezPDU);
    void sendRendezvousPDU();
    void rendezvousCondition();
    void handleRendezvousTimer(DTCPRendezvousTimer* timer);
    void handleInterrupterTimer(TheInterrupterTimer* msg);
    void changeInBuffers();

  public:
    DTP();
    virtual ~DTP();

//    bool read(int portId, unsigned char * buffer, int len);
//    bool readImmediate(int portId, unsigned char* buffer, int len);
//    bool write(int portId, unsigned char *buffer, int len);

    void delimitFromRMT();
    void svUpdate(unsigned int seqNum);

    void setFlow(const Flow* flow);
    void setDTCP(DTCP* dtcp);
    const QoSCube* getQoSCube() const;
    void setQoSCube(const QoSCube* qosCube);
    void setPduDroppingEnabled(bool pduDroppingEnabled);

    void flushAllQueuesAndPrepareToDie();
    cModule* createPolicyModule(const char* prefix, const char* name);
    void startATimer(unsigned int seqNum);

    void resetSenderInactivTimer();

    void setPDUHeader(PDU* pdu);
    void fillFlowControlPDU(FlowControlPDU* flowControlPdu);

    void sendFCOnlyPDU();
    void sendAckFlowPDU(unsigned int seqNum = 0, bool seqNumValid = false);
    void sendControlAckPDU();
    void sendEmptyDTPDU();

    void sendToRMT(PDU *pdu);



    void notifyStopSending();
    void notifyAboutUnableMaintain();

    void runCongestionNotificationPolicy();
    bool runInitialSeqNumPolicy();

    void setState(DTPState* state);
    void sendReliableControlPDU();
    void cancelATimer(unsigned int seqNum);
    bool isATimerQEmpty();


    /* Handle signals */
    void handleQueueInfoFromRMT(QueueInfo* queueInfo);
    void handleQueueInfoFromSocket(QueueInfo* queueInfo);

  protected:
    virtual void handleMessage(cMessage *msg);
    virtual void initialize(int step);
    int numInitStages() const
    {
      return 2;
    }
    void initSignalsAndListeners();



    //Signals

    simsignal_t sigEFCPStahpSending;
    simsignal_t sigEFCPStartSending;

    //Statistic signals
    simsignal_t sigStatDTPRTT;
    simsignal_t sigStatDTPClosedWinQ;
//    simsignal_t sigStatDTPRxCount;
    simsignal_t sigStatDTPSentSeqNum;
    simsignal_t sigStatDTPRecvSeqNum;

};

#endif /* DTP_H_ */
