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
 * @file QoSReq.cc
 * @author Marcel Marek
 * @date May 1, 2015
 * @brief
 * @detail
 */
#include "QoSReq.h"

const char* STR_REQDONOTCARE = "do-not-care";
const char* STR_REQYES = "yes";
const char* STR_REQNO = "no";
const int   VAL_DEFQOSREQ = 0;

QoSReq::QoSReq() : qoSId(VAL_DEFQOSREQ),
        avgBand(VAL_DEFQOSREQ), avgSDUBand(VAL_DEFQOSREQ), peakBandDuration(VAL_DEFQOSREQ), peakSDUBandDuration(VAL_DEFQOSREQ),
        burstPeriod(VAL_DEFQOSREQ), burstDuration(VAL_DEFQOSREQ), undetectedBitErr(VAL_DEFQOSREQ), pduDropProbability(VAL_DEFQOSREQ), maxSDUsize(VAL_DEFQOSREQ),
        partDeliv(false), incompleteDeliv(false), forceOrder(false),
        maxAllowGap(VAL_DEFQOSREQ), delay(VAL_DEFQOSREQ), jitter(VAL_DEFQOSREQ),
        costTime(VAL_DEFQOSREQ), costBits(VAL_DEFQOSREQ)
{
}

int QoSReq::getAvgBand() const {
    return avgBand;
}

void QoSReq::setAvgBand(int avgBand) {
    this->avgBand = avgBand;
}

int QoSReq::getAvgSduBand() const {
    return avgSDUBand;
}

void QoSReq::setAvgSduBand(int avgSduBand) {
    avgSDUBand = avgSduBand;
}

int QoSReq::getBurstDuration() const {
    return burstDuration;
}

void QoSReq::setBurstDuration(int burstDuration) {
    this->burstDuration = burstDuration;
}

int QoSReq::getBurstPeriod() const {
    return burstPeriod;
}

void QoSReq::setBurstPeriod(int burstPeriod) {
    this->burstPeriod = burstPeriod;
}

int QoSReq::getDelay() const {
    return delay;
}

void QoSReq::setDelay(int delay) {
    this->delay = delay;
}

bool QoSReq::isForceOrder() const {
    return forceOrder;
}

void QoSReq::setForceOrder(bool forceOrder) {
    this->forceOrder = forceOrder;
}

bool QoSReq::isIncompleteDelivery() const {
    return incompleteDeliv;
}

void QoSReq::setIncompleteDelivery(bool incompleteDeliv) {
    this->incompleteDeliv = incompleteDeliv;
}

int QoSReq::getJitter() const {
    return jitter;
}

void QoSReq::setJitter(int jitter) {
    this->jitter = jitter;
}

int QoSReq::getMaxAllowGap() const {
    return maxAllowGap;
}

void QoSReq::setMaxAllowGap(int maxAllowGap) {
    this->maxAllowGap = maxAllowGap;
}

int QoSReq::getMaxSduSize() const {
    return maxSDUsize;
}

void QoSReq::setMaxSduSize(int maxSdUsize) {
    maxSDUsize = maxSdUsize;
}

bool QoSReq::isPartialDelivery() const {
    return partDeliv;
}

void QoSReq::setPartialDelivery(bool partDeliv) {
    this->partDeliv = partDeliv;
}

int QoSReq::getPeakBandDuration() const {
    return peakBandDuration;
}

void QoSReq::setPeakBandDuration(int peakBandDuration) {
    this->peakBandDuration = peakBandDuration;
}

int QoSReq::getPeakSduBandDuration() const {
    return peakSDUBandDuration;
}

void QoSReq::setPeakSduBandDuration(int peakSduBandDuration) {
    peakSDUBandDuration = peakSduBandDuration;
}

double QoSReq::getUndetectedBitErr() const {
    return undetectedBitErr;
}

void QoSReq::setUndetectedBitErr(double undetectedBitErr) {
    this->undetectedBitErr = undetectedBitErr;
}

QoSReq::~QoSReq() {
    qoSId = VAL_DEFQOSREQ;

    avgBand = VAL_DEFQOSREQ;
    avgSDUBand = VAL_DEFQOSREQ;             //Average SDU bandwidth (measured in SDUs/sec)
    peakBandDuration = VAL_DEFQOSREQ;       //Peak bandwidth-duration (measured in bits/sec);
    peakSDUBandDuration = VAL_DEFQOSREQ;    //Peak SDU bandwidth-duration (measured in SDUs/sec);
    burstPeriod = VAL_DEFQOSREQ;            //Burst period measured in useconds
    burstDuration = VAL_DEFQOSREQ;          //Burst duration, measured in useconds fraction of Burst Period
    undetectedBitErr = VAL_DEFQOSREQ;    //Undetected bit error rate measured as a probability
    maxSDUsize = VAL_DEFQOSREQ;             //MaxSDUSize measured in bytes
    partDeliv = false;             //Partial Delivery - Can SDUs be delivered in pieces rather than all at once?
    incompleteDeliv = false;       //Incomplete Delivery - Can SDUs with missing pieces be delivered?
    forceOrder = false;            //Must SDUs be delivered in-order bits
    maxAllowGap = VAL_DEFQOSREQ;   //Max allowable gap in SDUs, (a gap of N SDUs is considered the same as all SDUs delivered, i.e. a gap of N is a "don't care.")
    delay = VAL_DEFQOSREQ;                  //Delay in usecs
    jitter = VAL_DEFQOSREQ;                 //Jitter in usecs
    costTime = VAL_DEFQOSREQ;               //measured in $/ms
    costBits = VAL_DEFQOSREQ;               //measured in $/Mb
}

