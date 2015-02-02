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
