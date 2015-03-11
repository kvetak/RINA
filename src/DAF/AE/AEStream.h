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

#ifndef __RINA_AESTREAM_H_
#define __RINA_AESTREAM_H_

//Standard libraries
#include <omnetpp.h>
//RINASim libraries
#include "AE.h"


class AEStream : public AE
{
    //Consts
    const char* TIM_START           = "StartCommunication";
    const char* TIM_STOP            = "StopCommunication";
    const char* MSG_STDATA          = "DATA-";
    const char* PAR_START           = "startAt";
    const char* PAR_STOP            = "stopAt";
    const char* PAR_BEGIN           = "beginStreamAt";
    const char* PAR_END             = "endStreamAt";
    const char* PAR_INTERVAL        = "interval";
    const char* PAR_SIZE            = "size";
    const char* PAR_DSTAPNAME       = "dstApName";
    const char* PAR_DSTAPINSTANCE   = "dstApInstance";
    const char* PAR_DSTAENAME       = "dstAeName";
    const char* PAR_DSTAEINSTANCE   = "dstAeInstance";

  protected:
    std::string dstApName;
    std::string dstApInstance;
    std::string dstAeName;
    std::string dstAeInstance;

    simtime_t startAt;
    simtime_t stopAt;
    simtime_t beginStreamAt;
    simtime_t endStreamAt;

    unsigned int size;
    double interval;

    virtual void initialize();
    virtual void handleMessage(cMessage *msg);
    void handleSelfMessage(cMessage* msg);

    void prepareAllocateRequest();
    void prepareStreamData();
    void prepareDeallocateRequest();

    virtual void processMRead(CDAPMessage* msg);
};

#endif
