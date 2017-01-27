//
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
/**
 * @file AEMgmt.cc
 * @author Vladimir Vesely, Kamil Jerabek (ivesely@fit.vutbr.cz, xjerab18@stud.fit.vutbr.cz)
 * @date Oct 2, 2015
 * @brief Kind of a Notification Board for DAF
 * @detail
 */

#include "DAF/AEManagement/AEMgmt.h"

const char* DAF_PAR_USEFANOTIF          = "useFANotifier";
const char* DAF_PAR_USEENROLLNOTIF      = "useEnrollmentNotifier";

Define_Module(AEMgmt);

void AEMgmt::initialize() {
    //Init signals and listeners
    initSignalsAndListeners();

    //Init pointers
    initPointers();

    initNamingInfo();
}

void AEMgmt::handleMessage(cMessage *msg) {

}

void AEMgmt::initPointers() {
/*    FANotif = dynamic_cast<FANotifierBase*>( getModuleByPath("^.faNotifier") );
    if (FANotif) {
        useFANotifier = true;
        this->par(DAF_PAR_USEFANOTIF) = true;
    }
*/
    DAFEnrollNotif = dynamic_cast<DAFEnrollmentNotifierBase*>( getModuleByPath("^.enrollmentNotifier") );
    if (DAFEnrollNotif) {
        useEnrollmentNotifier = true;
        this->par(DAF_PAR_USEENROLLNOTIF) = true;
    }
}

void AEMgmt::receiveData(CDAPMessage* msg) {
    Enter_Method("receiveData()");
    //std::string xxx = FANotif->getFullPath();

    //EnrollmentNotifier processing
    if (useEnrollmentNotifier && DAFEnrollNotif->isMessageProcessable(msg)) {
        DAFEnrollNotif->receiveMessage(msg);
    }

    //delete msg;
}

void AEMgmt::initSignalsAndListeners() {
    cModule* catcher1 = this->getParentModule();

    //Signals that this module is emitting
    sigRIBDSendData      = registerSignal(SIG_RIBD_DataSend);

    //Signals that this module is processing
    lisAEMgmtRcvData = new LisAEMgmtRcvData(this);
    catcher1->subscribe(SIG_CDAP_DateReceive, lisAEMgmtRcvData);
}

void AEMgmt::signalizeSendData(CDAPMessage* msg) {
    Enter_Method("signalizeSendData()");
    //Check dstAddress
    if (msg->getDstAddr() == Address::UNSPECIFIED_ADDRESS) {
        EV << "Destination address cannot be UNSPECIFIED!" << endl;
        return;
    }

    msg->setBitLength(msg->getBitLength() + msg->getHeaderBitLength());
    //Pass message to CDAP
    EV << "Emits SendData signal for message " << msg->getName() << endl;
    emit(sigRIBDSendData, msg);
}
