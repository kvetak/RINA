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

#include "RAFT.h"

Define_Module(RAFT);

const char* DAF_RAFT = "Raft";
const char* DAF_RAFT_SIMTIME = "Simtime";
const char* DAF_RAFT_CONNECT = "Connect";
const char* DAF_MSG_RAFTCON = "RAFTMSG";
const char* DAF_MSG_RAFT_START = "RAFTSTARTMSG";
const char* DAF_RAFT_ATTR_TIME = "t";
const char* DAF_RAFT_ATTR_SRC = "src_apn";
const char* DAF_RAFT_ATTR_SRC_INST = "src_inst";
const char* DAF_RAFT_ATTR_DST = "dst_apn";
const char* DAF_RAFT_ATTR_DST_INST = "dst_inst";
const char* DAF_RAFT_NEIGHBORS =  "Neighbors";
const char* DAF_RAFT_NEIGHBOR = "Neighbor";
const char* DAF_RAFT_MESSAGE_M_WRITE_VOTE_REQUEST = "M_WRITE(RAFT_RequestVoteRPC)";
const char* DAF_RAFT_MESSAGE_M_WRITE_R_APPEND_ENTRIES = "M_WRITE_R(RAFT_AppendEntriesRPC)";
const char* DAF_RAFT_MESSAGE_M_WRITE_APPEND_ENTRIES = "M_WRITE(RAFT_AppendEntriesRPC)";
const char* DAF_RAFT_MESSAGE_M_WRITE_R_REQUEST_VOTE = "M_WRITE_R(RAFT_RequestVoteRPC)";
const char* DAF_RAFT_MESSAGE_M_WRITE_APPEND_ENTRIES_HEARTBEAT = "M_WRITE(RAFT_AppendEntriesRPC_HeartBeat)";
const char* DAF_RAFT_MESSAGE_M_WRITE_R_APPEND_ENTRIES_HEARTBEAT = "M_WRITE_R(RAFT_AppendEntriesRPC_HeartBeat)";

void RAFT::initialize()
{
    //Parse XML config
    parseConfig(par(PAR_CONFIGDATA).xmlValue());

    this->setState(Follower);
    //this->startElectionTimer();
    this->currentTerm = 0;
    this->votedFor = "";
    this->votesResPos = 0;
    this->commitIndex = 0;
    this->lastApplied = 0;
    this->electionTimerSelfMessage = NULL;
    this->leaderHeartBeatMessage = NULL;
    this->nextIndex = NULL;
    this->matchIndex = NULL;

    enrollment = check_and_cast<DAFEnrollment*>(getModuleByPath("^.^.^.enrollment.enrollment"));

    //this->raftLog = new RAFTLog();
    this->raftLog = check_and_cast<RAFTLog*>(getModuleByPath("^.raftLog"));
    RIBBase * rib = check_and_cast<RIBBase*>(getModuleByPath("^.^.^.rib.rib"));
    //this->raftFsm = new RAFTFSM(rib);
    this->raftFsm = check_and_cast<RAFTFSM*>(getModuleByPath("^.raftFsm"));
    //lisRAFTNewMgmtAe = new LisRAFTNewMgmtAe(this);


    WATCH_LIST(nextIndexStatus);
    WATCH_LIST(matchIndexStatus);
    WATCH(currentTerm);
    WATCH(votedFor);
    WATCH(commitIndex);
    WATCH(lastApplied);
    WATCH(myId);
    WATCH(state);
}

void RAFT::setState(RAFT::State state) {
    this->state = state;
    this->updateDisplayString();
}

int RAFT::startElectionTimer() {
    //timeout set to 1.5-3s
    this->electionTimeReset = (rand() % 1500 + 1500) / 1000.0;
    simtime_t interval = this->electionTimeReset;
    this->electionTimerSelfMessage = new cMessage("electionTimer");

    scheduleAt(simTime() + interval, this->electionTimerSelfMessage);

    return 0;
}

LogIndex *RAFT::initializeLog(int num) {
    auto log = new LogIndex();

    for(auto it = mgmtaes.begin(); it != mgmtaes.end(); ++it) {
        AEMgmt* ae = *it;
        log->push_back(std::pair<std::string, int>(ae->getDstNamingInfo().getApn().getName(), num));
    }
    return log;
}

int RAFT::resetElectionTimer() {
    if (this->electionTimerSelfMessage) {
        cancelEvent(this->electionTimerSelfMessage);
    }

    this->startElectionTimer();
    return 0;
}

int RAFT::startLeaderHeartBeatTimer() {
    //timeout set to 1s (should be 100ms)
    this->leaderHeartBeatTimer = 1.0;
    simtime_t interval = this->leaderHeartBeatTimer;
    this->leaderHeartBeatMessage = new cMessage("leaderHeartBeatTimer");

    scheduleAt(simTime() + interval, this->leaderHeartBeatMessage);

    return 0;
}

