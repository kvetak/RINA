//
// Copyright © 2015 PRISTINE Consortium (http://ict-pristine.eu)
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
 * @file EFCPPolicySet.cc
 * @author Marcel Marek (imarek@fit.vutbr.cz)
 * @date April 3, 2015
 * @brief Holds names of EFCP policies to be used in specific QoSCube.
 * @detail
 */

#include "DIF/EFCP/EFCPPolicySet.h"

const char* ELEM_INITSEQNUM            = "InitialSeqNum";
const char* DEFAULT_INITSEQNUM         = "InitialSeqNumPolicyDefault";
const char* ELEM_RCVRINACTIV           = "RcvrInactivity";
const char* DEFAULT_RCVRINACTIV        = "RcvrInactivityPolicyDefault";
const char* ELEM_RTTESTIMAT            = "RTTEstimator";
const char* DEFAULT_RTTESTIMAT         = "RTTEstimatorPolicyDefault";
const char* ELEM_SENDERINACTIV         = "SenderInactivity";
const char* DEFAULT_SENDERINACTIV      = "SenderInactivityPolicyDefault";
const char* ELEM_SNDFCOVERRUN          = "SndFCOverrun";
const char* DEFAULT_SNDFCOVERRUN       = "SndFCOverrunPolicyDefault";
const char* ELEM_RCVFCOVERRUN          = "RcvFCOverrun";
const char* DEFAULT_RCVFCOVERRUN       = "RcvFCOverrunPolicyDefault";
const char* ELEM_LOSTCONTROLPDU        = "LostControlPDU";
const char* DEFAULT_LOSTCONTROLPDU     = "LostControlPDUPolicyDefault";
const char* ELEM_NOOVERRIDEPEAK        = "NoOverridePeak";
const char* DEFAULT_NOOVERRIDEPEAK     = "NoOverridePeakPolicyDefault";
const char* ELEM_NORATESLOWDOWN        = "NoRateSlowDown";
const char* DEFAULT_NORATESLOWDOWN     = "NoRateSlowDownPolicyDefault";
const char* ELEM_RATEREDUCTION         = "RateReduction";
const char* DEFAULT_RATEREDUCTION      = "RateReductionPolicyDefault";
const char* ELEM_RCVRACK               = "RcvrAck";
const char* DEFAULT_RCVRACK            = "RcvrAckPolicyDefault";
const char* ELEM_RCVRCONTROLACK        = "RcvrControlAck";
const char* DEFAULT_RCVRCONTROLACK     = "RcvrControlAckPolicyDefault";
const char* ELEM_RCVRFC                = "RcvrFC";
const char* DEFAULT_RCVRFC             = "RcvrFCPolicyDefault";
const char* ELEM_RECEIVINGFC           = "ReceivingFC";
const char* DEFAULT_RECEIVINGFC        = "ReceivingFCPolicyDefault";
const char* ELEM_RECONCILEFC           = "ReconcileFC";
const char* DEFAULT_RECONCILEFC        = "ReconcileFCPolicyDefault";
const char* ELEM_SENDERACK             = "SenderAck";
const char* DEFAULT_SENDERACK          = "SenderAckPolicyDefault";
const char* ELEM_SENDINGACK            = "SendingAck";
const char* DEFAULT_SENDINGACK         = "SendingAckPolicyDefault";
const char* ELEM_TXCONTROL             = "TxControl";
const char* DEFAULT_TXCONTROL          = "TxControlPolicyDefault";
const char* ELEM_RXTIMEREXPIRY         = "RxTimerExpiry";
const char* DEFAULT_RXTIMEREXPIRY      = "RxTimerExpiryPolicyDefault";
const char* ELEM_ECN                   = "ECN";
const char* DEFAULT_ECN                = "ECNPolicyDefault";
const char* ELEM_ECNSLOWDOWN           = "ECNSlowDown";
const char* DEFAULT_ECNSLOWDOWN        = "ECNSlowDownPolicyDefault";


EFCPPolicySet::EFCPPolicySet() : initialSeqNum(DEFAULT_INITSEQNUM), rcvrInactiv(DEFAULT_RCVRINACTIV),
    rttEstimat(DEFAULT_RTTESTIMAT), senderInactiv(DEFAULT_SENDERINACTIV), sndFcOverrun(DEFAULT_SNDFCOVERRUN),
    rcvFcOverrun(DEFAULT_RCVFCOVERRUN), lostControlPDU(DEFAULT_LOSTCONTROLPDU),
    noOverridePeak(DEFAULT_NOOVERRIDEPEAK), noRateSlowDown(DEFAULT_NORATESLOWDOWN),
    rateReduction(DEFAULT_RATEREDUCTION), rcvrAck(DEFAULT_RCVRACK), rcvrControlAck(DEFAULT_RCVRCONTROLACK),
    rcvrFC(DEFAULT_RCVRFC), receivingFC(DEFAULT_RECEIVINGFC), reconcileFC(DEFAULT_RECONCILEFC),
    senderAck(DEFAULT_SENDERACK), sendingAck(DEFAULT_SENDINGACK), txControl(DEFAULT_TXCONTROL), rxTimerExpiry(DEFAULT_RXTIMEREXPIRY),
    ecn(DEFAULT_ECN), ecnSlowDown(DEFAULT_ECNSLOWDOWN) {


}

