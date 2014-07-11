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
 * @file FAI.cc
 * @author Vladimir Vesely (ivesely@fit.vutbr.cz)
 * @date Apr 30, 2014
 * @brief
 * @detail
 */
#include <FAI.h>

Define_Module(FAI);

FAI::FAI() {
    // TODO Auto-generated destructor stub
}

FAI::~FAI() {
    // TODO Auto-generated destructor stub
}

void FAI::initialize() {
    this->portId = par("portId");
    this->cepId  = par("cepId");
}

void FAI::processAllocateRequest() {
}

void FAI::processDegenerateDataTransfer() {
}

void FAI::processAllocateResponse() {
}

void FAI::processCreateRequest() {
}

void FAI::processCreateResponse() {
}

void FAI::processDeallocateRequest() {
}

void FAI::processDeleteRequest() {
}

void FAI::processDeleteResponse() {
}

void FAI::handleMessage(cMessage *msg) {
    //Rcv Allocate_Request

    //Rcv Allocate_Response

    //Receive M_Create(Flow)

    //Receive M_Create_R(Flow)

    //Receive Deallocate_Request

    //Receive M_Delete(Flow)

    //Receive M_Delete_R(Flow)

}

std::string FAI::info() const {
    std::stringstream os;
    os << "FAI: port: " << this->portId << "cep:" << this->cepId<< endl;
    return os.str();
}

//Free function
std::ostream& operator<< (std::ostream& os, const FAI& fai) {
    return os << fai.info();
}