int RAFT::resetLeaderHeartBeatTimer() {
    if (this->leaderHeartBeatMessage) {
        cancelEvent(this->leaderHeartBeatMessage);
    }

    this->startLeaderHeartBeatTimer();
    return 0;
}


void RAFT::sendRequestVoteRPCsToAll() {
    EV << "RAFT: sendVoteRPCsToAll" << endl;
    for(auto it = mgmtaes.begin(); it != mgmtaes.end(); ++it) {
        AEMgmt* ae = *it;

        RAFTRequestVoteObj *obj = new RAFTRequestVoteObj(this->currentTerm,
                                                            this->myId,
                                                            this->raftLog->getLastLogIndex(),
                                                            this->raftLog->getLastLogTerm());


        CDAP_M_Write* write = new CDAP_M_Write(DAF_RAFT_MESSAGE_M_WRITE_VOTE_REQUEST);

        std::ostringstream os;
        os << "RAFT_RequestVoteRPC";
        object_t raftRequestVoteRPCObj;
        raftRequestVoteRPCObj.objectClass = obj->getClassName();
        raftRequestVoteRPCObj.objectName = os.str();
        raftRequestVoteRPCObj.objectVal = obj;
        raftRequestVoteRPCObj.objectInstance = 1;
        write->setObjectItem(raftRequestVoteRPCObj);

        write->setSrcAddr(Address(ae->getSrcNamingInfo().getApn()));
        write->setDstAddr(Address(ae->getDstNamingInfo().getApn()));

        ae->signalizeSendData(write);
    }
}

void RAFT::sendAppendEntriesRPCsToAll() {
    EV << "RAFT: sendAppendEntriesRPCsToAll" << endl;
    for(auto it = mgmtaes.begin(); it != mgmtaes.end(); ++it) {
        AEMgmt* ae = *it;
        this->sendAppendEntriesRPC(ae);
    }
}

void RAFT::checkAndUpdateCommitIndex() {
    bool cond = true;
    int commitIndex = this->commitIndex;
    int counter = 0;
    while (cond) {
        for(auto it = this->matchIndex->begin(); it != this->matchIndex->end(); ++it) {
            if ((*it).second > commitIndex) {
                counter += 1;
            }
        }

        //TODO: change to something better
        if (counter >= this->neighbors.size()-1) {
            commitIndex += 1;
        }
        else {
            break;
        }

        counter = 0;
    }

    this->commitIndex = commitIndex;
}

void RAFT::sendAppendEntriesRPC(AEMgmt* ae) {
    EV << "RAFT: sendAppendEntriesRPC normal" << endl;

    int tmpIndex = 0;
    for(auto itt = this->nextIndex->begin(); itt != this->nextIndex->end(); ++itt) {
        if ((*itt).first == ae->getDstNamingInfo().getApn().getName()) {
            tmpIndex = (*itt).second;
            break;
        }
    }

    if (tmpIndex > this->raftLog->getLastLogIndex()) {
        return;
    }

    RaftLog *tmpLog = this->raftLog->getLogsToBeSent(tmpIndex);
    int prevLogIndex = 1;
    int prevLogTerm = 1;
    if (tmpIndex > 0) {
        prevLogIndex = tmpIndex - 1;
        RAFTLogObj* objj = this->raftLog->findObj(prevLogIndex);
        if (objj) {
            prevLogTerm = objj->term - 1;
        }
        else {
            prevLogTerm = 0;
        }
    }

    RAFTAppendEntryObj* obj = new RAFTAppendEntryObj(this->currentTerm,
                                                        this->myId,
                                                        prevLogIndex,
                                                        prevLogTerm,
                                                        tmpLog,
                                                        this->commitIndex);

    CDAP_M_Write* write = new CDAP_M_Write(DAF_RAFT_MESSAGE_M_WRITE_APPEND_ENTRIES);

    std::ostringstream os;
    os << "RAFT_AppendEntriesRPC_HeartBeat";
    object_t raftAppendEntriesRPCObj;
    raftAppendEntriesRPCObj.objectClass = obj->getClassName();
    raftAppendEntriesRPCObj.objectName = os.str();
    raftAppendEntriesRPCObj.objectVal = obj;
    raftAppendEntriesRPCObj.objectInstance = 1;
    write->setObjectItem(raftAppendEntriesRPCObj);
    write->setByteLength(sizeof(raftAppendEntriesRPCObj) + sizeof(*obj));

    write->setSrcAddr(Address(ae->getSrcNamingInfo().getApn()));
    write->setDstAddr(Address(ae->getDstNamingInfo().getApn()));

    ae->signalizeSendData(write);
}

