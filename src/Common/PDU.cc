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
 * @file PDU.cc
 * @author Marcel Marek (imarek@fit.vutbr.cz)
 * @date Apr 30, 2014
 * @brief
 * @detail
 */

#include "Common/PDU.h"

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


