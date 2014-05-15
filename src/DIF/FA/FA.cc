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

#include <FA.h>

Define_Module(FA);

FA::FA() {
    // TODO Auto-generated constructor stub

}

FA::~FA() {
    // TODO Auto-generated destructor stub
}

bool FA::invokeNewFlowRequestPolicy(){
    return false;
}


bool FA::allocateRequest(Flow fl) {

    //Is malformed?
    //if (fl == NULL)
    //    return false;

    //Create FAI

    return true;
}

void FA::processAllocateRequest() {
    ;
}

void FA::processCreateFlowRequest() {
    ;
}

void FA::processDeallocateRequest() {
    ;
}

void FA::initialize() {
    //Register signals
    sigCreateRequestFlow = registerSignal("CreateRequest");
    sigCreateResponseFlow = registerSignal("CreateResponse");
    sigDeleteRequestFlow = registerSignal("DeleteRequest");
    sigDeleteResponseFlow = registerSignal("DeleteResponse");
}

void FA::handleMessage(cMessage *msg) {
    //Rcv Allocate_Request

    //Rcv M_Create(Flow)

    //Rcv Deallocate_Request
}
