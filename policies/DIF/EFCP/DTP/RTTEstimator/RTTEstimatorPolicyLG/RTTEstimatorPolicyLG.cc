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
 * RTTEstimatorPolicyLG.c
 *
 *  Created on: May 3, 2015
 *      Author: Marcel Marek
 */

#include "DIF/EFCP/DTP/RTTEstimator/RTTEstimatorPolicyLG/RTTEstimatorPolicyLG.h"
#include "DIF/EFCP/DTCP/ControlPDU_m.h"

const char * RTT_RTO_ESTIMATOR = "RTT_RTO_ESTIMATOR";

Register_Class(RTTEstimatorPolicyLG);

RTTEstimatorPolicyLG::RTTEstimatorPolicyLG()
{
    RTO = MIN_RTO;
}

RTTEstimatorPolicyLG::~RTTEstimatorPolicyLG()
{
}

void RTTEstimatorPolicyLG::initialize() {
    sigStatRTTRTO = registerSignal(RTT_RTO_ESTIMATOR);
}

bool RTTEstimatorPolicyLG::run(DTPState* dtpState, DTCPState* dtcpState)
{
      defaultAction(dtpState, dtcpState);
      if(RTO < MIN_RTO)
          RTO = MIN_RTO;
      emit(sigStatRTTRTO, RTO);

      return false;
}
