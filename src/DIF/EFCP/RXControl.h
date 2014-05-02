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
 * @file RXControl.h
 * @author Marcel Marek (imarek@fit.vutbr.cz)
 * @date May 3, 2014
 * @brief
 * @detail
 */

#ifndef RXCONTROL_H_
#define RXCONTROL_H_

#include <csimplemodule.h>

/*
 *
 */
class RXControl : public cSimpleModule
{
  private:
    unsigned int rightWinEdge; //The highest sequence number that the remote application is currently willing to accept on this connection.
    unsigned int lastRightWinEdgeSent; //The sequence number of the last Right Window Edge Sent in a Control PDU. (This should be the same as RightWindowEdge.)
    //rxQ  //retransmissionQueue  - The queue of PDUs that have been handed off to the RMT but not yet acknowledged.
    unsigned int nextSenderControlSeqNum; //This state variable will contain the Sequence Number to be assigned to a Control PDU sent on this connection.
    unsigned int lastRcvControlSeqNum; // - This state variable contains the sequence number of the next expected Transfer PDU received on this connection.
    unsigned int sendLeftWinEdge; // This state variable contains the Sequence Number of the lowest sequence number expected to be Acked. This should be the Sequence Number of the first PDU on the RetransmissionQ.
    unsigned int dataReXmitMax; // The maximum number of retransmissions of PDUs without a positive acknowledgement that will be tried before declaring an error.
    unsigned int rcvLeftWinEdge; // This state variable contains the Sequence Number of the lowest sequence number expected to be Acked. This should be the Sequence Number of the first PDU on the RetransmissionQ.
    /* Nota Bene: DTCP PDU Retransmission: Note that there is no retransmission queue
    for DTCP Control PDUs, when a lost control PDU is detected a new one is generated
    with the current information. */

  public:
    RXControl();
    virtual ~RXControl();
};

#endif /* RXCONTROL_H_ */