EFCPPolicySet::~EFCPPolicySet()
{

}


const char* EFCPPolicySet::getInitialSeqNum() const
{
  return initialSeqNum;
}

const char* EFCPPolicySet::getRcvrInactiv() const
{
  return rcvrInactiv;
}

const char* EFCPPolicySet::getRttEstimat() const
{
  return rttEstimat;
}

const char* EFCPPolicySet::getSenderInactiv() const
{
  return senderInactiv;
}

const char* EFCPPolicySet::getSndFcOverrun() const
{
  return sndFcOverrun;
}

const char* EFCPPolicySet::getLostControlPdu() const
{
  return lostControlPDU;
}

const char* EFCPPolicySet::getNoOverridePeak() const
{
  return noOverridePeak;
}

const char* EFCPPolicySet::getNoRateSlowDown() const
{
  return noRateSlowDown;
}

const char* EFCPPolicySet::getRateReduction() const
{
  return rateReduction;
}

const char* EFCPPolicySet::getRcvrAck() const
{
  return rcvrAck;
}

const char* EFCPPolicySet::getRcvrControlAck() const
{
  return rcvrControlAck;
}

const char* EFCPPolicySet::getRcvrFc() const
{
  return rcvrFC;
}

const char* EFCPPolicySet::getReceivingFc() const
{
  return receivingFC;
}

const char* EFCPPolicySet::getReconcileFc() const
{
  return reconcileFC;
}

const char* EFCPPolicySet::getSenderAck() const
{
  return senderAck;
}

const char* EFCPPolicySet::getSendingAck() const
{
  return sendingAck;
}

const char* EFCPPolicySet::getTxControl() const
{
  return txControl;
}

const char* EFCPPolicySet::getRxTimerExpiry() const
{
  return rxTimerExpiry;
}

const char* EFCPPolicySet::getEcn() const
{
  return ecn;
}

const char* EFCPPolicySet::getEcnSlowDown() const
{
  return ecnSlowDown;
}

const char* EFCPPolicySet::getRcvFcOverrun() const
{
  return rcvFcOverrun;
}

