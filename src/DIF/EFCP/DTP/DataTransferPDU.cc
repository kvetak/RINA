//
// Copyright © 2014 PRISTINE Consortium (http://ict-pristine.eu)
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

/*
 * @file DataTransferPDU.cc
 * @author Marcel Marek (imarek@fit.vutbr.cz)
 * @date Oct 19, 2014
 * @brief
 * @detail
 */

#include <DataTransferPDU.h>

Register_Class(DataTransferPDU);

DataTransferPDU::DataTransferPDU(const char *name, int kind): DataTransferPDU_Base(name,kind)
{
  userDataField_var = NULL;

}
void DataTransferPDU::copy(const DataTransferPDU& other){
  if(other.userDataField_var != NULL){

    this->userDataField_var = other.userDataField_var->dup();
    take(userDataField_var);
  }
}

unsigned int DataTransferPDU::getSize(){
  //TODO B2 check PDU_HEADER_LEN
  return userDataField_var->getSize() + PDU_HEADER_LEN;
}

DataTransferPDU::~DataTransferPDU()
{
  if(userDataField_var != NULL){
    drop(userDataField_var);
    delete userDataField_var;
  }
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
