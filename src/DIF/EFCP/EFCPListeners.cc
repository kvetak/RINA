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
/*
 * @file EFCPListeners.cc
 * @author Marcel Marek
 * @date Feb 12, 2015
 * @brief
 * @detail

 */

#include "DIF/EFCP/EFCPListeners.h"
//#include "Common/CongestionDescriptor.h"

EFCPListeners::EFCPListeners(EFCPTable* efcpTable)
{

this->efcpTable = efcpTable;


}

EFCPListeners::~EFCPListeners()
{

}

void LisEFCPCongestFromRA::receiveSignal(cComponent* src, simsignal_t id, cObject* obj, cObject *detail)
{

  CongestionDescriptor* cd = (CongestionDescriptor*) obj;
  DTP* dtp = efcpTable->getDTPBySrcCEP(cd->getConnectionId().getSrcCepId());

  if(dtp != NULL){
    dtp->runCongestionNotificationPolicy();
  }else{
    //Error
  }
}


void LisEFCPQueueInfoFromRMT::receiveSignal(cComponent* src, simsignal_t id, cObject* obj, cObject *detail)
{

  QueueInfo* qi = (QueueInfo*) obj;
  EFCPTableEntry* entry = efcpTable->getEntryByFlow(qi->getFlow());
  DTP* dtp = (*(entry->getEfcpiTab()->begin()))->getDtp();

  if(dtp != NULL){
    dtp->handleQueueInfoFromRMT(qi);
  }else{
    //Error
  }
}


void LisEFCPQueueInfoFromAE::receiveSignal(cComponent* src, simsignal_t id, cObject* obj, cObject *detail)
{

  //TODO
  return;
  QueueInfo* qi = (QueueInfo*) obj;
  EFCPTableEntry* entry = efcpTable->getEntryByFlow(qi->getFlow());

  if(entry == nullptr){
    return;
  }
  DTP* dtp = (*(entry->getEfcpiTab()->begin()))->getDtp();

  if(dtp != NULL){
    dtp->handleQueueInfoFromSocket(qi);
  }else{
    //Error
  }
}
