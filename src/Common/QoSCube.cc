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
#include "QoSCube.h"

const char* STR_DONOTCARE = "do-not-care";
const char* STR_YES = "yes";
const char* STR_NO = "no";

QoSCube::QoSCube() {
    // TODO Auto-generated constructor stub

}

int QoSCube::getAvgBand() const {
    return avgBand;
}

void QoSCube::setAvgBand(int avgBand) {
    this->avgBand = avgBand;
}

int QoSCube::getAvgSduBand() const {
    return avgSDUBand;
}

void QoSCube::setAvgSduBand(int avgSduBand) {
    avgSDUBand = avgSduBand;
}

int QoSCube::getBurstDuration() const {
    return burstDuration;
}

void QoSCube::setBurstDuration(int burstDuration) {
    this->burstDuration = burstDuration;
}

int QoSCube::getBurstPeriod() const {
    return burstPeriod;
}

void QoSCube::setBurstPeriod(int burstPeriod) {
    this->burstPeriod = burstPeriod;
}

int QoSCube::getDelay() const {
    return delay;
}

void QoSCube::setDelay(int delay) {
    this->delay = delay;
}

bool QoSCube::isForceOrder() const {
    return forceOrder;
}

void QoSCube::setForceOrder(bool forceOrder) {
    this->forceOrder = forceOrder;
}

bool QoSCube::isIncompleteDelivery() const {
    return incompleteDeliv;
}

void QoSCube::setIncompleteDelivery(bool incompleteDeliv) {
    this->incompleteDeliv = incompleteDeliv;
}

int QoSCube::getJitter() const {
    return jitter;
}

void QoSCube::setJitter(int jitter) {
    this->jitter = jitter;
}

int QoSCube::getMaxAllowGap() const {
    return maxAllowGap;
}

void QoSCube::setMaxAllowGap(int maxAllowGap) {
    this->maxAllowGap = maxAllowGap;
}

int QoSCube::getMaxSduSize() const {
    return maxSDUsize;
}

void QoSCube::setMaxSduSize(int maxSdUsize) {
    maxSDUsize = maxSdUsize;
}

bool QoSCube::isPartialDelivery() const {
    return partDeliv;
}

void QoSCube::setPartialDelivery(bool partDeliv) {
    this->partDeliv = partDeliv;
}

int QoSCube::getPeakBandDuration() const {
    return peakBandDuration;
}

void QoSCube::setPeakBandDuration(int peakBandDuration) {
    this->peakBandDuration = peakBandDuration;
}

int QoSCube::getPeakSduBandDuration() const {
    return peakSDUBandDuration;
}

void QoSCube::setPeakSduBandDuration(int peakSduBandDuration) {
    peakSDUBandDuration = peakSduBandDuration;
}

double QoSCube::getUndetectedBitErr() const {
    return undetectedBitErr;
}

void QoSCube::setUndetectedBitErr(double undetectedBitErr) {
    this->undetectedBitErr = undetectedBitErr;
}

QoSCube::~QoSCube() {
    // TODO Auto-generated destructor stub
}

unsigned short QoSCube::getQosId() const {
    return qoSId;
}

int QoSCube::getCostBits() const {
    return costBits;
}

void QoSCube::setCostBits(int costBits) {
    this->costBits = costBits;
}

int QoSCube::getCostTime() const {
    return costTime;
}

void QoSCube::setCostTime(int costTime) {
    this->costTime = costTime;
}

void QoSCube::setQosId(unsigned short qoSId) {
    this->qoSId = qoSId;
}

std::ostream& operator <<(std::ostream& os, const QoSCube& cube) {
    return os << cube.info();
}

short QoSCube::countFeasibilityScore(const QoSCube templ) const {
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

std::string QoSCube::info() const {
    std::ostringstream os;

    if (this->getQosId())
        os << "QoSCube Id> " << this->getQosId();
    else
        os << "QoS Parameters List>";

    os << "\n   average BW = ";
    if ( this->getAvgBand() < 0)
        os << STR_DONOTCARE;
    else
        os << this->getAvgBand() << " bit/s";

    os   << "\n   average SDU BW = ";
    if (this->getAvgSduBand() < 0)
        os << STR_DONOTCARE;
    else
        os << this->getAvgSduBand() << " SDU/s";

    os << "\n   peak BW duration = ";
    if (this->getPeakBandDuration() < 0)
        os << STR_DONOTCARE;
    else
        os << this->getPeakBandDuration() << " bit/s";

    os << "\n   peak SDU BW duration = ";
    if ( this->getPeakSduBandDuration() < 0)
        os << STR_DONOTCARE;
    else
        os << this->getPeakSduBandDuration() << " SDU/s";

    os << "\n   burst period = ";
    if ( this->getBurstPeriod() < 0 )
        os << STR_DONOTCARE;
    else
        os << this->getBurstPeriod() << " usecs";

    os << "\n   burst duration = ";
    if ( this->getBurstDuration() < 0 )
        os << STR_DONOTCARE;
    else
        os << this->getBurstDuration() << " usecs";

    os << "\n   undetect. bit errors = ";
    if ( this->getUndetectedBitErr() < 0 )
        os << STR_DONOTCARE;
    else
        os << this->getUndetectedBitErr() << "%";

    os << "\n   max SDU Size = ";
    if ( this->getMaxSduSize() < 0 )
        os << STR_DONOTCARE;
    else
        os << this->getMaxSduSize() << " B";

    os << "\n   partial delivery = " << (this->isPartialDelivery() ? STR_YES : STR_NO );

    os << "\n   incomplete delivery = " << (this->isIncompleteDelivery() ? STR_YES : STR_NO );

    os << "\n   force order = " << (this->isForceOrder() ? STR_YES : STR_NO );

    os << "\n   max allowed gap = ";
    if ( this->getMaxAllowGap() < 0 )
        os << STR_DONOTCARE;
    else
        os << this->getMaxAllowGap() << " SDUs";

    os << "\n   delay = ";
    if ( this->getDelay() < 0 )
        os << STR_DONOTCARE;
    else
        os << this->getDelay() << " usecs";

    os << "\n   jitter = ";
    if ( this->getJitter() < 0 )
        os << STR_DONOTCARE;
    else
        os << this->getJitter() << " usecs";

    os << "\n   cost-time = ";
    if ( this->getCostTime() < 0 )
        os << STR_DONOTCARE;
    else
        os << this->getCostTime() << " $/ms";

    os << "\n   cost-bits = ";
    if ( this->getCostBits() < 0 )
        os << STR_DONOTCARE;
    else
        os << this->getCostBits() << " $/Mb";
    return os.str();
}