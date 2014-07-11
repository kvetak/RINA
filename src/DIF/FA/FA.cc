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
    // TODO Auto-generated constructor stub

}

FA::~FA() {
    // TODO Auto-generated destructor stub
}

void FA::initialize() {

}

void FA::receiveAllocateRequest(Flow *fl) {
    EV << this->getFullPath() << " received AllocateRequest" << endl;
    //Is malformed?

    //Insert pending Allocation
//    std::string state;
//    state.assign("pending");
//    AllocationTable.insert(TFlowStrPair(fl, state));
    //Create FAI
    this->createFAI();
}

void FA::processCreateFlowRequest() {
    ;
}

void FA::processDeallocateRequest() {
    ;
}

bool FA::invokeNewFlowRequestPolicy() {
    //Is flow policy acceptable

    return true;
}

bool FA::createFAI() {
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

    return true;
}


void FA::handleMessage(cMessage *msg) {

    //Rcv Allocate_Request

    //Rcv M_Create(Flow)

    //Rcv Deallocate_Request
}
