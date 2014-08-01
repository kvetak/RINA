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
 * @file PDU.h
 * @author Marcel Marek (imarek@fit.vutbr.cz)
 * @date Apr 30, 2014
 * @brief
 * @detail
 */

#ifndef PDU_H_
#define PDU_H_


#define SDU_FRAG_LEN 2 //number of bytes for length field of a fragment
#define SDU_DELIMITER_FLAG_LEN 1 //size of SDUDelimiterFlags in bytes

#include <omnetpp.h>
#include "PDU_m.h"

class PDU : public PDU_Base
{
  private:
    void copy(const PDU& other){};
//      PDU();
//      ~PDU();

    public:
      PDU(const char *name=NULL, int kind=0) : PDU_Base(name,kind) {}
      PDU(const PDU& other) : PDU_Base(other) {copy(other);}
      PDU& operator=(const PDU& other) {if (this==&other) return *this; PDU_Base::operator=(other); copy(other); return *this;}
      virtual PDU *dup() const {return new PDU(*this);}
      // ADD CODE HERE to redefine and implement pure virtual functions from PDU_Base

      void addUserData(const unsigned char *userData, unsigned int size, bool *fragment);

      void putDelimitFlags(int delimitFlags, bool fragment, int sduSeqNum = -1);
      unsigned int getHeaderSize();
  };


#endif /* PDU_H_ */
