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
 * @file EFCPPolicySet.h
 * @author Marcel Marek (imarek@fit.vutbr.cz)
 * @date April 3, 2015
 * @brief Holds names of EFCP policies to be used in specific QoSCube.
 * @detail
 */

#ifndef EFCPPOLICYSET_H_
#define EFCPPOLICYSET_H_
#include <omnetpp.h>

class EFCPPolicySet
{
  private:
    const char* initialSeqNum;
    const char* rcvrInactiv;
    const char* rttEstimat;
    const char* senderInactiv;
    const char* fcOverrun;
    const char* lostControlPDU;
    const char* noOverridePeak;
    const char* noRateSlowDown;
    const char* rateReduction;
    const char* rcvrAck;
    const char* rcvrControlAck;
    const char* rcvrFC;
    const char* receivingFC;
    const char* reconcileFC;
    const char* senderAck;
    const char* sendingAck;
    const char* txControl;

  public:
    EFCPPolicySet();
    virtual ~EFCPPolicySet();
    bool init(cXMLElement* parent);
    const char* getFcOverrun() const;
    const char* getLostControlPdu() const;
    const char* getNoOverridePeak() const;
    const char* getNoRateSlowDown() const;
    const char* getRateReduction() const;
    const char* getRcvrAck() const;
    const char* getRcvrControlAck() const;
    const char* getRcvrFc() const;
    const char* getReceivingFc() const;
    const char* getReconcileFc() const;
    const char* getSenderAck() const;
    const char* getSendingAck() const;
    const char* getTxControl() const;
    const char* getInitialSeqNum() const;
    const char* getRcvrInactiv() const;
    const char* getRttEstimat() const;
    const char* getSenderInactiv() const;
};

#endif /* EFCPPOLICYSET_H_ */
