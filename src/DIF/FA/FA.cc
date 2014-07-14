//
// Copyright © 2014 PRISTINE Consortium (http://ict-pristine.eu)
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
/**
 * @file FA.cpp
 * @author Marcel Marek (imarek@fit.vutbr.cz)
 * @date Apr 29, 2014
 * @brief
 * @detail
 */
#include "FA.h"

Define_Module(FA);

FA::FA() {
    this->FaiTable = NULL;

}

FA::~FA() {
    this->FaiTable = NULL;
}

void FA::initialize() {
    this->FaiTable = dynamic_cast<FAITable*>( getParentModule()->getSubmodule("faiTable") );
}

void FA::receiveAllocateRequest(cObject* obj) {
    Flow* fl = dynamic_cast<Flow*>(obj);
    Enter_Method_Silent();
    EV << this->getFullPath() << " received AllocateRequest" << endl;
    //Is malformed?

    //Create FAI
    FAI* fai = this->createFAI(fl);
    //Insert to FAITable
    FAITableEntry* fte = new FAITableEntry(fai);
    FaiTable->insert(*fte);
    //Pass the AllocationRequest to newly created FAI
    fai->processAllocateRequest();
}

void FA::processCreateFlowRequest() {
    ;
}

void FA::processDeallocateRequest() {
    ;
}

bool FA::invokeNewFlowRequestPolicy(Flow* fl) {
    //Is flow policy acceptable
    //TODO: Vesely - Simulate wrong Flow
    if ( strcmp(fl->getSrcApni().getApn().getName().c_str(), "AppH2") )
        return false;
    return true;
}

FAI* FA::createFAI(Flow* fl) {
    // find factory object
    cModuleType *moduleType = cModuleType::get("rina.DIF.FA.FAI");

    // create (possibly compound) module and build its submodules (if any)
    int portId = ev.getRNG(RANDOM_NUMBER_GENERATOR)->intRand(MAX_PORTID);
    int cepId = ev.getRNG(RANDOM_NUMBER_GENERATOR)->intRand(MAX_CEPID);

    std::ostringstream ostr;
    ostr << "fai_" << portId << "_" << cepId;

    cModule *module = moduleType->create(ostr.str().c_str(), this->getParentModule());
    module->par("portId") = portId;
    module->par("cepId") = cepId;
    module->finalizeParameters();
    module->buildInside();

    // create activation message
    module->scheduleStart(simTime());
    module->callInitialize();

    FAI* fai = dynamic_cast<FAI*>(module);
    fai->postInitialize(this, fl);
    return fai;
}


void FA::handleMessage(cMessage *msg) {

    //Rcv Allocate_Request

    //Rcv M_Create(Flow)

    //Rcv Deallocate_Request
}
