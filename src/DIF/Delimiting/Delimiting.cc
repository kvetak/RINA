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
 * @file Delimiting.cc
 * @author Marcel Marek (imarek@fit.vutbr.cz)
 * @date Jul 31, 2014
 * @brief
 * @detail
 */

#include "Delimiting.h"

Define_Module(Delimiting);

Delimiting::Delimiting()
{
 seqNum = 1;
}

void Delimiting::initialize(int step){


}

void Delimiting::initGates(){
  northI = this->gateHalf(GATE_DELIMIT_NORTHIO, cGate::INPUT);
  northO = this->gateHalf(GATE_DELIMIT_NORTHIO, cGate::OUTPUT);

  southI = this->gateHalf(GATE_DELIMIT_SOUTHIO, cGate::INPUT, 0);
  southO = this->gateHalf(GATE_DELIMIT_SOUTHIO, cGate::OUTPUT, 0);
}


void Delimiting::handleMessage(cMessage* msg){
  if (msg->isSelfMessage())
  {
    //self-message
  }
  else
  {
    if (msg->arrivedOn(northI->getId()))
    {
      processMsgFromFAI(static_cast<SDUData*>(msg));
    }
    else if (msg->arrivedOn(southI->getId()))
    {
      handleMsgFromEfcpi(static_cast<UserDataField*>(msg));
    }
    else
    {
      //A2 panic!
    }

  }

}

void Delimiting::processMsgFromFAI(SDUData* sduData)
{

  /* TODO A3 Omitting possible fragmentation step for now  (ie sduData.size() > max_PDU_Size) */

  Data* data = new Data();
  data->setDataType(DATA_SDU_COMPLETE);
  data->encapsulate(sduData);

  PDUData* pduData = new PDUData();
  pduData->encapsulate(data);

  UserDataField* userDataField = new UserDataField();
  userDataField->encapsulate(pduData);
  userDataField->setCompleteSDU(true);
  userDataField->setNoLength(false);
  userDataField->setSduSeqNumPresent(true);
  userDataField->setSduSeqNum(seqNum++);

  send(userDataField, southO);




  /*
   * 1. Create new SDU and put msg to this new SDU.
   * 2. Check if SDU.size < (MAXSDUSIZE - header)
   *  2a partition it creating multiple SDUFrag and put them into some vector
   * 3. Go through Data vector and send them to EFCPI
   */

//  SDU* sdu = new SDU();
//  sdu->setDataType(SDU_COMPLETE_TYPE);
//  sdu->addUserData(msg);
//  sdu->encapsulate(msg);
//  sdu->setSeqNum(seqNum);

  //TODO A1 handle multiple gates -> change to cGate*
//  send(sdu, southO);
}

void Delimiting::handleMsgFromEfcpi(UserDataField* userDataField)
{
  /* simpliest implementation without delimiting queue, etc. */
  PDUData* pduData = static_cast<PDUData*>(userDataField->decapsulate());
  Data* data = pduData->decapsulate();
  SDUData* sduData = static_cast<SDUData*>(data->decapsulate());

  send(sduData, northO);

  delete userDataField;
  delete pduData;
  delete data;
//  delete sduData;




//  SDU* sdu = (SDU*) msg;
////  std::vector<CDAPMessage*> &msgVector = sdu->getMUserData();
//  cPacket* cdap = sdu->decapsulate();
//  take(cdap);
//
//  send(cdap, northO);
//  delete sdu;
}

Delimiting::~Delimiting()
{

}

