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

#include "MockEFCPI.h"

Define_Module(MockEFCPI);

void MockEFCPI::initialize()
{
    northI = this->gateHalf("northIo", cGate::INPUT);
    northO = this->gateHalf("northIo", cGate::OUTPUT);
    southI = this->gateHalf("southIo", cGate::INPUT);
    southO = this->gateHalf("southIo", cGate::OUTPUT);

    connID = new ConnectionId();
    connID->setSrcCepId(0);
    connID->setDstCepId(0);
    connID->setQoSId(VAL_MGMTQOSID);

    srcApn = APN(getModuleByPath(".^.^")->par("apName"));
    srcAddress = Address(srcApn);



}

void MockEFCPI::handleMessage(cMessage *msg)
{

  if (msg->arrivedOn(northI->getId()))
  {

    CDAPMessage* cdap = (CDAPMessage*)msg;
    DataTransferPDU* pdu = new DataTransferPDU();

    pdu->setConnId(*(connID->dup()));

    pdu->setSrcAddr(srcAddress);
    pdu->setDstAddr(cdap->getDstAddr());
    pdu->setSrcApn(srcApn);
    pdu->setDstApn(cdap->getDstAddr().getApname());

    pdu->setSeqNum(0);

    SDU* sdu = new SDU();
    sdu->setDataType(SDU_COMPLETE_TYPE);
    sdu->addUserData((cPacket*) msg);
    sdu->setSeqNum(0);

    UserDataField* userData = new UserDataField();
    userData->addData(sdu);
    pdu->setUserDataField(userData);
    pdu->updatePacketSize();


    send(pdu, southO);


  }
  else if (msg->arrivedOn(southI->getId()))
  {

    DataTransferPDU* pdu = (DataTransferPDU*) msg;

    UserDataField* userData = pdu->getUserDataField();

    SDU* sdu = userData->getData();
    take(sdu);

    cPacket* cdap = sdu->getUserData();
    take(cdap);

    send(cdap, northO);
    delete sdu;

    delete pdu;


  }

}