void RAFT::sendHeartBeatsToAll() {
    EV << "RAFT: sendHeartBeatsToAll" << endl;
    for(auto it = mgmtaes.begin(); it != mgmtaes.end(); ++it) {
        AEMgmt* ae = *it;

        //TODO: change this to better values for HeartBeat
        RAFTAppendEntryObj* obj = new RAFTAppendEntryObj(this->currentTerm, this->myId, 0, 0, NULL, this->commitIndex);
        CDAP_M_Write* write = new CDAP_M_Write(DAF_RAFT_MESSAGE_M_WRITE_APPEND_ENTRIES_HEARTBEAT);

        std::ostringstream os;
        os << "RAFT_AppendEntriesRPC_HeartBeat";
        object_t raftRequestVoteRPCObj;
        raftRequestVoteRPCObj.objectClass = obj->getClassName();
        raftRequestVoteRPCObj.objectName = os.str();
        raftRequestVoteRPCObj.objectVal = obj;
        raftRequestVoteRPCObj.objectInstance = 1;
        write->setObjectItem(raftRequestVoteRPCObj);
        write->setByteLength(sizeof(raftRequestVoteRPCObj));

        write->setSrcAddr(Address(ae->getSrcNamingInfo().getApn()));
        write->setDstAddr(Address(ae->getDstNamingInfo().getApn()));

        ae->signalizeSendData(write);

    }
}

void RAFT::reinitializeLeaderNextIndex() {
    this->nextIndex = new LogIndex();

    for(auto it = neighbors.begin(); it != neighbors.end(); ++it) {
        std::string str = *it;
        this->nextIndex->push_back(std::make_pair(str, this->raftLog->getLastLogIndex()+1));
    }
}

void RAFT::reinitializeLeaderMatchIndex() {
    this->matchIndex = new LogIndex();

    for(auto it = neighbors.begin(); it != neighbors.end(); ++it) {
        std::string str = *it;
        this->matchIndex->push_back(std::make_pair(str, 0));
    }
}

void RAFT::applyEntries(int fromIndex, int toIndex) {
    for (int i = fromIndex+1; i <= toIndex; i++) {
        RAFTLogObj* obj = this->raftLog->findObj(i);

        if (obj) {
            this->raftFsm->applyEntry(obj);
        }
    }
}

