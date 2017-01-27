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

#include "Common/Flow.h"
#include "DIF/EFCP/EFCPTable/EFCPTable.h"
#include "Common/ExternConsts.h"
#include "DIF/EFCP/EFCP_defs.h"
#include "DIF/RA/RA.h"
#include "DIF/EFCP/EFCPListeners.h"
//#include "DIF/EFCP/EFCPInstance.h"
//#include "DIF/Delimiting/Delimiting.h"


//class EFCPInstance;
//class EFCPTableEntry;
//class EFCPTable;



class EFCP : public cSimpleModule {
private:
//    bool dtcpPresent; /*!<a Boolean that indicates whether this connection is using DTCP. */
//    bool winBased; /*!< a Boolean that indicates whether window-based flow control is in use.*/
//    bool rateBased; /*!<a Boolean indicates whether rate-based flow control is in use.*/
//    int maxClosedWinQueLen; /*!<an Integer that the number PDUs that can be put on the ClosedWindowQueue before something must be done.*/
//    bool flowCont; /*!<a Boolean that indicates whether Flow Control is in use. The equivalent of the relation (Window-based OR Rate-based).*/
//    bool rexmsnPresent; /*!<a Boolean that indicates whether Retransmission Control (potentially with gaps) is in use*/
//    int dataRexmsnMax; /*!<an Integer that indicates the number of times the retransmission of a PDU will be attempted before some other action must be taken.*/
//
//    int sendRate; /*!<an Integer that indicates the number of PDUs that may be sent in a TimePeriod. Used with rate-based flow control.*/
//    int timePeriod; /*!<an Integer that indicates the length of time in microseconds for pacing rate-based flow control.*/
//
//    int initCredit; /*!<an Integer added to the initial sequence number to get right window edge.*/
//    int seqNumRollOverThresh; /*!<Integer. When the sequence number is increasing beyond this value, the sequence number space is close to rolling over, a new
//                                    connection should be instantiated and bound to the same port-ids, so that new PDUs can
//                                    be sent on the new connection.*/
//    int initATimer; /*!<an integer assigned per flow that indicates the maximum time that a
//                        receiver will wait before sending an Ack. Some DIFs may wish to set a maximum value for the DIF. */
//    int initSenderInactivTimer;/*!<an Integer that should be approximately 2Δt. This must be bounded. A DIF specification may want to specify a maximum value. */
//
//    int initRcvrInactivTimer; /*!<an Integer that should be approximately 3Δt. This must be bounded. A DIF specification may want to specify a maximum value.*/
//    int sendBytesFree; //The number of bytes that this flow can assume it currently has available for Writes
//    int sendBytesPercentFree; //The percent of bytes that is free for Writes
//    int sendBytesThresh; //The number of free bytes below which flow control should slow or block the user from doing any more Writes.
//    int sendBytesPercentThresh; //The percent of free bytes below, which flow control should slow or block the user from doing any more Writes.
//    int sendBuffFree; //The number of buffers of MaxSDU size that this flow can assume it currently has available for Writes.
//    int sendBuffPercentFree; //The percent of buffers of MaxSDU size that are free for Writes.
//    int sendBuffThresh; //The number of free buffers below which flow control should slow or block the user from doing any more Writes.
//    int sendBuffPercentThresh; //The percent of free buffers below which flow control should not advance or decreases the amount the Right Window Edge is moved.


    EFCPTable* efcpTable;
    RA* resourceAllocator;

    /* Listeners */

    LisEFCPCongestFromRA* lisEFCPCongestFromRA;
    LisEFCPQueueInfoFromAE* lisEFCPQueueInfoFromAE;

    Delimiting* createDelimiting(cModule* efcpi, int portId);
    DTCP* createDTCP(cModule* efcpi, const EFCPPolicySet* efcpPolicySet, const QoSCube* qosCube);
    cModule* createPolicyModule(const char* prefix, const char* name, const char* policy, cModule* parent, int verticalIndex = 1);



//    DTP dtp; //required part of the EFCP
//    DTStateVector dtStateV; //data-transfer state vector
//    DTCP* dtcp; //optional part of the EFCP

//    int portId; //FAI-identifier

//    std::map<unsigned int, DTP*> dtpMap; //list of currently existing DTP instances


protected:
    virtual void initialize(int step);
//    virtual int numInitStages() const {return 4;};

public:
    EFCP();
    virtual ~EFCP();


    EFCPInstance* createEFCPI(const Flow* flow, int cepId, int portId);
    bool deleteEFCPI(Flow *flow);


};

#endif /* EFCP_H_ */
