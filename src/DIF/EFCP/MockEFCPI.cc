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

#include "DIF/EFCP/MockEFCPI.h"

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
    ManagementPDU* pdu = new ManagementPDU();

    pdu->setConnId(*(connID->dup()));

    pdu->setSrcAddr(srcAddress);
    pdu->setDstAddr(cdap->getDstAddr());
    pdu->setSrcApn(srcApn);
    pdu->setDstApn(cdap->getDstAddr().getApn());

    pdu->setSeqNum(0);

    pdu->encapsulate(cdap);



    send(pdu, southO);


  }
  else if (msg->arrivedOn(southI->getId()))
  {

    cPacket* packet = (cPacket*)msg;
    send(packet->decapsulate(), northO);
    delete packet;

  }

}

MockEFCPI::~MockEFCPI()
{
  delete connID;



}