unsigned short QoSReq::getQosId() const {
    return qoSId;
}

double QoSReq::getCostBits() const {
    return costBits;
}

void QoSReq::setCostBits(double costBits) {
    this->costBits = costBits;
}

double QoSReq::getCostTime() const {
    return costTime;
}

void QoSReq::setCostTime(double costTime) {
    this->costTime = costTime;
}
double QoSReq::getATime() const {
    return aTime;
}

void QoSReq::setATime(double aTime) {
    this->aTime = aTime;
}

void QoSReq::setQosId(unsigned short qoSId) {
    this->qoSId = qoSId;
}

std::ostream& operator <<(std::ostream& os, const QoSReq& cube) {
    return os << cube.info();
}

short QoSReq::countFeasibilityScore(const QoSCube other) const {
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
        (getAvgBand() <= other.getAvgBand()) ? score++ : score--;

    if (getAvgSduBand() != VAL_QOSPARDONOTCARE)
        (getAvgSduBand() <= other.getAvgSduBand()) ? score++ : score--;

    if (getPeakBandDuration() != VAL_QOSPARDONOTCARE)
        (getPeakBandDuration() <= other.getPeakBandDuration()) ? score++ : score--;

    if (getPeakSduBandDuration() != VAL_QOSPARDONOTCARE)
        (getPeakSduBandDuration() <= other.getPeakSduBandDuration()) ? score++ : score--;

    if (getBurstPeriod() != VAL_QOSPARDONOTCARE)
        (getBurstPeriod() <= other.getBurstPeriod()) ? score++ : score--;

    if (getBurstDuration() != VAL_QOSPARDONOTCARE)
        (getBurstDuration() <= other.getBurstDuration()) ? score++ : score--;

    if (getUndetectedBitErr() != VAL_QOSPARDONOTCARE)
        (getUndetectedBitErr() <= other.getUndetectedBitErr()) ? score++ : score--;

    if (getPduDropProbability() != VAL_QOSPARDONOTCARE)
        (getPduDropProbability() <= other.getPduDropProbability()) ? score++ : score--;

    if (getMaxSduSize() != VAL_QOSPARDONOTCARE)
        (getMaxSduSize() <= other.getMaxSduSize()) ? score++ : score--;

    (isPartialDelivery() == other.isPartialDelivery()) ? score++ : score--;

    (isIncompleteDelivery() == other.isIncompleteDelivery()) ? score++ : score--;

    (isForceOrder() == other.isForceOrder()) ? score++ : score--;

    if (getMaxAllowGap() != VAL_QOSPARDONOTCARE)
        (getMaxAllowGap() <= other.getMaxAllowGap()) ? score++ : score--;

    if (getDelay() != VAL_QOSPARDONOTCARE)
        (getDelay() <= other.getDelay()) ? score++ : score--;

    if (getJitter() != VAL_QOSPARDONOTCARE)
        (getJitter() <= other.getJitter()) ? score++ : score--;

    if (getCostTime() != VAL_QOSPARDONOTCARE)
        (getCostTime() <= other.getCostTime()) ? score++ : score--;

    if (getCostBits() != VAL_QOSPARDONOTCARE)
        (getCostBits() <= other.getCostBits()) ? score++ : score--;

    if (getATime() != VAL_QOSPARDONOTCARE)
            (getATime() <= other.getATime()) ? score++ : score--;

    return score;
}


