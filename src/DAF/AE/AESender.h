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

#ifndef __RINA_AESender_H_
#define __RINA_AESender_H_

//Standard libraries
#include <omnetpp.h>
//RINASim libraries
#include "AE.h"

//Consts
extern const char* S_TIM_START;
extern const char* S_TIM_COM;
extern const char* S_TIM_STOP;

extern const char* S_PAR_START;
extern const char* S_PAR_STOP;
extern const char* S_PAR_SEND;

extern const char* S_PAR_DSTAPNAME;
extern const char* S_PAR_DSTAPINSTANCE;
extern const char* S_PAR_DSTAENAME;
extern const char* S_PAR_DSTAEINSTANCE;

extern const char* S_PAR_RATE;
extern const char* S_PAR_RATE_VAR;
extern const char* S_PAR_SIZE;
extern const char* S_PAR_SIZE_VAR;

extern const char* S_MSG_PING;
extern const char* S_PAR_PING;
extern const char* S_VAL_MODULEPATH;

class AESender : public AE
{
  public:
    AESender();
    virtual ~AESender();

  protected:
    virtual void initialize();
    virtual void finish();
    virtual void handleMessage(cMessage *msg);

    void handleSelfMessage(cMessage* msg);

  private:
    std::string myPath;

    std::string dstApName;
    std::string dstApInstance;
    std::string dstAeName;
    std::string dstAeInstance;

    simtime_t startAt;
    simtime_t stopAt;
    simtime_t sendAfter;

    double rate;
    double ratevar;

    unsigned int size;
    unsigned int sizevar;

    long send;
    long pingreceived;
    long received;
    long sendSize;
    long pingreceivedSize;
    long receivedSize;

    simtime_t minDelay;
    simtime_t maxDelay;
    simtime_t firstR;
    simtime_t lastR;

    void prepareAllocateRequest();
    void preparePing();
    void prepareDeallocateRequest();

    virtual void processMRead(CDAPMessage* msg);
    virtual void processMReadR(CDAPMessage* msg);

};

#endif
