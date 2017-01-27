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

/*
 * @file QoSReq.cc
 * @author Marcel Marek
 * @date May 1, 2015
 * @brief
 * @detail
 */
#include "Common/QoSReq.h"

const char* STR_REQDONOTCARE = "do-not-care";
const char* STR_REQYES = "yes";
const char* STR_REQNO = "no";
const int   VAL_DEFQOSREQ = -1;

QoSReq::QoSReq() :
        avgBand(VAL_DEFQOSREQ), avgSDUBand(VAL_DEFQOSREQ), peakBandDuration(VAL_DEFQOSREQ), peakSDUBandDuration(VAL_DEFQOSREQ),
        burstPeriod(VAL_DEFQOSREQ), burstDuration(VAL_DEFQOSREQ), undetectedBitErr(VAL_DEFQOSREQ), pduDropProbability(VAL_DEFQOSREQ), maxSDUsize(VAL_DEFQOSREQ),
        partDeliv(false), incompleteDeliv(false), forceOrder(false),
        maxAllowGap(VAL_DEFQOSREQ), delay(VAL_DEFQOSREQ), jitter(VAL_DEFQOSREQ),
        costTime(VAL_DEFQOSREQ), costBits(VAL_DEFQOSREQ)
{
}

QoSReq::QoSReq(int tavgBand, int tavgSDUBand, int tpeakBandDuration,
        int tpeakSDUBandDuration, int tburstPeriod, int tburstDuration,
        double tundetectedBitErr, double tpduDropProbab, int tmaxSDUsize,
        bool tpartDeliv, bool tincompleteDeliv, bool tforceOrder,
        unsigned int tmaxAllowGap, int tdelay, int tjitter, int tcostTime,
        int tcostBits) {
    avgBand = tavgBand;
    if (avgBand < 0)
        avgBand = VAL_QOSPARDONOTCARE;
    avgSDUBand = tavgSDUBand;
    if (avgSDUBand < 0)
        avgSDUBand = VAL_QOSPARDONOTCARE;
    peakBandDuration = tpeakBandDuration;
    if (peakBandDuration < 0)
        peakBandDuration = VAL_QOSPARDONOTCARE;
    peakSDUBandDuration = tpeakSDUBandDuration;
    if (peakSDUBandDuration < 0)
        peakSDUBandDuration = VAL_QOSPARDONOTCARE;
    burstPeriod = tburstPeriod;
    if (burstPeriod < 0)
        burstPeriod = VAL_QOSPARDONOTCARE;
    burstDuration = tburstDuration;
    if (burstDuration < 0)
        burstDuration = VAL_QOSPARDONOTCARE;
    undetectedBitErr = tundetectedBitErr;
    if (undetectedBitErr < 0 || undetectedBitErr > 1 )
        undetectedBitErr = VAL_QOSPARDONOTCARE;
    pduDropProbability = tpduDropProbab;
    if (pduDropProbability < 0 || pduDropProbability > 1 )
        pduDropProbability = VAL_QOSPARDONOTCARE;
    maxSDUsize = tmaxSDUsize;
    if (maxSDUsize < 0)
        maxSDUsize = VAL_QOSPARDONOTCARE;
    partDeliv = tpartDeliv;
    incompleteDeliv = tincompleteDeliv;
    forceOrder = tforceOrder;
    maxAllowGap = tmaxAllowGap;
    if (maxAllowGap < 0)
        maxAllowGap = VAL_QOSPARDONOTCARE;
    delay = tdelay;
    if (delay < 0)
        delay = VAL_QOSPARDONOTCARE;
    jitter = tjitter;
    if (jitter < 0)
        jitter = VAL_QOSPARDONOTCARE;
    costTime = tcostTime;
    if (costTime < 0)
        costTime = VAL_QOSPARDONOTCARE;
    costBits = tcostBits;
    if (costBits < 0)
        costBits = VAL_QOSPARDONOTCARE;
}

