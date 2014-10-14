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

#include "RIBdListeners.h"

RIBdListeners::RIBdListeners(RIBdBase* nribd) : ribd(nribd)
{
}

RIBdListeners::~RIBdListeners() {
    ribd = NULL;
}

void LisRIBDCreReq::receiveSignal(cComponent* src, simsignal_t id, cObject* obj) {
    EV << "CreateRequest initiated by " << src->getFullPath()
       << " and processed by " << ribd->getFullPath() << endl;
    ribd->sendCreateRequestFlow(obj);
}

void LisRIBDRcvData::receiveSignal(cComponent* src, simsignal_t id,
        cObject* obj) {
    EV << "ReceiveData initiated by " << src->getFullPath()
       << " and processed by " << ribd->getFullPath() << endl;
    ribd->receiveData(obj);
}
