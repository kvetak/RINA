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

#ifndef RABASE_H_
#define RABASE_H_

//Standard libraries
#include <omnetpp.h>
//RINASim libraries
#include "Common/QoSCube.h"
#include "DIF/RA/NM1FlowTable.h"
#include "Common/Flow.h"

typedef std::list<QoSCube> QoSCubeSet;
typedef QoSCubeSet::const_iterator QCubeCItem;

class RABase : public cSimpleModule
{
  public:
    RABase();
    virtual ~RABase();

    virtual void createNM1Flow(Flow *flow) = 0;
    virtual void createNM1FlowWithoutAllocate(Flow *flow) = 0;
    virtual void createNFlow(Flow *flow) = 0;
    virtual void postNFlowAllocation(Flow* flow) = 0;
    virtual void postNM1FlowAllocation(NM1FlowTableItem* ftItem) = 0;
    virtual void removeNM1Flow(Flow *flow) = 0;
    virtual void removeNM1FlowBindings(NM1FlowTableItem* ftItem) = 0;
    virtual bool bindNFlowToNM1Flow(Flow* flow) = 0;
    virtual void blockNM1PortOutput(NM1FlowTableItem* ftItem) = 0;
    virtual void unblockNM1PortOutput(NM1FlowTableItem* ftItem) = 0;
    virtual NM1FlowTable* getFlowTable() = 0;
    virtual void signalizeSlowdownRequestToRIBd(cPacket* pdu) = 0;
    virtual void signalizeSlowdownRequestToEFCP(cObject* pdu) = 0;
    virtual bool hasFlow(std::string addr, std::string qosId) = 0;

    const QoSCubeSet& getQoSCubes() const;
    const QoSCube* getQoSCubeById(std::string qosId) const;

  protected:
    //SimpleModule overloads
    virtual void initialize(int stage) = 0;
    virtual void handleMessage(cMessage *msg) = 0;

    QoSCubeSet QoSCubes;
};

//Free function
std::ostream& operator<< (std::ostream& os, const QoSCubeSet& cubes);

#endif /* RABASE_H_ */
