//
// Copyright © 2014 PRISTINE Consortium (http://ict-pristine.eu)
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

/*
 * @file QoSCube.cc
 * @author Marcel Marek
 * @date Apr 28, 2014
 * @brief
 * @detail
 */
#include "QosCube.h"

const char* STR_DONOTCARE = "do-not-care";
const char* STR_YES = "yes";
const char* STR_NO = "no";

QosCube::QosCube() {
    // TODO Auto-generated constructor stub

}

int QosCube::getAvgBand() const {
    return avgBand;
}

void QosCube::setAvgBand(int avgBand) {
    this->avgBand = avgBand;
}

int QosCube::getAvgSduBand() const {
    return avgSDUBand;
}

void QosCube::setAvgSduBand(int avgSduBand) {
    avgSDUBand = avgSduBand;
}

int QosCube::getBurstDuration() const {
    return burstDuration;
}

void QosCube::setBurstDuration(int burstDuration) {
    this->burstDuration = burstDuration;
}

int QosCube::getBurstPeriod() const {
    return burstPeriod;
}

void QosCube::setBurstPeriod(int burstPeriod) {
    this->burstPeriod = burstPeriod;
}

int QosCube::getDelay() const {
    return delay;
}

void QosCube::setDelay(int delay) {
    this->delay = delay;
}

bool QosCube::isForceOrder() const {
    return forceOrder;
}

void QosCube::setForceOrder(bool forceOrder) {
    this->forceOrder = forceOrder;
}

bool QosCube::isIncompleteDelivery() const {
    return incompleteDeliv;
}

void QosCube::setIncompleteDelivery(bool incompleteDeliv) {
    this->incompleteDeliv = incompleteDeliv;
}

int QosCube::getJitter() const {
    return jitter;
}

void QosCube::setJitter(int jitter) {
    this->jitter = jitter;
}

int QosCube::getMaxAllowGap() const {
    return maxAllowGap;
}

void QosCube::setMaxAllowGap(int maxAllowGap) {
    this->maxAllowGap = maxAllowGap;
}

int QosCube::getMaxSduSize() const {
    return maxSDUsize;
}

void QosCube::setMaxSduSize(int maxSdUsize) {
    maxSDUsize = maxSdUsize;
}

bool QosCube::isPartialDelivery() const {
    return partDeliv;
}

void QosCube::setPartialDelivery(bool partDeliv) {
    this->partDeliv = partDeliv;
}

int QosCube::getPeakBandDuration() const {
    return peakBandDuration;
}

void QosCube::setPeakBandDuration(int peakBandDuration) {
    this->peakBandDuration = peakBandDuration;
}

int QosCube::getPeakSduBandDuration() const {
    return peakSDUBandDuration;
}

void QosCube::setPeakSduBandDuration(int peakSduBandDuration) {
    peakSDUBandDuration = peakSduBandDuration;
}

double QosCube::getUndetectedBitErr() const {
    return undetectedBitErr;
}

void QosCube::setUndetectedBitErr(double undetectedBitErr) {
    this->undetectedBitErr = undetectedBitErr;
}

QosCube::~QosCube() {
    // TODO Auto-generated destructor stub
}

unsigned short QosCube::getQosId() const {
    return qoSId;
}

int QosCube::getCostBits() const {
    return costBits;
}

void QosCube::setCostBits(int costBits) {
    this->costBits = costBits;
}

int QosCube::getCostTime() const {
    return costTime;
}

void QosCube::setCostTime(int costTime) {
    this->costTime = costTime;
}

void QosCube::setQosId(unsigned short qoSId) {
    this->qoSId = qoSId;
}

std::ostream& operator <<(std::ostream& os, const QosCube& cube) {
    if (cube.getQosId())
        os << "QoSCube Id> " << cube.getQosId();
    else
        os << "QoS Parameters List>";

    os << "\n   average BW = ";
    if ( cube.getAvgBand() < 0)
        os << STR_DONOTCARE;
    else
        os << cube.getAvgBand() << " bit/s";

    os   << "\n   average SDU BW = ";
    if (cube.getAvgSduBand() < 0)
        os << STR_DONOTCARE;
    else
        os << cube.getAvgSduBand() << " SDU/s";

    os << "\n   peak BW duration = ";
    if (cube.getPeakBandDuration() < 0)
        os << STR_DONOTCARE;
    else
        os << cube.getPeakBandDuration() << " bit/s";

    os << "\n   peak SDU BW duration = ";
    if ( cube.getPeakSduBandDuration() < 0)
        os << STR_DONOTCARE;
    else
        os << cube.getPeakSduBandDuration() << " SDU/s";

    os << "\n   burst period = ";
    if ( cube.getBurstPeriod() < 0 )
        os << STR_DONOTCARE;
    else
        os << cube.getBurstPeriod() << " usecs";

    os << "\n   burst duration = ";
    if ( cube.getBurstDuration() < 0 )
        os << STR_DONOTCARE;
    else
        os << cube.getBurstDuration() << " usecs";

    os << "\n   undetect. bit errors = ";
    if ( cube.getUndetectedBitErr() < 0 )
        os << STR_DONOTCARE;
    else
        os << cube.getUndetectedBitErr() << "%";

    os << "\n   max SDU Size = ";
    if ( cube.getMaxSduSize() < 0 )
        os << STR_DONOTCARE;
    else
        os << cube.getMaxSduSize() << " B";

    os << "\n   partial delivery = " << (cube.isPartialDelivery() ? STR_YES : STR_NO );

    os << "\n   incomplete delivery = " << (cube.isIncompleteDelivery() ? STR_YES : STR_NO );

    os << "\n   force order = " << (cube.isForceOrder() ? STR_YES : STR_NO );

    os << "\n   max allowed gap = ";
    if ( cube.getMaxAllowGap() < 0 )
        os << STR_DONOTCARE;
    else
        os << cube.getMaxAllowGap() << " SDUs";

    os << "\n   delay = ";
    if ( cube.getDelay() < 0 )
        os << STR_DONOTCARE;
    else
        os << cube.getDelay() << " usecs";

    os << "\n   jitter = ";
    if ( cube.getJitter() < 0 )
        os << STR_DONOTCARE;
    else
        os << cube.getJitter() << " usecs";

    os << "\n   cost-time = ";
    if ( cube.getCostTime() < 0 )
        os << STR_DONOTCARE;
    else
        os << cube.getCostTime() << " $/ms";

    os << "\n   cost-bits = ";
    if ( cube.getCostBits() < 0 )
        os << STR_DONOTCARE;
    else
        os << cube.getCostBits() << " $/Mb";

    return os;
}

