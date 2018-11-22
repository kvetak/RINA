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

#ifndef DAF_RIB_RAFT_RAFTRESULTOBJ_H_
#define DAF_RIB_RAFT_RAFTRESULTOBJ_H_

#include <omnetpp.h>

class RAFTResultObj : public cObject {
public:
    enum Type {Vote, Append};
    RAFTResultObj();
    virtual ~RAFTResultObj();

    unsigned int term;
    bool voteGranted;

    bool success;

    Type type;

};

#endif /* DAF_RIB_RAFT_RAFTRESULTOBJ_H_ */
