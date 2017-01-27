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

#include "DIF/Delimiting/Delimiting.h"

Define_Module(Delimiting);

Delimiting::Delimiting()
{
 delimitingTimer = nullptr;
 delimitDelay = 0.0;

}

void Delimiting::initialize(int step){

  maxFlowSDUSize = getRINAModule<cModule*>(this, 2, {MOD_EFCP})->par("maxSDUSize");
  maxFlowPDUSize = getRINAModule<cModule*>(this, 2, {MOD_EFCP})->par("maxPDUSize");
  delimitDelay = getRINAModule<cModule*>(this, 2, {MOD_EFCP})->par("delimitDelay");
  sduSeqNum = 1;

  delimitingTimer = new DelimitingDelimitTimer;

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

    DelimitingTimers* timer = static_cast<DelimitingTimers*>(msg);
    switch (timer->getType())
    {
      case (DELIMITING_DELIMIT_TIMER): {

        UserDataField* userDataField;
        for(auto it = pduDataQOut.begin(); it != pduDataQOut.end(); it = pduDataQOut.erase(it))
        {
          userDataField = new UserDataField();
          userDataField->encapsulate((*it));
          userDataField->setCompleteSDU((*it)->getCompleteSDU());
          userDataField->setFirstFragment((*it)->getFirstFragment());
          userDataField->setMidFragment((*it)->getMidFragment());
          userDataField->setLastFragment((*it)->getLastFragment());
          userDataField->setNoLength(false);
          userDataField->setSduSeqNumPresent(true);
          userDataField->setSduSeqNum(sduSeqNum);
          send(userDataField, southO);
        }
        break;
      }
    }
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
  //TODO A2 sduSeqNum handling makes me want to laugh (or cry)

  /* Fragment, if necessary */
  std::vector<Data*> dataQ;
  if(sduData->getByteLength() > maxFlowPDUSize)
  {
    /* We need to fragment */
    int64_t length = sduData->getByteLength();
    Data* data = new Data;
    data->setDataType(DATA_FIRST_FRAG);
    data->encapsulate(sduData);
    data->setEncapMsgLength(length);
    length -= maxFlowPDUSize;
    data->setByteLength(maxFlowPDUSize);
    dataQ.push_back(data);

    for(;length - maxFlowPDUSize > 0; length -= maxFlowPDUSize)
    {
      /* Only the first fragment contains the actual SDUData, other fragments are there only for purpose of modelling */
      data = new Data;
      data->setDataType(DATA_MIDDLE_FRAG);
      //      data->encapsulate(sduData->dup()); // Uncomment this line if you want copy of SDUData in every fragment
      data->setByteLength(maxFlowPDUSize);
      dataQ.push_back(data);
    }

    data = new Data;
    data->setDataType(DATA_LAST_FRAG);
    //      data->encapsulate(sduData->dup()); // Uncomment this line if you want copy of SDUData in every fragment
    data->setByteLength(length);
    dataQ.push_back(data);



    PDUData* pduData;

    for(auto it = dataQ.begin(); it != dataQ.end(); it = dataQ.erase(it))
    {
      pduData = new PDUData();
      pduData->encapsulate((*it));
      pduDataQOut.push_back(pduData);

    }

    UserDataField* userDataField;
    for(auto it = pduDataQOut.begin(); it != pduDataQOut.end(); it = pduDataQOut.erase(it))
    {
      userDataField = new UserDataField();
      userDataField->encapsulate((*it));
      userDataField->setCompleteSDU((*it)->getCompleteSDU());
      userDataField->setFirstFragment((*it)->getFirstFragment());
      userDataField->setMidFragment((*it)->getMidFragment());
      userDataField->setLastFragment((*it)->getLastFragment());
      userDataField->setNoLength(false);
      userDataField->setSduSeqNumPresent(true);
      userDataField->setSduSeqNum(sduSeqNum);
      send(userDataField, southO);
    }
    sduSeqNum++;

  }
  else if(sduData->getByteLength() < maxFlowPDUSize * 0.8)
  {
    /* Concatenation */


    if (pduDataQOut.empty())
    {
      Data* data = new Data();
      data->setDataType(DATA_SDU_COMPLETE);
      data->encapsulate(sduData);

      PDUData* pduData = new PDUData();
      pduData->encapsulate(data);
      pduDataQOut.push_back(pduData);


      schedule(delimitingTimer);

      return;

    }else{

      PDUData* pduData = pduDataQOut.back();
      int64_t pduDatalength = pduData->getByteLength();
      int64_t restLength = maxFlowPDUSize - pduDatalength;

      if(restLength < sduData->getByteLength())
      {
        //We need to fragment
        int64_t length = sduData->getByteLength();
        Data* data = new Data();
        data->setDataType(DATA_FIRST_FRAG);
        data->encapsulate(sduData);
        data->setEncapMsgLength(length);
        data->setByteLength(restLength);

        length -= restLength;

        pduData->encapsulate(data);

        for(;length - maxFlowPDUSize > 0; length -= maxFlowPDUSize)
        {
          data = new Data;
          data->setDataType(DATA_MIDDLE_FRAG);
          //      data->encapsulate(sduData->dup()); // Uncomment this line if you want copy of SDUData in every fragment
          data->setByteLength(maxFlowPDUSize);
          dataQ.push_back(data);
        }

        data = new Data;
        data->setDataType(DATA_LAST_FRAG);
        //      data->encapsulate(sduData->dup()); // Uncomment this line if you want copy of SDUData in every fragment
        data->setByteLength(length);
        dataQ.push_back(data);

        for(auto it = dataQ.begin(); it != dataQ.end(); it = dataQ.erase(it))
        {
          pduData = new PDUData();
          pduData->encapsulate((*it));
          pduDataQOut.push_back(pduData);

        }

        UserDataField* userDataField;
        for(auto it = pduDataQOut.begin(); it != pduDataQOut.end() && ((*it)->getByteLength() > maxFlowPDUSize * 0.8 && pduDataQOut.size() > 1); it = pduDataQOut.erase(it))
        {
          userDataField = new UserDataField();
          userDataField->encapsulate((*it));
          userDataField->setCompleteSDU((*it)->getCompleteSDU());
          userDataField->setFirstFragment((*it)->getFirstFragment());
          userDataField->setMidFragment((*it)->getMidFragment());
          userDataField->setLastFragment((*it)->getLastFragment());
          userDataField->setNoLength(false);
          userDataField->setSduSeqNumPresent(true);
          userDataField->setSduSeqNum(sduSeqNum);
          send(userDataField, southO);
        }
        //        sduSeqNum++; //

      }
      else
      {
        //It fits!
        Data* data = new Data();
        data->setDataType(DATA_SDU_COMPLETE);
        data->encapsulate(sduData);

        //        pduData = new PDUData();
        pduData->encapsulate(data);

        schedule(delimitingTimer);

      }
    }
  }
  else
  {
    /* SDUData is small enough to fit in one PDU and too big for concatenation */


    cancelEvent(delimitingTimer);

    UserDataField* userDataField;
    for(auto it = pduDataQOut.begin(); it != pduDataQOut.end(); it = pduDataQOut.erase(it))
    {
      userDataField = new UserDataField();
      userDataField->encapsulate((*it));
      userDataField->setCompleteSDU((*it)->getCompleteSDU());
      userDataField->setFirstFragment((*it)->getFirstFragment());
      userDataField->setMidFragment((*it)->getMidFragment());
      userDataField->setLastFragment((*it)->getLastFragment());
      userDataField->setNoLength(false);
      userDataField->setSduSeqNumPresent(true);
      userDataField->setSduSeqNum(sduSeqNum);
      send(userDataField, southO);

    }
    sduSeqNum++;

    Data* data = new Data();
    data->setDataType(DATA_SDU_COMPLETE);
    data->encapsulate(sduData);

    PDUData* pduData = new PDUData();
    pduData->encapsulate(data);

    //    pduDataQOut.push_back(pduData);

    userDataField = new UserDataField();
    userDataField->encapsulate(pduData);
    userDataField->setCompleteSDU(true);
    userDataField->setNoLength(false);
    userDataField->setSduSeqNumPresent(true);
    userDataField->setSduSeqNum(sduSeqNum++);

//    userDataFieldQOut.push_back(userDataField);
    send(userDataField, southO);

  }
}

