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
 * PushBackChannel.h
 *
 *  Created on: Jan 30, 2015
 *      Author: imarek
 */

#ifndef PUSHBACKCHANNEL_H_
#define PUSHBACKCHANNEL_H_

#include <omnetpp.h>
//#include <cchannel.h>
#include "simtime.h"

class PushBackChannel : public cIdealChannel
{
  private:
    // stores the end of the last transmission; used if there is a datarate
    simtime_t txfinishtime;
  public:
    PushBackChannel();
    virtual ~PushBackChannel();
    virtual bool isBusy() const {return true;}
    static PushBackChannel *create(const char *name);
    void setBusy(bool busy);
};

#endif /* PUSHBACKCHANNEL_H_ */
