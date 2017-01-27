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

#ifndef SDU_H_
#define SDU_H_

#include <omnetpp.h>
#include <vector>
#include "DIF/EFCP/EFCP_defs.h"
#include "DAF/CDAP/CDAPMessage_m.h"
#include "Common/SDU_m.h"



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
//    unsigned char * userData; //Deprecated
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


    unsigned int getSize() const;
    unsigned int getAbsoluteSize() const;
    unsigned int getRestSize() const;

    bool addUserData(cPacket* msg);
    cPacket* getUserData();

    std::vector<SDU*>fragment(unsigned int size);
    SDU* genFragment(unsigned int size, unsigned int fSeqNum, unsigned int fOffset);
    void setFragment(unsigned int size, unsigned int fSeqNum, unsigned int fOffset);


};

#endif /* SDU_H_ */
