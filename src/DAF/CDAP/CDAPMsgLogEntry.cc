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

#include "CDAPMsgLogEntry.h"

CDAPMsgLogEntry::CDAPMsgLogEntry() {
    this->msgStatus = this->UNKNOWN;
    this->opCode = "";
}

CDAPMsgLogEntry::~CDAPMsgLogEntry() {
    this->msgStatus = this->UNKNOWN;
    this->invokeId = UNINIT_INVOKEID;
    this->requestedAt = 0;
    this->respondedAt = 0;
}

std::string CDAPMsgLogEntry::info() const {
    std::stringstream os;
    os << "" << this->getOpCode() << "status: " << this->getMessageStatusString()
       << "requested at: " << this->requestedAt
       << "\tresponded at:" << this->respondedAt << endl;
    return os.str();
}

std::string CDAPMsgLogEntry::getMessageStatusString() const {
    switch(this->msgStatus)
    {
        case REQUESTED:   return "requested";
        case RESPONDED:   return "responded";
        case UNKNOWN:
        default:                return "UNKNOWN";
    }
}

std::ostream& operator <<(std::ostream& os, const CDAPMsgLogEntry& mle) {
    return os << mle.info();
}

int CDAPMsgLogEntry::getInvokeId() const {
    return invokeId;
}

void CDAPMsgLogEntry::setInvokeId(int invokeId) {
    this->invokeId = invokeId;
}

void CDAPMsgLogEntry::setMsgStatus(CDAPMsgStatus msgStatus) {
    this->msgStatus = msgStatus;
}

const std::string& CDAPMsgLogEntry::getOpCode() const {
    return opCode;
}

void CDAPMsgLogEntry::setOpCode(const std::string& opCode) {
    this->opCode = opCode;
}

const simtime_t& CDAPMsgLogEntry::getRequestedAt() const {
    return requestedAt;
}

void CDAPMsgLogEntry::setRequestedAt(const simtime_t& requestedAt) {
    this->requestedAt = requestedAt;
}

const simtime_t& CDAPMsgLogEntry::getRespondedAt() const {
    return respondedAt;
}

void CDAPMsgLogEntry::setRespondedAt(const simtime_t& respondedAt) {
    this->respondedAt = respondedAt;
}
