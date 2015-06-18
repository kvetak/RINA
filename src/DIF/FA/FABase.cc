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


#include "FABase.h"

const char* TIM_FAPENDFLOWS = "FA-PendingFlows";

FABase::FABase() {
    this->N_flowTable = NULL;
}

FABase::~FABase() {
    this->N_flowTable = NULL;
}

NFlowTable* FABase::getNFlowTable() const {
    return N_flowTable;
}

void FABase::initMyAddress() {
    //Setup MyAddress
    cModule* ipc = this->getParentModule()->getParentModule();
    MyAddress = Address(ipc->par(PAR_IPCADDR), ipc->par(PAR_DIFNAME));
    EV << "SrcAddress that this FA will use is " << MyAddress << endl;

    std::ostringstream description;
    description << "address: " << MyAddress.getIpcAddress()
                << "\ndif: " << MyAddress.getDifName();
    ipc->getDisplayString().setTagArg("t", 0, description.str().c_str());
    ipc->getDisplayString().setTagArg("t", 1, "r");
}

const Address& FABase::getMyAddress() const {
    return MyAddress;
}