void RAFT::receiveData(CDAPMessage* msg) {
    Enter_Method("RAFT_receiveData()");
    //requests
    if (dynamic_cast<CDAP_M_Write*>(msg)) {
        CDAP_M_Write *mesg = check_and_cast<CDAP_M_Write*>(msg);

        /* ========== FOLLOWERS ==========
         * If election timeout elapses without receiving AppendEntries
         * RPC from current leader or granting vote to candidate:
         * convert to candidate
         */
        if (this->state == Follower) {
            EV << "RAFT: message received, reset election timer now" << endl;
            this->resetElectionTimer();
        }


        // Reuqest vote rpc case
        if (!strcmp(mesg->getName(), DAF_RAFT_MESSAGE_M_WRITE_VOTE_REQUEST)) {
            if (check_and_cast<RAFTRequestVoteObj*>(mesg->getObjectItem().objectVal)) {
                RAFTRequestVoteObj *obj = check_and_cast<RAFTRequestVoteObj*>(mesg->getObjectItem().objectVal);
                RAFTResultObj *robj = new RAFTResultObj();
                robj->type = RAFTResultObj::Vote;
                robj->term = this->currentTerm;
                /* ======== RECEIVER IMPLEMENTATION =========
                 * 1. Reply false if term < currentTerm (§5.1)
                 */
                robj->voteGranted = false;

                /* ======== RECEIVER IMPLEMENTATION =========
                 * 2. If votedFor is null or candidateId, and candidate’s log is at
                 * least as up-to-date as receiver’s log, grant vote (§5.2, §5.4)
                 */
                if (obj->term >= this->currentTerm) {
                    if (this->votedFor == "" || this->votedFor == obj->candidateId) {
                        if (this->raftLog->getLastLogIndex() <= obj->lastLogIndex) {
                            robj->voteGranted = true;
                            this->votedFor = obj->candidateId;
                        }
                    }
                    this->currentTerm = obj->term;
                }

                EV << "RAFT: " << DAF_RAFT_MESSAGE_M_WRITE_VOTE_REQUEST << " received --> send vote RPCResponse" << endl;

                this->sendRequestVoteRPCResponse(robj, mesg->getSrcAddr().getApn().getName());
            }
        }

        if (!strcmp(mesg->getName(), DAF_RAFT_MESSAGE_M_WRITE_APPEND_ENTRIES_HEARTBEAT)) {
            if (check_and_cast<RAFTAppendEntryObj*>(mesg->getObjectItem().objectVal)) {
                RAFTAppendEntryObj* obj = check_and_cast<RAFTAppendEntryObj*>(mesg->getObjectItem().objectVal);
                RAFTResultObj *robj = new RAFTResultObj();
                robj->type = RAFTResultObj::Append;
                robj->term = this->currentTerm;
                robj->success = true;

                if (obj->term < this->currentTerm) {
                    robj->success = false;
                }
                else {
                    this->currentTerm = obj->term;
                }

                /* ======== RECEIVER IMPLEMENTATION =========
                 * 5. If leaderCommit > commitIndex, set commitIndex =
                 * min(leaderCommit, index of last new entry)
                 */
                if (obj->leaderCommit > this->commitIndex) {
                    if (obj->leaderCommit < this->raftLog->getLastLogIndex()) {
                        this->commitIndex = obj->leaderCommit;
                    }
                    else {
                        this->commitIndex = this->raftLog->getLastLogIndex();
                    }

                    /* ======= ALL SERVERS =======
                     * If commitIndex > lastApplied: increment lastApplied, apply
                     * log[lastApplied] to state machine (§5.3)
                     */
                    if (this->commitIndex > this->lastApplied) {
                        this->applyEntries(this->lastApplied, this->commitIndex);
                        this->lastApplied = this->commitIndex;
                    }
                }

                //TODO: not sure what else just for HeartBeat
                sendAppendEntriesRPCResponseHeartBeat(robj, mesg->getSrcAddr().getApn().getName());

                /* ======== CANDIDATES (§5.2) =========
                 * If AppendEntries RPC received from new leader: convert to follower
                 */
                this->setState(Follower);
                EV << "RAFT: " << DAF_RAFT_MESSAGE_M_WRITE_APPEND_ENTRIES_HEARTBEAT << " received, send response (State: -->Follower)" << endl;
            }
        }
        if (!strcmp(mesg->getName(), DAF_RAFT_MESSAGE_M_WRITE_APPEND_ENTRIES)) {
            if (check_and_cast<RAFTAppendEntryObj*>(mesg->getObjectItem().objectVal)) {
                RAFTAppendEntryObj* obj = check_and_cast<RAFTAppendEntryObj*>(mesg->getObjectItem().objectVal);
                RAFTResultObj *robj = new RAFTResultObj();
                robj->type = RAFTResultObj::Append;
                robj->term = this->currentTerm;
                robj->success = true;

                /* ======== RECEIVER IMPLEMENTATION =========
                 * 1. Reply false if term < currentTerm (§5.1)
                 */
                if (obj->term < this->currentTerm) {
                    robj->success = false;
                }
                else {
                    this->currentTerm = obj->term;
                }

                /* ======== RECEIVER IMPLEMENTATION =========
                 * 2. Reply false if log doesn’t contain an entry at prevLogIndex
                 * whose term matches prevLogTerm (§5.3)
                 */
                if (!this->raftLog->empty()) {
                    if (this->raftLog->findObj(obj->prevLogIndex)) {
                        if (this->raftLog->findObj(obj->prevLogIndex)->term != robj->term) {
                            robj->success = false;
                        }
                    }
                }

                /* ======== RECEIVER IMPLEMENTATION =========
                 * 3. If an existing entry conflicts with a new one (same index
                 * but different terms), delete the existing entry and all that
                 * follow it (§5.3)
                 * 4. Append any new entries not already in the log
                 */
                if (obj->entries) {
                    this->raftLog->appendNewEntries(obj->entries);
                }

                /* ======== RECEIVER IMPLEMENTATION =========
                 * 5. If leaderCommit > commitIndex, set commitIndex =
                 * min(leaderCommit, index of last new entry)
                 */
                if (obj->leaderCommit > this->commitIndex) {
                    if (obj->leaderCommit < this->raftLog->getLastLogIndex()) {
                        this->commitIndex = obj->leaderCommit;
                    }
                    else {
                        this->commitIndex = this->raftLog->getLastLogIndex();
                    }

                    /* ======= ALL SERVERS =======
                     * If commitIndex > lastApplied: increment lastApplied, apply
                     * log[lastApplied] to state machine (§5.3)
                     */
                    if (this->commitIndex > this->lastApplied) {
                        this->applyEntries(this->lastApplied, this->commitIndex);
                        this->lastApplied = this->commitIndex;
                    }
                }

                sendAppendEntriesRPCResponse(robj, mesg->getSrcAddr().getApn().getName());

                /* ======== CANDIDATES (§5.2) =========
                 * If AppendEntries RPC received from new leader: convert to follower
                 */
                this->setState(Follower);

                EV << "RAFT: " << DAF_RAFT_MESSAGE_M_WRITE_APPEND_ENTRIES << " received, send response (State: -->Follower)" << endl;
            }
        }

    }
    //responses
    if (dynamic_cast<CDAP_M_Write_R*>(msg)) {
        CDAP_M_Write_R *mesg = check_and_cast<CDAP_M_Write_R*>(msg);

        if (!strcmp(mesg->getName(), DAF_RAFT_MESSAGE_M_WRITE_R_REQUEST_VOTE)) {
            if (check_and_cast<RAFTResultObj*>(mesg->getObjectItem().objectVal)) {
                RAFTResultObj* obj = check_and_cast<RAFTResultObj*>(mesg->getObjectItem().objectVal);

                EV << "RAFT: " << DAF_RAFT_MESSAGE_M_WRITE_R_REQUEST_VOTE << " received, count votes (State: Candidate)" << endl;
                /* ======== CANDIDATES (§5.2) =========
                 * If votes received from majority of servers: become leader
                 */
                if (obj->voteGranted) {
                    this->votesResPos += 1;
                    //TODO: majority of servers? change this vv
                    if (this->votesResPos+1 >= this->neighbors.size() && this->state != Leader) {
                        EV << "RAFT: M_WRITE_R(RAFT_RequestVoteRPC) positive received from majority of nodes (State: Candidate-->Leader)" << endl;
                        //become leader
                        this->setState(Leader);
                        this->reinitializeLeaderNextIndex();
                        this->reinitializeLeaderMatchIndex();
                        sendHeartBeatsToAll();
                        this->startLeaderHeartBeatTimer();

                        //TODO: start doing things as leader
                    }
                }
                /* ======== ALL SERVERS =========
                 * If RPC request or response contains term T > currentTerm:
                 * set currentTerm = T, convert to follower (§5.1)
                 */
                if (obj->term > this->currentTerm) {
                    this->currentTerm = obj->term;
                    this->setState(Follower);
                    //TODO: clear all staff as follower
                }
            }
        }

        if (!strcmp(mesg->getName(), DAF_RAFT_MESSAGE_M_WRITE_R_APPEND_ENTRIES_HEARTBEAT)) {
            if (check_and_cast<RAFTResultObj*>(mesg->getObjectItem().objectVal)) {
                RAFTResultObj* obj = check_and_cast<RAFTResultObj*>(mesg->getObjectItem().objectVal);

                EV << "RAFT: " << DAF_RAFT_MESSAGE_M_WRITE_R_APPEND_ENTRIES_HEARTBEAT << " received" << endl;
                /* ======== ALL SERVERS =========
                 * If RPC request or response contains term T > currentTerm:
                 * set currentTerm = T, convert to follower (§5.1)
                 */
                if (obj->term > this->currentTerm) {
                    this->currentTerm = obj->term;
                    this->setState(Follower);
                    //TODO: clear all staff as follower
                }
            }
        }

        if (!strcmp(mesg->getName(), DAF_RAFT_MESSAGE_M_WRITE_R_APPEND_ENTRIES)) {
            if (check_and_cast<RAFTResultObj*>(mesg->getObjectItem().objectVal)) {
                RAFTResultObj* obj = check_and_cast<RAFTResultObj*>(mesg->getObjectItem().objectVal);

                /* ======== ALL SERVERS =========
                 * If RPC request or response contains term T > currentTerm:
                 * set currentTerm = T, convert to follower (§5.1)
                 */
                if (obj->term > this->currentTerm) {
                    this->currentTerm = obj->term;
                    this->setState(Follower);
                    //TODO: clear all staff as follower
                }

                EV << "RAFT: " << DAF_RAFT_MESSAGE_M_WRITE_R_APPEND_ENTRIES << " received" << endl;
                /* ======== LEADER =========
                 * If last log index ≥ nextIndex for a follower: send
                 * AppendEntries RPC with log entries starting at nextIndex
                 * • If successful: update nextIndex and matchIndex for follower (§5.3)
                 * • If AppendEntries fails because of log inconsistency:
                 *      decrement nextIndex and retry (§5.3)
                 */
                if (obj->success) {
                    this->setLogIndexValue(mesg->getSrcAddr().getApn().getName(),
                                            this->matchIndex,
                                            this->getLogIndexIndex(mesg->getSrcAddr().getApn().getName(),
                                                                    this->nextIndex));
                    this->setLogIndexValue(mesg->getSrcAddr().getApn().getName(),
                                            this->nextIndex,
                                            this->getLogIndexIndex(mesg->getSrcAddr().getApn().getName(),
                                                                    this->nextIndex)+1);
                }
                else {
                    this->setLogIndexValue(mesg->getSrcAddr().getApn().getName(),
                                            this->nextIndex,
                                            this->getLogIndexIndex(mesg->getSrcAddr().getApn().getName(),
                                                                    this->nextIndex)-1);
                    this->setLogIndexValue(mesg->getSrcAddr().getApn().getName(),
                                            this->matchIndex,
                                            this->getLogIndexIndex(mesg->getSrcAddr().getApn().getName(),
                                                                    this->nextIndex)-1);

                    AEMgmt *ae = NULL;
                    for(auto it = mgmtaes.begin(); it != mgmtaes.end(); ++it) {
                        ae = *it;
                        break;
                    }

                    if (ae) {
                        this->sendAppendEntriesRPC(ae);
                    }
                }

                /* ======== LEADER =========
                 * If there exists an N such that N > commitIndex, a majority
                 * of matchIndex[i] ≥ N, and log[N].term == currentTerm:
                 * set commitIndex = N (§5.3, §5.4)
                 */
                this->checkAndUpdateCommitIndex();
            }
        }
    }
    this->updateLogStatus();
}

