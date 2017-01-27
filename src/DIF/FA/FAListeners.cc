// The MIT License (MIT)
//
// Copyright (c) 2014-2016 Brno University of Technology, PRISTINE project
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.

#include "DIF/FA/FAListeners.h"

void LisFAAllocReq::receiveSignal(cComponent* src, simsignal_t id, cObject* obj, cObject *detail) {
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
        cObject* obj, cObject *detail) {
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
void LisFACreReq::receiveSignal(cComponent* src, simsignal_t id, cObject* obj, cObject *detail) {
    EV << "CreateRequest initiated by " << src->getFullPath() << " and processed by " << fa->getFullPath() << endl;
    Flow* flow = dynamic_cast<Flow*>(obj);
    if (flow)
        fa->receiveCreateFlowRequestFromRibd(flow);
    else
        EV << "Received not a flow object!" << endl;
    return;
}


void LisFACreFloPosi::receiveSignal(cComponent* src, simsignal_t id,
        cObject* obj, cObject *detail) {
    EV << "NM1FlowCreated initiated by " << src->getFullPath() << " and processed by " << fa->getFullPath() << endl;
    Flow* flow = dynamic_cast<Flow*>(obj);
    if (flow
        && fa->getMyAddress().getApn() == flow->getSrcApni().getApn()
        && !flow->isManagementFlowLocalToIPCP() )
    {
        //EV << "-----\n" << flow->info() << endl;
        TFAIPtrs entries = fa->getNFlowTable()->findEntriesByDstNeighborAndFwd(flow->getDstApni().getApn());
        for (TFTPtrsIter it = entries.begin(); it != entries.end(); ++it) {
            fa->receiveNM1FlowCreated( (*it)->getFlow() );
        }
    }
    else {
        if (!flow) { EV << "Received not a flow object!" << endl; }
        else if (!flow->getConId().getQoSId().compare(VAL_MGMTQOSID)) { EV << "Management flow allocated!" << endl; }
        else { EV << "Flow not intended for my FA!" << endl; }
    }
}

void LisFAAllocFinMgmt::receiveSignal(cComponent* src, simsignal_t id,
        cObject* obj, cObject *detail) {
    EV << "AllocFinMgmt initiated by " << src->getFullPath() << " and processed by " << fa->getFullPath() << endl;

    /*
    Flow* flow = dynamic_cast<Flow*>(obj);
    EV << flow->info() << endl;
    if (flow
        && fa->getMyAddress().getApname() == flow->getSrcApni().getApn()
        && flow->isManagementFlow())
    {
        //Notify pending flows that mgmt flow is prepared
        TFAIPtrs entries = fa->getNFlowTable()->findEntriesAffectedByMgmt(flow);
        for (TFTPtrsIter it = entries.begin(); it != entries.end(); ++it) {
            fa->PendingFlows.push_back((*it)->getFlow());
        }
        fa->receiveMgmtAllocateFinish();
    }
    else {
        if (!flow) { EV << "Received not a flow object!" << endl; }
        else if (!flow->getConId().getQoSId().compare(VAL_MGMTQOSID)) { EV << "Management flow allocated!" << endl; }
        else { EV << "Flow not intended for my FA!" << endl; }
    }
    */
    APNIPair* apnip = dynamic_cast<APNIPair*>(obj);
    //EV << "!!!!!" << apnip->info() << endl;
    if (apnip && fa->getMyAddress().getApn() == apnip->first.getApn()) {
        //EV << "!!!!!Uvnitr" << endl;
        //Notify pending flows that mgmt flow is prepared
        TFAIPtrs entries = fa->getNFlowTable()->findEntriesAffectedByMgmt(apnip);
        for (TFTPtrsIter it = entries.begin(); it != entries.end(); ++it) {
            fa->PendingFlows.push_back((*it)->getFlow());
        }
        //EV << "!!!!!Venku" << endl;
        fa->receiveMgmtAllocateFinish();
    }
    else {
        EV << "FA received unknown object!" << endl;
    }



}
