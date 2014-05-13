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
 * @file FlowAllocator.cpp
 * @author Marcel Marek (imarek@fit.vutbr.cz)
 * @date Apr 29, 2014
 * @brief
 * @detail
 */

#include <FlowAllocator.h>

FlowAllocator::FlowAllocator() {
    // TODO Auto-generated constructor stub

}

FlowAllocator::~FlowAllocator() {
    // TODO Auto-generated destructor stub
}

bool FlowAllocator::invokeNewFlowRequestPolicy(){
    return false;
}


bool FlowAllocator::allocateRequest(Flow fl) {

    //Is malformed?
    //if (fl == NULL)
    //    return false;

    //Create FAI

    return true;
}

void FlowAllocator::processAllocateRequest() {
    ;
}

void FlowAllocator::processCreateFlowRequest() {
    ;
}

void FlowAllocator::processDeallocateRequest() {
    ;
}

void FlowAllocator::initialize() {
    //Register signals
    sigCreateRequestFlow = registerSignal("CreateRequest");
    sigCreateResponseFlow = registerSignal("CreateResponse");
    sigDeleteRequestFlow = registerSignal("DeleteRequest");
    sigDeleteResponseFlow = registerSignal("DeleteResponse");
}

void FlowAllocator::handleMessage(cMessage *msg) {
    //Rcv Allocate_Request

    //Rcv M_Create(Flow)

    //Rcv Deallocate_Request
}
