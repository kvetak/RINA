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

#include "RA.h"

Define_Module(RA);

void RA::initialize()
{
    //Register FA signals
    registerFASigs();
}

void RA::registerFASigs() {
    FA* fa = ModuleAccess<FA>("fa").get();
    //Register signals
    sigFACreReq = registerSignal("CreateRequestFlow");
    sigFACreRes = registerSignal("CreateResponseFlow");
    sigDelReq = registerSignal("DeleteRequestFlow");
    sigDelRes = registerSignal("DeleteResponseFlow");
    //Subscribe FA signals
    //this->getParentModule()->getParentModule()->subscribe("CreateRequest",  lCreReq);
    fa->lisCreReq = new LisFACreReq(fa);
    this->subscribe(sigFACreReq,  fa->lisCreReq);
    fa->lisCreRes = new LisFACreRes(fa);
    this->subscribe(sigFACreRes, fa->lisCreRes);
    fa->lisDelReq = new LisFADelReq(fa);
    this->subscribe(sigDelReq,  fa->lisDelReq);
    fa->lisDelRes = new LisFADelRes(fa);
    this->subscribe(sigDelRes, fa->lisDelRes);
}

void RA::signalizeFACreateRequestFlow() {
    //EV << "Sending... " << getSignalName(sigFACreReq) << endl;
    emit(sigFACreReq, true);
}

void RA::signalizeFACreateResponseFlow() {
    emit(sigFACreRes, true);
}

void RA::signalizeFADeleteRequestFlow() {
    emit(sigDelReq, true);
}

void RA::signalizeFADeleteResponseFlow() {
    emit(sigDelRes, true);
}

void RA::handleMessage(cMessage *msg)
{

}
