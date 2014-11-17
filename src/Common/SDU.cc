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
/**
 * @file SDU.cc
 * @author Marcel Marek (imarek@fit.vutbr.cz)
 * @date Apr 29, 2014
 * @brief
 * @detail
 */
#include <SDU.h>

SDU::SDU(const char *name, int kind) : SDU_Base(name, kind)
{
   fSeqNum_var = seqNum_var = fOffset_var = fSize_var = this->offset_var = this->size_var = 0;

}

SDU::SDU(const SDU& other): SDU_Base(other){
  copy(other);
}

void SDU::copy(const SDU& other){
  mUserDataType::const_iterator it;

  for(it = other.mUserData_var.begin(); it != other.mUserData_var.end(); ++it){

    mUserData_var.push_back((*it)->dup());
  }
}

/*
 * This size returns size depending on @var dataType_var
 */
unsigned int SDU::getSize() const
{
  if (dataType_var == SDU_TYPE)
  {
    return size_var;
  }
  else if (dataType_var == SDU_FRAGMENT_TYPE)
  {
    return fSize_var;
  }else{
    return 0; //PANIC!
  }
}
/*
 * This method returns the absolute size of the SDU.
 */
unsigned int SDU::getAbsoluteSize() const
{
  return size_var;

}

unsigned int SDU::getRestSize()const
{
  return size_var - offset_var;
}

void SDU::setSize(unsigned int size)
{
  if(userData !=NULL){
    unsigned char *tmp = new unsigned char[size];
    memcpy(tmp,userData, (this->size_var < size) ? this->size_var : size);
    this->size_var = size;
    free(userData);
    userData = tmp;
  }else{
    this->size_var = size;
    userData = new unsigned char[size];
  }

}

unsigned char* SDU::getUserData() const
{
  return &userData[offset_var];
}

const unsigned char* SDU::getUserData(unsigned int size)
{
  offset_var += size;
  return &userData[offset_var - size];
}

void SDU::setUserData(unsigned char* userData, unsigned int size)
{
  if(this->userData != NULL){
    free(this->userData);
    this->offset_var = 0;
  }
  this->size_var = size;
  this->userData = new unsigned char[size];
  memcpy(this->userData, userData, size);
//    this->userData = userData;
}

bool SDU::addUserData(CDAPMessage* msg){

//    if(msg->getSize() > MAXSDUSIZE){
//        return false;
//    }

    //TODO A1 check current SDU size

  this->mUserData_var.push_back(msg);
  size_var += msg->getSize();

    return true;
}
/**
 * Returns SDU Fragments vector of specified size
 *
 */
std::vector<SDU*> SDU::fragment(unsigned int size){

  std::vector<SDU*> frags;
  SDU* tmp;
  for(unsigned int i = 0; i* size < this->size_var; i++){
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
  fSize_var = fSize;
  fSeqNum_var = fSeqNum;
  fOffset_var = fOffset;
  dataType_var = SDU_FRAGMENT_TYPE;
  if(fSeqNum == 0){
    fragType_var = SDU_FRAG_FIRST;
  }else if(fSize + fOffset == this->size_var){
    fragType_var = SDU_FRAG_LAST;
  }else{
    fragType_var = SDU_FRAG_MIDDLE;
  }
}

SDU::~SDU()
{
  std::vector<CDAPMessage*>::iterator it;
  for(it = mUserData_var.begin(); it != mUserData_var.end();){
    if((*it) != NULL){
      delete (*it);
    }
    it = mUserData_var.erase(it);

  }
}

