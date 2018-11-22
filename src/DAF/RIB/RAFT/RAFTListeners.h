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

#ifndef DAF_RIB_RAFT_RAFTLISTENERS_H_
#define DAF_RIB_RAFT_RAFTLISTENERS_H_

#include "DAF/RIB/RAFT/RAFT.h"

class RAFT;
class RAFTListeners : public cListener {
public:
    RAFTListeners(RAFT* raft);
    virtual ~RAFTListeners();
    virtual void receiveSignal(cComponent *src, simsignal_t id,  cObject *obj, cObject* detail) {
               EV << "Signal to RAFTListener initiated by " << src->getFullPath() << endl;
        }
protected:
    RAFT* raft;
};


class LisRAFTNewMgmtAe : public RAFTListeners {
public:
    LisRAFTNewMgmtAe(RAFT* raft): RAFTListeners(raft){};
    virtual void receiveSignal(cComponent *src, simsignal_t id,  cObject *obj, cObject* detail);
};

#endif /* DAF_RIB_RAFT_RAFTLISTENERS_H_ */