void RAFT::updateLogStatus() {
    if (!nextIndex || !matchIndex) {
        return;
    }

    nextIndexStatus = TmpOut();
    for(auto it = nextIndex->begin(); it != nextIndex->end(); ++it) {
        std::ostringstream os;
        os << (*it).first << " " << (*it).second;
        nextIndexStatus.push_back(os.str());
    }

    matchIndexStatus = TmpOut();
    for(auto it = matchIndex->begin(); it != matchIndex->end(); ++it) {
        std::ostringstream os;
        os << (*it).first << " " << (*it).second;
        matchIndexStatus.push_back(os.str());
    }
}

int RAFT::getLogIndexIndex(std::string neigh, LogIndex *logIndex) {
    for(auto it = logIndex->begin(); it != logIndex->end(); ++it) {
        if ((*it).first == neigh) {
            return (*it).second;
        }
    }

    return 0;
}

void RAFT::setLogIndexValue(std::string neigh, LogIndex *logIndex, int value) {
    for(auto it = logIndex->begin(); it != logIndex->end(); ++it) {
        if ((*it).first == neigh) {
            (*it).second = value;
        }
    }
}

void RAFT::sendRequestVoteRPCResponse(RAFTResultObj *obj, std::string dstApn) {
    CDAP_M_Write_R* write = new CDAP_M_Write_R(DAF_RAFT_MESSAGE_M_WRITE_R_REQUEST_VOTE);
    EV << "RAFT: sendRequestVoteRPCResponse" << endl;

    std::ostringstream os;
    os << "RAFT_RequestVoteRPC";
    object_t raftRequestVoteRPCObj;
    raftRequestVoteRPCObj.objectClass = obj->getClassName();
    raftRequestVoteRPCObj.objectName = os.str();
    raftRequestVoteRPCObj.objectVal = obj;
    raftRequestVoteRPCObj.objectInstance = 1;
    write->setObjectItem(raftRequestVoteRPCObj);
    write->setByteLength(sizeof(raftRequestVoteRPCObj));

    AEMgmt *ae = this->getMgmtAEByDstApn(dstApn);
    write->setSrcAddr(Address(ae->getSrcNamingInfo().getApn()));
    write->setDstAddr(Address(ae->getDstNamingInfo().getApn()));

    ae->signalizeSendData(write);
}

