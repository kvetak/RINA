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

#ifndef DAF_RIB_RAFT_RAFTREQUESTVOTEOBJ_H_
#define DAF_RIB_RAFT_RAFTREQUESTVOTEOBJ_H_

#include <omnetpp.h>

class RAFTRequestVoteObj : public cObject {
public:
    RAFTRequestVoteObj(unsigned int term, std::string candidateId,
            unsigned int lastLogIndex, unsigned int lastLogTerm);
    virtual ~RAFTRequestVoteObj();

    unsigned int term;
    std::string candidateId;
    unsigned int lastLogIndex;
    unsigned int lastLogTerm;
};

#endif /* DAF_RIB_RAFT_RAFTREQUESTVOTEOBJ_H_ */
