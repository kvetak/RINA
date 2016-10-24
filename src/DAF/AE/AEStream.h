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

#ifndef __RINA_AESTREAM_H_
#define __RINA_AESTREAM_H_

//Standard libraries
#include <omnetpp.h>
//RINASim libraries
#include "AE.h"


class AEStream : public AE
{
    //Consts
    const char* TIM_START;
    const char* TIM_STOP;
    const char* MSG_STDATA;
    const char* PAR_START;
    const char* PAR_STOP;
    const char* PAR_BEGIN;
    const char* PAR_END;
    const char* PAR_INTERVAL;
    const char* PAR_SIZE;
    const char* PAR_DSTAPNAME;
    const char* PAR_DSTAPINSTANCE;
    const char* PAR_DSTAENAME;
    const char* PAR_DSTAEINSTANCE;

  public:
    AEStream();

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

    void onStart();
    void afterOnStart();

    void prepareAllocateRequest();
    void prepareStreamData();
    void prepareDeallocateRequest();

    virtual void processMRead(CDAPMessage* msg);
};

#endif
