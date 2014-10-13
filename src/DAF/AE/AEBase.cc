
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

#include "AEBase.h"

Define_Module(AEBase);

const char* PAR_AVGBW               = "averageBandwidth";
const char* PAR_AVGSDUBW            = "averageSDUBandwidth";
const char* PAR_PEAKBWDUR           = "peakBandwidthDuration";
const char* PAR_PEAKSDUBWDUR        = "peakSDUBandwidthDuration";
const char* PAR_BURSTPERIOD         = "burstPeriod";
const char* PAR_BURSTDURATION       = "burstDuration";
const char* PAR_UNDETECTBITERR      = "undetectedBitErr";
const char* PAR_MAXSDUSIZE          = "maxSDUsize";
const char* PAR_PARTIALDELIVER      = "partialDelivery";
const char* PAR_INCOMPLETEDELIVER   = "incompleteDelivery";
const char* PAR_FORCEORDER          = "forceOrder";
const char* PAR_MAXALLOWGAP         = "maxAllowGap";
const char* PAR_DELAY               = "delay";
const char* PAR_JITTER              = "jitter";
const char* PAR_COSTTIME            = "costTime";
const char* PAR_COSTBITS            = "costBits";

const APNamingInfo& AEBase::getApni() const {
    return apni;
}

void AEBase::setApni(const APNamingInfo& apni) {
    this->apni = apni;
}

const Flows& AEBase::getFlows() const {
    return flows;
}

void AEBase::setFlows(const Flows& flows) {
    this->flows = flows;
}

const std::string& AEBase::getSrcAeInstance() const {
    return srcAeInstance;
}

void AEBase::setSrcAeInstance(const std::string& srcAeInstance) {
    this->srcAeInstance = srcAeInstance;
}

const std::string& AEBase::getSrcAeName() const {
    return srcAeName;
}

void AEBase::setSrcAeName(const std::string& srcAeName) {
    this->srcAeName = srcAeName;
}

const std::string& AEBase::getSrcApInstance() const {
    return srcApInstance;
}

void AEBase::setSrcApInstance(const std::string& srcApInstance) {
    this->srcApInstance = srcApInstance;
}

const std::string& AEBase::getSrcApName() const {
    return srcApName;
}

void AEBase::setSrcApName(const std::string& srcApName) {
    this->srcApName = srcApName;
}

void AEBase::initNamingInfo() {
    //Source info
    srcApName = this->getParentModule()->getParentModule()->par(PAR_APNAME).stdstringValue();
    srcApInstance = this->getParentModule()->getParentModule()->par(PAR_APINSTANCE).stdstringValue();
    srcAeName = this->par(PAR_AENAME).stdstringValue();
    srcAeInstance = this->par(PAR_AEINSTANCE).stdstringValue();

    apni = APNamingInfo(APN(this->srcApName), this->srcApInstance,
            this->srcAeName, this->srcAeInstance);
}

void AEBase::initialize()
{
    initNamingInfo();
    initQoSRequiremets();
}

const QosCube& AEBase::getQoSRequirements() const {
    return QoSRequirements;
}

void AEBase::setQoSRequirements(const QosCube& qoSRequirements) {
    QoSRequirements = qoSRequirements;
}

