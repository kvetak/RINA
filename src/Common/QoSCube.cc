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
 * @file QoSCube.cc
 * @author Marcel Marek
 * @date Apr 28, 2014
 * @brief
 * @detail
 */
#include "Common/QoSCube.h"

const char* STR_DONOTCARE = "do-not-care";
const char* STR_YES = "yes";
const char* STR_NO = "no";
const int   VAL_DEFAULT_QOS = 0;
const std::string VAL_UNDEF_QOSID = "UNDEF-QoSCube";
const std::string VAL_MGMTQOSID = "MGMT-QoSCube";

QoSCube::QoSCube() : qoSId(VAL_UNDEF_QOSID),
        avgBand(VAL_DEFAULT_QOS), avgSDUBand(VAL_DEFAULT_QOS), peakBandDuration(VAL_DEFAULT_QOS), peakSDUBandDuration(VAL_DEFAULT_QOS),
        burstPeriod(VAL_DEFAULT_QOS), burstDuration(VAL_DEFAULT_QOS), undetectedBitErr(VAL_DEFAULT_QOS), pduDropProbability(VAL_DEFAULT_QOS), maxSDUsize(VAL_DEFAULT_QOS),
        partDeliv(false), incompleteDeliv(false), forceOrder(false),
        maxAllowGap(VAL_DEFAULT_QOS), delay(VAL_DEFAULT_QOS), jitter(VAL_DEFAULT_QOS),
        costTime(VAL_DEFAULT_QOS), costBits(VAL_DEFAULT_QOS), aTime(VAL_DEFAULT_QOS),
        rxOn(false), windowFCOn(false), rateFCOn(false), efcpPolicies(new EFCPPolicySet()), resiliencyFactor(VAL_DEFAULT_QOS)
{
}