bool EFCPPolicySet::init(cXMLElement* parent)
{


    cXMLElementList attrs = parent->getChildren();
  for (cXMLElementList::iterator jt = attrs.begin(); jt != attrs.end(); ++jt)
  {
    cXMLElement* policyTag = *jt;
    if (!strcmp(policyTag->getTagName(), ELEM_INITSEQNUM))
    {
      initialSeqNum = policyTag->getNodeValue() ? policyTag->getNodeValue() : DEFAULT_INITSEQNUM;
    }
    else if (!strcmp(policyTag->getTagName(), ELEM_RCVRINACTIV))
    {
      rcvrInactiv = policyTag->getNodeValue() ? policyTag->getNodeValue() : DEFAULT_RCVRINACTIV;
    }
    else if (!strcmp(policyTag->getTagName(), ELEM_RTTESTIMAT))
    {
      rttEstimat = policyTag->getNodeValue() ? policyTag->getNodeValue() : DEFAULT_RTTESTIMAT;
    }
    else if (!strcmp(policyTag->getTagName(), ELEM_SENDERINACTIV))
    {
      senderInactiv = policyTag->getNodeValue() ? policyTag->getNodeValue() : DEFAULT_SENDERINACTIV;
    }
    else if (!strcmp(policyTag->getTagName(), ELEM_SNDFCOVERRUN))
    {
      sndFcOverrun = policyTag->getNodeValue() ? policyTag->getNodeValue() : DEFAULT_SNDFCOVERRUN;
    }
    else if (!strcmp(policyTag->getTagName(), ELEM_RCVFCOVERRUN))
    {
      rcvFcOverrun = policyTag->getNodeValue() ? policyTag->getNodeValue() : DEFAULT_RCVFCOVERRUN;
    }
    else if (!strcmp(policyTag->getTagName(), ELEM_LOSTCONTROLPDU))
    {
      lostControlPDU = policyTag->getNodeValue() ? policyTag->getNodeValue() : DEFAULT_LOSTCONTROLPDU;
    }
    else if (!strcmp(policyTag->getTagName(), ELEM_NOOVERRIDEPEAK))
    {
      noOverridePeak = policyTag->getNodeValue() ? policyTag->getNodeValue() : DEFAULT_NOOVERRIDEPEAK;
    }
    else if (!strcmp(policyTag->getTagName(), ELEM_NORATESLOWDOWN))
    {
      noRateSlowDown = policyTag->getNodeValue() ? policyTag->getNodeValue() : DEFAULT_NORATESLOWDOWN;
    }
    else if (!strcmp(policyTag->getTagName(), ELEM_RATEREDUCTION))
    {
      rateReduction = policyTag->getNodeValue() ? policyTag->getNodeValue() : DEFAULT_RATEREDUCTION;
    }
    else if (!strcmp(policyTag->getTagName(), ELEM_RCVRACK))
    {
      rcvrAck = policyTag->getNodeValue() ? policyTag->getNodeValue() : DEFAULT_RCVRACK;
    }
    else if (!strcmp(policyTag->getTagName(), ELEM_RCVRCONTROLACK))
    {
      rcvrControlAck = policyTag->getNodeValue() ? policyTag->getNodeValue() : DEFAULT_RCVRCONTROLACK;
    }
    else if (!strcmp(policyTag->getTagName(), ELEM_RCVRFC))
    {
      rcvrFC = policyTag->getNodeValue() ? policyTag->getNodeValue() : DEFAULT_RCVRFC;
    }
    else if (!strcmp(policyTag->getTagName(), ELEM_RECEIVINGFC))
    {
      receivingFC = policyTag->getNodeValue() ? policyTag->getNodeValue() : DEFAULT_RECEIVINGFC;
    }
    else if (!strcmp(policyTag->getTagName(), ELEM_RECONCILEFC))
    {
      reconcileFC = policyTag->getNodeValue() ? policyTag->getNodeValue() : DEFAULT_RECONCILEFC;
    }
    else if (!strcmp(policyTag->getTagName(), ELEM_SENDERACK))
    {
      senderAck = policyTag->getNodeValue() ? policyTag->getNodeValue() : DEFAULT_SENDERACK;
    }
    else if (!strcmp(policyTag->getTagName(), ELEM_SENDINGACK))
    {
      sendingAck = policyTag->getNodeValue() ? policyTag->getNodeValue() : DEFAULT_SENDINGACK;
    }
    else if (!strcmp(policyTag->getTagName(), ELEM_TXCONTROL))
    {
      txControl = policyTag->getNodeValue() ? policyTag->getNodeValue() : DEFAULT_TXCONTROL;
    }
    else if (!strcmp(policyTag->getTagName(), ELEM_RXTIMEREXPIRY))
    {
      rxTimerExpiry = policyTag->getNodeValue() ? policyTag->getNodeValue() : DEFAULT_RXTIMEREXPIRY;
    }
    else if (!strcmp(policyTag->getTagName(), ELEM_ECN))
    {
      ecn = policyTag->getNodeValue() ? policyTag->getNodeValue() : DEFAULT_ECN;
    }
    else if (!strcmp(policyTag->getTagName(), ELEM_ECNSLOWDOWN))
    {
      ecnSlowDown = policyTag->getNodeValue() ? policyTag->getNodeValue() : DEFAULT_ECNSLOWDOWN;
    }
  }
  return true;
}


std::string EFCPPolicySet::info() const {
    std::ostringstream os;

    os << "\n   Inititial Seq Num = ";
        os << this->getInitialSeqNum();

        os << "\n   RcvrInactiv = ";
        os << this->getRcvrInactiv();

        os << "\n   RTT = ";
        os << this->getRttEstimat();

        os << "\n   SenderInactiv = ";
        os << this->getSenderInactiv();

        os << "\n   SndFcOverrun = ";
        os << this->getSndFcOverrun();

        os << "\n   RcvFcOverrun = ";
        os << this->getRcvFcOverrun();

        os << "\n   LostControlPDU = ";
        os << this->getLostControlPdu();

        os << "\n   NoOverridePeak = ";
        os << this->getNoOverridePeak();

        os << "\n   NoRateSlowDown = ";
        os << this->getNoRateSlowDown();

        os << "\n   RateReduction = ";
        os << this->getRateReduction();

        os << "\n   RcvrAck = ";
        os << this->getRcvrAck();

        os << "\n   RcvrAckControl = ";
        os << this->getRcvrControlAck();


        os << "\n   RcvrFC = ";
        os << this->getRcvrFc();

        os << "\n   ReceivingFC = ";
        os << this->getReceivingFc();

        os << "\n   ReconcileFC = ";
        os << this->getReconcileFc();

        os << "\n   SenderAck = ";
        os << this->getSenderAck();

        os << "\n   SendingAck = ";
                os << this->getSendingAck();

        os << "\n   TxControl = ";
        os << this->getTxControl();

        os << "\n   RxTimerExpiry = ";
        os << this->getRxTimerExpiry();

        os << "\n   ECN = ";
        os << this->getEcn();

        os << "\n   ECNSlowDown = ";
        os << this->getEcnSlowDown();



    return os.str();
}


std::ostream& operator <<(std::ostream& os, const EFCPPolicySet& efcpPolicySet) {
    return os << efcpPolicySet.info();
}

std::ostream& operator <<(std::ostream& os, const EFCPPolicySet* efcpPolicySet) {
    return os << efcpPolicySet->info();
}
