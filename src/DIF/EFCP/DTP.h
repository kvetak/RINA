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

#ifndef DTP_H_
#define DTP_H_

#include <omnetpp.h>
#include <vector>
#include "TxControlPolicy.h"
#include "DefaultTxControlPolicy.h"

#include "DTPState.h"
#include "DTPTimers_m.h"
#include "DTCP.h"
//#include "PDU.h"
#include "DataTransferPDU.h"
//#include "ControlPDU_m.h"
#include "SDU.h"
#include "RMT.h"

#include "RA.h"

//#include "SDUs.h"

#define DTP_MODULE_NAME "dtp"
#define DEFAULT_INIT_SEQUENCE_NUMBER 1
//#include "FA.h" //or FlowAllocatorFactory


class DTP : public cSimpleModule
{
    /* Friend policies */
    friend class DefaultTxControlPolicy;
  private:
    DTPState state; //state of this data-transfer
    DTCP* dtcp;
    Flow* flow;

    QosCube qosCube;


    /* Various queues */
    /* Output queues - from App to RMT */
    std::vector<SDU*> sduQ; //SDUs generated from delimiting //TODO A1 Deprecated - delete
    std::vector<SDU*> dataQ; //SDU or SDUFragments generated from delimiting
    std::vector<PDU*> generatedPDUs;
    std::vector<PDU*> postablePDUs;
    std::vector<PDU*> closedWindowQ;
    std::vector<RxExpiryTimer*> rxQ; //retransmissionQ //TODO A2 This variable should probably go into some other class
    /* Input queues - from RMT to App */
    std::vector<PDU*> reassemblyPDUQ;

    /* Timers */
    SenderInactivityTimer* senderInactivityTimer;
    RcvrInactivityTimer* rcvrInactivityTimer;
    /* This timer should be in FlowControl, but since for some reason "rateFulfilled" is in DTState it is better available from here */
    SendingRateTimer* sendingRateTimer;

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
    void handleDTPRxExpiryTimer(RxExpiryTimer* timer);
    void handleDTPSendingRateTimer(SendingRateTimer* timer);
//    void handleDTPWindowTimer(WindowTimer* timer);
    void handleDTPRcvrInactivityTimer(RcvrInactivityTimer* timer);
    void handleDTPSenderInactivityTimer(SenderInactivityTimer* timer);
    void handleDTPATimer(ATimer* timer);

    void handleMsgFromDelimiting(Data* msg);
    void handleMsgFromDelimitingnew(SDU* sdu);
    void handleMsgFromRmt(PDU* msg);
    void handleMsgFromRmtnew(PDU* msg);
    void handleDataTransferPDUFromRmtnew(DataTransferPDU* pdu);

    /* Send */



    /** Delimits content of buffer from application */
    unsigned int delimit(unsigned char *buffer, unsigned int len);
    unsigned int delimit(SDU* sdu);

    unsigned int delimitFromRMT(PDU *pdu, unsigned int len);


    /** Encapsulate all SDUs from sduQ into PDUs and put them in generated_PDU Queue */
    void generatePDUs();
    void generatePDUsnew();

    void trySendGenPDUs(std::vector<PDU*>* pduQ);






//    void sendPostablePDUsToRMT();
    void sendPDUToRMT(PDU* pdu);

    void fromRMT(PDU* pdu);

    /** This method does SDU protection eg CRC*/
    void sduProtection(SDU *sdu);

    void getSDUFromQ(SDU *sdu);


    void setConnId(const ConnectionId& connId);

    /* Policies */
    TxControlPolicy *txControlPolicy;

    /* Policy-related methods */
    void runTxControlPolicy(std::vector<PDU*>* pduQ);
    void runFlowControlOverrunPolicy();
    void runNoRateSlowDownPolicy();
    void runNoOverrideDefaultPeakPolicy();
    void runReconcileFlowControlPolicy();
    bool runInitialSequenceNumberPolicy();
    void runRcvrFlowControlPolicy();
    void runRateReductionPolicy();
    void runRcvrAckPolicy(unsigned int seqNum);
    void runReceivingFlowControlPolicy();
    void runRxTimerExpiryPolicy(RxExpiryTimer* timer);
    void runRcvrInactivityTimerPolicy();
    void runSenderInactivityTimerPolicy();
    bool runSendingAckPolicy(ATimer* timer);



    unsigned int getFlowControlRightWinEdge();

    /* This method SHOULD return amount of time to wait before retransmission attempt */
    unsigned int getRxTime();

    unsigned int getAllowableGap();

    void svUpdate(unsigned int seqNum);

    void flushReassemblyPDUQ();
    void clearRxQ();
    void clearClosedWindowQ();

    void sendToRMT(PDU *pdu);

    void schedule(DTPTimers* timer, double time =0.0);

    void handleSDUs(CDAPMessage* cdap);
    void setPDUHeader(PDU* pdu);
    void initGates();
    void delimitFromRMT(DataTransferPDU* pdu);
    void commonRcvControl(ControlPDU* pdu);

  public:
    DTP();
    virtual ~DTP();

    bool read(int portId, unsigned char * buffer, int len);
    bool readImmediate(int portId, unsigned char* buffer, int len);
    bool write(int portId, unsigned char *buffer, int len);

    void setFlow(Flow* flow);
    void setDTCP(DTCP* dtcp);
    const QosCube& getQosCube() const;
    void setQosCube(const QosCube& qosCube);

  protected:
    virtual void handleMessage(cMessage *msg);
    virtual void initialize(int step);

};

#endif /* DTP_H_ */