QoSCube::QoSCube(cXMLElementList& attrs) : qoSId(VAL_UNDEF_QOSID),
        avgBand(VAL_QOSPARDONOTCARE), avgSDUBand(VAL_QOSPARDONOTCARE), peakBandDuration(VAL_QOSPARDONOTCARE), peakSDUBandDuration(VAL_QOSPARDONOTCARE),
        burstPeriod(VAL_QOSPARDONOTCARE), burstDuration(VAL_QOSPARDONOTCARE), undetectedBitErr(VAL_QOSPARDONOTCARE), pduDropProbability(VAL_QOSPARDONOTCARE), maxSDUsize(VAL_QOSPARDONOTCARE),
        partDeliv(false), incompleteDeliv(false), forceOrder(false),
        maxAllowGap(VAL_QOSPARDONOTCARE), delay(VAL_QOSPARDONOTCARE), jitter(VAL_QOSPARDONOTCARE),
        costTime(VAL_QOSPARDONOTCARE), costBits(VAL_QOSPARDONOTCARE), aTime(VAL_DEFAULT_QOS),
        rxOn(false), windowFCOn(false), rateFCOn(false), efcpPolicies(new EFCPPolicySet()), resiliencyFactor(VAL_QOSPARDONOTCARE)
{
  for (cXMLElementList::iterator jt = attrs.begin(); jt != attrs.end(); ++jt)
  {
    cXMLElement* n = *jt;

    if (!strcmp(n->getTagName(), ELEM_AVGBW))
    {
      avgBand = n->getNodeValue() ? atoi(n->getNodeValue()) : VAL_QOSPARDONOTCARE;
      if (avgBand < 0)
        avgBand = VAL_QOSPARDONOTCARE;
    }
    else if (!strcmp(n->getTagName(), ELEM_AVGSDUBW))
    {
      avgSDUBand = n->getNodeValue() ? atoi(n->getNodeValue()) : VAL_QOSPARDONOTCARE;
      if (avgSDUBand < 0)
        avgSDUBand = VAL_QOSPARDONOTCARE;
    }
    else if (!strcmp(n->getTagName(), ELEM_PEAKBWDUR))
    {
      peakBandDuration = n->getNodeValue() ? atoi(n->getNodeValue()) : VAL_QOSPARDONOTCARE;
      if (peakBandDuration < 0)
        peakBandDuration = VAL_QOSPARDONOTCARE;
    }
    else if (!strcmp(n->getTagName(), ELEM_PEAKSDUBWDUR))
    {
      peakSDUBandDuration = n->getNodeValue() ? atoi(n->getNodeValue()) : VAL_QOSPARDONOTCARE;
      if (peakSDUBandDuration < 0)
        peakSDUBandDuration = VAL_QOSPARDONOTCARE;
    }
    else if (!strcmp(n->getTagName(), ELEM_BURSTPERIOD))
    {
      burstPeriod = n->getNodeValue() ? atoi(n->getNodeValue()) : VAL_QOSPARDONOTCARE;
      if (burstPeriod < 0)
        burstPeriod = VAL_QOSPARDONOTCARE;
    }
    else if (!strcmp(n->getTagName(), ELEM_BURSTDURATION))
    {
      burstDuration = n->getNodeValue() ? atoi(n->getNodeValue()) : VAL_QOSPARDONOTCARE;
      if (burstDuration < 0)
        burstDuration = VAL_QOSPARDONOTCARE;
    }
    else if (!strcmp(n->getTagName(), ELEM_UNDETECTBITERR))
    {
      undetectedBitErr = n->getNodeValue() ? atof(n->getNodeValue()) : VAL_QOSPARDONOTCARE;
      if (undetectedBitErr < 0 || undetectedBitErr > 1)
        undetectedBitErr = VAL_QOSPARDONOTCARE;
    }
    else if (!strcmp(n->getTagName(), ELEM_PDUDROPPROBAB))
    {
      pduDropProbability = n->getNodeValue() ? atof(n->getNodeValue()) : VAL_QOSPARDONOTCARE;
      if (pduDropProbability < 0 || pduDropProbability > 1)
        pduDropProbability = VAL_QOSPARDONOTCARE;
    }
    else if (!strcmp(n->getTagName(), ELEM_MAXSDUSIZE))
    {
      maxSDUsize = n->getNodeValue() ? atoi(n->getNodeValue()) : VAL_QOSPARDONOTCARE;
      if (maxSDUsize < 0)
        maxSDUsize = VAL_QOSPARDONOTCARE;
    }
    else if (!strcmp(n->getTagName(), ELEM_PARTIALDELIVER))
    {
      partDeliv = n->getNodeValue() ? atoi(n->getNodeValue()) : VAL_QOSPARDEFBOOL;
    }
    else if (!strcmp(n->getTagName(), ELEM_INCOMPLETEDELIVER))
    {
      incompleteDeliv = n->getNodeValue() ? atoi(n->getNodeValue()) : VAL_QOSPARDEFBOOL;
    }
    else if (!strcmp(n->getTagName(), ELEM_FORCEORDER))
    {
      forceOrder = n->getNodeValue() ? atoi(n->getNodeValue()) : VAL_QOSPARDEFBOOL;
    }
    else if (!strcmp(n->getTagName(), ELEM_MAXALLOWGAP))
    {
      maxAllowGap = n->getNodeValue() ? atoi(n->getNodeValue()) : VAL_QOSPARDONOTCARE;
      if (maxAllowGap < 0)
        maxAllowGap = VAL_QOSPARDONOTCARE;
    }
    else if (!strcmp(n->getTagName(), ELEM_DELAY))
    {
      delay = n->getNodeValue() ? atoi(n->getNodeValue()) : VAL_QOSPARDONOTCARE;
      if (delay < 0)
        delay = VAL_QOSPARDONOTCARE;
    }
    else if (!strcmp(n->getTagName(), ELEM_JITTER))
    {
      jitter = n->getNodeValue() ? atoi(n->getNodeValue()) : VAL_QOSPARDONOTCARE;
      if (jitter < 0)
        jitter = VAL_QOSPARDONOTCARE;
    }
    else if (!strcmp(n->getTagName(), ELEM_COSTTIME))
    {
      costTime = n->getNodeValue() ? atoi(n->getNodeValue()) : VAL_QOSPARDEFBOOL;
      if (costTime < 0)
        costTime = VAL_QOSPARDONOTCARE;
    }
    else if (!strcmp(n->getTagName(), ELEM_COSTBITS))
    {
      costBits = n->getNodeValue() ? atoi(n->getNodeValue()) : VAL_QOSPARDEFBOOL;
      if (costBits < 0)
        costBits = VAL_QOSPARDONOTCARE;
    }
    else if (!strcmp(n->getTagName(), ELEM_ATIME))
    {
      aTime = n->getNodeValue() ? atof(n->getNodeValue()) : VAL_QOSPARDONOTCARE;
      if (aTime < 0)
        aTime = VAL_DEFAULT_QOS;
    }
    else if (!strcmp(n->getTagName(), ELEM_RXON))
    {
        rxOn = (atoi(n->getNodeValue()) == 1) ? true : VAL_QOSPARDEFBOOL;
    }
    else if (!strcmp(n->getTagName(), ELEM_WINON))
    {
        windowFCOn = (atoi(n->getNodeValue()) == 1) ? true : VAL_QOSPARDEFBOOL;
    }
    else if (!strcmp(n->getTagName(), ELEM_RATEON))
    {
        rateFCOn = (atoi(n->getNodeValue()) == 1) ? true : VAL_QOSPARDEFBOOL;
    }
    else if (!strcmp(n->getTagName(), ELEM_EFCPPOL))
    {
      efcpPolicies->init(n);
    }
    else if(!strcmp(n->getTagName(), ELEM_RESILIENCYFACTOR))
    {
        resiliencyFactor = n->getNodeValue() ? atoi(n->getNodeValue()) : VAL_QOSPARDONOTCARE;
        if (resiliencyFactor < 0)
            resiliencyFactor = VAL_QOSPARDONOTCARE;
    }
  }
}

