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
 * @file DTCPState.h
 * @author Marcel Marek (imarek@fit.vutbr.cz)
 * @date May 3, 2014
 * @brief
 * @detail
 */

#ifndef DTCPSTATE_H_
#define DTCPSTATE_H_

#include <omnetpp.h>
#include <DTCPTimers_m.h>

/*
 *
 */
class DTCPState : public cSimpleModule
{
  private:
    bool winBased; /*!< a Boolean that indicates whether window-based flow control is in use.*/
    bool rateBased; /*!<a Boolean indicates whether rate-based flow control is in use.*/
    bool rxPresent; /*!<a Boolean that indicates whether Retransmission Control (potentially with gaps) is in use*/

//    bool setDRFFlag; // This Boolean indicates that the next PDU sent should have the DRF Flag set.
//    bool immediate; //If Retransmission Control is present, this Boolean indicates whether Acks are sent immediately or after the A timer expires, or if DTCP is not present that there is no delay to allow late packets to arrive.
    unsigned int sndLeftWinEdge;
    unsigned int sndRightWinEdge;
    unsigned int rcvRightWinEdge; //The absolute value of the credit on this flow.
    unsigned int rcvRightWinEdgeSent;
//    unsigned int rtt;
    unsigned int rcvCredit; // Size of the receiver's window (local value)
    unsigned int sndCredit; // Size of the sender's window (desired value from remote end)


//    unsigned int controlSeqNum; //sequence number for ControlPDUs
    /* Moved from RX */
    unsigned int nextSenderControlSeqNum; //This state variable will contain the Sequence Number to be assigned to a Control PDU sent on this connection.
    unsigned int lastControlSeqNumRcv; // - This state variable contains the sequence number of the next expected Transfer PDU received on this connection.
    unsigned int lastControlSeqNumSent;

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


    unsigned int rcvrRate; //This variable contains the current rate that the receiver has told the sender that it may send PDUs at.

    unsigned int pdusRcvdinTimeUnit; //This variable contains the number of PDUs received in this Time Unit. When PDUsRcvdinTimeUnit equals RcvrRate, the receiver is allowed to discard any PDUs received until a new time unit begins.

    /* Without getters/setters */
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


    unsigned int rxSent; //number of PDUs sent from RxQ due to RxTimer expiration

    void clearPDUQ(PDUQ_t* pduQ);

    const QoSCube* qoSCube; //We'll see how this work out.


  public:
    DTCPState();
    virtual ~DTCPState();
//    unsigned int getRtt() const;
//    void setRtt(unsigned int rtt);
//    bool isImmediate() const;
//    void setImmediate(bool immediate);
    unsigned int getRcvrRightWinEdgeSent() const;
    void setRcvRightWinEdgeSent(unsigned int rcvrRightWinEdgeSent);
    unsigned int getSndRightWinEdge() const;
    void setSenderRightWinEdge(unsigned int senderRightWinEdge);
    unsigned int getSndLeftWinEdge() const;
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
    unsigned int getNextSndCtrlSeqNumNoInc();
    unsigned int getLastCtrlSeqNumRcv();
    void setLastCtrlSeqNumRcv(unsigned int ctrlSeqNum);
    void incRcvRtWinEdge();
    void initFC();
    unsigned int getRcvRightWinEdge() const;
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
    bool isClosedWinQClosed() const;
    void incRxSent();
    unsigned int getRxSent() const;
    bool isRateBased() const;
    void setRateBased(bool rateBased);
    bool isRxPresent() const;
    void setRxPresent(bool rxPresent);
    bool isWinBased() const;
    void setWinBased(bool winBased);

    bool isFCPresent(){ return winBased || rateBased;}

    const QoSCube* getQoSCube() const;
    void setQoSCube(const QoSCube*& qoSCube);

    unsigned int getPdusRcvdInTimeUnit() const;
    void setPdusRcvdinTimeUnit(unsigned int pdusRcvdinTimeUnit);

    void resetRcvVars();
    unsigned int getLastControlSeqNumSent() const;
    void setLastControlSeqNumSent(unsigned int lastControlSeqNumSent);
    
  protected:
    virtual void handleMessage(cMessage *msg);
    virtual void initialize(int step);
    int numInitStages() const { return 3;};
    void initFromQoS(const QoSCube* qosCube);

};

#endif /* DTCPSTATE_H_ */
