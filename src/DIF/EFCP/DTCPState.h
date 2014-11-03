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

/*
 *
 */
class DTCPState : public cObject
{
  private:
//    bool setDRFFlag; // This Boolean indicates that the next PDU sent should have the DRF Flag set.
    bool immediate; //If Retransmission Control is present, this Boolean indicates whether Acks are sent immediately or after the A timer expires, or if DTCP is not present that there is no delay to allow late packets to arrive.
    unsigned int sndRightWinEdge;
    unsigned int rcvRightWinEdgeSent;
    unsigned int rcvRtWinEdge;
//    unsigned int rtt;
    unsigned int rcvCredit; // Size of the receiver's window (local value)
    unsigned int sndCredit; // Size of the sender's window (desired value from remote end)
    //retransmissionQ

//    unsigned int controlSeqNum; //sequence number for ControlPDUs


    void setRcvRtWinEdge(unsigned int rcvRtWinEdge);
  public:
    DTCPState();
    virtual ~DTCPState();
//    unsigned int getRtt() const;
//    void setRtt(unsigned int rtt);
    bool isImmediate() const;
    void setImmediate(bool immediate);
    unsigned int getRcvrRightWinEdgeSent() const;
    void setRcvrRightWinEdgeSent(unsigned int rcvrRightWinEdgeSent);
    unsigned int getSenderRightWinEdge() const;
    void setSenderRightWinEdge(unsigned int senderRightWinEdge);
//    bool isSetDrfFlag() const;
//    void setSetDrfFlag(bool setDrfFlag);
    unsigned int getRcvCredit() const;
    void setRcvCredit(unsigned int rcvCredit);
    unsigned int getSndCredit() const;
    void setSndCredit(unsigned int sndCredit);
    unsigned int getRcvRtWinEdge() const;
    void updateRcvRtWinEdge(unsigned int rcvLtWinEdge);
//    unsigned int getNextCtrlSeqNum();

};

#endif /* DTCPSTATE_H_ */