QoSReq::QoSReq(cXMLElementList& attrs) :
                avgBand(VAL_DEFQOSREQ), avgSDUBand(VAL_DEFQOSREQ), peakBandDuration(VAL_DEFQOSREQ), peakSDUBandDuration(VAL_DEFQOSREQ),
                burstPeriod(VAL_DEFQOSREQ), burstDuration(VAL_DEFQOSREQ), undetectedBitErr(VAL_DEFQOSREQ), pduDropProbability(VAL_DEFQOSREQ), maxSDUsize(VAL_DEFQOSREQ),
                partDeliv(false), incompleteDeliv(false), forceOrder(false),
                maxAllowGap(VAL_DEFQOSREQ), delay(VAL_DEFQOSREQ), jitter(VAL_DEFQOSREQ),
                costTime(VAL_DEFQOSREQ), costBits(VAL_DEFQOSREQ)
{
    for (cXMLElementList::iterator jt = attrs.begin(); jt != attrs.end(); ++jt) {
        cXMLElement* n = *jt;

        if ( !strcmp(n->getTagName(), ELEM_AVGBW) ) {
            avgBand = n->getNodeValue() ? atoi(n->getNodeValue()) : VAL_QOSPARDONOTCARE;
            if (avgBand < 0)
                avgBand = VAL_QOSPARDONOTCARE;
        }
        else if (!strcmp(n->getTagName(), ELEM_AVGSDUBW)) {
            avgSDUBand = n->getNodeValue() ? atoi(n->getNodeValue()) : VAL_QOSPARDONOTCARE;
            if (avgSDUBand < 0)
                avgSDUBand = VAL_QOSPARDONOTCARE;
        }
        else if (!strcmp(n->getTagName(), ELEM_PEAKBWDUR)) {
            peakBandDuration = n->getNodeValue() ? atoi(n->getNodeValue()) : VAL_QOSPARDONOTCARE;
            if (peakBandDuration < 0)
                peakBandDuration = VAL_QOSPARDONOTCARE;
        }
        else if (!strcmp(n->getTagName(), ELEM_PEAKSDUBWDUR)) {
            peakSDUBandDuration = n->getNodeValue() ? atoi(n->getNodeValue()) : VAL_QOSPARDONOTCARE;
            if (peakSDUBandDuration < 0)
                peakSDUBandDuration = VAL_QOSPARDONOTCARE;
        }
        else if (!strcmp(n->getTagName(), ELEM_BURSTPERIOD)) {
            burstPeriod = n->getNodeValue() ? atoi(n->getNodeValue()) : VAL_QOSPARDONOTCARE;
            if (burstPeriod < 0)
                burstPeriod = VAL_QOSPARDONOTCARE;
        }
        else if (!strcmp(n->getTagName(), ELEM_BURSTDURATION)) {
            burstDuration = n->getNodeValue() ? atoi(n->getNodeValue()) : VAL_QOSPARDONOTCARE;
            if (burstDuration < 0)
                burstDuration = VAL_QOSPARDONOTCARE;
        }
        else if (!strcmp(n->getTagName(), ELEM_UNDETECTBITERR)) {
            undetectedBitErr = n->getNodeValue() ? atof(n->getNodeValue()) : VAL_QOSPARDONOTCARE;
            if (undetectedBitErr < 0 || undetectedBitErr > 1 )
                undetectedBitErr = VAL_QOSPARDONOTCARE;
        }
        else if (!strcmp(n->getTagName(), ELEM_PDUDROPPROBAB)) {
            pduDropProbability = n->getNodeValue() ? atof(n->getNodeValue()) : VAL_QOSPARDONOTCARE;
            if (pduDropProbability < 0 || pduDropProbability > 1 )
                pduDropProbability = VAL_QOSPARDONOTCARE;
        }
        else if (!strcmp(n->getTagName(), ELEM_MAXSDUSIZE)) {
            maxSDUsize = n->getNodeValue() ? atoi(n->getNodeValue()) : VAL_QOSPARDONOTCARE;
            if (maxSDUsize < 0)
                maxSDUsize = VAL_QOSPARDONOTCARE;
        }
        else if (!strcmp(n->getTagName(), ELEM_PARTIALDELIVER)) {
            partDeliv = n->getNodeValue() ? atoi(n->getNodeValue()) : VAL_QOSPARDEFBOOL;
        }
        else if (!strcmp(n->getTagName(), ELEM_INCOMPLETEDELIVER)) {
            incompleteDeliv = n->getNodeValue() ? atoi(n->getNodeValue()) : VAL_QOSPARDEFBOOL;
        }
        else if (!strcmp(n->getTagName(), ELEM_FORCEORDER)) {
            forceOrder = n->getNodeValue() ? atoi(n->getNodeValue()) : VAL_QOSPARDEFBOOL;
        }
        else if (!strcmp(n->getTagName(), ELEM_MAXALLOWGAP)) {
            maxAllowGap = n->getNodeValue() ? atoi(n->getNodeValue()) : VAL_QOSPARDONOTCARE;
            if (maxAllowGap < 0)
                maxAllowGap = VAL_QOSPARDONOTCARE;
        }
        else if (!strcmp(n->getTagName(), ELEM_DELAY)) {
            delay = n->getNodeValue() ? atoi(n->getNodeValue()) : VAL_QOSPARDONOTCARE;
            if (delay < 0)
                delay = VAL_QOSPARDONOTCARE;
        }
        else if (!strcmp(n->getTagName(), ELEM_JITTER)) {
            jitter = n->getNodeValue() ? atoi(n->getNodeValue()) : VAL_QOSPARDONOTCARE;
            if (jitter < 0)
                jitter = VAL_QOSPARDONOTCARE;
        }
        else if (!strcmp(n->getTagName(), ELEM_COSTTIME)) {
            costTime = n->getNodeValue() ? atoi(n->getNodeValue()) : VAL_QOSPARDEFBOOL;
            if (costTime < 0)
                costTime = VAL_QOSPARDONOTCARE;
        }
        else if (!strcmp(n->getTagName(), ELEM_COSTBITS)) {
            costBits = n->getNodeValue() ? atoi(n->getNodeValue()) : VAL_QOSPARDEFBOOL;
            if (costBits < 0)
                costBits = VAL_QOSPARDONOTCARE;
        }
    }
}

