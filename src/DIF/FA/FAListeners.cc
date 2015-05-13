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

#include "FAListeners.h"

void LisFAAllocReq::receiveSignal(cComponent* src, simsignal_t id, cObject* obj) {
    EV << "AllocateRequest initiated by " << src->getFullPath()
       << " and processed by " << fa->getFullPath() << endl;
    Flow* flow = dynamic_cast<Flow*>(obj);
    if (flow) {
        fa->receiveAllocateRequest(flow);
    }
    else
        EV << "FAListener received not a flow object!" << endl;
}

void LisFADeallocReq::receiveSignal(cComponent* src, simsignal_t id,
        cObject* obj) {
    EV << "DeallocateRequest initiated by " << src->getFullPath()
       << " and processed by " << fa->getFullPath() << endl;
    Flow* flow = dynamic_cast<Flow*>(obj);
    if (flow) {
        fa->receiveDeallocateRequest(flow);
    }
    else
        EV << "FAListener received not a flow object!" << endl;
}

/**
 *
 * @param src
 * @param id
 * @param obj
 */
void LisFACreReq::receiveSignal(cComponent* src, simsignal_t id, cObject* obj) {
    EV << "CreateRequest initiated by " << src->getFullPath() << " and processed by " << fa->getFullPath() << endl;
    Flow* flow = dynamic_cast<Flow*>(obj);
    if (flow)
        fa->receiveCreateFlowRequestFromRibd(flow);
    else
        EV << "Received not a flow object!" << endl;
    return;
}


void LisFACreFloPosi::receiveSignal(cComponent* src, simsignal_t id,
        cObject* obj) {
    EV << "NM1FlowCreated initiated by " << src->getFullPath() << " and processed by " << fa->getFullPath() << endl;
    Flow* flow = dynamic_cast<Flow*>(obj);
    if (flow
            && fa->getMyAddress().getApname() == flow->getSrcApni().getApn()
            && flow->getConId().getQoSId() != VAL_MGMTQOSCUBE) {
        //EV << "-----\n" << flow->info() << endl;
        TFAIPtrs entries = fa->getFaiTable()->findEntryByDstNeighborAndFwd(flow->getDstApni().getApn());
        for (TFTPtrsIter it = entries.begin(); it != entries.end(); ++it) {
            fa->receiveNM1FlowCreated( (*it)->getFlow() );
        }
    }
    else {
        if (!flow) { EV << "Received not a flow object!" << endl; }
        else if (flow->getConId().getQoSId() == VAL_MGMTQOSCUBE) { EV << "Management flow allocated!" << endl; }
        else { EV << "Flow not intended for my FA!" << endl; }
    }
}

