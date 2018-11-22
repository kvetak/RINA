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

#include <RAFTListeners.h>

RAFTListeners::RAFTListeners(RAFT* raft): raft(raft) {

}

RAFTListeners::~RAFTListeners() {
    raft = NULL;
}


void LisRAFTNewMgmtAe::receiveSignal(cComponent* src, simsignal_t id,
        cObject* obj, cObject* detail) {
    EV << "RAFTNewMgmtAe initiated by " << src->getFullPath() << " and processed by " << raft->getFullPath() << endl;

    AEMgmt* mgmtae = dynamic_cast<AEMgmt*>(obj);
    if (mgmtae){
        raft->checkAndAddIAE(mgmtae);
    }
    else {
        EV << "LisRAFTNewMgmtAe received unknown object!" << endl;
    }

}

