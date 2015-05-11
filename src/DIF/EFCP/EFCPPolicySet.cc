//
// Copyright © 2015 PRISTINE Consortium (http://ict-pristine.eu)
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
 * @file EFCPPolicySet.cc
 * @author Marcel Marek (imarek@fit.vutbr.cz)
 * @date April 3, 2015
 * @brief Holds names of EFCP policies to be used in specific QoSCube.
 * @detail
 */

#include <EFCPPolicySet.h>

const char* ELEM_INITSEQNUM            = "InitialSeqNum";
const char* DEFAULT_INITSEQNUM         = "InitialSeqNumPolicyDefault";
const char* ELEM_RCVRINACTIV           = "RcvrInactivity";
const char* DEFAULT_RCVRINACTIV        = "RcvrInactivityPolicyDefault";
const char* ELEM_RTTESTIMAT            = "RTTEstimator";
const char* DEFAULT_RTTESTIMAT         = "RTTEstimatorPolicyDefault";
const char* ELEM_SENDERINACTIV         = "SenderInactivity";
const char* DEFAULT_SENDERINACTIV      = "SenderInactivityPolicyDefault";
const char* ELEM_FCOVERRUN             = "FCOverrun";
const char* DEFAULT_FCOVERRUN          = "FCOverrunPolicyDefault";
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

EFCPPolicySet::EFCPPolicySet() : initialSeqNum(DEFAULT_INITSEQNUM), rcvrInactiv(DEFAULT_RCVRINACTIV),
    rttEstimat(DEFAULT_RTTESTIMAT), senderInactiv(DEFAULT_SENDERINACTIV), fcOverrun(DEFAULT_FCOVERRUN), lostControlPDU(DEFAULT_LOSTCONTROLPDU),
    noOverridePeak(DEFAULT_NOOVERRIDEPEAK), noRateSlowDown(DEFAULT_NORATESLOWDOWN),
    rateReduction(DEFAULT_RATEREDUCTION), rcvrAck(DEFAULT_RCVRACK), rcvrControlAck(DEFAULT_RCVRCONTROLACK),
    rcvrFC(DEFAULT_RCVRFC), receivingFC(DEFAULT_RECEIVINGFC), reconcileFC(DEFAULT_RECONCILEFC),
    senderAck(DEFAULT_SENDERACK), sendingAck(DEFAULT_SENDINGACK), txControl(DEFAULT_TXCONTROL){


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

const char* EFCPPolicySet::getFcOverrun() const
{
  return fcOverrun;
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
    else if (!strcmp(policyTag->getTagName(), ELEM_FCOVERRUN))
    {
      fcOverrun = policyTag->getNodeValue() ? policyTag->getNodeValue() : DEFAULT_FCOVERRUN;
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
  }
  return true;
}
