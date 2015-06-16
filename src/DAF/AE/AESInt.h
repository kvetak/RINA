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

#ifndef __RINA_AESInt_H_
#define __RINA_AESInt_H_

//Standard libraries
#include <omnetpp.h>
//RINASim libraries
#include "AE.h"


#include <map>


class _AESInt_self : public cMessage {
public:
    _AESInt_self();
};

class _PingMsg : public CDAP_M_Read {
public:
    _PingMsg();
    simtime_t pingAt;
};

class _PongMsg : public CDAP_M_Read_R {
public:
    _PongMsg(simtime_t pingAt);
    simtime_t pingAt, pongAt;
};

double minMaxNormal (double a, double b, int rng=0);

class AESInt : public AE {

public:
    AESInt();
    virtual ~AESInt();

protected:
    bool inTime;
    int maxSize;

    virtual void doIni() = 0;
    virtual void doFin() = 0;
    virtual void iniCom() = 0;

    virtual void processMsg(_AESInt_self *);
    virtual void processMsg(_PingMsg *);
    virtual void processMsg(_PongMsg *);

    void sendMsg(_PingMsg *, int);
    void sendMsg(_PongMsg *, int);

private:
    std::string dstApName;
    std::string dstApInstance;
    std::string dstAeName;
    std::string dstAeInstance;

    simtime_t startAt;
    simtime_t stopAt;
    simtime_t sendDuring;
    simtime_t sendAfter;

    long send;
    long received;
    long sendSize;
    long receivedSize;

    double recTimes;
    std::map<double, int> times;

    simtime_t maxDelay;
    simtime_t sumDelay;

    virtual void initialize();
    virtual void finish();
    virtual void handleMessage(cMessage *msg);
    void handleSelfMessage(cMessage* msg);

    virtual void processMRead(CDAPMessage* msg);
    virtual void processMReadR(CDAPMessage* msg);

    double dround(double a, int ndigits);
};

#endif