void RAFT::sendAppendEntriesRPCResponseHeartBeat(RAFTResultObj *obj, std::string dstApn) {
    CDAP_M_Write_R* write = new CDAP_M_Write_R(DAF_RAFT_MESSAGE_M_WRITE_R_APPEND_ENTRIES_HEARTBEAT);
    EV << "RAFT: sendAppendEntriesRPCResponseHeartBeat" << endl;

    std::ostringstream os;
    os << "RAFT_AppendEntriesRPC_HeartBeat";
    object_t raftAppendEntriesRPCHeartBeatObj;
    raftAppendEntriesRPCHeartBeatObj.objectClass = obj->getClassName();
    raftAppendEntriesRPCHeartBeatObj.objectName = os.str();
    raftAppendEntriesRPCHeartBeatObj.objectVal = obj;
    raftAppendEntriesRPCHeartBeatObj.objectInstance = 1;
    write->setObjectItem(raftAppendEntriesRPCHeartBeatObj);
    write->setByteLength(sizeof(raftAppendEntriesRPCHeartBeatObj));

    AEMgmt *ae = this->getMgmtAEByDstApn(dstApn);
    write->setSrcAddr(Address(ae->getSrcNamingInfo().getApn()));
    write->setDstAddr(Address(ae->getDstNamingInfo().getApn()));

    ae->signalizeSendData(write);
}

void RAFT::sendAppendEntriesRPCResponse(RAFTResultObj *obj, std::string dstApn) {
    CDAP_M_Write_R* write = new CDAP_M_Write_R(DAF_RAFT_MESSAGE_M_WRITE_R_APPEND_ENTRIES);
    EV << "RAFT: sendAppendEntriesRPCResponse" << endl;

    std::ostringstream os;
    os << "RAFT_AppendEntriesRPC_HeartBeat";
    object_t raftAppendEntriesRPCHeartBeatObj;
    raftAppendEntriesRPCHeartBeatObj.objectClass = obj->getClassName();
    raftAppendEntriesRPCHeartBeatObj.objectName = os.str();
    raftAppendEntriesRPCHeartBeatObj.objectVal = obj;
    raftAppendEntriesRPCHeartBeatObj.objectInstance = 1;
    write->setObjectItem(raftAppendEntriesRPCHeartBeatObj);
    write->setByteLength(sizeof(raftAppendEntriesRPCHeartBeatObj));

    AEMgmt *ae = this->getMgmtAEByDstApn(dstApn);
    write->setSrcAddr(Address(ae->getSrcNamingInfo().getApn()));
    write->setDstAddr(Address(ae->getDstNamingInfo().getApn()));

    ae->signalizeSendData(write);
}

