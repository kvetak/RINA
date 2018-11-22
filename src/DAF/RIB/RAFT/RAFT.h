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

#ifndef __RINA_RAFT_H_
#define __RINA_RAFT_H_

#include <omnetpp.h>
#include "Common/APNamingInfo.h"
#include "DAF/RIB/RAFT/RAFTLog.h"
#include "DAF/RIB/RAFT/RAFTFSM.h"
#include "DAF/Enrollment/DAFEnrollment.h"
#include "DAF/CDAP/CDAPMessage_m.h"
#include "DAF/AEManagement/AEMgmt.h"
#include "DAF/RIB/RAFT/RAFTListeners.h"
#include "DAF/RIB/RAFT/RAFTResultObj.h"
#include "DAF/RIB/RAFT/RAFTRequestVoteObj.h"
#include "DAF/RIB/RAFT/RAFTAppendEntryObj.h"
#include "DAF/RIB/RIB/RIBBase.h"
#include "DAF/RIB/RIB/SimpleRIB/Simplerib.h"

using namespace omnetpp;
class AEMgmt;
class DAFEnrollment;
typedef std::list<std::pair<std::string, int>> LogIndex;
typedef LogIndex::iterator LogIndexLogIter;
typedef LogIndex::const_iterator LogIndexConstIter;

typedef std::list<APNIPair> APNIPairs;
typedef std::map<simtime_t, APNIPairs*> DAFRAFTCommands;

typedef std::list<std::string> Neighbors;
typedef std::list<std::string> TmpOut;

typedef std::list<AEMgmt*> MgmtAEs;

/**
 * TODO - Generated class
 */
class RAFT : public cSimpleModule
{
public:
    enum State { Follower, Candidate, Leader};

    void checkAndAddIAE(AEMgmt* mgmtae);
    void receiveData(CDAPMessage* msg);
    CDAPMessage* commandReceivedFromClient(CDAPMessage* msg);
  protected:
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);


    int startElectionTimer();
    int resetElectionTimer();
    int startLeaderHeartBeatTimer();
    int resetLeaderHeartBeatTimer();
    void sendRequestVoteRPCsToAll();
    void sendAppendEntriesRPCResponse(RAFTResultObj *obj, std::string dstApn);
    void sendRequestVoteRPCResponse(RAFTResultObj *obj, std::string dstApn);
    void sendAppendEntriesRPCResponseHeartBeat(RAFTResultObj *obj, std::string dstApn);
    void sendHeartBeatsToAll();
    void sendAppendEntriesRPCsToAll();
    AEMgmt* getMgmtAEByDstApn(std::string dst);
    void updateDisplayString();
    void reinitializeLeaderNextIndex();
    void reinitializeLeaderMatchIndex();
    void setState(RAFT::State state);
    int getLogIndexIndex(std::string neigh, LogIndex *logIndex);
    void setLogIndexValue(std::string neigh, LogIndex *logIndex, int value);
    void sendAppendEntriesRPC(AEMgmt* ae);
    void checkAndUpdateCommitIndex();
    void applyEntries(int fromIndex, int toIndex);
    LogIndex *initializeLog(int num);
    void updateLogStatus();

  private:
    //persistent state on all servers
    unsigned int currentTerm;
    std::string votedFor;
    RAFTLog *raftLog;

    //volatile state on all servers
    unsigned int commitIndex;
    unsigned int lastApplied;

    //volatile state on leaders
    LogIndex *nextIndex;
    LogIndex *matchIndex;

    std::string myId;


    int votesResPos;
    RAFTFSM *raftFsm;

    //LisRAFTNewMgmtAe* lisRAFTNewMgmtAe;


    float electionTimeReset;
    float leaderHeartBeatTimer;
    cMessage *electionTimerSelfMessage;
    cMessage *leaderHeartBeatMessage;

    RAFT::State state;

    void parseConfig(cXMLElement* config);
    DAFEnrollment* enrollment;
    DAFRAFTCommands mgmtAeGenerateCommands;
    Neighbors neighbors;
    MgmtAEs mgmtaes;

    TmpOut nextIndexStatus;
    TmpOut matchIndexStatus;
};

#endif
