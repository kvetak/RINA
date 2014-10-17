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

#ifndef FLOW_H_
#define FLOW_H_

//Standard libraries
#include <string>
#include <sstream>
//RINASim libraries
#include "APNamingInfo.h"
#include "ConnectionId.h"
#include "Address.h"

extern const int VAL_UNDEF_PORTADDR;
extern const int VAL_MAXHOPCOUNT;
extern const int VAL_MAXCREATERETRIES;

class Flow : public cObject
{
  public:
    Flow();
    Flow(APNamingInfo src, APNamingInfo dst);
    virtual ~Flow();

    //TODO: VV - Completely missing overloading of < and > operators

    bool operator== (const Flow& other);

    virtual Flow* dup() const;

    std::string info() const;

    std::string getFlowName() const;
    Flow& swapFlow();

    ConnectionId& getConnectionId();
    const ConnectionId& getConId() const;
    void setConId(const ConnectionId& conId);
    uint32_t getCreateFlowRetries() const;
    void setCreateFlowRetries(uint32_t createFlowRetries);
    const APNamingInfo& getDstApni() const;
    void setDstApni(const APNamingInfo& dstApni);
    int getDstPortId() const;
    void setDstPortId(int dstPortId);
    uint32_t getHopCount() const;
    void setHopCount(uint32_t hopCount);
    uint32_t getMaxCreateFlowRetries() const;
    void setMaxCreateFlowRetries(uint32_t maxCreateFlowRetries);
    const APNamingInfo& getSrcApni() const;
    void setSrcApni(const APNamingInfo& srcApni);
    int getSrcPortId() const;
    void setSrcPortId(int srcPortId);
    const Address& getDstAddr() const;
    void setDstAddr(const Address& dstAddr);
    const Address& getSrcAddr() const;
    void setSrcAddr(const Address& srcAddr);
    const QosCube& getQosParameters() const;
    void setQosParameters(const QosCube& qosParameters);

  protected:
    //Properties are based on RINA-Demo-2012-001.pdf page 6
    APNamingInfo srcApni;
    APNamingInfo dstApni;
    int srcPortId;
    int dstPortId;
    Address srcAddr;
    Address dstAddr;
    ConnectionId conId;
    uint32_t createFlowRetries;
    uint32_t maxCreateFlowRetries;
    uint32_t hopCount;

    QosCube qosParameters;

    void swapPortIds();
    void swapAddresses();
    void swapCepIds();
};

//Free function
std::ostream& operator<< (std::ostream& os, const Flow& fl);

#endif /* FLOW_H_ */
