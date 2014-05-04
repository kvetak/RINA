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
#include "PDU.h"
#include "DataTransferPDU_m.h"
#include "SDU.h"

#include "FlowAllocator.h" //or FlowAllocatorFactory
#include "RMT.h"

class DTP : public cSimpleModule
{
    /* Friend policies */
    friend class DefaultTxControlPolicy;
  private:
    DTPState state; //state of this data-transfer
    DTCP* dtcp;
    RMT* rmt;


    std::vector<SDU*> sduQ; //SDUs generated from delimiting
    std::vector<PDU*> generatedPDUs;
    std::vector<PDU*> postablePDUs;
    std::vector<PDU*> closedWindowQ;
    std::vector<RxExpiryTimer*> rxQ; //retransmissionQ //TODO A2 This variable should probably go into some other class

    InactivityTimer* senderInactivity;

    FlowAllocator* flowAllocator;
    /* OR
     * FlowAllocatorFactory flowFactory;
     * int flowAllocatorId;
     */

    ConnectionId connId;


    /* Policies */
    TxControlPolicy *txControlPolicy;




    /** Delimits  content of buffer */
    int delimit(unsigned char *buffer, unsigned int len);

    /** Encapsulate all SDUs from sduQ into PDUs and put them in generated_PDU Queue */
    void generatePDUs();

    void trySendGenPDUs();

    void sendPostablePDUsToRMT();

    /** This method does SDU protection eg CRC*/
    void sduProtection(SDU *sdu);
    void getSDUFromQ(SDU *sdu);
    void setConnId(const ConnectionId& connId);

    /* Policy-related methods */
    void runTxControlPolicy();
    void runFlowControlOverrunPolicy();
    void runNoRateSlowDownPolicy();
    void runNoOverrideDefaultPeakPolicy();
    void runReconcileFlowControlPolicy();

    unsigned int getFlowControlRightWinEdge();

    /* This method SHOULD return amount of time to wait before retransmission attempt */
    unsigned int getRxTime();



    void schedule(DTPTimers* timer, double time =0.0);

  public:
    DTP();
    virtual ~DTP();

    bool read(int portId, unsigned char * buffer, int len);
    bool readImmediate(int portId, unsigned char* buffer, int len);
    bool write(int portId, unsigned char *buffer, int len);



  protected:
    virtual void handleMessage(cMessage *msg);

};

#endif /* DTP_H_ */
