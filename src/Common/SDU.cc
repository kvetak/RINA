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

//SDU::SDU()
//{
//  this->offset = this->size = 0;
//
//}

unsigned int SDU::getSize() const
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

bool SDU::addUserData(mCDAPMessage* msg){

//    if(msg->getSize() > MAXSDUSIZE){
//        return false;
//    }

    //TODO A1 check current SDU size

  this->mUserData_var.push_back(msg);

    return true;
}

SDU::~SDU()
{
  // TODO Auto-generated destructor stub
}

