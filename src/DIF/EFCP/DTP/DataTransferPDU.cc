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
 * @file DataTransferPDU.cc
 * @author Marcel Marek (imarek@fit.vutbr.cz)
 * @date Oct 19, 2014
 * @brief
 * @detail
 */

#include "DataTransferPDU.h"

Register_Class(DataTransferPDU);

DataTransferPDU::DataTransferPDU(const char *name, int kind): DataTransferPDU_Base(name,kind)
{
  userDataField_var = NULL;

}
void DataTransferPDU::copy(const DataTransferPDU& other){
  if(other.userDataField_var != NULL){

//    this->userDataField_var = other.userDataField_var->dup();
//    take(userDataField_var);
  }
}

unsigned int DataTransferPDU::getSize(){
  //TODO B2 check PDU_HEADER_LEN
  return userDataField_var->getSize() + PDU_HEADER_LEN;
}



UserDataFieldPtr& DataTransferPDU::getUserDataField()
{
    return userDataField_var;
}

void DataTransferPDU::updatePacketSize()
{
  setByteLength(userDataField_var->getSize() + PDU_HEADER_LEN);
}

void DataTransferPDU::setUserDataField(const UserDataFieldPtr& userDataField)
{
    take(userDataField);
    this->userDataField_var = userDataField;
  updatePacketSize();
}

//TODO B1 This obviously needs more work.
int DataTransferPDU::getSDUGap(const DataTransferPDU* other)
{
  if(! userDataField_var->getSduDelimitFlags() & SDU_SEQ_NUM_PRESENT){
    return -1;
  }else{

    return other->userDataField_var->getSduSeqNum() - userDataField_var->getSduSeqNum();
  }
}

unsigned int DataTransferPDU::getSDUSeqNum() const
{
  return userDataField_var->getSduSeqNum();
}
