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

#ifndef __RINA_AEConstantMsg_H_
#define __RINA_AEConstantMsg_H_

//Standard libraries
#include <omnetpp.h>
//RINASim libraries
#include "AE.h"

class PingMsg : public CDAP_M_Read {
public:
    PingMsg(bool _counted);
    simtime_t pingAt;
    bool counted;
};

class PongMsg : public CDAP_M_Read_R {
public:
    PongMsg(simtime_t _pingAt, bool _counted);
    simtime_t pingAt, pongAt;
    bool counted;
};

class StartMsg : public CDAP_M_Read {
public:
    StartMsg();
};


class SignalMsg : public cObject {
    public:
    std::string qos;
    simtime_t delay, rtt;
    char type;

    SignalMsg(std::string _qos);
    SignalMsg(std::string _qos, simtime_t _delay);
    SignalMsg(std::string _qos, simtime_t _delay, simtime_t _rtt);
};

#endif
