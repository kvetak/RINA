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
 * @file DTPRTTEstimatorPolicyBase.h
 * @author Marcel Marek (imarek@fit.vutbr.cz)
 * @date Jan 22, 2015
 * @brief
 * @detail
 */

#ifndef RTTESTIMATORPOLICYBASE_H_
#define RTTESTIMATORPOLICYBASE_H_

#include <omnetpp.h>

#include "DIF/EFCP/EFCPPolicy.h"
#include "DIF/EFCP/EFCP_defs.h"

/*
 *
 */
class RTTEstimatorPolicyBase : public EFCPPolicy
{
  public:
    RTTEstimatorPolicyBase();
    virtual ~RTTEstimatorPolicyBase();
//    virtual bool run(DTPState* dtpState, DTCPState* dtcpState) = 0;
    double RTO;     // Retransmission timeout
    double getRTO();
    void setRto(double rto);

  protected:
    virtual void initialize(){};
    virtual void handleMessage(cMessage* msg){};
    void defaultAction(DTPState* dtpState, DTCPState* dtcpState);
};

#endif /* RTTESTIMATORPOLICYBASE_H_ */