QoSCube::QoSCube(std::string tqosid,
        int tavgBand, int tavgSDUBand,
        int tpeakBandDuration, int tpeakSDUBandDuration,
        int tburstPeriod, int tburstDuration,
        double tundetectedBitErr, double tpduDropProbab,
        int tmaxSDUsize,
        bool tpartDeliv, bool tincompleteDeliv, bool tforceOrder,
        unsigned int tmaxAllowGap, int tdelay, int tjitter,
        int tcosttime, int tcostbits,
        double tatime, bool trxon, bool twinfcon, bool tratefcon) :
                qoSId(tqosid),
                avgBand(tavgBand), avgSDUBand(tavgSDUBand),
                peakBandDuration(tpeakBandDuration), peakSDUBandDuration(tpeakSDUBandDuration),
                burstPeriod(tburstPeriod), burstDuration(tburstDuration),
                undetectedBitErr(tundetectedBitErr), pduDropProbability(tpduDropProbab),
                maxSDUsize(tmaxSDUsize),
                partDeliv(tpartDeliv), incompleteDeliv(tincompleteDeliv), forceOrder(tforceOrder),
                maxAllowGap(tmaxAllowGap), delay(tdelay), jitter(tjitter),
                costTime(tcosttime), costBits(tcostbits),
                aTime(tatime), rxOn(trxon), windowFCOn(twinfcon), rateFCOn(tratefcon),
                efcpPolicies(new EFCPPolicySet())
{
}

QoSCube::~QoSCube() {

    qoSId = VAL_DEFAULT_QOS;

    avgBand = VAL_DEFAULT_QOS;
    avgSDUBand = VAL_DEFAULT_QOS;             //Average SDU bandwidth (measured in SDUs/sec)
    peakBandDuration = VAL_DEFAULT_QOS;       //Peak bandwidth-duration (measured in bits/sec);
    peakSDUBandDuration = VAL_DEFAULT_QOS;    //Peak SDU bandwidth-duration (measured in SDUs/sec);
    burstPeriod = VAL_DEFAULT_QOS;            //Burst period measured in useconds
    burstDuration = VAL_DEFAULT_QOS;          //Burst duration, measured in useconds fraction of Burst Period
    undetectedBitErr = VAL_DEFAULT_QOS;    //Undetected bit error rate measured as a probability
    pduDropProbability = VAL_DEFAULT_QOS;
    maxSDUsize = VAL_DEFAULT_QOS;             //MaxSDUSize measured in bytes
    partDeliv = false;             //Partial Delivery - Can SDUs be delivered in pieces rather than all at once?
    incompleteDeliv = false;       //Incomplete Delivery - Can SDUs with missing pieces be delivered?
    forceOrder = false;            //Must SDUs be delivered in-order bits
    maxAllowGap = VAL_DEFAULT_QOS;   //Max allowable gap in SDUs, (a gap of N SDUs is considered the same as all SDUs delivered, i.e. a gap of N is a "don't care.")
    delay = VAL_DEFAULT_QOS;                  //Delay in usecs
    jitter = VAL_DEFAULT_QOS;                 //Jitter in usecs
    costTime = VAL_DEFAULT_QOS;               //measured in $/ms
    costBits = VAL_DEFAULT_QOS;               //measured in $/Mb
    aTime = VAL_DEFAULT_QOS;
}

const QoSCube QoSCube::MANAGEMENT(VAL_MGMTQOSID,
                                  12000, 10,
                                  24000, 20,
                                  10000, 10000,
                                  0.0, 0.0,
                                  1500,
                                  false, false, true,
                                  0, 0, 0,
                                  0, 0,
                                  0.0, true, true, false
                                 );

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

