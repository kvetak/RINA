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

#include "DIF/FA/FANotifierListeners.h"

FANotifierListeners::FANotifierListeners(FANotifierBase* nfanb) : fanb(nfanb)
{
}

FANotifierListeners::~FANotifierListeners() {
    fanb = NULL;
}

void LisRIBDCreReq::receiveSignal(cComponent* src, simsignal_t id, cObject* obj, cObject *detail) {
    EV << "CreateRequest initiated by " << src->getFullPath()
       << " and processed by " << fanb->getFullPath() << endl;
    Flow* flow = dynamic_cast<Flow*>(obj);
    if (flow)
        fanb->sendCreateRequestFlow(flow);
    else
        EV << "RIBdListener received unknown object!" << endl;
}

void LisRIBDAllReqFromFai::receiveSignal(cComponent* src, simsignal_t id,
        cObject* obj, cObject *detail) {
    EV << "AllocationRequest{fromFAI} initiated by " << src->getFullPath()
       << " and processed by " << fanb->getFullPath() << endl;
    Flow* flow = dynamic_cast<Flow*>(obj);
    if (flow) {
        //Check whether dstApp is local...
        const APN dstApn = flow->getSrcApni().getApn();
        if (fanb->getMyAddress().getApn() == dstApn) {
            fanb->receiveAllocationRequestFromFai(flow);
        }
    }
    else
        EV << "RIBdListener received unknown object!" << endl;

}

void LisRIBDCreResNega::receiveSignal(cComponent* src, simsignal_t id,
        cObject* obj, cObject *detail) {
    EV << "CreateResponseFlowNegative initiated by " << src->getFullPath()
       << " and processed by " << fanb->getFullPath() << endl;
    Flow* flow = dynamic_cast<Flow*>(obj);
    if (flow)
        fanb->sendCreateResponseNegative(flow);
    else
        EV << "RIBdListener received unknown object!" << endl;
}

void LisRIBDCreResPosi::receiveSignal(cComponent* src, simsignal_t id,
        cObject* obj, cObject *detail) {
    EV << "CreateResponseFlowPositive initiated by " << src->getFullPath()
       << " and processed by " << fanb->getFullPath() << endl;
    Flow* flow = dynamic_cast<Flow*>(obj);
    if (flow)
        fanb->sendCreateResponsePostive(flow);
    else
        EV << "RIBdListener received unknown object!" << endl;
}

void LisRIBDDelReq::receiveSignal(cComponent* src, simsignal_t id,
        cObject* obj, cObject *detail) {
    EV << "DeleteRequest initiated by " << src->getFullPath()
       << " and processed by " << fanb->getFullPath() << endl;
    Flow* flow = dynamic_cast<Flow*>(obj);
    if (flow)
        fanb->sendDeleteRequestFlow(flow);
    else
        EV << "RIBdListener received unknown object!" << endl;
}

void LisRIBDDelRes::receiveSignal(cComponent* src, simsignal_t id,
        cObject* obj, cObject *detail) {
    EV << "DeleteResponse initiated by " << src->getFullPath()
       << " and processed by " << fanb->getFullPath() << endl;
    Flow* flow = dynamic_cast<Flow*>(obj);
    if (flow)
        fanb->sendDeleteResponseFlow(flow);
    else
        EV << "RIBdListener received unknown object!" << endl;
}

void LisRIBDCreFloNega::receiveSignal(cComponent* src, simsignal_t id,
        cObject* obj, cObject *detail) {
    EV << "CreateFlowNegative initiated by " << src->getFullPath()
       << " and processed by " << fanb->getFullPath() << endl;
    Flow* flow = dynamic_cast<Flow*>(obj);
    if (flow)
        fanb->receiveCreateFlowNegativeFromRa(flow);
    else
        EV << "RIBdListener received unknown object!" << endl;

}

void LisRIBDCreFloPosi::receiveSignal(cComponent* src, simsignal_t id,
        cObject* obj, cObject *detail) {
    EV << "CreateFlowPositive initiated by " << src->getFullPath()
       << " and processed by " << fanb->getFullPath() << endl;
    Flow* flow = dynamic_cast<Flow*>(obj);
    if (flow)
        fanb->receiveCreateFlowPositiveFromRa(flow);
    else
        EV << "RIBdListener received unknown object!" << endl;

}

