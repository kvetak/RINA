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

#include <RAFTLog.h>


Define_Module(RAFTLog);

void RAFTLog::initialize() {
    this->raftLog = new RaftLog();
    WATCH_LIST((*raftLog));
}

void RAFTLog::handleMessage(cMessage *msg) {

}

bool RAFTLog::empty() {
    return this->raftLog->empty();
}


RAFTLogObj *RAFTLog::createObjLeader(CDAPMessage *entry, unsigned int term) {
    unsigned int index = 1;

    if (!this->raftLog->empty()) {
        index = this->raftLog->back().index + 1;
    }

    RAFTLogObj* tmpObj = new RAFTLogObj(term, index, entry);

    this->raftLog->push_back(*tmpObj);

    return tmpObj;
}

//delete including index
int RAFTLog::deleteFromIndex(unsigned int index) {
    int num = this->raftLog->size() - index;

    for (int i = 0; i < num; i++) {
        this->raftLog->pop_back();
    }

    return 0;
}

int RAFTLog::getLastLogIndex() {
    if (raftLog->empty()) {
        return 0;
    }
    else {
        return raftLog->back().index;
    }
}

int RAFTLog::getLastLogTerm() {
    if (raftLog->empty()) {
        return 0;
    }
    else {
        return raftLog->back().term;
    }
}

/*
 * return new logs to be sent from the next index of each node
 */
RaftLog *RAFTLog::getLogsToBeSent(unsigned int index) {
    if (raftLog->back().index < index) {
        return NULL;
    }

    RaftLog *tmpLog = new RaftLog();

    for (auto it = raftLog->begin(); it != this->raftLog->end(); ++it) {
        RAFTLogObj obj = *it;

        if (obj.index < index) {
            continue;
        }

        RAFTLogObj tmpObj = RAFTLogObj(obj.term, obj.index, obj.entry);
        tmpLog->push_back(tmpObj);
    }

    return tmpLog;
}

/*
 * append received entries, solves conflicts etc.
 */
int RAFTLog::appendNewEntries(RaftLog *raftLog) {
    RAFTLogObj remoteFirst = *raftLog->begin();
    int tmpIndexParamLog = 0;
    int clCnt = 0;
    int ret = 0;

    if (this->raftLog->empty()) {
        this->appendLogFromIndex(raftLog, 1);
        return 0;
    }

    RAFTLogObj localLast = this->raftLog->back();

    if (localLast.index < remoteFirst.index) {
        this->appendLogFromIndex(raftLog, 1);
    }
    else {
        ret = this->checkConflict(raftLog, &clCnt, &tmpIndexParamLog);

        if (ret < 0) {
            this->deleteFromIndex(clCnt);
            this->appendLogFromIndex(raftLog, tmpIndexParamLog);
        }
        else {
            this->appendLogFromIndex(raftLog, tmpIndexParamLog);
        }
    }

    return 0;
}

/*
 * check for conflicts in terms on index, if there is conflict, it returns -1
 * if not it returns 0
 * @param clCnt - stores the last index of the same element in class raftLog
 * @param indexParamLog - stores the last index of the same element in param raftLog
 */
int RAFTLog::checkConflict(RaftLog *raftLog, int *clCnt, int *indexParamLog) {
    auto it = this->raftLog->begin();
    clCnt = 0;
    indexParamLog = 0;
    auto tmpIt = raftLog->begin();

    while (it != this->raftLog->end()) {
        if ((*it).index == raftLog->begin()->index) {
            break;
        }

        clCnt++;
        it++;
    }

    while (it != this->raftLog->end() && tmpIt != raftLog->end()) {
        if ((*it).term != (*tmpIt).term) {
            return -1;
        }

        indexParamLog++;
        clCnt++;
        it++;
        tmpIt++;
    }

    return 0;
}

int RAFTLog::appendLogFromIndex(RaftLog *raftLog, int index) {
    int tmpIndexCounter = 1;

    for (auto it = raftLog->begin(); it != raftLog->end(); ++it, tmpIndexCounter++) {
        if (tmpIndexCounter >= index) {

            RAFTLogObj tmpObj = (*it);

            if (dynamic_cast<CDAP_M_Create*>(tmpObj.entry)) {
                CDAP_M_Create* tmpMsg = check_and_cast<CDAP_M_Create*>(tmpObj.entry);
                CDAP_M_Create* newTmpMsg = new CDAP_M_Create();
                newTmpMsg->setObjectItem(tmpMsg->getObjectItem());

                RAFTLogObj tmpObj = RAFTLogObj((*it).term, (*it).index, newTmpMsg);
                this->raftLog->push_back(*it);
            }
            else if (dynamic_cast<CDAP_M_Write*>(tmpObj.entry)) {
                CDAP_M_Write* tmpMsg = check_and_cast<CDAP_M_Write*>(tmpObj.entry);
                CDAP_M_Write* newTmpMsg = new CDAP_M_Write();
                newTmpMsg->setObjectItem(tmpMsg->getObjectItem());

                RAFTLogObj tmpObj = RAFTLogObj((*it).term, (*it).index, newTmpMsg);
                this->raftLog->push_back(*it);
            }
        }
    }

    return 0;
}

int RAFTLog::matchIndexTerm(unsigned int index, unsigned int term) {
    RAFTLogObj *obj = this->findObj(index);

    if (obj == NULL) {
        return -2;
    }

    if (obj->term != term) {
        return -1;
    }

    return 0;
}

RAFTLogObj *RAFTLog::findObj(unsigned int index) {
    for(auto it = this->raftLog->begin(); it != this->raftLog->end(); ++it) {
        RAFTLogObj *obj = &(*it);
        if (obj->index == index) {
            return obj;
        }
    }

    return NULL;
}

