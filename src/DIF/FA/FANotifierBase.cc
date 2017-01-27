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

#include "DIF/FA/FANotifierBase.h"

const Address& FANotifierBase::getMyAddress() const {
    return MyAddress;
}

void FANotifierBase::initialize() {
    initMyAddress();
}

void FANotifierBase::initMyAddress() {
    std::string v = this->getFullPath();
    //Setup MyAddress
    cModule* ipc = this->getParentModule()->getParentModule();
    MyAddress = Address(ipc->par(PAR_IPCADDR), ipc->par(PAR_DIFNAME));
    EV << "SrcAddress that this FANotifier will use is " << MyAddress << endl;
}

bool FANotifierBase::isMessageProcessable(CDAPMessage* msg) {
    Enter_Method_Silent();
    bool status =   (
            ( dynamic_cast<CDAP_M_Create*>(msg)   && dynamic_cast<Flow*>(dynamic_cast<CDAP_M_Create*>(msg)->getObjectItem().objectVal) ) ||
            ( dynamic_cast<CDAP_M_Create_R*>(msg) && dynamic_cast<Flow*>(dynamic_cast<CDAP_M_Create_R*>(msg)->getObjectItem().objectVal) ) ||
            ( dynamic_cast<CDAP_M_Delete*>(msg)   && dynamic_cast<Flow*>(dynamic_cast<CDAP_M_Delete*>(msg)->getObjectItem().objectVal) ) ||
            ( dynamic_cast<CDAP_M_Delete_R*>(msg) && dynamic_cast<Flow*>(dynamic_cast<CDAP_M_Delete_R*>(msg)->getObjectItem().objectVal) )
                    )
                    ? true : false;
    return status;
}

void FANotifierBase::receiveMessage(CDAPMessage* msg) {
    Enter_Method("receiveMessage()");
    CDAPProcessingBase::receiveMessage(msg);
}

