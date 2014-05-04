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
    bool setDRFFlag; // This Boolean indicates that the next PDU sent should have the DRF Flag set.
    bool immediate; //If Retransmission Control is present, this Boolean indicates whether Acks are sent immediately or after the A timer expires, or if DTCP is not present that there is no delay to allow late packets to arrive.
    unsigned int senderRightWinEdge;
    unsigned int rcvrRightWinEdgeSent;
    unsigned int rtt;
    //retransmissionQ
  public:
    DTCPState();
    virtual ~DTCPState();
    unsigned int getRtt() const;
    void setRtt(unsigned int rtt);
};

#endif /* DTCPSTATE_H_ */
