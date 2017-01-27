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
 * @file Socket.cc
 * @author Marcel Marek
 * @date Apr 28, 2016
 * @brief
 * @detail
 */

#include "Common/Socket.h"
#include <string>

Define_Module(Socket);

Socket::Socket()
{
    readImm = true;
    inputQCapacity = 10;
}

Flow* Socket::getFlow() const {
    return flow;
}

void Socket::initialize(int step) {

    if(step == 2){
        sigSocketQueueInfo = registerSignal(SIG_Socket_QueueInfo);
    }
}

void Socket::setFlow(Flow* flow) {
    this->flow = flow;
}

Socket::~Socket()
{
}

QueueInfo* Socket::makeQueueInfo()
{

  QueueInfo* qi = new QueueInfo();
  qi->setCapacity(inputQCapacity);
  qi->setOccupied(toAE.size());
  qi->setFlow(flow);
  return qi;
}

void Socket::handleMessage(cMessage* msg) {
  std::string str = msg->getArrivalGate()->getName();
  if(strstr(msg->getArrivalGate()->getName(), "southIo$i") != NULL){

      if(readImm){
          send(msg,"cdapIo$o");
          QueueInfo* qi = makeQueueInfo();
              emit(sigSocketQueueInfo, qi);
      }else{
          toAE.push(msg);
          //emit notify AE, there is msg waiting to be read
          //emit notify EFCP
      QueueInfo* qi = makeQueueInfo();
          emit(sigSocketQueueInfo, qi);

      }
  }
  else { //if(strstr(msg->getArrivalGate()->getName(), "cdapIo$i") != NULL){
    send(msg,"southIo$o", 0);
    QueueInfo* qi = makeQueueInfo();
        emit(sigSocketQueueInfo, qi);
  }
}
