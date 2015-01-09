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

//void PDU::addUserData(const unsigned char* userData, unsigned int size, bool *fragment){
//
//  if(userData_arraysize == 0){
//    userData_var= new unsigned char[size];
//    memcpy(userData_var, userData, size);
//    *fragment = false;
//
//
//  }else{
//
//    if(*fragment){
////    if(pduLen_var - PDU_HEADER_LEN == userData_arraysize){
//      //allocate new space
//      unsigned char * tmp = new unsigned char[userData_arraysize + SDU_FRAG_LEN];
//      //put size of the exising segment/SDU in the PDU
//      tmp[0] = userData_arraysize & 0xFF;
//      tmp[1] = (userData_arraysize << 8) & 0xFF;
//      //update size of the userData array
//      userData_arraysize += SDU_FRAG_LEN;
//      //copy existing data
//      memcpy(&tmp[SDU_FRAG_LEN], userData_var, userData_arraysize);
//
//      delete [] userData_var;
//      //assign pointer
//      userData_var = tmp;
//
//      *fragment = true;
//    }
//
//    //allocate new space
//    unsigned char * tmp = new unsigned char [size + this->userData_arraysize + SDU_FRAG_LEN];
//    //put size of the exising segment/SDU in the PDU
//    tmp[this->userData_arraysize] = size & 0xFF;
//    tmp[this->userData_arraysize +1 ] = (size << 8) & 0xFF;
//    this->userData_arraysize += SDU_FRAG_LEN;
//    //copy existing data
//    memcpy(tmp, this->userData_var, this->userData_arraysize);
//    //copy new data
//    memcpy(&tmp[this->userData_arraysize], userData, size);
//    delete [] this->userData_var;
//    this->userData_var = tmp;
//
//  }
//
//  this->userData_arraysize += size;
//
//  pduLen_var = PDU_HEADER_LEN + userData_arraysize;
//
//}
/*
 * @param sduSeqNum is unused for the moment because its usage is not clear to me (yet)
 */
//void PDU::putDelimitFlags(int delimitFlags, bool fragment, int sduSeqNum){
//  //TODO B2 Incorporate size of the delimiter flag field into process of delimiting SDUs/PDUs
//  if(sduSeqNum != -1){
//    //SDU Sequence Number present
//
//    //TODO B2 add support for SDU Seq Number
//  }
//
//  flags_var |= 0x08 & (sduSeqNum == -1) ? 0x00: 0xFF;
//  flags_var |= delimitFlags;
//
//
//  unsigned char * tmp = new unsigned char[userData_arraysize + SDU_DELIMITER_FLAG_LEN];
//  //put size of the exising segment/SDU in the PDU
//  tmp[0] = 0x08 & (sduSeqNum == -1) ? 0x00: 0xFF;
//  tmp[0] |= delimitFlags;
//
//  //update size of the userData array
//  userData_arraysize += SDU_DELIMITER_FLAG_LEN;
//  //copy existing data
//  memcpy(&tmp[SDU_DELIMITER_FLAG_LEN], userData_var, userData_arraysize);
//
//  delete [] userData_var;
//  //assign pointer
//  userData_var = tmp;
//}

unsigned int PDU::getHeaderSize(){
  return PDU_HEADER_LEN;
}

unsigned int PDU::getSize(){
    return getPduLen() + getHeaderSize();
}

//std::string PDU::info() const {
//  std::stringstream os;
//  os << "srcAddr: " << srcAddr_var;
//  return os.str();
//}

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

