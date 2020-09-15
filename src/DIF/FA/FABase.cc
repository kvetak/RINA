// The MIT License (MIT)
//
// Copyright (c) 2014-2016 Brno University of Technology, PRISTINE project
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.


#include "DIF/FA/FABase.h"

#include "DIF/FA/NFlowTable.h"
#include "Common/ExternConsts.h"
#include "Common/APNamingInfo.h"

const int FABase::RANDOM_NUMBER_GENERATOR = 0;
const int FABase::MAX_PORTID = 65535;
const int FABase::MAX_CEPID  = 65535;
const char* TIM_FAPENDFLOWS = "FA-PendingFlows";

NFlowTable* FABase::getNFlowTable() const {
    return nFlowTable;
}

void FABase::initMyAddress() {
    //Setup myAddress
    cModule* ipc = this->getModuleByPath("^.^");
    myAddress = Address(ipc->par(PAR_IPCADDR), ipc->par(PAR_DIFNAME));
    EV << "SrcAddress that this FA will use is " << myAddress << endl;

    std::ostringstream description;
    description << "address: " << myAddress.getIpcAddress()
                << "\ndif: " << myAddress.getDifName();
    ipc->getDisplayString().setTagArg("t", 0, description.str().c_str());
    ipc->getDisplayString().setTagArg("t", 1, "r");
}


const Address& FABase::getMyAddress() const {
    return myAddress;
}
