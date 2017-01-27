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
 * @file UserDataField.cc
 * @author Marcel Marek (imarek@fit.vutbr.cz)
 * @date Oct 19, 2014
 * @brief
 * @detail
 */

#include "DIF/Delimiting/UserDataField.h"
Register_Class(UserDataField);

UserDataField::UserDataField(const char *name, int kind) : UserDataField_Base(name,kind)
{
  size = 0;
  sduDelimitFlags = 0;
  sduSeqNum = 0;

}

UserDataField::UserDataField(const UserDataField& other): ::UserDataField_Base(other){
  sduDelimitFlags = other.sduDelimitFlags;
  sduSeqNum = other.sduSeqNum;
  size = other.size;
//  PDUData::const_iterator it;
//
//  for(it = other.pduData.begin(); it != other.pduData.end(); ++it){
//    SDU* sdu = (*it)->dup();
//    take(sdu);
//    pduData.push_back(sdu);
//  }
}

void copy(const UserDataField& other){

}


/**
 *
 * @param sdu
 */
//void UserDataField::addData(SDU* data){
//
//
//  if(pduData.empty()){
//    //sduSeqnum is set only for first SDU/fragment in UserDataField
//    sduSeqNum = data->getSeqNum();
//    sduDelimitFlags |= SDU_SEQ_NUM_PRESENT;
//  }
//  take(data);
//  pduData.push_back(data);
//  size += data->getSize();
//  sduDelimitFlags |= data->getFragType();
//
//
//
//  //TOOD A2 Handle all delimitFlags (eg noLength)
// /* The code below is weird. Left it here for future decryption.
//  if(data->getDataType() == SDU_COMPLETE_TYPE || (data->getDataType() == SDU_FRAGMENT_TYPE && data->getFragType() == SDU_FRAG_FIRST)){
//    //TODO B1 SduSeqNum is the first SDU/fragment in userDataField, so it should be set only once.
//    sduSeqNum = data->getSeqNum();
//    sduDelimitFlags |= SDU_SEQ_NUM_PRESENT;
//  }
//  */
//}

//SDU* UserDataField::getData(){
//
//  if(pduData.empty()){
//    return NULL;
//  }
//  //TODO B1 What if it is SDU fragment? (fragType_var != 0)
//  SDU* tmp = pduData.front();
//  tmp->getFragType();
//  pduData.erase(pduData.begin());
//  size -= tmp->getSize();
//  drop(tmp);
//  return tmp;
//}

unsigned int UserDataField::getSduDelimitFlags() const
{
  return sduDelimitFlags;
}

unsigned int UserDataField::getSduSeqNum() const
{
  return sduSeqNum;
}

//void UserDataField::setSduDelimitFlags(unsigned int sduDelimitFlags)
//{
//  this->sduDelimitFlags = sduDelimitFlags;
//}

unsigned int UserDataField::getSize(){
  return size;
}

UserDataField::~UserDataField()
{
//  std::vector<SDU*>::iterator it;
//  for(it = pduData.begin(); it != pduData.end();){
//    drop(*it);
//    delete (*it);
//    it = pduData.erase(it);
//
//  }

}

void UserDataField::setSduSeqNum(unsigned int sduSeqNum) {
    this->sduSeqNum = sduSeqNum;
}

//bool UserDataField::operator<(const UserDataField& other) const
//{
//  if(this->getSduSeqNumPresent() && other.getSduSeqNumPresent())
//  {
//    if(this->getSduSeqNum() < other.getSduSeqNum){
//      return true;
//    }else if(this->getSduSeqNum() > other.getSduSeqNum){
//      return false;
//    }else {
//      if(this->getFirstFragmen()){
//        return true;
//      }else if(other.getFirstFragmen()){
//        return true;
//      }else if(this->is)
//    }
//
//  }
//
//
//}
