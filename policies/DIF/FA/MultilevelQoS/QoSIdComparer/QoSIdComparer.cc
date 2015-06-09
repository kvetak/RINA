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

#include <QoSIdComparer.h>

Define_Module(QoSIdComparer);

void QoSIdComparer::initialize() {
    mHops = par("maxHops").longValue();
    mlBandw = par("mulBandw").longValue();
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
