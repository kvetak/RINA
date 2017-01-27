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

#include "DAF/Enrollment/DAFEnrollmentNotifierBase.h"

bool DAFEnrollmentNotifierBase::isMessageProcessable(CDAPMessage* msg) {
    Enter_Method_Silent();
    bool status =   (
            ( dynamic_cast<CDAP_M_Connect*>(msg) ) ||
            ( dynamic_cast<CDAP_M_Connect_R*>(msg) ) ||
            ( dynamic_cast<CDAP_M_Start*>(msg) && dynamic_cast<DAFEnrollmentObj*>(dynamic_cast<CDAP_M_Start*>(msg)->getObjectItem().objectVal) ) ||
            ( dynamic_cast<CDAP_M_Start_R*>(msg) && dynamic_cast<DAFEnrollmentObj*>(dynamic_cast<CDAP_M_Start_R*>(msg)->getObjectItem().objectVal) ) ||
            ( dynamic_cast<CDAP_M_Stop*>(msg) && dynamic_cast<DAFEnrollmentObj*>(dynamic_cast<CDAP_M_Stop*>(msg)->getObjectItem().objectVal) ) ||
            ( dynamic_cast<CDAP_M_Stop_R*>(msg) && dynamic_cast<DAFEnrollmentObj*>(dynamic_cast<CDAP_M_Stop_R*>(msg)->getObjectItem().objectVal) )
                    )
                    ? true : false;
    return status;
}

void DAFEnrollmentNotifierBase::receiveMessage(CDAPMessage* msg) {
    Enter_Method("receiveMessage()");
    CDAPProcessingBase::receiveMessage(msg);
}

