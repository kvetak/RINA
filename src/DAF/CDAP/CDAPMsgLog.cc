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

#include <CDAPMsgLog.h>

Define_Module(CDAPMsgLog);

CDAPMsgLog::CDAPMsgLog() {
    // TODO Auto-generated constructor stub

}

CDAPMsgLog::~CDAPMsgLog() {
    // TODO Auto-generated destructor stub

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
