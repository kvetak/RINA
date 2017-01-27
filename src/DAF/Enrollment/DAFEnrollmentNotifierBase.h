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

#ifndef DAFENROLLMENTNOTIFIERBASE_H_
#define DAFENROLLMENTNOTIFIERBASE_H_

#include <omnetpp.h>
#include "Common/CDAPProcessingBase.h"
#include "Common/ExternConsts.h"
#include "Common/RINASignals.h"
#include "DAF/Enrollment/DAFEnrollmentObj.h"
#include "DAF/Enrollment/DAFOperationObj.h"
#include "Common/Flow.h"

class DAFEnrollmentNotifierBase : public cSimpleModule, public CDAPProcessingBase {
public:

    virtual void sendStartEnrollmentRequest(DAFEnrollmentObj* obj) = 0;
    virtual void sendStartEnrollmentResponse(DAFEnrollmentObj* obj) = 0;
    virtual void sendStopEnrollmentRequest(DAFEnrollmentObj* obj) = 0;
    virtual void sendStopEnrollmentResponse(DAFEnrollmentObj* obj) = 0;
    virtual void sendStartOperationRequest(DAFOperationObj* obj) = 0;
    virtual void sendStartOperationResponse(DAFOperationObj* obj) = 0;
    virtual void sendCACE(CDAPMessage* msg) = 0;
    virtual Flow* getFlow() = 0;

    //CDAPProcessingBase interface
    virtual bool isMessageProcessable(CDAPMessage* msg);
    virtual void receiveMessage(CDAPMessage* msg);
    virtual void signalizeMessage(CDAPMessage* msg) = 0;
};

#endif /* DAFENROLLMENTNOTIFIERBASE_H_ */