void Delimiting::handleMsgFromEfcpi(UserDataField* userDataField)
{


  userDataFieldQIn.push_back(userDataField);

  PDUData* pduData;
  for(auto it = userDataFieldQIn.begin(); it != userDataFieldQIn.end(); it = userDataFieldQIn.erase(it))
  {
    pduData = static_cast<PDUData*>((*it)->decapsulate());
    Data* data;
    for(; (data = pduData->decapsulate()) != nullptr; ){
      dataQIn.push_back(data);
    }
    delete (*it);
    delete pduData;
  }

  for(auto it = dataQIn.begin(); it != dataQIn.end(); )
  {
    if((*it)->getDataType() == DATA_SDU_COMPLETE)
    {
      SDUData* sduData = dynamic_cast<SDUData*>((*it)->decapsulate());
      if (sduData != nullptr)
      {
        sduDataQIn.push_back(sduData);
      }
      delete (*it);
      it = dataQIn.erase(it);
    }
    else if ((*it)->getDataType() == DATA_FIRST_FRAG)
    {
      /* Try to find lastFragment */
      auto tmpIt = it;
      tmpIt++;
      bool found = false;
      for(; tmpIt != dataQIn.end(); ++tmpIt){
        if((*tmpIt)->getDataType() == DATA_LAST_FRAG){
          found = true;
          break;
        }
      }

      if(found){
        //restore original length
        (*it)->setByteLength((*it)->getEncapMsgLength());
        SDUData* sduData = dynamic_cast<SDUData*>((*it)->decapsulate());
        if (sduData != nullptr)
        {
          sduDataQIn.push_back(sduData);
        }
        delete (*it);
        it = dataQIn.erase(it);

        for(; it != dataQIn.end() && ((*it)->getDataType() == DATA_MIDDLE_FRAG || (*it)->getDataType() == DATA_LAST_FRAG); it = dataQIn.erase(it))
        {
          /* All the middle and the last fragments are empty */
          delete (*it);
        }
      }else{
        break;
      }

    }
    else
    {
      break;
    }
  }


  //TODO A1: This is only if immediate = true, otherwise we should wait for some kind of read()
  for(auto it = sduDataQIn.begin(); it != sduDataQIn.end(); it = sduDataQIn.erase(it))
  {
    send((*it), northO);
  }
}
void Delimiting::schedule(DelimitingTimers* timer)
{

  switch (timer->getType()){
    case DELIMITING_DELIMIT_TIMER:
    {
      if(!timer->isScheduled()){
        scheduleAt(simTime() + delimitDelay, timer);
      }
      break;
    }


  }
}



Delimiting::~Delimiting()
{
  cancelAndDelete(delimitingTimer);

  for(auto it = dataQIn.begin(); it != dataQIn.end();)
  {
    delete (*it);
    it = dataQIn.erase(it);
  }


}

