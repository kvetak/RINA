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
 * @file UserDataField.cc
 * @author Marcel Marek (imarek@fit.vutbr.cz)
 * @date Oct 19, 2014
 * @brief
 * @detail
 */

#include <UserDataField.h>

UserDataField::UserDataField()
{
  size = 0;
  sduDelimitFlags = 0;
  sduSeqNum = 0;

}

UserDataField::UserDataField(const UserDataField& other){
  sduDelimitFlags = other.sduDelimitFlags;
  sduSeqNum = other.sduSeqNum;
  size = other.size;
  PDUData::const_iterator it;

  for(it = other.pduData.begin(); it != other.pduData.end(); ++it){
    SDU* sdu = (*it)->dup();
    take(sdu);
    pduData.push_back(sdu);
  }
}
/**
 *
 * @param sdu
 */
void UserDataField::addData(SDU* data){


  if(pduData.empty()){
    //sduSeqnum is set only for first SDU/fragment in UserDataField
    sduSeqNum = data->getSeqNum();
    sduDelimitFlags |= SDU_SEQ_NUM_PRESENT;
  }
  take(data);
  pduData.push_back(data);
  size += data->getSize();
  sduDelimitFlags |= data->getFragType();



  //TOOD A2 Handle all delimitFlags (eg noLength)
 /* The code below is weird. Left it here for future decryption.
  if(data->getDataType() == SDU_COMPLETE_TYPE || (data->getDataType() == SDU_FRAGMENT_TYPE && data->getFragType() == SDU_FRAG_FIRST)){
    //TODO B1 SduSeqNum is the first SDU/fragment in userDataField, so it should be set only once.
    sduSeqNum = data->getSeqNum();
    sduDelimitFlags |= SDU_SEQ_NUM_PRESENT;
  }
  */
}

SDU* UserDataField::getData(){

  if(pduData.empty()){
    return NULL;
  }
  //TODO B1 What if it is SDU fragment? (fragType_var != 0)
  SDU* tmp = pduData.front();
  tmp->getFragType();
  pduData.erase(pduData.begin());
  size -= tmp->getSize();
  drop(tmp);
  return tmp;
}

unsigned int UserDataField::getSduDelimitFlags() const
{
  return sduDelimitFlags;
}

unsigned int UserDataField::getSduSeqNum() const
{
  return sduSeqNum;
}

void UserDataField::setSduDelimitFlags(unsigned int sduDelimitFlags)
{
  this->sduDelimitFlags = sduDelimitFlags;
}

unsigned int UserDataField::getSize(){
  return size;
}

UserDataField::~UserDataField()
{
  std::vector<SDU*>::iterator it;
  for(it = pduData.begin(); it != pduData.end();){
    drop(*it);
    delete (*it);
    it = pduData.erase(it);

  }

}

void UserDataField::setSduSeqNum(unsigned int sduSeqNum) {
    this->sduSeqNum = sduSeqNum;
}
