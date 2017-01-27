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

/**
 * @file DAFEnrollmentBase.h
 * @author Kamil Jerabek (xjerab18@stud.fit.vutbr.cz)
 * @date Apr 1, 2015
 * @brief DAFEnrollment and CACE Base
 * @detail
 */

#ifndef DAFENROLLMENTBASE_H_
#define DAFENROLLMENTBASE_H_

#include <omnetpp.h>
#include "Common/RINASignals.h"
#include "Common/Flow.h"
#include "DAF/CDAP/CDAPMessage_m.h"
#include "DAF/Enrollment/DAFEnrollmentStateTableEntry.h"
#include "Common/QoSReq.h"

class DAFEnrollmentBase : public cSimpleModule {
public:
    DAFEnrollmentBase();
    virtual ~DAFEnrollmentBase();
    //virtual void startCACE(APNIPair* apnip) = 0;
    virtual void startEnrollment(DAFEnrollmentStateTableEntry* entry) = 0;
    //virtual void insertStateTableEntry(Flow* flow) = 0;
    //virtual void receivePositiveConnectResponse(CDAPMessage* msg) = 0;
    //virtual void receiveNegativeConnectResponse(CDAPMessage* msg) = 0;
    //virtual void receiveConnectRequest(CDAPMessage* msg) = 0;

    virtual void receiveStartEnrollmentRequest(CDAPMessage* msg) = 0;
    virtual void receiveStartEnrollmentResponse(CDAPMessage* msg) = 0;
    virtual void receiveStopEnrollmentRequest(CDAPMessage* msg) = 0;
    virtual void receiveStopEnrollmentResponse(CDAPMessage* msg) = 0;
    virtual void receiveStartOperationRequest(CDAPMessage* msg) = 0;
    virtual void receiveStartOperationResponse(CDAPMessage* msg) = 0;

protected:
    virtual void initialize() = 0;

    virtual void parseConfig(cXMLElement* config) = 0;

    //virtual void authenticate(DAFEnrollmentStateTableEntry* entry, CDAP_M_Connect* msg) = 0;
};

#endif /* DAFENROLLMENTBASE_H_ */
