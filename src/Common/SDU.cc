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
 * @file SDU.cc
 * @author Marcel Marek (imarek@fit.vutbr.cz)
 * @date Apr 29, 2014
 * @brief
 * @detail
 */
#include "Common/SDU.h"

SDU::SDU(const char *name, int kind) : SDU_Base(name, kind)
{
   fSeqNum = seqNum = fOffset = fSize = offset = size = 0;

}

SDU::SDU(const SDU& other): SDU_Base(other){
  copy(other);
}

void SDU::copy(const SDU& other){
  mUserDataType::const_iterator it;

  for(it = other.mUserData_var.begin(); it != other.mUserData_var.end(); ++it){
    cPacket *cdap = (*it)->dup();
    take(cdap);

    mUserData_var.push_back(cdap);
  }
}

/*
 * This size returns size depending on @var dataType_var
 */
unsigned int SDU::getSize() const
{
//  if (dataType_var == SDU_COMPLETE_TYPE)
  {
    return size;
  }
//  else if (dataType_var == SDU_FRAGMENT_TYPE)
  {
    return fSize;
//  }else{
    return 0; //PANIC!
  }
}
/*
 * This method returns the absolute size of the SDU.
 */
unsigned int SDU::getAbsoluteSize() const
{
  return size;

}

unsigned int SDU::getRestSize()const
{
  return size - offset;
}

//void SDU::setSize(unsigned int size)
//{
//  if(userData !=NULL){
//    unsigned char *tmp = new unsigned char[size];
//    memcpy(tmp,userData, (this->size_var < size) ? this->size_var : size);
//    this->size_var = size;
//    free(userData);
//    userData = tmp;
//  }else{
//    this->size_var = size;
//    userData = new unsigned char[size];
//  }
//
//}

//unsigned char* SDU::getUserData() const
//{
//  return &userData[offset_var];
//}

//const unsigned char* SDU::getUserData(unsigned int size)
//{
//  offset_var += size;
//  return &userData[offset_var - size];
//}

//void SDU::setUserData(unsigned char* userData, unsigned int size)
//{
//  if(this->userData != NULL){
//    free(this->userData);
//    this->offset_var = 0;
//  }
//  this->size_var = size;
//  this->userData = new unsigned char[size];
//  memcpy(this->userData, userData, size);
////    this->userData = userData;
//}

bool SDU::addUserData(cPacket* msg){

//    if(msg->getSize() > MAXSDUSIZE){
//        return false;
//    }

    //TODO A1 check current SDU size
  take(msg);
  this->mUserData_var.push_back(msg);
  this->size += msg->getByteLength();

  return true;
}

cPacket* SDU::getUserData(){

  if (!mUserData_var.empty())
  {
    cPacket* cdap;
    cdap = mUserData_var.front();

    mUserData_var.erase(mUserData_var.begin());
    drop(cdap);
    return cdap;
  }
  else
  {
    return NULL;
  }
}
/**
 * Returns SDU Fragments vector of specified size
 *
 */
std::vector<SDU*> SDU::fragment(unsigned int size){

  std::vector<SDU*> frags;
  SDU* tmp;
  for(unsigned int i = 0; i* size < this->size; i++){
    tmp = this->genFragment(size, i, i*size);
    frags.push_back(tmp);
  }

  return frags;
}

SDU* SDU::genFragment(unsigned int size, unsigned int fSeqNum, unsigned int fOffset){
  SDU* tmp = this->dup();
  tmp = new SDU(*this);
  tmp->setFragment(size, fSeqNum, fOffset);
  return tmp;

}

void SDU::setFragment(unsigned int fSize, unsigned int fSeqNum, unsigned int fOffset){
  this->fSize = fSize;
  this->fSeqNum = fSeqNum;
  this->fOffset = fOffset;
//  dataType_var = SDU_FRAGMENT_TYPE;
  if(fSeqNum == 0){
    this->fragType = SDU_FRAG_FIRST;
  }else if(fSize + fOffset == this->size){
    this->fragType = SDU_FRAG_LAST;
  }else{
    this->fragType = SDU_FRAG_MIDDLE;
  }
}

SDU::~SDU()
{
  std::vector<cPacket*>::iterator it;
  for(it = mUserData_var.begin(); it != mUserData_var.end();){
    if((*it) != NULL){
      drop((*it));
      delete (*it);
    }
    it = mUserData_var.erase(it);

  }
}

