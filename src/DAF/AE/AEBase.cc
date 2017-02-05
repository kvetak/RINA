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

#include "DAF/AE/AEBase.h"

Define_Module(AEBase);

const char* PAR_AVGBW               = "averageBandwidth";
const char* PAR_AVGSDUBW            = "averageSDUBandwidth";
const char* PAR_PEAKBWDUR           = "peakBandwidthDuration";
const char* PAR_PEAKSDUBWDUR        = "peakSDUBandwidthDuration";
const char* PAR_BURSTPERIOD         = "burstPeriod";
const char* PAR_BURSTDURATION       = "burstDuration";
const char* PAR_UNDETECTBITERR      = "undetectedBitErr";
const char* PAR_PDUDROPPROBAB       = "pduDroppingProbability";
const char* PAR_MAXSDUSIZE          = "maxSDUsize";
const char* PAR_PARTIALDELIVER      = "partialDelivery";
const char* PAR_INCOMPLETEDELIVER   = "incompleteDelivery";
const char* PAR_FORCEORDER          = "forceOrder";
const char* PAR_MAXALLOWGAP         = "maxAllowGap";
const char* PAR_DELAY               = "delay";
const char* PAR_JITTER              = "jitter";
const char* PAR_COSTTIME            = "costTime";
const char* PAR_COSTBITS            = "costBits";
const char* PAR_ATIME               = "aTime";
const char* PAR_RESILIENCYFACTOR    = "resiliencyFactor";

const APNamingInfo& AEBase::getApni() const {
    return apni;
}

void AEBase::setApni(const APNamingInfo& apni) {
    this->apni = apni;
}

const int AEBase::getAuthType(){
    return authType;
}

const std::string& AEBase::getAuthName() const {
    return authName;
}

const std::string& AEBase::getAuthPassword() const {
    return authPassword;
}

const std::string& AEBase::getAuthOther() const {
    return authOther;
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

void AEBase::changeConStatus(CDAPConnectionState conState){
    this->connectionState = conState;
}

CDAPConnectionState AEBase::getConStatus(){
    return this->connectionState;
}

void AEBase::initNamingInfo() {
    //Source info
    srcApName = this->getModuleByPath("^.^.^")->par(PAR_APNAME).stdstringValue();
    srcApInstance = this->getModuleByPath("^.^.^")->par(PAR_APINSTANCE).stdstringValue();
    srcAeName = this->par(PAR_AENAME).stdstringValue();
    srcAeInstance = this->par(PAR_AEINSTANCE).stdstringValue();

    apni = APNamingInfo(APN(this->srcApName), this->srcApInstance,
            this->srcAeName, this->srcAeInstance);
}

void AEBase::initialize()
{
    initNamingInfo();
    initQoSRequirements();
}

const QoSReq& AEBase::getQoSRequirements() const {
    return QoSRequirements;
}

void AEBase::setQoSRequirements(const QoSReq& qoSRequirements) {
    QoSRequirements = qoSRequirements;
}

void AEBase::initQoSRequirements() {
    //Check whether module has all QoS parameters
    if (! (hasPar(PAR_AVGBW) &&
           hasPar(PAR_AVGSDUBW) &&
           hasPar(PAR_PEAKBWDUR) &&
           hasPar(PAR_PEAKSDUBWDUR) &&
           hasPar(PAR_BURSTPERIOD) &&
           hasPar(PAR_BURSTDURATION) &&
           hasPar(PAR_UNDETECTBITERR) &&
           hasPar(PAR_PDUDROPPROBAB) &&
           hasPar(PAR_MAXSDUSIZE) &&
           hasPar(PAR_PARTIALDELIVER) &&
           hasPar(PAR_INCOMPLETEDELIVER) &&
           hasPar(PAR_FORCEORDER) &&
           hasPar(PAR_MAXALLOWGAP) &&
           hasPar(PAR_DELAY) &&
           hasPar(PAR_JITTER) &&
           hasPar(PAR_COSTTIME) &&
           hasPar(PAR_COSTBITS)
           //&& hasPar(PAR_ATIME)
          )
       ) {
        std::ostringstream ss;
        ss << "Module " << this->getFullName() << " is not derived from AEBase. It misses some important QoS parameters!";
        error(ss.str().c_str());
    }

    //Create QoS req according to parameters
    QoSReq req(par(PAR_AVGBW),par(PAR_AVGSDUBW),par(PAR_PEAKBWDUR),par(PAR_PEAKSDUBWDUR),par(PAR_BURSTPERIOD),par(PAR_BURSTDURATION),
            par(PAR_UNDETECTBITERR).doubleValue(),par(PAR_PDUDROPPROBAB).doubleValue(),
            par(PAR_MAXSDUSIZE),
            par(PAR_PARTIALDELIVER).boolValue(),par(PAR_INCOMPLETEDELIVER).boolValue(),par(PAR_FORCEORDER).boolValue(),
            par(PAR_MAXALLOWGAP),par(PAR_DELAY),par(PAR_JITTER),
            par(PAR_COSTTIME),par(PAR_COSTBITS)
            );
    this->setQoSRequirements(req);
    //EV << "QQQQQQ\n" << cube << "\n\nXXXX\n" << this->getQoSRequirements();

}

void AEBase::handleMessage(cMessage *msg)
{

}

Flow* AEBase::getFlowObject() const {
    return FlowObject;
}

void AEBase::setFlowObject(Flow* flowObject) {
    FlowObject = flowObject;
}

bool AEBase::hasFlow(const Flow* flow) {
    return FlowObject ? *FlowObject == *flow : false;
}


const unsigned long AEBase::getCdapConId() {
    return this->cdapConId;
}
void AEBase::setCdapConId(unsigned long cdapConId) {
    this->cdapConId = cdapConId;
}


const int AEBase::getStartInvokeId() {
    return this->startInvokeId;
}

void AEBase::setStartInvokeId(int invokeId) {
    this->startInvokeId = invokeId;
}
