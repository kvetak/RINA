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
 * @file EFCP.h
 * @author Marcel Marek
 * @date Apr 28, 2014
 * @brief
 * @detail
 */

#ifndef EFCP_H_
#define EFCP_H_

/*
 *
 */
#include <omnetpp.h>


#include "EFCPTable.h"
#include "FAI.h"
//#include "EFCPInstance.h"
//#include "Delimiting.h"


//class EFCPInstance;
//class EFCPTableEntry;
//class EFCPTable;



class EFCP : public cSimpleModule {
private:
    bool dtcpPresent; /*!<a Boolean that indicates whether this connection is using DTCP. */
    bool winBased; /*!< a Boolean that indicates whether window-based flow control is in use.*/
    bool rateBased; /*!<a Boolean indicates whether rate-based flow control is in use.*/
    int maxClosedWinQueLen; /*!<an Integer that the number PDUs that can be put on the ClosedWindowQueue before something must be done.*/
    bool flowCont; /*!<a Boolean that indicates whether Flow Control is in use. The equivalent of the relation (Window-based OR Rate-based).*/
    bool rexmsnPresent; /*!<a Boolean that indicates whether Retransmission Control (potentially with gaps) is in use*/
    int dataRexmsnMax; /*!<an Integer that indicates the number of times the retransmission of a PDU will be attempted before some other action must be taken.*/

    int sendRate; /*!<an Integer that indicates the number of PDUs that may be sent in a TimePeriod. Used with rate-based flow control.*/
    int timePeriod; /*!<an Integer that indicates the length of time in microseconds for pacing rate-based flow control.*/

    int initCredit; /*!<an Integer added to the initial sequence number to get right window edge.*/
    int seqNumRollOverThresh; /*!<Integer. When the sequence number is increasing beyond this value, the sequence number space is close to rolling over, a new
                                    connection should be instantiated and bound to the same port-ids, so that new PDUs can
                                    be sent on the new connection.*/
    int initATimer; /*!<an integer assigned per flow that indicates the maximum time that a
                        receiver will wait before sending an Ack. Some DIFs may wish to set a maximum value for the DIF. */
    int initSenderInactivTimer;/*!<an Integer that should be approximately 2Δt. This must be bounded. A DIF specification may want to specify a maximum value. */

    int initRcvrInactivTimer; /*!<an Integer that should be approximately 3Δt. This must be bounded. A DIF specification may want to specify a maximum value.*/
    int sendBytesFree; //The number of bytes that this flow can assume it currently has available for Writes
    int sendBytesPercentFree; //The percent of bytes that is free for Writes
    int sendBytesThresh; //The number of free bytes below which flow control should slow or block the user from doing any more Writes.
    int sendBytesPercentThresh; //The percent of free bytes below, which flow control should slow or block the user from doing any more Writes.
    int sendBuffFree; //The number of buffers of MaxSDU size that this flow can assume it currently has available for Writes.
    int sendBuffPercentFree; //The percent of buffers of MaxSDU size that are free for Writes.
    int sendBuffThresh; //The number of free buffers below which flow control should slow or block the user from doing any more Writes.
    int sendBuffPercentThresh; //The percent of free buffers below which flow control should not advance or decreases the amount the Right Window Edge is moved.


    EFCPTable* efcpTable;



//    DTP dtp; //required part of the EFCP
//    DTStateVector dtStateV; //data-transfer state vector
//    DTCP* dtcp; //optional part of the EFCP

//    int portId; //FAI-identifier

//    std::map<unsigned int, DTP*> dtpMap; //list of currently existing DTP instances


public:
    EFCP();
    virtual ~EFCP();


    EFCPInstance* createEFCPI(FAI* fai);

};

#endif /* EFCP_H_ */
