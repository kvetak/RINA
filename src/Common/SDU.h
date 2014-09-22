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

class SDU : public SDU_Base
{

  private:
    unsigned char * userData; //depricated
//    unsigned int size;
//    unsigned int offset;
//    std::vector<mCDAPMessage*> mUserData;

    void copy(const SDU& other){};

public:
//  SDU();
  virtual ~SDU();

    SDU(const char *name=NULL, int kind=0) : SDU_Base(name,kind) {this->offset_var = this->size_var = 0;}
    SDU(const SDU& other) : SDU_Base(other) {copy(other);}
    SDU& operator=(const SDU& other) {if (this==&other) return *this; SDU_Base::operator=(other); copy(other); return *this;}
    virtual SDU *dup() const {return new SDU(*this);}
    // ADD CODE HERE to redefine and implement pure virtual functions from SDU_Base

    unsigned int getSize() const;
    unsigned int getRestSize() const;
    void setSize(unsigned int size);
    unsigned char* getUserData() const;
    const unsigned char* getUserData(unsigned int offset);
    void setUserData(unsigned char* userData, unsigned int size);

    bool addUserData(CDAPMessage* msg);


};

#endif /* SDU_H_ */