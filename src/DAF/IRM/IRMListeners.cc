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

#include "IRM.h"
#include "IRMListeners.h"

IRMListeners::IRMListeners(IRM* nirm) {
    this->irm = nirm;
}

IRMListeners::~IRMListeners() {

}

void LisIRMAllocResNegaFa::receiveSignal(cComponent* src, simsignal_t id,
        cObject* obj) {
    EV << "AllocationResponseNegative{fromFA} initiated by " << src->getFullPath() << " and processed by " << irm->getFullPath() << endl;
    this->irm->receiveAllocationResponseNegative(obj);
}

void LisIRMAllocReqFai::receiveSignal(cComponent* src, simsignal_t id,
        cObject* obj) {
    EV << "AllocationRequest{fromFAI} initiated by " << src->getFullPath() << " and processed by " << irm->getFullPath() << endl;
    this->irm->receiveAllocationRequestFromFAI(obj);
}

void LisIRMAllocResNegaFai::receiveSignal(cComponent* src, simsignal_t id,
        cObject* obj) {
    EV << "AllocationResponseNegative{fromFAI} initiated by " << src->getFullPath() << " and processed by " << irm->getFullPath() << endl;
    this->irm->receiveAllocationResponseNegative(obj);
}

void LisIRMAllocReq::receiveSignal(cComponent* src, simsignal_t id,
        cObject* obj) {
    EV << "AllocationRequest initiated by " << src->getFullPath() << " and processed by " << irm->getFullPath() << endl;
    irm->receiveAllocationRequest(obj);
}

void LisIRMAllocResNegaAppNotFound::receiveSignal(cComponent* src,
        simsignal_t id, cObject* obj) {
    EV << "AllocationResponseNegative{AppNotFound} initiated by " << src->getFullPath() << " and processed by " << irm->getFullPath() << endl;
}

void LisIRMDeallocReq::receiveSignal(cComponent* src, simsignal_t id,
        cObject* obj) {
    EV << "AllocationRequest initiated by " << src->getFullPath() << " and processed by " << irm->getFullPath() << endl;
    irm->receiveDeallocationRequest(obj);
}
