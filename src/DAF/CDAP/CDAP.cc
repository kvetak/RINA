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

#include "CDAP.h"

Define_Module(CDAP);

void CDAP::initialize()
{
    initSignalsAndListeners();
}

void CDAP::handleMessage(cMessage *msg)
{
    signalizeReceiveData(msg);
}

void CDAP::initSignalsAndListeners() {
    cModule* catcher = this->getParentModule()->getParentModule();

    //Signals emmited by this module
    sigCDAPReceiveData = registerSignal(SIG_CDAP_DateReceive);

    //Listeners registered to process signal
    lisCDAPSendData = new LisCDAPSendData(this);
    catcher->subscribe(SIG_AE_DataSend, lisCDAPSendData);
    catcher->subscribe(SIG_RIBD_DataSend, lisCDAPSendData);
}

void CDAP::sendData(cObject* obj) {
    //Change and take ownership
    Enter_Method("SendData()");
    take(check_and_cast<cOwnedObject*>(obj) );

    //Send message
    CDAPMessage* msg = dynamic_cast<CDAPMessage*>(obj);
    cGate* out = gateHalf(GATE_SPLITIO, cGate::OUTPUT, msg->getHandle());
    send(msg, out);
}

void CDAP::signalizeReceiveData(cMessage* msg) {
    emit(sigCDAPReceiveData, msg);
}
