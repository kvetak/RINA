/*
 * PushBackChannel.cpp
 *
 *  Created on: Jan 30, 2015
 *      Author: imarek
 */

#include <PushBackChannel.h>
Define_Channel(PushBackChannel);

PushBackChannel::PushBackChannel()
{
  txfinishtime = SIMTIME_ZERO;


}

PushBackChannel::~PushBackChannel()
{
  // TODO Auto-generated destructor stub
}

void PushBackChannel::setBusy(bool busy)
{
  if(busy){
    txfinishtime = SimTime::getMaxTime();
  }else{
    txfinishtime = 0;
  }
}
