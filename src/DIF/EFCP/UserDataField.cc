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

}
/**
 *
 * @param sdu
 */
void UserDataField::addData(SDU* data){

  pduData.push_back(data);
  size += data->getSize();
  sduDelimitFlags |= data->getFragType();

  //TOOD A2 Handle all delimitFlags (eg noLength)
  if(data->getDataType() == SDU_TYPE || (data->getDataType() == SDU_FRAGMENT_TYPE && data->getFragType() == SDU_FRAG_FIRST)){
    sduSeqNum = data->getSeqNum();
    sduDelimitFlags |= SDU_SEQ_NUM_PRESENT;
  }
}

SDU* UserDataField::getData(){

  if(pduData.empty()){
    return NULL;
  }
  SDU* tmp = pduData.front();
  pduData.erase(pduData.begin());
  size -= tmp->getSize();
  return tmp;
}

unsigned int UserDataField::getSize(){
  return size;
}

UserDataField::~UserDataField()
{
  // TODO Auto-generated destructor stub
}

