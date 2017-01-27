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
 * @file DataTransferPDU.h
 * @author Marcel Marek (imarek@fit.vutbr.cz)
 * @date Oct 19, 2014
 * @brief
 * @detail
 */

#ifndef DATATRANSFERPDU_H_
#define DATATRANSFERPDU_H_

#include "DIF/EFCP/DTP/DataTransferPDU_m.h"
/*
 *
 */
class DataTransferPDU : public DataTransferPDU_Base
  {
    private:
      void copy(const DataTransferPDU& other);
      UserDataFieldPtr userDataField_var;

    public:
      DataTransferPDU(const char *name=NULL, int kind=0);
      DataTransferPDU(const DataTransferPDU& other) : DataTransferPDU_Base(other) {copy(other);}
//      DataTransferPDU& operator=(const DataTransferPDU& other) {if (this==&other) return *this; DataTransferPDU_Base::operator=(other); copy(other); return *this;}
      virtual DataTransferPDU *dup() const {return new DataTransferPDU(*this);}
      // ADD CODE HERE to redefine and implement pure virtual functions from DataTransferPDU_Base

      unsigned int getSize();

      UserDataFieldPtr& getUserDataField();
      void setUserDataField(const UserDataFieldPtr& userDataField);

      int getSDUGap(const DataTransferPDU* other);
      unsigned int getSDUSeqNum() const;
      /**
       * This method needs to be run when you change userDataField_var's size via direct pointer.
       */
    void updatePacketSize();
};

typedef std::vector<DataTransferPDU*> PDUQ_t;

#endif /* DATATRANSFERPDU_H_ */

