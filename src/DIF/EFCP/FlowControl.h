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
 * @file FlowControl.h
 * @author Marcel Marek (imarek@fit.vutbr.cz)
 * @date May 3, 2014
 * @brief
 * @detail
 */

#ifndef FLOWCONTROL_H_
#define FLOWCONTROL_H_

#include <csimplemodule.h>
#include "ControlPDU_m.h"
#include "FCTimers_m.h"
#include "DTP.h"
#include "DTCP.h"

/*
 *
 */
class FlowControl : public cSimpleModule
{
    friend class DTCP;
    friend class DTP;
  private:
    unsigned long timeUnit; //This field contains the unit of time in milliseconds over which the rate is computed.
    unsigned int sendRightWindowEdge; // The largest Sequence Number of a PDU that may be sent without the receiver discarding it.
    unsigned int sendingRate; // This variable contains the number of PDUs that may be sent in one Time Unit. The rate is defined such that the sender may send the specified number of PDUs in that unit of time. Thus, the rate will not necessarily generate a steady flow, but  may exhibit a bursty pattern.
    unsigned int pdusSentInTimeUnit; //This variable contains the number of PDUs sent in this Time Unit. When PDUsSentinTimeUnit equals SndrRate, the sender must wait for the beginning of a new time unit before additional PDUs may be sent.
    unsigned long sendingTimeUnit; //The time period used to measure the SendingRate (measured in milliseconds).
    unsigned int sendBytesFree; // The number of bytes that this flow can assume it has available for Writes.
    unsigned int sendBytesPercentFree; // The percent of bytes that are free for Writes.
    unsigned int sendBytesThreshold; //The number of free bytes at which flow control blocks the user from doing any more Writes.
    unsigned int sendBytesPercentThresh; //The percent of free bytes at which flow control blocks the user from doing any more Writes.
    unsigned int sendBuffersFree; //The number of buffers of MaxSDU size that this flow can assume it has available for Writes.
    unsigned int sendBuffersPercentFree; //The percent of buffers of MaxSDU size that are free for Writes.
    unsigned int sendBuffersThreshold; //The number of free buffers at which flow control blocks the user from doing any more Writes.
    unsigned int sendBufferPercentThreshold; //The percent of free buffers at which flow control blocks the user from doing any more Writes.
    unsigned int rcvRightWindowEdge; //The absolute value of the credit on this flow.
    unsigned int rcvrRate; //This variable contains the current rate that the receiver has told the sender that it may send PDUs at.
    unsigned int pdusRcvdinTimeUnit; //This variable contains the number of PDUs received in this Time Unit. When PDUsRcvdinTimeUnit equals RcvrRate, the receiver is allowed to discard any PDUs received until a new time unit begins.
    unsigned int rcvBytesFree; //The number of bytes that this flow can assume it has available for incoming PDUs on this connection.
    unsigned int rcvBytesPercentFree; //The percent of bytes that are free for incoming PDUs on this connection.
    unsigned int rcvBytesThreshold; //The number of free bytes at which flow control does not move the Right Window Edge.
    unsigned int rcvBytesPercentThreshold; //The percent of free bytes at which flow control does not move the Right Window Edge.
    unsigned int rcvBuffersFree; //The number of buffers of MaxPDU size that this flow can assume it has available for incoming PDUs
    unsigned int rcvBuffersPercentFree; //The percent of buffers of MaxPDU size that are free.
    unsigned int rcvBuffersThreshold; //The number of free buffers at which flow control does not advance the Right Window Edge.
    unsigned int rcvBufferPercentThreshold; //The percent of free buffers at which flow control does not advance the Right Window Edge.


    bool sendingRateFullfilled; //This Boolean indicates that with rate-based flow control all the PDUs that can be sent during this time period have been sent.

    /* Not found in specs but needed */
    unsigned int configRcvrRate; //contains the initial and desired rcvrRate - or at least that's how I understand ConfigRate variable from RateReduction Policy
    unsigned int dupFC; //duplicate Flow Control PDUs



    /* FC Timers */
    FCSendingRateTimer* sendingRateTimer;
//    FCWindowTimer* sendingWindowTimer;

    void schedule(FCTimers* timer, double time = 0.0);
    void handleSendingRateTimer(FCSendingRateTimer* sendingRateTimer);

  public:
    FlowControl();
    virtual ~FlowControl();
    unsigned int getSendRightWindowEdge() const;
    void setSendRightWindowEdge(unsigned int sendRightWindowEdge);
    void setSendingRate(unsigned int sendingRate);
    unsigned int getSendingRate();
    void setRcvrRate(unsigned int rcvrRate);
    unsigned int getRcvrRate();

    void incDupFC();
    unsigned long getSendingTimeUnit() const;
    void setSendingTimeUnit(unsigned long sendingTimeUnit);
    unsigned int getRcvRightWindowEdge() const;
    void setRcvRightWindowEdge(unsigned int rcvRightWindowEdge);
    bool isSendingRateFullfilled() const;
    void setSendingRateFullfilled(bool rateFullfilled);

  protected:
    virtual void handleMessage(cMessage *msg);
};

#endif /* FLOWCONTROL_H_ */