CDAPMessage* RAFT::commandReceivedFromClient(CDAPMessage* msg) {
    Enter_Method("commandReceivedFromClient()");
    /* ======== LEADER =========
     * If command received from client: append entry to local log,
     * respond after entry applied to state machine (§5.3)
     */
    if (dynamic_cast<CDAP_M_Create*>(msg) || dynamic_cast<CDAP_M_Write*>(msg)) {
        object_t* tmpObj = NULL;
        CDAPMessage* rmsg = NULL;
        RAFTLogObj *obj = NULL;


        if (this->state == Leader) {
            if (dynamic_cast<CDAP_M_Write*>(msg)) {
                CDAP_M_Write* tmpMsg = check_and_cast<CDAP_M_Write*>(msg);
                CDAP_M_Write* newTmpMsg = new CDAP_M_Write();
                newTmpMsg->setObjectItem(tmpMsg->getObjectItem());
                obj = this->raftLog->createObjLeader(newTmpMsg, this->currentTerm);
            }
            else if (dynamic_cast<CDAP_M_Create*>(msg)) {
                CDAP_M_Create* tmpMsg = check_and_cast<CDAP_M_Create*>(msg);
                CDAP_M_Create* newTmpMsg = new CDAP_M_Create();
                newTmpMsg->setObjectItem(tmpMsg->getObjectItem());
                obj = this->raftLog->createObjLeader(newTmpMsg, this->currentTerm);
            }

            tmpObj = this->raftFsm->applyEntry(obj);
            this->lastApplied += 1;

            this->sendAppendEntriesRPCsToAll();

            if (dynamic_cast<CDAP_M_Write*>(msg)) {
                rmsg = new CDAP_M_Write_R("CDAP_M_Write_R(raft)");
            }
            else {
                rmsg = new CDAP_M_Create_R("CDAP_M_Create_R(raft)");
            }
        }
        else {
            if (dynamic_cast<CDAP_M_Write*>(msg)) {
                rmsg = new CDAP_M_Write_R("CDAP_M_Write_R(raft) notLeader");
            }
            else {
                rmsg = new CDAP_M_Create_R("CDAP_M_Create_R(raft) notLeader");
            }
        }

        result_t result;
        if (tmpObj) {
            result.resultValue = 0;
        }
        else {
            result.resultValue = 1;
        }

        if (rmsg) {
            ((CDAP_M_Create_R*)rmsg)->setResult(result);
        }

        return rmsg;
    }

    return NULL;
}

void RAFT::handleMessage(cMessage *msg) {
    if (msg->isSelfMessage()) {
        if (msg == this->electionTimerSelfMessage) {
            /* ======== CANDIDATES (§5.2) =========
             * If election timeout elapses: start new election
             */
            if (this->state == Candidate) {
                EV << "RAFT: election timeout elapsed: start new election (State: Candidate-->Candidate)" << endl;
                this->resetElectionTimer();
                this->currentTerm += 1;
                this->votesResPos = 0;
                this->sendRequestVoteRPCsToAll();
            }

            /* ======== CANDIDATES (§5.2) =========
             * On conversion to candidate, start election:
             * • Increment currentTerm
             * • Vote for self
             * • Reset election timer
             * • Send RequestVote RPCs to all other servers
             */
            if (this->state == Follower) {
                EV << "RAFT: election timeout elapsed: start new selection (State: Follower-->Candidate)" << endl;
                this->setState(Candidate);
                this->currentTerm += 1;
                this->resetElectionTimer();
                this->sendRequestVoteRPCsToAll();
            }
        }

        if (msg == this->leaderHeartBeatMessage) {
            /* ======== LEADER =========
             * Upon election: send initial empty AppendEntries RPCs
             * (heartbeat) to each server; repeat during idle periods to
             * prevent election timeouts (§5.2)
             */
            if (this->state == Leader) {
                EV << "RAFT: HartBeat timer elapsed (State: Leader)" << endl;
                sendHeartBeatsToAll();
                this->startLeaderHeartBeatTimer();
            }
        }
        //raft connection mgmt flows
        if ( !opp_strcmp(msg->getName(), DAF_MSG_RAFTCON) ) {
            APNIPairs* apnip = this->mgmtAeGenerateCommands[simTime()];

            while (!apnip->empty())
            {
                APNIPair pair = apnip->front();
                this->enrollment->createFlow(&pair);
                apnip->pop_front();
            }
        }

        //raft start according to config time
        if (!opp_strcmp(msg->getName(), DAF_MSG_RAFT_START)) {
            this->nextIndex = this->initializeLog(0);
            this->matchIndex = this->initializeLog(0);
            this->startElectionTimer();
        }
    }

    delete msg;
}

