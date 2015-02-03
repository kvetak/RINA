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
#include "SDU.h"



typedef std::vector<SDU*> PDUData;
/*
 *
 */
class UserDataField: public cOwnedObject
{
  private:
    unsigned int sduDelimitFlags;
    unsigned int sduSeqNum;
    PDUData pduData;
    unsigned int size;

    void copy(const UserDataField& other);

  public:
    UserDataField();
    UserDataField(const UserDataField& other);
    virtual ~UserDataField();
    void addData(SDU* data);
    /**
     * This method removes first SDU from userDataField and returns it.
     * Also updates remaining size of UserDataField
     * @return SDU
     */
    SDU* getData();
    virtual UserDataField* dup() const {return new UserDataField(*this);}

    unsigned int getSize();
    unsigned int getSduDelimitFlags() const;
    void setSduDelimitFlags(unsigned int sduDelimitFlags);
    unsigned int getSduSeqNum() const;
    void setSduSeqNum(unsigned int sduSeqNum);
};

#endif /* USERDATAFIELD_H_ */