const QoSReq QoSReq::MANAGEMENT(
                                  12000, 10,
                                  24000, 20,
                                  10000, 10000,
                                  0.0, 0.0,
                                  1500,
                                  false, false, true,
                                  0, 0, 0,
                                  0, 0
                                 );

QoSReq::~QoSReq() {
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

std::ostream& operator <<(std::ostream& os, const QoSReq& qosreq) {
    return os << qosreq.info();
}

//XXX: Vesely: BEAWARE! Do-not-care value might be the problem when comparing
//             other AP with some requirements and this with none!!!
bool QoSReq::compare(const QoSReq& other) const {
    //EV << "!!!!!Mine" << endl << info() << endl << "!!!!Other" << other.info() ;
    return (other.getAvgBand() <= avgBand && other.getAvgSduBand() <= avgSDUBand
            && other.getPeakBandDuration() <= peakBandDuration && other.getPeakSduBandDuration() <= getPeakSduBandDuration()
            && other.getBurstPeriod() <= burstPeriod && other.getBurstDuration() <= burstDuration
            && other.getUndetectedBitErr() <= undetectedBitErr && other.getPduDropProbability() <= pduDropProbability
            && other.getMaxSduSize() <= maxSDUsize
            && other.isPartialDelivery() == partDeliv && other.isIncompleteDelivery() == incompleteDeliv && other.isForceOrder() == forceOrder
            && other.getMaxAllowGap() <= maxAllowGap && other.getDelay() <= delay && other.getJitter() <= jitter
            && other.getCostTime() <= costTime && other.getCostBits() <= costBits
           ) ? true : false;
}

std::string QoSReq::info() const {
    std::ostringstream os;

    os << "QoS Requirements List>";

    os << "\n   average BW = ";
    if ( this->getAvgBand() < 0)
        os << STR_DONOTCARE;
    else
        os << this->getAvgBand() << " bit/s";

    os   << ", average SDU BW = ";
    if (this->getAvgSduBand() < 0)
        os << STR_DONOTCARE;
    else
        os << this->getAvgSduBand() << " SDU/s";

    os << "\n   peak BW duration = ";
    if (this->getPeakBandDuration() < 0)
        os << STR_DONOTCARE;
    else
        os << this->getPeakBandDuration() << " bit/s";

    os << ", peak SDU BW duration = ";
    if ( this->getPeakSduBandDuration() < 0)
        os << STR_DONOTCARE;
    else
        os << this->getPeakSduBandDuration() << " SDU/s";

    os << "\n   burst period = ";
    if ( this->getBurstPeriod() < 0 )
        os << STR_DONOTCARE;
    else
        os << this->getBurstPeriod() << " usecs";

    os << ", burst duration = ";
    if ( this->getBurstDuration() < 0 )
        os << STR_DONOTCARE;
    else
        os << this->getBurstDuration() << " usecs";

    os << "\n   undetect. bit errors = ";
    if ( this->getUndetectedBitErr() < 0 )
        os << STR_DONOTCARE;
    else
        os << this->getUndetectedBitErr() << "%";

    os << ", PDU dropping probability = ";
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

    os << ", incomplete delivery = " << (this->isIncompleteDelivery() ? STR_YES : STR_NO );

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

    os << ", jitter = ";
    if ( this->getJitter() < 0 )
        os << STR_DONOTCARE;
    else
        os << this->getJitter() << " usecs";

    os << "\n   cost-time = ";
    if ( this->getCostTime() < 0 )
        os << STR_DONOTCARE;
    else
        os << this->getCostTime() << " $/ms";

    os << ", cost-bits = ";
    if ( this->getCostBits() < 0 )
        os << STR_DONOTCARE;
    else
        os << this->getCostBits() << " $/Mb";

    os << "\n   resiliency factor = ";
    if ( this->getResiliencyFactor() < 0 )
        os << STR_DONOTCARE;
    else
        os << this->getResiliencyFactor() << " usecs";

    return os.str();
}

double QoSReq::getPduDropProbability() const {
     return pduDropProbability;
}

void QoSReq::setPduDropProbability(double pduDropProbability) {
     this->pduDropProbability = pduDropProbability;
}

