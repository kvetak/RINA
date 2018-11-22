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

#ifndef DAF_RIB_RAFT_RAFTLOGOBJ_H_
#define DAF_RIB_RAFT_RAFTLOGOBJ_H_

#include <string>
#include <omnetpp.h>
#include "DAF/CDAP/CDAPMessage_m.h"

class RAFTLogObj {
public:
    RAFTLogObj(unsigned int term, unsigned int index,
            CDAPMessage *entry);
    virtual ~RAFTLogObj();

    std::string info() const;

    unsigned int term;
    unsigned int index;
    CDAPMessage *entry;

};

//Free function
std::ostream& operator<< (std::ostream& os, const RAFTLogObj& obj);

#endif /* DAF_RIB_RAFT_RAFTLOGOBJ_H_ */
