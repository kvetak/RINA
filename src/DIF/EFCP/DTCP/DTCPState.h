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
 * @file DTCPState.h
 * @author Marcel Marek (imarek@fit.vutbr.cz)
 * @date May 3, 2014
 * @brief
 * @detail
 */

#ifndef DTCPSTATE_H_
#define DTCPSTATE_H_

#include <cobject.h>
#include <omnetpp.h>
#include <DTCPTimers_m.h>

/*
 *
 */
class DTCPState : public cSimpleModule
{
  private:
//    bool setDRFFlag; // This Boolean indicates that the next PDU sent should have the DRF Flag set.
    bool immediate; //If Retransmission Control is present, this Boolean indicates whether Acks are sent immediately or after the A timer expires, or if DTCP is not present that there is no delay to allow late packets to arrive.
    unsigned int senderLeftWinEdge;
    unsigned int sndRtWinEdge;
    unsigned int rcvRtWinEdgeSent;
//    unsigned int rtt;
    unsigned int rcvCredit; // Size of the receiver's window (local value)
    unsigned int sndCredit; // Size of the sender's window (desired value from remote end)


//    unsigned int controlSeqNum; //sequence number for ControlPDUs
    /* Moved from RX */
    unsigned int nextSenderControlSeqNum; //This state variable will contain the Sequence Number to be assigned to a Control PDU sent on this connection.
    unsigned int lastControlSeqNumRcv; // - This state variable contains the sequence number of the next expected Transfer PDU received on this connection.

    unsigned int dataReXmitMax; // The maximum number of retransmissions of PDUs without a positive acknowledgment that will be tried before declaring an error.

    /* Moved from FC */
    unsigned long timeUnit; //This field contains the unit of time in milliseconds over which the rate is computed.
    unsigned int sendingRate; // This variable contains the number of PDUs that may be sent in one Time Unit. The rate is defined such that the sender may send the specified number of PDUs in that unit of time. Thus, the rate will not necessarily generate a steady flow, but  may exhibit a bursty pattern.

    unsigned int pdusSentInTimeUnit; //This variable contains the number of PDUs sent in this Time Unit. When PDUsSentinTimeUnit equals SndrRate, the sender must wait for the beginning of a new time unit before additional PDUs may be sent.
    unsigned long sendingTimeUnit; //The time period used to measure the SendingRate (measured in milliseconds).

    /* Without getters/setters */
    unsigned int sendBytesFree; // The number of bytes that this flow can assume it has available for Writes.
    unsigned int sendBytesPercentFree; // The percent of bytes that are free for Writes.
    unsigned int sendBytesThreshold; //The number of free bytes at which flow control blocks the user from doing any more Writes.
    unsigned int sendBytesPercentThresh; //The percent of free bytes at which flow control blocks the user from doing any more Writes.
    unsigned int sendBuffersFree; //The number of buffers of MaxSDU size that this flow can assume it has available for Writes.
    unsigned int sendBuffersPercentFree; //The percent of buffers of MaxSDU size that are free for Writes.
    unsigned int sendBuffersThreshold; //The number of free buffers at which flow control blocks the user from doing any more Writes.
    unsigned int sendBufferPercentThreshold; //The percent of free buffers at which flow control blocks the user from doing any more Writes.
    /* End without getters/setters */

    unsigned int rcvRtWinEdge; //The absolute value of the credit on this flow.
    unsigned int rcvrRate; //This variable contains the current rate that the receiver has told the sender that it may send PDUs at.

    /* Without getters/setters */
    unsigned int pdusRcvdinTimeUnit; //This variable contains the number of PDUs received in this Time Unit. When PDUsRcvdinTimeUnit equals RcvrRate, the receiver is allowed to discard any PDUs received until a new time unit begins.
    unsigned int rcvBytesFree; //The number of bytes that this flow can assume it has available for incoming PDUs on this connection.
    unsigned int rcvBytesPercentFree; //The percent of bytes that are free for incoming PDUs on this connection.
    unsigned int rcvBytesThreshold; //The number of free bytes at which flow control does not move the Right Window Edge.
    unsigned int rcvBytesPercentThreshold; //The percent of free bytes at which flow control does not move the Right Window Edge.
    unsigned int rcvBuffersFree; //The number of buffers of MaxPDU size that this flow can assume it has available for incoming PDUs
    /* End without getters/setters */

    unsigned int rcvBuffersPercentFree; //The percent of buffers of MaxPDU size that are free.
    unsigned int rcvBufferPercentThreshold; //The percent of free buffers at which flow control does not advance the Right Window Edge.

