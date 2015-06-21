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

#ifndef __RINA_AEEXTENDEDPING_H_
#define __RINA_AEEXTENDEDPING_H_

//Standard libraries
#include <omnetpp.h>
//RINASim libraries
#include "AE.h"


class AEExtendedPing : public AE
{
  public:
    AEExtendedPing();
    virtual ~AEExtendedPing();

  protected:
    virtual void initialize();
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
    simtime_t connectAt;
    simtime_t pingAt;
    int rate;
    unsigned int size;

    void prepareAllocateRequest();
    void preparePing();
    void prepareConnectionRequest();
    void prepareDeallocateRequest();

    virtual void processMRead(CDAPMessage* msg);
    virtual void processMReadR(CDAPMessage* msg);

};

#endif