void RAFT::checkAndAddIAE(AEMgmt* mgmtae) {
    std::string dstApn = mgmtae->getDstNamingInfo().getApn().getName();
    for(auto it = neighbors.begin(); it != neighbors.end(); ++it) {
        std::string str = *it;
        if (dstApn == str) {
            mgmtaes.push_back(mgmtae);
            this->myId = mgmtae->getSrcNamingInfo().getApn().getName();
            break;
        }
    }
}

AEMgmt *RAFT::getMgmtAEByDstApn(std::string dst) {
    for(auto it = mgmtaes.begin(); it != mgmtaes.end(); ++it) {
        AEMgmt* ae = *it;
        if (ae->getDstNamingInfo().getApn().getName() == dst) {
            return ae;
        }
    }

    return NULL;
}



void RAFT::parseConfig(cXMLElement* config) {
    cXMLElement* mainTag = NULL;
    if (config != NULL && config->hasChildren() && config->getFirstChildWithTag(DAF_RAFT))
        mainTag = config->getFirstChildWithTag(DAF_RAFT);
    else {
        EV << "configData parameter not initialized!" << endl;
        return;
    }

    cXMLElement* neighbors = mainTag->getFirstChildWithTag(DAF_RAFT_NEIGHBORS);
    if (neighbors) {

        if (neighbors->getAttribute(DAF_RAFT_ATTR_TIME)) {
            simtime_t cas = atof(neighbors->getAttribute(DAF_RAFT_ATTR_TIME));
            cMessage* cmsg = new cMessage(DAF_MSG_RAFT_START);
            scheduleAt(cas, cmsg);
        }

        cXMLElementList neighborList = neighbors->getChildrenByTagName(DAF_RAFT_NEIGHBOR);
        for (cXMLElementList::const_iterator it = neighborList.begin(); it != neighborList.end(); ++it) {
            cXMLElement* m = *it;

            if (!m->getAttribute(DAF_RAFT_ATTR_DST)) {
                EV << "\nSimTime tag is missing time attribute!" << endl;
                continue;
            }

            this->neighbors.push_back(m->getAttribute(DAF_RAFT_ATTR_DST));
        }
    }

    cXMLElementList enrll = mainTag->getChildrenByTagName(DAF_RAFT_SIMTIME);
    for (cXMLElementList::const_iterator it = enrll.begin(); it != enrll.end(); ++it) {
        cXMLElement* m = *it;

        if (!m->getAttribute(DAF_RAFT_ATTR_TIME)) {
            EV << "\nSimTime tag is missing time attribute!" << endl;
            continue;
        }

        simtime_t cas = atof(m->getAttribute(DAF_RAFT_ATTR_TIME));

        if (m->getFirstChildWithTag(DAF_RAFT_CONNECT)) {
            this->mgmtAeGenerateCommands[cas] = new APNIPairs();
            cMessage* cmsg = new cMessage(DAF_MSG_RAFTCON);
            scheduleAt(cas, cmsg);
        }


        cXMLElementList coms = m->getChildren();
        for (cXMLElementList::const_iterator jt = coms.begin(); jt != coms.end(); ++jt) {
            cXMLElement* n = *jt;

            if ( !( strcmp(n->getTagName(), DAF_RAFT_CONNECT) )
                    && !(n->getAttribute(DAF_RAFT_ATTR_SRC))
                    && !(n->getAttribute(DAF_RAFT_ATTR_SRC_INST))
                    && !(n->getAttribute(DAF_RAFT_ATTR_DST))
                    && !(n->getAttribute(DAF_RAFT_ATTR_DST_INST))
               ) {
                EV << "\nError when parsing Connect/Release record" << endl;
                continue;
            }

            APNIPair apn = APNIPair();
            if ( !strcmp(n->getTagName(), DAF_RAFT_CONNECT) ) {
                std::string ap1 = n->getAttribute(DAF_RAFT_ATTR_SRC);
                std::string ap2 = n->getAttribute(DAF_RAFT_ATTR_DST);
                APNIPair apn = APNIPair(APNamingInfo(APN(ap1)), APNamingInfo(APN(ap2)));
                std::string api1 = n->getAttribute(DAF_RAFT_ATTR_SRC_INST);
                std::string api2 = n->getAttribute(DAF_RAFT_ATTR_DST_INST);
                apn.first.setApinstance(api1);
                apn.second.setApinstance(api2);

                this->mgmtAeGenerateCommands[cas]->push_back(apn);
                //EV << "!!!!!!!!!!!!!" << PreenrollConnects[cas]->size() << endl;
            }
        }
    }
}

void RAFT::updateDisplayString() {
    std::ostringstream os;
    os << "state: ";
    if (this->state == Follower) {
        os << "Follower" << endl;
    }
    else if (this->state == Candidate) {
        os << "Candidate" << endl;
    }
    else if (this->state == Leader) {
        os << "Leader" << endl;
    }
    setPolicyDisplayString(this, os.str().c_str());
}


