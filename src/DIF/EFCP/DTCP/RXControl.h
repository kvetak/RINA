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
 * @file RXControl.h
 * @author Marcel Marek (imarek@fit.vutbr.cz)
 * @date May 3, 2014
 * @brief
 * @detail
 */

#ifndef RXCONTROL_H_
#define RXCONTROL_H_

#include <omnetpp.h>

/*
 *
 */
class RXControl : public cSimpleModule
{
    friend class DTP;
  private:
//    unsigned int rightWinEdge; //The highest sequence number that the remote application is currently willing to accept on this connection.
//    unsigned int lastRightWinEdgeSent; //The sequence number of the last Right Window Edge Sent in a Control PDU. (This should be the same as RightWindowEdge.)
    //rxQ  //retransmissionQueue  - The queue of PDUs that have been handed off to the RMT but not yet acknowledged.

    /* Moved to DTCPState because it is needed even if RXControl is not present */
//    unsigned int nextSenderControlSeqNum; //This state variable will contain the Sequence Number to be assigned to a Control PDU sent on this connection.
//    unsigned int lastControlSeqNumRcv; // - This state variable contains the sequence number of the next expected Transfer PDU received on this connection.

//    unsigned int sendLeftWinEdge; // This state variable contains the Sequence Number of the lowest sequence number expected to be Acked. This should be the Sequence Number of the first PDU on the RetransmissionQ.
//    unsigned int dataReXmitMax; // The maximum number of retransmissions of PDUs without a positive acknowledgement that will be tried before declaring an error.
//    unsigned int rcvLeftWinEdge; // This state variable contains the Sequence Number of the lowest sequence number expected to be Acked. This should be the Sequence Number of the first PDU on the RetransmissionQ.



    //    unsigned int dupAcks;


    /* Nota Bene: DTCP PDU Retransmission: Note that there is no retransmission queue
    for DTCP Control PDUs, when a lost control PDU is detected a new one is generated
    with the current information. */

  public:
    RXControl();
    virtual ~RXControl();

//   unsigned int getRightWinEdge();

//   unsigned int getNextSndCtrlSeqNum();
//   unsigned int getLastCtrlSeqNumRcv();
//   void setLastCtrlSeqNumRcv(unsigned int ctrlSeqNum);
//   void incDupAcks();
};

#endif /* RXCONTROL_H_ */
