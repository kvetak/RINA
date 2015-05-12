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
const int   VAL_DEFQOS = 0;

const char* ELEM_ATIME               = "ATime";
const char* ELEM_EFCPPOL             = "EFCPPolicySet";


QoSCube::QoSCube() : qoSId(VAL_DEFQOS),
        avgBand(VAL_DEFQOS), avgSDUBand(VAL_DEFQOS), peakBandDuration(VAL_DEFQOS), peakSDUBandDuration(VAL_DEFQOS),
        burstPeriod(VAL_DEFQOS), burstDuration(VAL_DEFQOS), undetectedBitErr(VAL_DEFQOS), pduDropProbability(VAL_DEFQOS), maxSDUsize(VAL_DEFQOS),
        partDeliv(false), incompleteDeliv(false), forceOrder(false),
        maxAllowGap(VAL_DEFQOS), delay(VAL_DEFQOS), jitter(VAL_DEFQOS),
        costTime(VAL_DEFQOS), costBits(VAL_DEFQOS)
{
}

QoSCube::QoSCube(cXMLElementList& attrs) : qoSId(VAL_DEFQOS),
        avgBand(VAL_QOSPARDONOTCARE), avgSDUBand(VAL_QOSPARDONOTCARE), peakBandDuration(VAL_QOSPARDONOTCARE), peakSDUBandDuration(VAL_QOSPARDONOTCARE),
        burstPeriod(VAL_QOSPARDONOTCARE), burstDuration(VAL_QOSPARDONOTCARE), undetectedBitErr(VAL_QOSPARDONOTCARE), pduDropProbability(VAL_QOSPARDONOTCARE), maxSDUsize(VAL_QOSPARDONOTCARE),
        partDeliv(false), incompleteDeliv(false), forceOrder(false),
        maxAllowGap(VAL_QOSPARDONOTCARE), delay(VAL_QOSPARDONOTCARE), jitter(VAL_QOSPARDONOTCARE),
        costTime(VAL_QOSPARDONOTCARE), costBits(VAL_QOSPARDONOTCARE)
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
        }else if (!strcmp(n->getTagName(), ELEM_ATIME)) {
          aTime = n->getNodeValue() ? atof(n->getNodeValue()) : VAL_QOSPARDEFBOOL;
          if (aTime < 0)
              aTime = VAL_QOSPARDONOTCARE;
       }else if(!strcmp(n->getTagName(), ELEM_EFCPPOL)) {
         efcpPolicies->init(n);
       }
    }
}
QoSCube::~QoSCube() {
    qoSId = VAL_DEFQOS;

    avgBand = VAL_DEFQOS;
    avgSDUBand = VAL_DEFQOS;             //Average SDU bandwidth (measured in SDUs/sec)
    peakBandDuration = VAL_DEFQOS;       //Peak bandwidth-duration (measured in bits/sec);
    peakSDUBandDuration = VAL_DEFQOS;    //Peak SDU bandwidth-duration (measured in SDUs/sec);
    burstPeriod = VAL_DEFQOS;            //Burst period measured in useconds
    burstDuration = VAL_DEFQOS;          //Burst duration, measured in useconds fraction of Burst Period
    undetectedBitErr = VAL_DEFQOS;    //Undetected bit error rate measured as a probability
    pduDropProbability = VAL_DEFQOS;
    maxSDUsize = VAL_DEFQOS;             //MaxSDUSize measured in bytes
    partDeliv = false;             //Partial Delivery - Can SDUs be delivered in pieces rather than all at once?
    incompleteDeliv = false;       //Incomplete Delivery - Can SDUs with missing pieces be delivered?
    forceOrder = false;            //Must SDUs be delivered in-order bits
    maxAllowGap = VAL_DEFQOS;   //Max allowable gap in SDUs, (a gap of N SDUs is considered the same as all SDUs delivered, i.e. a gap of N is a "don't care.")
    delay = VAL_DEFQOS;                  //Delay in usecs
    jitter = VAL_DEFQOS;                 //Jitter in usecs
    costTime = VAL_DEFQOS;               //measured in $/ms
    costBits = VAL_DEFQOS;               //measured in $/Mb
    aTime = VAL_DEFQOS;
}

