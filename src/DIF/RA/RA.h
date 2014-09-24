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
 * @file RA.h
 * @author Tomas Hykel (xhykel01@stud.fit.vutbr.cz)
 * @brief
 * @detail
 */

#ifndef __RINA_RA_H_
#define __RINA_RA_H_

#include <omnetpp.h>
#include "FA.h"
#include "DA.h"
#include "Flow.h"
#include "FABase.h"
#include "RMT.h"

class RA : public cSimpleModule
{
  public:

  protected:
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);

  private:
    DA* DifAllocator;
    RMT* rmt;
    std::string processName;

    void createFlow(std::string dstIpc);
    void removeFlow();

    void bindFlowToRMT(cModule* ipc, Flow *flow);
    void bindMediumToRMT();

    void registerFASigs();
    void registerFAISigs();

    //--------------------- FA ---------------------
    //Signals
    simsignal_t sigFACreReq;
    simsignal_t sigFACreRes;
    simsignal_t sigDelReq;
    simsignal_t sigDelRes;
    //Signaling
    void signalizeFACreateRequestFlow();
    void signalizeFACreateResponseFlow();
    void signalizeFADeleteRequestFlow();
    void signalizeFADeleteResponseFlow();
    //--------------------- FAI ---------------------


};

#endif
