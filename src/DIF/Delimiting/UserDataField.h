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
 * @file UserDataField.h
 * @author Marcel Marek (imarek@fit.vutbr.cz)
 * @date Oct 19, 2014
 * @brief
 * @detail
 */

#ifndef USERDATAFIELD_H_
#define USERDATAFIELD_H_
#include <omnetpp.h>
#include <vector>
#include "Common/SDU.h"
#include "DIF/Delimiting/UserDataField_m.h"



//typedef std::vector<SDU*> PDUData;
/*
 *
 */
class UserDataField: public UserDataField_Base
{
  private:
    unsigned int sduDelimitFlags;
    /* SDU delimiter flags */
    bool sduSeqNumPresent;


    unsigned int sduSeqNum;
//    PDUData pduData;
    unsigned int size;

    void copy(const UserDataField& other);

  public:
//    UserDataField();
    UserDataField(const char *name=NULL, int kind=0);
    UserDataField(const UserDataField& other);
//    UserDataField(const UserDataField& other) : UserDataField_Base(other) {copy(other);}
    virtual ~UserDataField();
//    void addData(SDU* data);
    /**
     * This method removes first SDU from userDataField and returns it.
     * Also updates remaining size of UserDataField
     * @return SDU
     */
//    SDU* getData();
//    UserDataField* dup() const {return new UserDataField();}
    virtual UserDataField* dup() const {return new UserDataField(*this);}


    unsigned int getSize();
    unsigned int getSduDelimitFlags() const;
    void setSduDelimitFlags(unsigned int sduDelimitFlags);
    unsigned int getSduSeqNum() const;
    void setSduSeqNum(unsigned int sduSeqNum);



    UserDataField& operator=(const UserDataField& other) {if (this==&other) return *this; UserDataField_Base::operator=(other); copy(other); return *this;}
//    bool operator<(const UserDataField& other) const;




};

#endif /* USERDATAFIELD_H_ */
