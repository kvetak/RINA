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


#include "DIF/FA/NewFlowRequest/MinComparer/MinComparer.h"

Define_Module(MinComparer);

bool MinComparer::isFeasibility(const QoSReq requirements, const QoSCube cube) const {

  //  std::cout << requirements.getDelay() << "/" << requirements.getPduDropProbability() << " vs " << cube.getDelay() << "/" << cube.getPduDropProbability()<<endl;

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

    if (requirements.getUndetectedBitErr() != VAL_QOSPARDONOTCARE && requirements.getUndetectedBitErr() < cube.getUndetectedBitErr())
        return false;

    if (requirements.getPduDropProbability() != VAL_QOSPARDONOTCARE && requirements.getPduDropProbability() < cube.getPduDropProbability())
        return false;

    if (requirements.getMaxSduSize() != VAL_QOSPARDONOTCARE && requirements.getMaxSduSize() > cube.getMaxSduSize())
        return false;

    if(!cube.isPartialDelivery() && requirements.isPartialDelivery())
        return false;

    if(!cube.isIncompleteDelivery() && requirements.isIncompleteDelivery())
        return false;

    if(!cube.isForceOrder() && requirements.isForceOrder())
        return false;

    if (requirements.getMaxAllowGap() != VAL_QOSPARDONOTCARE && requirements.getMaxAllowGap() < cube.getMaxAllowGap())
        return false;

    if (requirements.getDelay() != VAL_QOSPARDONOTCARE && requirements.getDelay() < cube.getDelay())
        return false;

    if (requirements.getJitter() != VAL_QOSPARDONOTCARE && requirements.getJitter() < cube.getJitter())
        return false;

    if (requirements.getCostTime() != VAL_QOSPARDONOTCARE && requirements.getCostTime() < cube.getCostTime())
        return false;

    if (requirements.getCostBits() != VAL_QOSPARDONOTCARE && requirements.getCostBits() < cube.getCostBits())
        return false;
   // std::cout << "OK" << endl;
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
        flow.setQosCube(QoSCube::MANAGEMENT);
        return true;
    }

    //TODO: Compare QoS Parameters with available QoS cubes
    QoSCubeSet cubes = ResourceAllocator->getQoSCubes();
    //EV << ResourceAllocator->getQoSCubes();

    std::string qosid = VAL_UNDEF_QOSID;
    //XXX: Vesely->Gaixas: Please, check following cost variable value and overall functionality of this comparer
    double cost = DBL_MAX;
    QoSCube qs;

    for (QCubeCItem it = cubes.begin(); it != cubes.end(); ++it) {
        if(it->getQosId() == VAL_MGMTQOSID) { continue; }

        if( isFeasibility(flow.getQosRequirements(), *it) ){
            double tmpscore = it->getCostBits();
            if (cost > tmpscore) {
                cost = tmpscore;
                qosid = it->getQosId();
                qs = *it;
            }
        }
    }
    flow.getConnectionId().setQoSId(qosid);
    flow.setQosCube(qs);
    return qosid.compare(VAL_UNDEF_QOSID) ? true : false;

}

