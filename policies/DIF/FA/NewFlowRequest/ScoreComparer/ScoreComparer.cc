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


#include "DIF/FA/NewFlowRequest/ScoreComparer/ScoreComparer.h"

Define_Module(ScoreComparer);

short ScoreComparer::countFeasibilityScore(const QoSReq& requirements, const QoSCube& cube) const {
    short score = 0;

    if (requirements.getAvgBand() != VAL_QOSPARDONOTCARE)
        (requirements.getAvgBand() <= cube.getAvgBand()) ? score++ : score--;

    if (requirements.getAvgSduBand() != VAL_QOSPARDONOTCARE)
        (requirements.getAvgSduBand() <= cube.getAvgSduBand()) ? score++ : score--;

    if (requirements.getPeakBandDuration() != VAL_QOSPARDONOTCARE)
        (requirements.getPeakBandDuration() <= cube.getPeakBandDuration()) ? score++ : score--;

    if (requirements.getPeakSduBandDuration() != VAL_QOSPARDONOTCARE)
        (requirements.getPeakSduBandDuration() <= cube.getPeakSduBandDuration()) ? score++ : score--;

    if (requirements.getBurstPeriod() != VAL_QOSPARDONOTCARE)
        (requirements.getBurstPeriod() <= cube.getBurstPeriod()) ? score++ : score--;

    if (requirements.getBurstDuration() != VAL_QOSPARDONOTCARE)
        (requirements.getBurstDuration() <= cube.getBurstDuration()) ? score++ : score--;

    if (requirements.getUndetectedBitErr() != VAL_QOSPARDONOTCARE)
        (requirements.getUndetectedBitErr() >= cube.getUndetectedBitErr()) ? score++ : score--;

    if (requirements.getPduDropProbability() != VAL_QOSPARDONOTCARE)
        (requirements.getPduDropProbability() >= cube.getPduDropProbability()) ? score++ : score--;

    if (requirements.getMaxSduSize() != VAL_QOSPARDONOTCARE)
        (requirements.getMaxSduSize() <= cube.getMaxSduSize()) ? score++ : score--;

    (requirements.isPartialDelivery() == cube.isPartialDelivery()) ? score++ : score--;

    (requirements.isIncompleteDelivery() == cube.isIncompleteDelivery()) ? score++ : score--;

    (requirements.isForceOrder() == cube.isForceOrder()) ? score++ : score--;

    if (requirements.getMaxAllowGap() != VAL_QOSPARDONOTCARE)
        (requirements.getMaxAllowGap() >= cube.getMaxAllowGap()) ? score++ : score--;

    if (requirements.getDelay() != VAL_QOSPARDONOTCARE)
        (requirements.getDelay() >= cube.getDelay()) ? score++ : score--;

    if (requirements.getJitter() != VAL_QOSPARDONOTCARE)
        (requirements.getJitter() >= cube.getJitter()) ? score++ : score--;

    if (requirements.getCostTime() != VAL_QOSPARDONOTCARE)
        (requirements.getCostTime() >= cube.getCostTime()) ? score++ : score--;

    if (requirements.getCostBits() != VAL_QOSPARDONOTCARE)
        (requirements.getCostBits() >= cube.getCostBits()) ? score++ : score--;

    return score;
}

bool ScoreComparer::run(Flow& flow) {
    Enter_Method("invokeNewFlowRequestPolicy()");
    //Is flow policy acceptable
    std::string apname = flow.getSrcApni().getApn().getName();

    //FIXME: Vesely - Simulate error and DTCP flag better
    if ( apname.find("Err") != std::string::npos) {
        return false;
    }

    //EV << flow.getQosRequirements().getAvgBand() << endl;

    //Always translate management traffic to appropriate management QoSCube
    if (flow.isManagementFlow()) {
        flow.getConnectionId().setQoSId(VAL_MGMTQOSID);
        flow.setQosCube(QoSCube::MANAGEMENT);
        return true;
    }

    //TODO: Compare QoS Parameters with available QoS cubes
    QoSCubeSet cubes = ResourceAllocator->getQoSCubes();
    //EV << ResourceAllocator->getQoSCubes();

    std::string qosid = VAL_UNDEF_QOSID;
    short score = 0;
    QoSCube qs;

    for (QCubeCItem it = cubes.begin(); it != cubes.end(); ++it) {
        short tmpscore = countFeasibilityScore(flow.getQosRequirements(), *it);
        if (score < tmpscore) {
            score = tmpscore;
            qosid = it->getQosId();
            qs = *it;
        }
    }
    flow.getConnectionId().setQoSId(qosid);
    flow.setQosCube(qs);
    return qosid.compare(VAL_UNDEF_QOSID) ? true : false;
}

