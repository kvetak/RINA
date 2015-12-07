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

/*
 * @file DataTransferPDU.h
 * @author Marcel Marek (imarek@fit.vutbr.cz)
 * @date Oct 19, 2014
 * @brief
 * @detail
 */

#ifndef DATATRANSFERPDU_H_
#define DATATRANSFERPDU_H_

#include "DataTransferPDU_m.h"
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
      ~DataTransferPDU();

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

