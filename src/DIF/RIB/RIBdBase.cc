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

#include <RIBdBase.h>

RIBdBase::RIBdBase() {
    // TODO Auto-generated constructor stub

}

RIBdBase::~RIBdBase() {
    // TODO Auto-generated destructor stub

}

void RIBdBase::setMyAddress(const Address& addr) {
    MyAddress = addr;
}

const Address& RIBdBase::getMyAddress() const {
    return MyAddress;
}

void RIBdBase::initMyAddress() {
    //Setup MyAddress
    cModule* ipc = this->getParentModule()->getParentModule();
    MyAddress = Address(ipc->par(PAR_IPCADDR), ipc->par(PAR_DIFNAME));
    EV << "SrcAddress that this RIBd will use is " << MyAddress << endl;
}

long RIBdBase::getNewInvokeId() {
    long newinvoke = getParentModule()->getSubmodule(MOD_CDAP)->par(PAR_CURINVOKEID).longValue() + 1;
    getParentModule()->getSubmodule(MOD_CDAP)->par(PAR_CURINVOKEID) = newinvoke;
    return newinvoke;
}
