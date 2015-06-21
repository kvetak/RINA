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
/**
 * @file Delimiting.h
 * @author Marcel Marek (imarek@fit.vutbr.cz)
 * @date Jul 31, 2014
 * @brief
 * @detail
 */

#ifndef DELIMITING_H_
#define DELIMITING_H_

#include <omnetpp.h>
#include "CDAPMessage_m.h"
#include "SDU.h"
#include "DataTransferPDU_m.h"
//#include <csimplemodule.h>

#define DELIMITING_MODULE_NAME "delimiting"

#define GATE_DELIMIT_NORTHIO "northIo"
#define GATE_DELIMIT_SOUTHIO "southIo"

class Delimiting : public cSimpleModule
{
  private:

    cGate* northI;
    cGate* northO;
    //TODO A2 Change to [] of gates
    cGate* southI;
    cGate* southO;

    unsigned int seqNum;

    void processMsgFromFAI(cPacket* msg);
    void handleMsgFromEfcpi(Data* msg);
  public:
    Delimiting();
    virtual ~Delimiting();

    void initGates();

  protected:
    virtual void handleMessage(cMessage *msg);
    virtual void initialize(int step);


};

#endif /* DELIMITING_H_ */
