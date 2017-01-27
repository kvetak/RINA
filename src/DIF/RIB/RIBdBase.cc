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

#include "DIF/RIB/RIBdBase.h"

RIBdBase::RIBdBase() {

}

RIBdBase::~RIBdBase() {

}

void RIBdBase::setMyAddress(const Address& addr) {
    MyAddress = addr;
}

const Address& RIBdBase::getMyAddress() const {
    return MyAddress;
}

void RIBdBase::initMyAddress() {
    //Setup MyAddress
    cModule* ipc = this->getModuleByPath("^.^");
    MyAddress = Address(ipc->par(PAR_IPCADDR), ipc->par(PAR_DIFNAME));
    EV << "SrcAddress that this RIBd will use is " << MyAddress << endl;
}

long RIBdBase::getNewInvokeId() {
    long newinvoke = getParentModule()->getSubmodule(MOD_CDAP)->par(PAR_CURINVOKEID).longValue() + 1;
    getParentModule()->getSubmodule(MOD_CDAP)->par(PAR_CURINVOKEID) = newinvoke;
    return newinvoke;
}
