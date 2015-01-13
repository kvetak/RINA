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

#ifndef SDU_H_
#define SDU_H_


#include <cobject.h>
#include <vector>
#include "EFCP_defs.h"
#include "CDAPMessage_m.h"
#include "SDU_m.h"

typedef std::vector<CDAPMessage*> mUserDataType;
class SDU : public SDU_Base
{

  private:
    unsigned char * userData; //Deprecated
//    unsigned int size;
//    unsigned int offset;
    mUserDataType mUserData_var;

    void copy(const SDU& other);

public:
//  SDU();
  virtual ~SDU();

    SDU(const char *name=NULL, int kind=0);
    SDU(const SDU& other); // : SDU_Base(other) {copy(other);}
    SDU& operator=(const SDU& other)
    {
      if (this == &other)
        return *this;
      SDU_Base::operator=(other);
      copy(other);
      return *this;
    }
    virtual SDU *dup() const {return new SDU(*this);}
    // ADD CODE HERE to redefine and implement pure virtual functions from SDU_Base

    unsigned int getSize() const;
    unsigned int getAbsoluteSize() const;
    unsigned int getRestSize() const;
    void setSize(unsigned int size);
    unsigned char* getUserData() const;
    const unsigned char* getUserData(unsigned int offset);
    void setUserData(unsigned char* userData, unsigned int size);

    bool addUserData(CDAPMessage* msg);
    CDAPMessage* getUserData();

    std::vector<SDU*>fragment(unsigned int size);
    SDU* genFragment(unsigned int size, unsigned int fSeqNum, unsigned int fOffset);
    void setFragment(unsigned int size, unsigned int fSeqNum, unsigned int fOffset);


};

#endif /* SDU_H_ */
