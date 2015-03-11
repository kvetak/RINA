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

CDAPMsgLogEntry::CDAPMsgLogEntry(unsigned char opc, long invoke, bool srflag) :
        opCode(opc), invokeId(invoke), processedAt(simTime()), sndFlag(srflag)
{
}

CDAPMsgLogEntry::~CDAPMsgLogEntry() {
    opCode = 0;
    invokeId = UNINIT_INVOKEID;
    processedAt = 0;
    sndFlag = false;
}

std::string CDAPMsgLogEntry::info() const {
    std::ostringstream os;
    os << (sndFlag ? "Sent " : "Received " )
       << getOpCodeString() << "(" << (int)opCode
       << ")\ninvokeId: " << invokeId << endl
       << "processed at: " << this->processedAt;
    return os.str();
}

std::ostream& operator <<(std::ostream& os, const CDAPMsgLogEntry& mle) {
    return os << mle.info();
}

long CDAPMsgLogEntry::getInvokeId() const {
    return invokeId;
}

void CDAPMsgLogEntry::setInvokeId(long invokeId) {
    this->invokeId = invokeId;
}

const unsigned char CDAPMsgLogEntry::getOpCode() const {
    return opCode;
}

void CDAPMsgLogEntry::setOpCode(const unsigned char opCode) {
    this->opCode = opCode;
}

const simtime_t& CDAPMsgLogEntry::getProcessedAt() const {
    return processedAt;
}

void CDAPMsgLogEntry::setProcessedAt(const simtime_t& requestedAt) {
    this->processedAt = requestedAt;
}

std::string CDAPMsgLogEntry::getOpCodeString() const {
    switch(this->opCode)
    {
        case 1:   return "M_CONNECT";
        case 2:   return "M_CONNECT_R";
        case 3:   return "M_RELEASE";
        case 4:   return "M_RELEASE_R";
        case 5:   return "M_CREATE";
        case 6:   return "M_CREATE_R";
        case 7:   return "M_DELETE";
        case 8:   return "M_DELETE_R";
        case 9:   return "M_READ";
        case 10:   return "M_READ_R";
        case 11:  return "M_CANCELREAD";
        case 12:  return "M_CANCELREAD_R";
        case 13:  return "M_WRITE";
        case 14:  return "M_WRITE_R";
        case 15:  return "M_START";
        case 16:  return "M_START_R";
        case 17:  return "M_STOP";
        case 18:  return "M_STOP_R";
        default:  return "UNKNOWN";
    }
}

