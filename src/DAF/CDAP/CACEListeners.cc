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

#include "CACEListeners.h"


CACEListeners::CACEListeners(CACE* ncace): cace(ncace)
{
}

CACEListeners::~CACEListeners() {
    cace = NULL;
}

void LisCACESendData::receiveSignal(cComponent* src, simsignal_t id,
        cObject* obj) {
    EV << "SendData initiated by " << src->getFullPath() << " and processed by " << cace->getFullPath() << endl;
    CDAPMessage* msg = dynamic_cast<CDAPMessage*>(obj);
    if (msg)
        cace->sendData(msg);
    else
        EV << "Received not a CACEMessage!" << endl;
}
