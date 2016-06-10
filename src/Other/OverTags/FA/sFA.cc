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

#include "sFA.h"

Define_Module(sFA);


void sFA::initialize() {
    initPointers();
    initSignalsAndListeners();

    signalToAgent = this->getParentModule()->getParentModule()->registerSignal("agentRequest");

    //Setup MyAddress
    initMyAddress();
}

bool sFA::receiveAllocateRequest(Flow* flow) {
    Enter_Method("receiveAllocateRequest()");
    EV << this->getFullPath() << " received AllocateRequest" << endl;


    //Insert new Flow into FAITable
    N_flowTable->insertNew(flow);

    //Change allocation status to pending
    N_flowTable->changeAllocStatus(flow, NFlowTableEntry::ALLOC_PEND);

    //Add source and destination address in case of data flow
    if (flow->getSrcAddr() == Address::UNSPECIFIED_ADDRESS
        && flow->getSrcNeighbor() == Address::UNSPECIFIED_ADDRESS) {
        setOriginalAddresses(flow);
        setNeighborAddresses(flow);
        //XXX: Vesely - Dirty! Needs refactoring...
        flow->setSrcNeighbor(flow->getSrcAddr());
    }

    //Are both Apps local? YES then Degenerate transfer
    if ( DifAllocator->isAppLocal( flow->getDstApni().getApn() ) ) {
        flow->setDdtFlag(true);
    }

    //Check whether local IPCP is enrolled into DIF
    //Successful enrollment implies existence of N-1 mgmt-flow, if not then
    //FA needs to init allocation of N-1 mgmt-flow
    if (!flow->isDdtFlag() && !Enrollment->isEnrolled(MyAddress.getApn())) {
        EV << "IPCP not enrolled to DIF, thus executing enrollment!" << endl;
        receiveMgmtAllocateRequest(APNamingInfo(MyAddress.getApn()), APNamingInfo(flow->getDstNeighbor().getApn()));
    }

    //Is malformed?
    if (isMalformedFlow(flow)){
        N_flowTable->changeAllocStatus(flow, NFlowTableEntry::ALLOC_ERR);
        //TODO: Vesely - What about special signal for errors????
        //this->signalizeAllocateResponseNegative(fl);
        return false;
    }


    //Create FAI
    FAI* fai = this->createFAI(flow);
    fai->setDegenerateDataTransfer(flow->isDdtFlag());

    //Update flow object
    flow->setSrcPortId(fai->getLocalPortId());
    flow->getConnectionId().setSrcCepId(fai->getLocalCepId());

    emit(signalToAgent, fai);
    //Postpone allocation request until management flow is ready
    bool status = false;

    /*
    if ( flow->isDdtFlag() || Enrollment->isEnrolled(MyAddress.getApn())
       ){
        status = fai->receiveAllocateRequest();
    }
    else
    {
        status = true;
        EV << "Management flow is not ready!" << endl;
    }
     */
    //Potentially wait for response from RA, after this continue with X

    return status;
}
