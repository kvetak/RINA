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

SDU::SDU()
{
  this->offset = this->size = 0;

}

unsigned int SDU::getSize() const
{
  return size;
}

unsigned int SDU::getRestSize()const
{
  return size - offset;
}

void SDU::setSize(unsigned int size)
{
  if(userData !=NULL){
    unsigned char *tmp = new unsigned char[size];
    memcpy(tmp,userData, (this->size < size) ? this->size : size);
    this->size = size;
    free(userData);
    userData = tmp;
  }else{
    this->size = size;
    userData = new unsigned char[size];
  }

}

unsigned char* SDU::getUserData() const
{
  return &userData[offset];
}

const unsigned char* SDU::getUserData(unsigned int size)
{
  offset += size;
  return &userData[offset - size];
}

void SDU::setUserData(unsigned char* userData, unsigned int size)
{
  if(this->userData != NULL){
    free(this->userData);
    this->offset = 0;
  }
  this->size = size;
  this->userData = new unsigned char[size];
  memcpy(this->userData, userData, size);
//    this->userData = userData;
}

bool SDU::addUserData(mCDAPMessage* msg){

//    if(msg->getSize() > MAXSDUSIZE){
//        return false;
//    }
    return true;
}

SDU::~SDU()
{
  // TODO Auto-generated destructor stub
}

