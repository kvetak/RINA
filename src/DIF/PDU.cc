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
/**
 * @file PDU.cc
 * @author Marcel Marek (imarek@fit.vutbr.cz)
 * @date Apr 30, 2014
 * @brief
 * @detail
 */

#include <PDU.h>

Register_Class(PDU);

void PDU::addUserData(const unsigned char* userData, unsigned int size){

  if(userData_arraysize == 0){
    userData_var= new unsigned char[size];
    memcpy(userData_var, userData, size);


  }else{

    if(pduLen_var - PDU_HEADER_LEN == userData_arraysize){
      //allocate new space
      unsigned char * tmp = new unsigned char[userData_arraysize + SDU_FRAG_LEN];
      //put size of the exising segment/SDU in the PDU
      tmp[0] = userData_arraysize && 0xFF;
      tmp[1] = (userData_arraysize << 2) && 0xFF;
      //copy existing data
      memcpy(tmp, userData_var, userData_arraysize);
      //update size of the userData array
      userData_arraysize += SDU_FRAG_LEN;
      delete [] userData_var;
      //assign pointer
      userData_var = tmp;


    }
    //allocate new space
    unsigned char * tmp = new unsigned char [size + this->userData_arraysize + SDU_FRAG_LEN];
    //put size of the exising segment/SDU in the PDU
    tmp[this->userData_arraysize] = this->userData_arraysize && 0xFF;
    tmp[this->userData_arraysize +1 ] = (this->userData_arraysize << 2) && 0xFF;
    this->userData_arraysize += SDU_FRAG_LEN;
    //copy existing data
    memcpy(tmp, this->userData_var, this->userData_arraysize);
    //copy new data
    memcpy(&tmp[this->userData_arraysize], userData, size);
    //partially update size of the userData array
    this->userData_arraysize += SDU_FRAG_LEN;
    delete [] this->userData_var;
    this->userData_var = tmp;

  }

  this->userData_arraysize += size;

  pduLen_var = PDU_HEADER_LEN + userData_arraysize;

}
/*
 * @param sduSeqNum is unused for the moment because its usage is not clear to me (yet)
 */
void PDU::putDelimitFlags(int sduSeqNum){
  if(sduSeqNum == -1){
    //sduSeqNot used
  }

}

unsigned int getHeaderSize(){
  return PDU_HEADER_LEN;
}

//PDU::PDU()
//{
//  // TODO Auto-generated constructor stub
//
//}
//
//PDU::~PDU()
//{
//  // TODO Auto-generated destructor stub
//}