std::ostream& operator <<(std::ostream& os, const QoSCube& cube) {
    return os << cube.info();
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

unsigned short QoSCube::getQosId() const {
    return qoSId;
}

double QoSCube::getCostBits() const {
    return costBits;
}

void QoSCube::setCostBits(double costBits) {
    this->costBits = costBits;
}

double QoSCube::getCostTime() const {
    return costTime;
}

void QoSCube::setCostTime(double costTime) {
    this->costTime = costTime;
}

double QoSCube::getATime() const {
    return aTime;
}

void QoSCube::setATime(double aTime) {
    this->aTime = aTime;
}

void QoSCube::setQosId(unsigned short qoSId) {
    this->qoSId = qoSId;
}

bool QoSCube::isDTCPNeeded()const {
  return isPartialDelivery() || isForceOrder() || isIncompleteDelivery() || avgBand >= 0;
}

double QoSCube::getPduDropProbability() const {
    return pduDropProbability;
}

void QoSCube::setPduDropProbability(double pduDropProbability) {
    this->pduDropProbability = pduDropProbability;
}

std::string QoSCube::info() const {
    std::ostringstream os;

    if (this->getQosId())
        os << "QoSCube Id> " << this->getQosId();

    os << "\n   average BW = ";
        os << this->getAvgBand() << " bit/s";

    os   << "\n   average SDU BW = ";
        os << this->getAvgSduBand() << " SDU/s";

    os << "\n   peak BW duration = ";
        os << this->getPeakBandDuration() << " bit/s";

    os << "\n   peak SDU BW duration = ";
        os << this->getPeakSduBandDuration() << " SDU/s";

    os << "\n   burst period = ";
        os << this->getBurstPeriod() << " usecs";

    os << "\n   burst duration = ";
        os << this->getBurstDuration() << " usecs";

    os << "\n   undetect. bit errors = ";
        os << this->getUndetectedBitErr() << "%";

    os << "\n   PDU dropping probability = ";
        os << this->getPduDropProbability() << "%";

    os << "\n   max SDU Size = ";
        os << this->getMaxSduSize() << " B";

    os << "\n   partial delivery = " << (this->isPartialDelivery() ? STR_YES : STR_NO );

    os << "\n   incomplete delivery = " << (this->isIncompleteDelivery() ? STR_YES : STR_NO );

    os << "\n   force order = " << (this->isForceOrder() ? STR_YES : STR_NO );

    os << "\n   max allowed gap = ";
        os << this->getMaxAllowGap() << " SDUs";

    os << "\n   delay = ";
        os << this->getDelay() << " usecs";

    os << "\n   jitter = ";
        os << this->getJitter() << " usecs";

    os << "\n   cost-time = ";
        os << this->getCostTime() << " $/ms";

    os << "\n   cost-bits = ";
        os << this->getCostBits() << " $/Mb";

    os << "\n   A-Time = ";
        os << this->getATime() << "ms";

    return os.str();
}

const EFCPPolicySet* QoSCube::getEfcpPolicies() const
{
  return efcpPolicies;
}

bool QoSCube::isDefined() {
    return avgBand != VAL_QOSPARDONOTCARE && avgSDUBand != VAL_QOSPARDONOTCARE
            && peakBandDuration != VAL_QOSPARDONOTCARE && peakSDUBandDuration != VAL_QOSPARDONOTCARE
            && burstPeriod != VAL_QOSPARDONOTCARE && burstDuration != VAL_QOSPARDONOTCARE
            && undetectedBitErr != VAL_QOSPARDONOTCARE && pduDropProbability != VAL_QOSPARDONOTCARE
            && maxSDUsize != VAL_QOSPARDONOTCARE && maxAllowGap != VAL_QOSPARDONOTCARE
            && delay != VAL_QOSPARDONOTCARE && jitter != VAL_QOSPARDONOTCARE
            && costTime != VAL_QOSPARDONOTCARE && costBits != VAL_QOSPARDONOTCARE
            && aTime != VAL_QOSPARDONOTCARE
            ;
}

void QoSCube::setEfcpPolicies(EFCPPolicySet* efcpPolicies)
{
  this->efcpPolicies = efcpPolicies;
}

