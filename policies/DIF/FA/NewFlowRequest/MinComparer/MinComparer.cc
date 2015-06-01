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

#include <MinComparer.h>

Define_Module(MinComparer);

bool MinComparer::isFeasibility(const QoSReq requirements, const QoSCube cube) const {
    if (requirements.getAvgBand() != VAL_QOSPARDONOTCARE && requirements.getAvgBand() > cube.getAvgBand())
        return false;

    if (requirements.getAvgSduBand() != VAL_QOSPARDONOTCARE && requirements.getAvgSduBand() > cube.getAvgSduBand())
        return false;

    if (requirements.getPeakBandDuration() != VAL_QOSPARDONOTCARE && requirements.getPeakBandDuration() > cube.getPeakBandDuration())
        return false;

    if (requirements.getPeakSduBandDuration() != VAL_QOSPARDONOTCARE && requirements.getPeakSduBandDuration() > cube.getPeakSduBandDuration())
        return false;

    if (requirements.getBurstPeriod() != VAL_QOSPARDONOTCARE && requirements.getBurstPeriod() > cube.getBurstPeriod())
        return false;

    if (requirements.getBurstDuration() != VAL_QOSPARDONOTCARE && requirements.getBurstDuration() > cube.getBurstDuration())
        return false;

    if (requirements.getUndetectedBitErr() != VAL_QOSPARDONOTCARE && requirements.getUndetectedBitErr() > cube.getUndetectedBitErr())
        return false;

    if (requirements.getPduDropProbability() != VAL_QOSPARDONOTCARE && requirements.getPduDropProbability() > cube.getPduDropProbability())
        return false;

    if (requirements.getMaxSduSize() != VAL_QOSPARDONOTCARE && requirements.getMaxSduSize() > cube.getMaxSduSize())
        return false;

    if(!cube.isPartialDelivery() && requirements.isPartialDelivery())
        return false;

    if(!cube.isIncompleteDelivery() && requirements.isIncompleteDelivery())
        return false;

    if(!cube.isForceOrder() && requirements.isForceOrder())
        return false;

    if (requirements.getMaxAllowGap() != VAL_QOSPARDONOTCARE && requirements.getMaxAllowGap() > cube.getMaxAllowGap())
        return false;

    if (requirements.getDelay() != VAL_QOSPARDONOTCARE && requirements.getDelay() > cube.getDelay())
        return false;

    if (requirements.getJitter() != VAL_QOSPARDONOTCARE && requirements.getJitter() > cube.getJitter())
        return false;

    if (requirements.getCostTime() != VAL_QOSPARDONOTCARE && requirements.getCostTime() > cube.getCostTime())
        return false;

    if (requirements.getCostBits() != VAL_QOSPARDONOTCARE && requirements.getCostBits() > cube.getCostBits())
        return false;

    return true;

}
bool MinComparer::run(Flow& flow) {
    Enter_Method("invokeNewFlowRequestPolicy()");
    //Is flow policy acceptable
    std::string apname = flow.getSrcApni().getApn().getName();

    //FIXME: Vesely - Simulate error and DTCP flag better
    if ( apname.find("Err") != std::string::npos) {
        return false;
    }

    //Always translate management traffic to appropriate management QoSCube
    if (flow.isManagementFlow()) {
        flow.getConnectionId().setQoSId(VAL_MGMTQOSID);
        return true;
    }

    //TODO: Compare QoS Parameters with available QoS cubes
    QoSCubeSet cubes = ResourceAllocator->getQoSCubes();
    //EV << ResourceAllocator->getQoSCubes();

    std::string qosid = VAL_UNDEF_QOSID;
    //XXX: Vesely->Gaixas: Please, check following cost variable value and overall functionality of this comparer
    double cost = DBL_MAX;

    for (QCubeCItem it = cubes.begin(); it != cubes.end(); ++it) {
        if( isFeasibility(flow.getQosRequirements(), *it) ){
            double tmpscore = flow.getQosRequirements().getCostBits();
            if (cost > tmpscore) {
                cost = tmpscore;
                qosid = it->getQosId();
            }
        }
    }
    flow.getConnectionId().setQoSId(qosid);
    return qosid.compare(VAL_UNDEF_QOSID) ? true : false;

}

