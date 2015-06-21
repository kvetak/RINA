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

#include "DTPState.h"
#include "DTPTimers_m.h"
#include "DTCP.h"
//#include "PDU.h"
#include "DataTransferPDU.h"
#include "ControlPDU_m.h"
#include "SDU.h"
#include "RMT.h"

#include "RA.h"


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

    int deletePdu;
    bool pduDroppingEnabled;

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
    /* Output queues - from App to RMT */
    std::vector<SDU*> sduQ; //SDUs generated from delimiting //TODO A1 Deprecated - delete
    std::vector<SDU*> dataQ; //SDU or SDUFragments generated from delimiting



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
    void handleMsgFromDelimiting(SDU* sdu);
    void handleMsgFromRMT(PDU* msg);
    void handleDataTransferPDUFromRMT(DataTransferPDU* pdu);

    /* Send */


    /** Delimits content of buffer from application */
    unsigned int delimit(SDU* sdu);
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
    bool runInitialSeqNumPolicy();
//    void runRateReductionPolicy();
//    void runRxTimerExpiryPolicy(RxExpiryTimer* timer);
    void runRcvrInactivityTimerPolicy();
    void runSenderInactivityTimerPolicy();
    void runRTTEstimatorPolicy();





    unsigned int getFlowControlRightWinEdge();

    /* This method SHOULD return amount of time to wait before retransmission attempt */
    double getRxTime();

    unsigned int getAllowableGap();

    void svUpdate(unsigned int seqNum);

    void flushReassemblyPDUQ();
    void clearRxQ();
    void clearClosedWindowQ();



    void schedule(DTPTimers* timer, double time =0.0);

//    void handleSDUs(CDAPMessage* cdap);

    void initGates();

    bool commonRcvControl(ControlPDU* pdu);



    void sendAckOnlyPDU(unsigned int seqNum);
    bool setDRFInPDU(bool override);

    void redrawGUI();
    void addPDUToReassemblyQ(DataTransferPDU* pdu);
    void fillFlowControlPDU(FlowControlPDU* flowControlPdu);


    void rcvrBufferStateChange();
    bool isDuplicate(unsigned int seqNum);
    void notifyAboutInactivity();


    void notifyStartSending();

  public:
    DTP();
    virtual ~DTP();

//    bool read(int portId, unsigned char * buffer, int len);
//    bool readImmediate(int portId, unsigned char* buffer, int len);
//    bool write(int portId, unsigned char *buffer, int len);

    void delimitFromRMT(DataTransferPDU* pdu);

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

    void sendFCOnlyPDU();
    void sendAckFlowPDU(unsigned int seqNum = 0, bool seqNumValid = false);
    void sendControlAckPDU();
      void sendEmptyDTPDU();

    void sendToRMT(PDU *pdu);



    void notifyStopSending();
    void notifyAboutUnableMaintain();

    void runCongestionNotificationPolicy();
    void setState(DTPState* state);

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

};

#endif /* DTP_H_ */
