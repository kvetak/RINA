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

#include "AE.h"

Define_Module(AE);

AE::AE() {
}

AE::~AE() {
}

void AE::initSignalsAndListeners() {
    cModule* catcher = this->getParentModule()->getParentModule();

    //Signals that this module is emitting
    sigAEAllocReq      = registerSignal(SIG_AE_AllocateRequest);
    sigAEDeallocReq    = registerSignal(SIG_AE_DeallocateRequest);

    //Signals that this module is processing

}

void AE::initNamingInfo() {
    //Source info
    srcApName = this->getParentModule()->par("apName").str();
    srcApInstance = this->getParentModule()->par("apInstance").str();
    srcAeName = this->par("aeName").str();
    srcAeInstance = this->par("aeInstance").str();
}

void AE::signalizeAllocateRequest() {
    emit(sigAEAllocReq, flow);
}

void AE::initialize() {
    initNamingInfo();
    initSignalsAndListeners();
}

void AE::handleMessage(cMessage* msg) {
}

void AE::signalizeDeallocateRequest() {
    emit(sigAEDeallocReq, flow);
}


