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

#include <QoSMinComparer.h>

Define_Module(QoSMinComparer);

void QoSMinComparer::initialize() {
    mHops = par("maxHops").longValue();
    mlBandw = par("mulBandw").longValue();
}


bool QoSMinComparer::isValid(const QoSCube &upperQoS, const QoSCube &lowerQoS) {
    if(upperQoS.getAvgBand()*mlBandw > lowerQoS.getAvgBand()) return false;
    if(upperQoS.getAvgSduBand()*mlBandw > lowerQoS.getAvgSduBand()) return false;
    if(upperQoS.getPeakBandDuration()*mlBandw > lowerQoS.getPeakBandDuration()) return false;
    if(upperQoS.getPeakSduBandDuration()*mlBandw > lowerQoS.getPeakSduBandDuration()) return false;
    if(upperQoS.getBurstPeriod()*mlBandw > lowerQoS.getBurstPeriod()) return false;
    if(upperQoS.getBurstDuration()*mlBandw > lowerQoS.getBurstDuration()) return false;
    if(1-pow(1-upperQoS.getUndetectedBitErr(), mHops) > lowerQoS.getUndetectedBitErr()) return false;
    if(1-pow(1-upperQoS.getPduDropProbability(), mHops) > lowerQoS.getPduDropProbability()) return false;
    if(upperQoS.getMaxSduSize() > lowerQoS.getMaxSduSize()) return false;
    if(!upperQoS.isPartialDelivery() && lowerQoS.isPartialDelivery()) return false;
    if(!upperQoS.isIncompleteDelivery() && lowerQoS.isIncompleteDelivery()) return false;
    if(upperQoS.isForceOrder() && lowerQoS.isForceOrder()) return false;
    if(upperQoS.getMaxAllowGap() < lowerQoS.getMaxAllowGap()) return false;
    if(upperQoS.getDelay() < lowerQoS.getDelay()*mHops) return false;
    if(upperQoS.getJitter() < lowerQoS.getJitter()) return false;
    if(upperQoS.getCostTime() < lowerQoS.getCostTime()*mHops) return false;
    if(upperQoS.getCostBits() < lowerQoS.getCostBits()*mHops) return false;

    return true;
}

void QoSMinComparer::setRequirements(Flow * lowerflow, const QoSCube &upperQoS) {
    QoSReq qosParams(upperQoS.getAvgBand()*mlBandw, upperQoS.getAvgSduBand()*mlBandw,
            upperQoS.getPeakBandDuration()*mlBandw,upperQoS.getPeakSduBandDuration()*mlBandw,
            upperQoS.getBurstPeriod()*mlBandw, upperQoS.getBurstDuration()*mlBandw,
            1-pow(1-upperQoS.getUndetectedBitErr(), mHops),1-pow(1-upperQoS.getPduDropProbability(), mHops),
            upperQoS.getMaxSduSize(), upperQoS.isPartialDelivery(), upperQoS.isIncompleteDelivery(), upperQoS.isForceOrder(),
            upperQoS.getMaxAllowGap(), upperQoS.getDelay()/mHops, upperQoS.getJitter(),
            upperQoS.getCostTime()/mHops, upperQoS.getCostBits()/mHops);
    lowerflow->setQosRequirements(qosParams);
}