    bool sendingRateFullfilled; //This Boolean indicates that with rate-based flow control all the PDUs that can be sent during this time period have been sent.


    unsigned int dupAcks;
    /* Not found in specs but needed */
    unsigned int configRcvrRate; //contains the initial and desired rcvrRate - or at least that's how I understand ConfigRate variable from RateReduction Policy
    unsigned int dupFC; //duplicate Flow Control PDUs
    bool closedWindow; /*!< This Boolean indicates whether or not the flow control window is closed.*/
    unsigned int maxClosedWinQueLen; /*!<an Integer that the number PDUs that can be put on the ClosedWindowQueue before something must be done.*/
    std::vector<DataTransferPDU*> closedWindowQ;

    std::vector<DTCPRxExpiryTimer*> rxQ;





    void clearPDUQ(PDUQ_t* pduQ);

  public:
    DTCPState();
    virtual ~DTCPState();
//    unsigned int getRtt() const;
//    void setRtt(unsigned int rtt);
    bool isImmediate() const;
    void setImmediate(bool immediate);
    unsigned int getRcvrRightWinEdgeSent() const;
    void setRcvRtWinEdgeSent(unsigned int rcvrRightWinEdgeSent);
    unsigned int getSenderRightWinEdge() const;
    void setSenderRightWinEdge(unsigned int senderRightWinEdge);
    unsigned int getSenderLeftWinEdge() const;
    void setSenderLeftWinEdge(unsigned int senderLeftWinEdge);
//    bool isSetDrfFlag() const;
//    void setSetDrfFlag(bool setDrfFlag);
    unsigned int getRcvCredit() const;
    void setRcvCredit(unsigned int rcvCredit);
    unsigned int getSndCredit() const;
    void setSndCredit(unsigned int sndCredit);

    void updateRcvRtWinEdge(unsigned int rcvLtWinEdge);
//    unsigned int getNextCtrlSeqNum();
    unsigned int getNextSndCtrlSeqNum();
    unsigned int getLastCtrlSeqNumRcv();
    void setLastCtrlSeqNumRcv(unsigned int ctrlSeqNum);
    void incRcvRtWinEdge();
    void initFC();
    unsigned int getRcvRtWinEdge() const;
    void setRcvRtWinEdge(unsigned int rcvRtWinEdge);
    unsigned int getRcvBufferPercentThreshold() const;
    void setRcvBufferPercentThreshold(unsigned int rcvBufferPercentThreshold);
    unsigned int getRcvBuffersPercentFree() const;
    void setRcvBuffersPercentFree(unsigned int rcvBuffersPercentFree);


    void deleteRxTimer(unsigned int seqNum);
    unsigned int getDataReXmitMax() const;
    void setDataReXmitMax(unsigned int dataReXmitMax);

    std::vector<DTCPRxExpiryTimer*>* getRxQ();
    void pushBackToRxQ(DTCPRxExpiryTimer* timer);
    void clearRxQ();

    bool isClosedWindow() const;
    void setClosedWindow(bool closedWindow);
    unsigned int getClosedWinQueLen() const;
    std::vector<DataTransferPDU*>* getClosedWindowQ();
    void pushBackToClosedWinQ(DataTransferPDU* pdu);
    void clearClosedWindowQ();

    unsigned int getMaxClosedWinQueLen() const;
    void setMaxClosedWinQueLen(unsigned int maxClosedWinQueLen);

    /* Maybe */
    unsigned int getRxQLen();
    DTCPRxExpiryTimer* getRxTimer(unsigned int index);
    bool isSendingRateFullfilled() const;
    void setSendingRateFullfilled(bool sendingRateFullfilled);
    unsigned int getPdusSentInTimeUnit() const;
    void setPdusSentInTimeUnit(unsigned int pdusSentInTimeUnit);
    unsigned long getSendingTimeUnit() const;
    void setSendingTimeUnit(unsigned long sendingTimeUnit);
    unsigned int getSendingRate() const;
    void setSendingRate(unsigned int sendingRate);
    unsigned int getRcvrRate() const;
    void setRcvrRate(unsigned int rcvrRate);
    unsigned int getConfigRcvrRate() const;
    void setConfigRcvrRate(unsigned int configRcvrRate);

    void incDupAcks();
    unsigned int getDupAcks() const;
    void incDupFC();
    unsigned int getDupFC() const;
    unsigned long getTimeUnit() const;

    void updateSndLWE(unsigned int seqNum);


};

#endif /* DTCPSTATE_H_ */
