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

#include "DAF/CDAP/CDAPMsgLogEntry.h"

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

