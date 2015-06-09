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

#ifndef __RINA_AEPING_H_
#define __RINA_AEPING_H_

//Standard libraries
#include <omnetpp.h>
//RINASim libraries
#include "AE.h"

class AEPing : public AE
{
    //Consts
    const char* TIM_START;
    const char* TIM_STOP;
    const char* MSG_PING;
    const char* PAR_START;
    const char* PAR_STOP;
    const char* PAR_PING;
    const char* PAR_RATE;
    const char* PAR_SIZE;
    const char* PAR_DSTAPNAME;
    const char* PAR_DSTAPINSTANCE;
    const char* PAR_DSTAENAME;
    const char* PAR_DSTAEINSTANCE;
    const char* VAL_MODULEPATH;

  public:
    AEPing();
    virtual ~AEPing();

  protected:
    std::string dstApName;
    std::string dstApInstance;
    std::string dstAeName;
    std::string dstAeInstance;

    simtime_t startAt;
    simtime_t stopAt;
    simtime_t pingAt;
    int rate;
    unsigned int size;


    void initPing();
    void handleSelfMessage(cMessage* msg);

    void prepareAllocateRequest();
    void preparePing();
    void prepareDeallocateRequest();

    //=== AEPing interface starts here ===
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);

    virtual void onStart();
    virtual void onPing();
    virtual void onStop();

    virtual void processMRead(CDAPMessage* msg);
    virtual void processMReadR(CDAPMessage* msg);
    //=== AEPing interface ends here ===

  private:
    std::string myPath;
};

#endif
