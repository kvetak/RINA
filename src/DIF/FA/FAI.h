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
/**
 * @file FAI.h
 * @author Vladimir Vesely (ivesely@fit.vutbr.cz)
 * @date Apr 30, 2014
 * @brief
 * @detail
 */
#ifndef FAI_H_
#define FAI_H_

//Standard libraries
#include <omnetpp.h>
//RINASim libraries
#include "FABase.h"
#include "Flow.h"

class FAI : public cSimpleModule  {
  public:
    FAI();
    virtual ~FAI();

    std::string info() const;

    bool receiveAllocateRequest();
    void processDegenerateDataTransfer();
    void receiveAllocateResponsePositive(cObject* obj);
    void receiveAllocateResponseNegative();
    bool receiveCreateRequest();
    void processCreateResponse();
    void receiveDeallocateRequest();
    void receiveDeleteRequest();
    void receiveDeleteResponse();

    void postInitialize(FABase* fa, Flow* fl, simsignal_t sigAlReq);

    const FABase* getFa() const {
        return FlowAlloc;
    }
    const Flow* getFlow() const {
        return FlowObject;
    }

  protected:
    int portId;
    int cepId;

    FABase* FlowAlloc;
    Flow* FlowObject;

    simsignal_t sigFAIAllocReq;
    simsignal_t sigFAICreReq;
    simsignal_t sigFAIDelReq;
    simsignal_t sigFAICreResNega;
    simsignal_t sigFAICreResPosi;

    virtual void initialize();
    virtual void handleMessage(cMessage *msg);

  private:
    bool createEFCP();
    bool createBindings();
    bool deleteBindings();


    void signalizeCreateFlowRequest(Flow* flow);
    void signalizeDeleteFlowRequest();
    void signalizeDeleteFlowResponse(Flow* flow);
    void signalizeAllocationRequestFromFAI(Flow* flow);

};

//Free function
std::ostream& operator<< (std::ostream& os, const FAI& fai);

#endif /* FAI_H_ */
