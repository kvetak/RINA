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

#include "AEMgmtBase.h"

AEMgmtBase::AEMgmtBase() {
}

AEMgmtBase::~AEMgmtBase() {
}

void AEMgmtBase::setMyAddress(const Address& addr) {
    MyAddress = addr;
}

const Address& AEMgmtBase::getMyAddress() const {
    return MyAddress;
}

void AEMgmtBase::initMyAddress() {
    //Setup MyAddress
    cModule* ipc = this->getParentModule()->getParentModule();
    MyAddress = Address(ipc->par(PAR_IPCADDR), ipc->par(PAR_DIFNAME));
    EV << "SrcAddress that this RIBd will use is " << MyAddress << endl;
}

long AEMgmtBase::getNewInvokeId() {
    long newinvoke = getParentModule()->getSubmodule(MOD_CDAP)->par(PAR_CURINVOKEID).longValue() + 1;
    getParentModule()->getSubmodule(MOD_CDAP)->par(PAR_CURINVOKEID) = newinvoke;
    return newinvoke;
}

void AEMgmtBase::initNamingInfo() {
    //Source info
    srcApName = this->getModuleByPath("^.^.^")->par("apName").stdstringValue();
    srcApInstance = this->getModuleByPath("^.^.^")->par("apInstance").stdstringValue();
    srcAeName = this->par("aeName").stdstringValue();
    srcAeInstance = this->par("aeInstance").stdstringValue();

    dstApName = this->par("dstApName").stdstringValue();
    dstApInstance = this->par("dstApName").stdstringValue();
    dstAeName = this->par("dstAeName").stdstringValue();
    dstAeInstance = this->par("dstAeInstance").stdstringValue();

    srcApni = APNamingInfo(APN(this->srcApName), this->srcApInstance,
            this->srcAeName, this->srcAeInstance);

    dstApni = APNamingInfo(APN(this->dstApName), this->dstApInstance,
            this->dstAeName, this->dstAeInstance);
}

const APNamingInfo& AEMgmtBase::getSrcNamingInfo() const {
    return srcApni;
}

const APNamingInfo& AEMgmtBase::getDstNamingInfo() const {
    return dstApni;
}
