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

#ifndef DIF_EFCP_DTCP_RCVRFC_RCVRFCPOLICYDEFAULTWITHCOUNTERS_RCVRFCPOLICYDEFAULTWITHCOUNTERS_H_
#define DIF_EFCP_DTCP_RCVRFC_RCVRFCPOLICYDEFAULTWITHCOUNTERS_RCVRFCPOLICYDEFAULTWITHCOUNTERS_H_

#include "DIF/EFCP/DTCP/RcvrFC/RcvrFCPolicyBase.h"

class RcvrFCPolicyDefaultWithCounters: public virtual RcvrFCPolicyBase {
public:
    RcvrFCPolicyDefaultWithCounters();
    virtual ~RcvrFCPolicyDefaultWithCounters();
    void initialize();
    bool run(DTPState* dtpState, DTCPState* dtcpState);
    virtual void handleMessage(cMessage* msg);

private:
    simsignal_t sigStatPktRcvd, sigStatGoodput;
    uint32_t pktRcvd, lastPktRcvd;
    cMessage* m1;
};

#endif /* DIF_EFCP_DTCP_RCVRFC_RCVRFCPOLICYDEFAULTWITHCOUNTERS_RCVRFCPOLICYDEFAULTWITHCOUNTERS_H_ */
