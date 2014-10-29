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
    EV << "CreateFlowPositive initiated by " << src->getFullPath() << " and processed by " << fa->getFullPath() << endl;
    Flow* flow = dynamic_cast<Flow*>(obj);
    if (flow) {
        EV << "-----\n" << flow->info() << endl;
        FAITableEntry* entry = fa->getFaiTable()->findEntryByDstNeighborAndFwd(flow->getDstApni().getApn());
        if (fa->getMyAddress().getApname() == flow->getSrcApni().getApn()
            && entry )

            fa->receiveCreateFlowPositive(entry->getFlow());
        else
            EV << "Flow not in my FaiTable" << endl;
    }
    else
        EV << "Received not a flow object!" << endl;
}

void LisFACreRes::receiveSignal(cComponent* src, simsignal_t id, cObject* obj) {
    EV << "CreateFlowResponsePositive initiated by " << src->getFullPath()
       << " and processed by " << fa->getFullPath() << endl;
    Flow* flow = dynamic_cast<Flow*>(obj);
    if (flow) {
        FAITableEntry* entry = fa->getFaiTable()->findEntryByApns(flow->getSrcApni().getApn(), flow->getDstApni().getApn());
        if ( entry )
            fa->receiveCreateResponseFlowPositiveFromRibd(flow);
        else
            EV << "Flow not in FaiTable" << endl;
    }
    else
        EV << "Received not a flow object!" << endl;
}
/*
void LisFAAllocResNega::receiveSignal(cComponent* src, simsignal_t id,
        cObject* obj) {
    EV << "AllocateResponseNegative initiated by " << src->getFullPath() << " and processed by " << fa->getFullPath() << endl;
    Flow* flow = dynamic_cast<Flow*>(obj);
    if (flow) {
        //Pass request to FA that has this Flow in its Flow table
        if (fa->getFaiTable()->findEntryByFlow(flow))
            fa->receiveAllocateResponseNegative(flow);
        else
            EV << "Flow not in FaiTable" << endl;
    }
    else
        EV << "Received not a flow object!" << endl;
}
*/
