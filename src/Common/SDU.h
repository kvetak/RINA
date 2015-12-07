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

#include <omnetpp.h>
#include <cobject.h>
#include <vector>
#include "EFCP_defs.h"
#include "CDAPMessage_m.h"
#include "SDU_m.h"


#define SDU_SEQ_NUM_PRESENT 0x08
#define SDU_NO_LENGTH 0x04
#define SDU_NO_L_MID_FRAG 0x00
#define SDU_NO_L_FIRST_FRAG 0x01
#define SDU_NO_L_LAST_FRAG 0x02
#define SDU_NO_L_ONE_SDU 0x03

#define SDU_L_COMP_SDU 0x00 /* It may express ZERO or more complete SDUs*/
#define SDU_L_SDU_FIRST_FRAG 0x01
#define SDU_L_LAST_FRAG_SDU 0x02
#define SDU_L_LAST_SDU_FIRST_FRAG 0x03 /* Last fragment, ZERO or more SDUs followed by first fragment */

typedef std::vector<cPacket*> mUserDataType;
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

    bool addUserData(cPacket* msg);
    cPacket* getUserData();

    std::vector<SDU*>fragment(unsigned int size);
    SDU* genFragment(unsigned int size, unsigned int fSeqNum, unsigned int fOffset);
    void setFragment(unsigned int size, unsigned int fSeqNum, unsigned int fOffset);


};

#endif /* SDU_H_ */
