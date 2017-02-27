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

#include "DIF/FA/MultilevelQoS/QoSIdComparer/QoSIdComparer.h"

Define_Module(QoSIdComparer);

void QoSIdComparer::initialize() {
    mHops = par("maxHops").longValue();
    mlBandw = par("mulBandw").longValue();
    setPolicyDisplayString(this);
}


bool QoSIdComparer::isValid(const QoSCube &upperQoS, const QoSCube &lowerQoS) {
    return upperQoS.getQosId() == lowerQoS.getQosId();
}

void QoSIdComparer::setRequirements(Flow * lowerflow, const QoSCube &upperQoS) {
    QoSReq qosParams(upperQoS.getAvgBand()*mlBandw, upperQoS.getAvgSduBand()*mlBandw,
            upperQoS.getPeakBandDuration()*mlBandw,upperQoS.getPeakSduBandDuration()*mlBandw,
            upperQoS.getBurstPeriod()*mlBandw, upperQoS.getBurstDuration()*mlBandw,
            1-pow(1-upperQoS.getUndetectedBitErr(), mHops),1-pow(1-upperQoS.getPduDropProbability(), mHops),
            upperQoS.getMaxSduSize(), upperQoS.isPartialDelivery(), upperQoS.isIncompleteDelivery(), upperQoS.isForceOrder(),
            upperQoS.getMaxAllowGap(), upperQoS.getDelay()/mHops, upperQoS.getJitter(),
            upperQoS.getCostTime()/mHops, upperQoS.getCostBits()/mHops);
    lowerflow->setQosRequirements(qosParams);
}
