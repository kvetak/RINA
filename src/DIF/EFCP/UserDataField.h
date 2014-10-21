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

//TODO put it somewhere reasonable
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

typedef std::vector<SDU*> PDUData;
/*
 *
 */
class UserDataField: public cObject
{
  private:
    unsigned int sduDelimitFlags;
    unsigned int sduSeqNum;
    PDUData pduData;
    unsigned int size;

  public:
    UserDataField();
    virtual ~UserDataField();
    void addData(SDU* data);
    SDU* getData();

    unsigned int getSize();
    unsigned int getSduDelimitFlags() const;
    void setSduDelimitFlags(unsigned int sduDelimitFlags);
};

#endif /* USERDATAFIELD_H_ */