std::string QoSCube::getQosId() const {
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

void QoSCube::setQosId(std::string qoSId) {
    this->qoSId = qoSId;
}

bool QoSCube::isDTCPNeeded()const {
  return isRxOn() || isWindowFcOn() || isRateFcOn();
}

double QoSCube::getPduDropProbability() const {
    return pduDropProbability;
}

void QoSCube::setPduDropProbability(double pduDropProbability) {
    this->pduDropProbability = pduDropProbability;
}

std::string QoSCube::info() const {
    std::ostringstream os;

    os << "QoSCube Id> " << this->getQosId();

    os << "\n   average BW = ";
        os << this->getAvgBand() << " bit/s";

    os   << ", average SDU BW = ";
        os << this->getAvgSduBand() << " SDU/s";

    os << "\n   peak BW duration = ";
        os << this->getPeakBandDuration() << " bit/s";

    os << ", peak SDU BW duration = ";
        os << this->getPeakSduBandDuration() << " SDU/s";

    os << "\n   burst period = ";
        os << this->getBurstPeriod() << " usecs";

    os << ", burst duration = ";
        os << this->getBurstDuration() << " usecs";

    os << "\n   undetect. bit errors = ";
        os << this->getUndetectedBitErr() << "%";

    os << ", PDU dropping probability = ";
        os << this->getPduDropProbability() << "%";

    os << "\n   max SDU Size = ";
        os << this->getMaxSduSize() << " B";

    os << "\n   partial delivery = " << (this->isPartialDelivery() ? STR_YES : STR_NO );

    os << ", incomplete delivery = " << (this->isIncompleteDelivery() ? STR_YES : STR_NO );

    os << "\n   force order = " << (this->isForceOrder() ? STR_YES : STR_NO );

    os << "\n   max allowed gap = ";
        os << this->getMaxAllowGap() << " SDUs";

    os << "\n   delay = ";
        os << this->getDelay() << " usecs";

    os << ", jitter = ";
        os << this->getJitter() << " usecs";

    os << "\n   cost-time = ";
        os << this->getCostTime() << " $/ms";

    os << ", cost-bits = ";
        os << this->getCostBits() << " $/Mb";

    os << "\n   A-Time = ";
        os << this->getATime() << "ms";

    os << "\n   resiliency factor = ";
    if ( this->getResiliencyFactor() < 0 )
        os << STR_DONOTCARE;
    else
        os << this->getResiliencyFactor() << " usecs";

    os << "\n  EFCP Policy Set:";
       os << this->getEfcpPolicies();

    return os.str();
}

const EFCPPolicySet* QoSCube::getEfcpPolicies() const
{
  return efcpPolicies;
}

bool QoSCube::isRateFcOn() const
{
return rateFCOn;
}

bool QoSCube::isRxOn() const
{
return rxOn;
}

bool QoSCube::isWindowFcOn() const
{
return windowFCOn;
}

bool QoSCube::isDefined() {
    return avgBand != VAL_QOSPARDONOTCARE && avgSDUBand != VAL_QOSPARDONOTCARE
            && peakBandDuration != VAL_QOSPARDONOTCARE && peakSDUBandDuration != VAL_QOSPARDONOTCARE
            && burstPeriod != VAL_QOSPARDONOTCARE && burstDuration != VAL_QOSPARDONOTCARE
            && undetectedBitErr != VAL_QOSPARDONOTCARE && pduDropProbability != VAL_QOSPARDONOTCARE
            && maxSDUsize != VAL_QOSPARDONOTCARE && maxAllowGap != VAL_QOSPARDONOTCARE
            && delay != VAL_QOSPARDONOTCARE && jitter != VAL_QOSPARDONOTCARE
            && costTime != VAL_QOSPARDONOTCARE && costBits != VAL_QOSPARDONOTCARE
            && aTime != VAL_QOSPARDONOTCARE && rxOn != VAL_QOSPARDONOTCARE
            && windowFCOn != VAL_QOSPARDONOTCARE && rateFCOn!= VAL_QOSPARDONOTCARE
            ;
}

void QoSCube::setEfcpPolicies(EFCPPolicySet* efcpPolicies)
{
  this->efcpPolicies = efcpPolicies;
}


void QoSCube::setRateFcOn(bool rateFcOn)
{
  rateFCOn = rateFcOn;
}

void QoSCube::setRxOn(bool rxOn)
{
  this->rxOn = rxOn;
}

void QoSCube::setWindowFcOn(bool windowFcOn)
{
  windowFCOn = windowFcOn;
}
