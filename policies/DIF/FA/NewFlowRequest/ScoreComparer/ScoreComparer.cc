//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
// 

#include <ScoreComparer.h>

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
        (requirements.getUndetectedBitErr() <= cube.getUndetectedBitErr()) ? score++ : score--;

    if (requirements.getPduDropProbability() != VAL_QOSPARDONOTCARE)
        (requirements.getPduDropProbability() <= cube.getPduDropProbability()) ? score++ : score--;

    if (requirements.getMaxSduSize() != VAL_QOSPARDONOTCARE)
        (requirements.getMaxSduSize() <= cube.getMaxSduSize()) ? score++ : score--;

    (requirements.isPartialDelivery() == cube.isPartialDelivery()) ? score++ : score--;

    (requirements.isIncompleteDelivery() == cube.isIncompleteDelivery()) ? score++ : score--;

    (requirements.isForceOrder() == cube.isForceOrder()) ? score++ : score--;

    if (requirements.getMaxAllowGap() != VAL_QOSPARDONOTCARE)
        (requirements.getMaxAllowGap() <= cube.getMaxAllowGap()) ? score++ : score--;

    if (requirements.getDelay() != VAL_QOSPARDONOTCARE)
        (requirements.getDelay() <= cube.getDelay()) ? score++ : score--;

    if (requirements.getJitter() != VAL_QOSPARDONOTCARE)
        (requirements.getJitter() <= cube.getJitter()) ? score++ : score--;

    if (requirements.getCostTime() != VAL_QOSPARDONOTCARE)
        (requirements.getCostTime() <= cube.getCostTime()) ? score++ : score--;

    if (requirements.getCostBits() != VAL_QOSPARDONOTCARE)
        (requirements.getCostBits() <= cube.getCostBits()) ? score++ : score--;

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

    EV << flow.getQosRequirements().getAvgBand() << endl;

    //Always translate management traffic to appropriate management QoSCube
    if (flow.getQosRequirements().compare(QoSReq::MANAGEMENT)) {
        flow.getConnectionId().setQoSId(VAL_MGMTQOSID);
        return true;
    }

    //TODO: Compare QoS Parameters with available QoS cubes
    QoSCubeSet cubes = ResourceAllocator->getQoSCubes();
    //EV << ResourceAllocator->getQoSCubes();

    std::string qosid = VAL_UNDEF_QOSID;
    short score = 0;

    for (QCubeCItem it = cubes.begin(); it != cubes.end(); ++it) {
        short tmpscore = countFeasibilityScore(flow.getQosRequirements(), *it);
//        EV << "QosID: " << it->getQosId()
//           << " tmpscore: " << tmpscore
//           << " score: " << score << endl
//           << " qosid: " << qosid << endl;
        if (score < tmpscore) {
            score = tmpscore;
            qosid = it->getQosId();
        }
    }
    flow.getConnectionId().setQoSId(qosid);
    return qosid.compare(VAL_UNDEF_QOSID) ? true : false;
}

