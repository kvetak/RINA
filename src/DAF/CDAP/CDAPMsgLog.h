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

#ifndef CDAPMSGLOG_H_
#define CDAPMSGLOG_H_

//Standard libraries
#include <omnetpp.h>
//RINASim libraries
#include "DAF/CDAP/CDAPMsgLogEntry.h"

typedef std::list<CDAPMsgLogEntry> TMessageLog;
typedef TMessageLog::iterator TMLIter;
typedef TMessageLog::const_iterator TMLConstIter;

class CDAPMsgLog : public cSimpleModule {
  public:
    CDAPMsgLog();
    virtual ~CDAPMsgLog();

    std::string info() const;

    void insert(CDAPMessage* cdapmsg, bool srflag);
    CDAPMsgLogEntry* findByMessage(CDAPMessage* cdapmsg);
    CDAPMsgLogEntry* findRequestByInvId(CDAPMessage* cdapmsg);

  protected:
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);

  private:
    TMessageLog MsgLog;
};

#endif /* CDAPMSGLOG_H_ */
