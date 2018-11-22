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

#ifndef __RINA_AERAFT_H_
#define __RINA_AERAFT_H_

#include <omnetpp.h>
#include "DAF/AE/AE.h"

using namespace omnetpp;


class AERaft : public AE {
public:
    AERaft();
    virtual ~AERaft();
    bool onA_read(APIReqObj* obj);
    bool onA_write(APIReqObj* obj);
    bool onA_create(APIReqObj* obj);

private:
    void processMRead(CDAPMessage* msg);
    void processMReadR(CDAPMessage* msg);
    void processMWrite(CDAPMessage* msg);
    void processMWriteR(CDAPMessage* msg);
    void processMCreate(CDAPMessage* msg);
    void processMCreateR(CDAPMessage* msg);

    object_t objPing;
    object_t objStream;
};

#endif
