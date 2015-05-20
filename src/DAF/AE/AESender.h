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


#include <map>


class PingMsg : public CDAP_M_Read {
public:
    PingMsg();
    simtime_t pingAt;
};

class PongMsg : public CDAP_M_Read_R {
public:
    PongMsg(simtime_t pingAt);
    simtime_t pingAt, pongAt;
};

class AESender : public AE
{
    //Consts
    const char* S_TIM_START;
    const char* S_TIM_COM;
    const char* S_TIM_STOP;

    const char* S_PAR_START;
    const char* S_PAR_STOP;
    const char* S_PAR_SEND;

    const char* S_PAR_DSTAPNAME;
    const char* S_PAR_DSTAPINSTANCE;
    const char* S_PAR_DSTAENAME;
    const char* S_PAR_DSTAEINSTANCE;

    const char* S_PAR_RATE;
    const char* S_PAR_RATE_VAR;
    const char* S_PAR_SIZE;
    const char* S_PAR_SIZE_VAR;

    const char* S_MSG_PING;
    const char* S_PAR_PING;
    const char* S_VAL_MODULEPATH;

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

    int pduburst;

    double recTimes;

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


    std::map<double, int> times;
    double dround(double a, int ndigits);

};

#endif
