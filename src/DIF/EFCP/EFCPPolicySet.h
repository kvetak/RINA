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
    const char* sndFcOverrun;
    const char* rcvFcOverrun;
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
    const char* rxTimerExpiry;
    const char* ecn;
    const char* ecnSlowDown;

  public:
    EFCPPolicySet();
    virtual ~EFCPPolicySet();
    bool init(cXMLElement* parent);
    const char* getSndFcOverrun() const;
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
    const char* getRxTimerExpiry() const;
    const char* getRcvFcOverrun() const;
    const char* getEcn() const;
    const char* getEcnSlowDown() const;

    std::string info() const;
};

std::ostream& operator<< (std::ostream& os, const EFCPPolicySet& efcpPolicySet);
std::ostream& operator<< (std::ostream& os, const EFCPPolicySet* efcpPolicySet);

#endif /* EFCPPOLICYSET_H_ */
