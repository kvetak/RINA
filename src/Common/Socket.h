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
/*
 * @file Socket.h
 * @author Marcel Marek
 * @date Apr 28, 2016
 * @brief
 * @detail
 */

#ifndef SOCKET_H_
#define SOCKET_H_

#include "Common/RINASignals.h"
#include "Common/ExternConsts.h"
#include <omnetpp.h>
#include "Common/QueueInfo.h"
#include <queue>
#include "Common/Flow.h"

class Socket : public cSimpleModule
{
private:
    bool readImm;
    std::queue<cMessage*> toAE;
    Flow* flow;

    //signals
    simsignal_t sigSocketQueueInfo;

    int inputQCapacity; // input from network

    QueueInfo* makeQueueInfo();

  public:
    Socket();
    virtual ~Socket();
    void handleMessage(cMessage* msg);
    void initialize(int step);
    Flow* getFlow() const;
    void setFlow(Flow* flow);

  protected:
    int numInitStages() const
    {
      return 4;
    }
};

#endif /* SOCKET_H_ */
