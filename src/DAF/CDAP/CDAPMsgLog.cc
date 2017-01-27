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

#include "DAF/CDAP/CDAPMsgLog.h"

Define_Module(CDAPMsgLog);

CDAPMsgLog::CDAPMsgLog() {


}

CDAPMsgLog::~CDAPMsgLog() {


}

void CDAPMsgLog::insert(CDAPMessage* cdapmsg, bool srflag) {
    MsgLog.push_back(CDAPMsgLogEntry(cdapmsg->getOpCode(), cdapmsg->getInvokeID(), srflag));
}

void CDAPMsgLog::initialize() {
    WATCH_LIST(MsgLog);
}

CDAPMsgLogEntry* CDAPMsgLog::findByMessage(CDAPMessage* cdapmsg) {
    for (TMLIter it = MsgLog.begin(); it != MsgLog.end(); it++) {
        if (it->getOpCode() == cdapmsg->getOpCode()
            && it->getInvokeId() == cdapmsg->getInvokeID())
            return &(*it);
    }
    return NULL;
}

CDAPMsgLogEntry* CDAPMsgLog::findRequestByInvId(CDAPMessage* cdapmsg) {
    for (TMLIter it = MsgLog.begin(); it != MsgLog.end(); it++) {
        if ( it->getOpCode() == cdapmsg->getOpCode() - 1
            && it->getInvokeId() == cdapmsg->getInvokeID())
            return &(*it);
    }
    return NULL;
}

void CDAPMsgLog::handleMessage(cMessage* msg) {
}

std::string CDAPMsgLog::info() const {
    std::string os;
    return os;
}
