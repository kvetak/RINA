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
 * @file DTPState.h
 * @author Marcel Marek
 * @date Apr 28, 2014
 * @brief
 * @detail
 * EFCPSpec 8.5.2 DTP State - the DTSV
 */
#ifndef DTPSTATE_H_
#define DTPSTATE_H_

    typedef enum {
        //NULL = 0,
        DTP_STATE_ACTIVE = 1,
        DTP_STATE_PORT_ID_TRANS = 0x10, //Port-id transition
    } DTPStateState;

/*
 *
 */
class DTPState {

private:
    int maxFlowSDUSize;
    int maxFlowPDUSize;
    int seqNumRollOverThresh;
    int state;
    bool dtcpPresent; /*!<a Boolean that indicates whether this connection is using DTCP. */
    bool winBased; /*!< a Boolean that indicates whether window-based flow control is in use.*/
    bool rateBased; /*!<a Boolean indicates whether rate-based flow control is in use.*/
    bool rexmsnPresent; /*!<a Boolean that indicates whether Retransmission Control (potentially with gaps) is in use*/
    bool closedWindow; /*!< This Boolean indicates whether or not the flow control window is closed.*/

    bool rateFullfilled; //This Boolean indicates that with rate-based flow control all the PDUs that can be sent during this time period have been sent.

    int closedWinQueLen; //The number of PDUs queued to send because the flow control window is shut.

    int maxClosedWinQueLen; /*!<an Integer that the number PDUs that can be put on the ClosedWindowQueue before something must be done.*/
    bool partDeliv; /* Partial Delivery of SDUs is Allowed */
    bool incompDeliv; /* Delivery of Incomplete SDUs is Allowed */
    //queue<PDU,timer>rexmsnQ; //The queue of PDUs that have been handed off to the RMT but not yet acknowledged.
    //queue<PDU> closedWinQ; //The queue of PDUs ready to be sent once the window opens.
    int rcvLeftWinEdge;
    int maxSeqNumRcvd;
    int senderLeftWinEdge;
    int nextSeqNumToSend;
    //queue<PDU,seqNum> pduReassemblyQ
    //queue<User_data>


public:
    DTPState();
    virtual ~DTPState();
};

#endif /* DTPSTATE_H_ */