void AEBase::initQoSRequiremets() {
    //Check whether module has all QoS parameters
    if (! (hasPar(PAR_AVGBW) &&
           hasPar(PAR_AVGSDUBW) &&
           hasPar(PAR_PEAKBWDUR) &&
           hasPar(PAR_PEAKSDUBWDUR) &&
           hasPar(PAR_BURSTPERIOD) &&
           hasPar(PAR_BURSTDURATION) &&
           hasPar(PAR_UNDETECTBITERR) &&
           hasPar(PAR_MAXSDUSIZE) &&
           hasPar(PAR_PARTIALDELIVER) &&
           hasPar(PAR_INCOMPLETEDELIVER) &&
           hasPar(PAR_FORCEORDER) &&
           hasPar(PAR_MAXALLOWGAP) &&
           hasPar(PAR_DELAY) &&
           hasPar(PAR_JITTER) &&
           hasPar(PAR_COSTTIME) &&
           hasPar(PAR_COSTBITS)
          )
       ) {
        std::stringstream ss;
        ss << "Module " << this->getFullName() << " is not derived from AEBase. It misses some important QoS parameters!";
        error(ss.str().c_str());
    }

    //Create QoS cube according to parameters
    QosCube cube;

    int avgBand                 = VAL_QOSPARDONOTCARE;    //Average bandwidth (measured at the application in bits/sec)
    int avgSDUBand              = VAL_QOSPARDONOTCARE;    //Average SDU bandwidth (measured in SDUs/sec)
    int peakBandDuration        = VAL_QOSPARDONOTCARE;    //Peak bandwidth-duration (measured in bits/sec);
    int peakSDUBandDuration     = VAL_QOSPARDONOTCARE;    //Peak SDU bandwidth-duration (measured in SDUs/sec);
    int burstPeriod             = VAL_QOSPARDONOTCARE;    //Burst period measured in useconds
    int burstDuration           = VAL_QOSPARDONOTCARE;    //Burst duration, measured in usecs fraction of Burst Period
    int undetectedBitErr        = VAL_QOSPARDONOTCARE;    //Undetected bit error rate measured as a probability
    int maxSDUsize              = VAL_QOSPARDONOTCARE;    //MaxSDUSize measured in bytes
    bool partDeliv              = VAL_QOSPARDEFBOOL;      //Partial Delivery - Can SDUs be delivered in pieces rather than all at once?
    bool incompleteDeliv        = VAL_QOSPARDEFBOOL;      //Incomplete Delivery - Can SDUs with missing pieces be delivered?
    bool forceOrder             = VAL_QOSPARDEFBOOL;      //Must SDUs be delivered in order?
    unsigned int maxAllowGap    = VAL_QOSPARDONOTCARE;    //Max allowable gap in SDUs, (a gap of N SDUs is considered the same as all SDUs delivered, i.e. a gap of N is a "don't care.")
    int delay                   = VAL_QOSPARDONOTCARE;    //Delay in usecs
    int jitter                  = VAL_QOSPARDONOTCARE;    //Jitter in usecs2
    int costtime                = VAL_QOSPARDONOTCARE;    //measured in $/ms
    int costbits                = VAL_QOSPARDONOTCARE;    //measured in $/Mb

    avgBand = par(PAR_AVGBW);
    if (avgBand < 0)
        avgBand = VAL_QOSPARDONOTCARE;
    avgSDUBand = par(PAR_AVGSDUBW);
    if (avgSDUBand < 0)
        avgSDUBand = VAL_QOSPARDONOTCARE;
    peakBandDuration = par(PAR_PEAKBWDUR);
    if (peakBandDuration < 0)
        peakBandDuration = VAL_QOSPARDONOTCARE;
    peakSDUBandDuration = par(PAR_PEAKSDUBWDUR);
    if (peakSDUBandDuration < 0)
        peakSDUBandDuration = VAL_QOSPARDONOTCARE;
    burstPeriod = par(PAR_BURSTPERIOD);
    if (burstPeriod < 0)
        burstPeriod = VAL_QOSPARDONOTCARE;
    burstDuration = par(PAR_BURSTDURATION);
    if (burstDuration < 0)
        burstDuration = VAL_QOSPARDONOTCARE;
    undetectedBitErr = par(PAR_UNDETECTBITERR);
    if (undetectedBitErr < 0 || undetectedBitErr > 1 )
        undetectedBitErr = VAL_QOSPARDONOTCARE;
    maxSDUsize = par(PAR_MAXSDUSIZE);
    if (maxSDUsize < 0)
        maxSDUsize = VAL_QOSPARDONOTCARE;
    partDeliv = par(PAR_PARTIALDELIVER);
    incompleteDeliv = par(PAR_INCOMPLETEDELIVER);
    forceOrder = par(PAR_FORCEORDER);
    maxAllowGap = par(PAR_MAXALLOWGAP);
    if (maxAllowGap < 0)
        maxAllowGap = VAL_QOSPARDONOTCARE;
    delay = par(PAR_DELAY);
    if (delay < 0)
        delay = VAL_QOSPARDONOTCARE;
    jitter = par(PAR_JITTER);
    if (jitter < 0)
        jitter = VAL_QOSPARDONOTCARE;
    costtime = par(PAR_COSTTIME);
    if (costtime < 0)
        costtime = VAL_QOSPARDONOTCARE;
    costbits = par(PAR_COSTBITS);
    if (costbits < 0)
        costbits = VAL_QOSPARDONOTCARE;

    cube.setQosId(0);
    cube.setAvgBand(avgBand);
    cube.setAvgSduBand(avgSDUBand);
    cube.setPeakBandDuration(peakBandDuration);
    cube.setPeakSduBandDuration(peakSDUBandDuration);
    cube.setBurstPeriod(burstPeriod);
    cube.setBurstDuration(burstDuration);
    cube.setUndetectedBitErr(undetectedBitErr);
    cube.setMaxSduSize(maxSDUsize);
    cube.setPartialDelivery(partDeliv);
    cube.setIncompleteDelivery(incompleteDeliv);
    cube.setForceOrder(forceOrder);
    cube.setMaxAllowGap(maxAllowGap);
    cube.setDelay(delay);
    cube.setJitter(jitter);
    cube.setCostBits(costbits);
    cube.setCostTime(costtime);

    this->setQoSRequirements(cube);

    //EV << "QQQQQQ\n" << cube << "\n\nXXXX\n" << this->getQoSRequirements();

}

void AEBase::handleMessage(cMessage *msg)
{
    // TODO - Generated method body
}

void AEBase::insertFlow(Flow& flow) {
    flows.push_back(flow);
}

bool AEBase::hasFlow(const Flow* flow) {
    for (TFlowsIter it = flows.begin(); it != flows.end(); ++it) {
        if (*it == *flow)
            return true;
    }
    return false;
}