short QosCube::countFeasibilityScore(const QosCube templ) const {
    short score = 0;

    /*
    EV << "AvgBw> \t" << getAvgBand() << " / " << templ.getAvgBand() << endl;
    EV << "AvgSduBw> \t" << getAvgSduBand() << " / " << templ.getAvgSduBand() << endl;
    EV << "PeakAvgBw> \t" << getPeakBandDuration() << " / " << templ.getPeakBandDuration() << endl;
    EV << "PeakAvgSduBw> \t" << getPeakSduBandDuration() << " / " << templ.getPeakSduBandDuration() << endl;
    EV << "BurstPeriod> \t" << getBurstPeriod() << " / " << templ.getBurstPeriod() << endl;
    EV << "BurstDuration> \t" << getBurstDuration() << " / " << templ.getBurstDuration() << endl;
    EV << "UndetecBitErr> \t" << getUndetectedBitErr() << " / " << templ.getUndetectedBitErr() << endl;
    EV << "MaxSduSize> \t" << getMaxSduSize() << " / " << templ.getMaxSduSize() << endl;
    EV << "PartiDeliv> \t" << isPartialDelivery() << " / " << templ.isPartialDelivery() << endl;
    EV << "IncomDeliv> \t" << isIncompleteDelivery() << " / " << templ.isIncompleteDelivery() << endl;
    EV << "ForceOrder> \t" << isForceOrder() << " / " << templ.isForceOrder() << endl;
    EV << "MaxAllowGap> \t" << getMaxAllowGap() << " / " << templ.getMaxAllowGap() << endl;
    EV << "Delay> \t" << getDelay() << " / " << templ.getDelay() << endl;
    EV << "Jitter> \t" << getJitter() << " / " << templ.getJitter() << endl;
    EV << "CostTime> \t" << getCostTime() << " / " << templ.getCostTime() << endl;
    EV << "CostBits> \t" << getCostBits() << " / " << templ.getCostBits() << endl;
    */

    if (getAvgBand() != VAL_QOSPARDONOTCARE)
        (getAvgBand() <= templ.getAvgBand()) ? score++ : score--;

    if (getAvgSduBand() != VAL_QOSPARDONOTCARE)
        (getAvgSduBand() <= templ.getAvgSduBand()) ? score++ : score--;

    if (getPeakBandDuration() != VAL_QOSPARDONOTCARE)
        (getPeakBandDuration() <= templ.getPeakBandDuration()) ? score++ : score--;

    if (getPeakSduBandDuration() != VAL_QOSPARDONOTCARE)
        (getPeakSduBandDuration() <= templ.getPeakSduBandDuration()) ? score++ : score--;

    if (getBurstPeriod() != VAL_QOSPARDONOTCARE)
        (getBurstPeriod() <= templ.getBurstPeriod()) ? score++ : score--;

    if (getBurstDuration() != VAL_QOSPARDONOTCARE)
        (getBurstDuration() <= templ.getBurstDuration()) ? score++ : score--;

    if (getUndetectedBitErr() != VAL_QOSPARDONOTCARE)
        (getUndetectedBitErr() <= templ.getUndetectedBitErr()) ? score++ : score--;

    if (getMaxSduSize() != VAL_QOSPARDONOTCARE)
        (getMaxSduSize() <= templ.getMaxSduSize()) ? score++ : score--;

    (isPartialDelivery() == templ.isPartialDelivery()) ? score++ : score--;

    (isIncompleteDelivery() == templ.isIncompleteDelivery()) ? score++ : score--;

    (isForceOrder() == templ.isForceOrder()) ? score++ : score--;

    if (getMaxAllowGap() != VAL_QOSPARDONOTCARE)
        (getMaxAllowGap() <= templ.getMaxAllowGap()) ? score++ : score--;

    if (getDelay() != VAL_QOSPARDONOTCARE)
        (getDelay() <= templ.getDelay()) ? score++ : score--;

    if (getJitter() != VAL_QOSPARDONOTCARE)
        (getJitter() <= templ.getJitter()) ? score++ : score--;

    if (getCostTime() != VAL_QOSPARDONOTCARE)
        (getCostTime() <= templ.getCostTime()) ? score++ : score--;

    if (getCostBits() != VAL_QOSPARDONOTCARE)
        (getCostBits() <= templ.getCostBits()) ? score++ : score--;

    return score;
}