short QoSReq::countFeasibilityScore(const QoSReq other) const {
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
        (getAvgBand() <= other.getAvgBand()) ? score++ : score--;

    if (getAvgSduBand() != VAL_QOSPARDONOTCARE)
        (getAvgSduBand() <= other.getAvgSduBand()) ? score++ : score--;

    if (getPeakBandDuration() != VAL_QOSPARDONOTCARE)
        (getPeakBandDuration() <= other.getPeakBandDuration()) ? score++ : score--;

    if (getPeakSduBandDuration() != VAL_QOSPARDONOTCARE)
        (getPeakSduBandDuration() <= other.getPeakSduBandDuration()) ? score++ : score--;

    if (getBurstPeriod() != VAL_QOSPARDONOTCARE)
        (getBurstPeriod() <= other.getBurstPeriod()) ? score++ : score--;

    if (getBurstDuration() != VAL_QOSPARDONOTCARE)
        (getBurstDuration() <= other.getBurstDuration()) ? score++ : score--;

    if (getUndetectedBitErr() != VAL_QOSPARDONOTCARE)
        (getUndetectedBitErr() <= other.getUndetectedBitErr()) ? score++ : score--;

    if (getPduDropProbability() != VAL_QOSPARDONOTCARE)
        (getPduDropProbability() <= other.getPduDropProbability()) ? score++ : score--;

    if (getMaxSduSize() != VAL_QOSPARDONOTCARE)
        (getMaxSduSize() <= other.getMaxSduSize()) ? score++ : score--;

    (isPartialDelivery() == other.isPartialDelivery()) ? score++ : score--;

    (isIncompleteDelivery() == other.isIncompleteDelivery()) ? score++ : score--;

    (isForceOrder() == other.isForceOrder()) ? score++ : score--;

    if (getMaxAllowGap() != VAL_QOSPARDONOTCARE)
        (getMaxAllowGap() <= other.getMaxAllowGap()) ? score++ : score--;

    if (getDelay() != VAL_QOSPARDONOTCARE)
        (getDelay() <= other.getDelay()) ? score++ : score--;

    if (getJitter() != VAL_QOSPARDONOTCARE)
        (getJitter() <= other.getJitter()) ? score++ : score--;

    if (getCostTime() != VAL_QOSPARDONOTCARE)
        (getCostTime() <= other.getCostTime()) ? score++ : score--;

    if (getCostBits() != VAL_QOSPARDONOTCARE)
        (getCostBits() <= other.getCostBits()) ? score++ : score--;

    if (getATime() != VAL_QOSPARDONOTCARE)
            (getATime() <= other.getATime()) ? score++ : score--;

    return score;
}

bool QoSReq::isFeasibility(const QoSCube other) const {
    if (getAvgBand() != VAL_QOSPARDONOTCARE && getAvgBand() > other.getAvgBand())
        return false;

    if (getAvgSduBand() != VAL_QOSPARDONOTCARE && getAvgSduBand() > other.getAvgSduBand())
        return false;

    if (getPeakBandDuration() != VAL_QOSPARDONOTCARE && getPeakBandDuration() > other.getPeakBandDuration())
        return false;

    if (getPeakSduBandDuration() != VAL_QOSPARDONOTCARE && getPeakSduBandDuration() > other.getPeakSduBandDuration())
        return false;

    if (getBurstPeriod() != VAL_QOSPARDONOTCARE && getBurstPeriod() > other.getBurstPeriod())
        return false;

    if (getBurstDuration() != VAL_QOSPARDONOTCARE && getBurstDuration() > other.getBurstDuration())
        return false;

    if (getUndetectedBitErr() != VAL_QOSPARDONOTCARE && getUndetectedBitErr() > other.getUndetectedBitErr())
        return false;

    if (getPduDropProbability() != VAL_QOSPARDONOTCARE && getPduDropProbability() > other.getPduDropProbability())
        return false;

    if (getMaxSduSize() != VAL_QOSPARDONOTCARE && getMaxSduSize() > other.getMaxSduSize())
        return false;

    if(!other.isPartialDelivery() && isPartialDelivery())
        return false;

    if(!other.isIncompleteDelivery() && isIncompleteDelivery())
        return false;

    if(!other.isForceOrder() && isForceOrder())
        return false;

    if (getMaxAllowGap() != VAL_QOSPARDONOTCARE && getMaxAllowGap() > other.getMaxAllowGap())
        return false;

    if (getDelay() != VAL_QOSPARDONOTCARE && getDelay() > other.getDelay())
        return false;

    if (getJitter() != VAL_QOSPARDONOTCARE && getJitter() > other.getJitter())
        return false;

    if (getCostTime() != VAL_QOSPARDONOTCARE && getCostTime() > other.getCostTime())
        return false;

    if (getCostBits() != VAL_QOSPARDONOTCARE && getCostBits() > other.getCostBits())
        return false;

    if (getATime() != VAL_QOSPARDONOTCARE && getATime() > other.getATime())
        return false;

    return true;
}

bool QoSReq::isDTCPNeeded()const {
  return isPartialDelivery() || isForceOrder() || isIncompleteDelivery() || avgBand >= 0;
}

double QoSReq::getPduDropProbability() const {
    return pduDropProbability;
}

void QoSReq::setPduDropProbability(double pduDropProbability) {
    this->pduDropProbability = pduDropProbability;
}

std::string QoSReq::info() const {
    std::ostringstream os;

    if (this->getQosId())
        os << "QoSReq Id> " << this->getQosId();
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

    os << "\n   PDU dropping probability = ";
    if ( this->getPduDropProbability() < 0 )
        os << STR_DONOTCARE;
    else
        os << this->getPduDropProbability() << "%";

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

    os << "\n   A-Time = ";
    if ( this->getATime() < 0 )
        os << STR_DONOTCARE;
    else
        os << this->getATime() << "ms";


    return os.str();
}

