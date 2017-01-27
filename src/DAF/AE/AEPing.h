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

#ifndef __RINA_AEPING_H_
#define __RINA_AEPING_H_

//Standard libraries
#include <omnetpp.h>
//RINASim libraries
#include "DAF/AE/AE.h"

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
    virtual void afterOnStart();

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

    void onStart();
    void connect();
    virtual void onPing();
    virtual void onStop();

    virtual void processMRead(CDAPMessage* msg);
    virtual void processMReadR(CDAPMessage* msg);
    //=== AEPing interface ends here ===

  private:
    std::string myPath;
};

#endif
