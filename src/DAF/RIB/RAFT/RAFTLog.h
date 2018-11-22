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

#ifndef DAF_RIB_RAFT_RAFTLOG_H_
#define DAF_RIB_RAFT_RAFTLOG_H_

#include <omnetpp.h>
#include "DAF/RIB/RAFT/RAFTLogObj.h"
#include "DAF/CDAP/CDAPMessage_m.h"
#include <list>

using namespace omnetpp;
typedef std::list<RAFTLogObj> RaftLog;
typedef RaftLog::iterator RaftLogIter;
typedef RaftLog::const_iterator RaftLogConstIter;


class RAFTLog : public cSimpleModule {
public:
    RAFTLogObj *createObjLeader(CDAPMessage *entry, unsigned int term);
    int appendNewEntries(RaftLog *raftLog);
    int matchIndexTerm(unsigned int index, unsigned int term);
    int getLastLogIndex();
    int getLastLogTerm();
    RaftLog *getLogsToBeSent(unsigned int index);
    RAFTLogObj *findObj(unsigned int index);

    int deleteFromIndex(unsigned int index);
    int appendLogFromIndex(RaftLog *raftLog, int index);
    int checkConflict(RaftLog *raftLog, int *clCnt, int *indexParamLog);
    bool empty();

    RaftLog *raftLog;

protected:
  virtual void initialize();
  virtual void handleMessage(cMessage *msg);
};

#endif /* DAF_RIB_RAFT_RAFTLOG_H_ */
