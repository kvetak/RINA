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

extern const int VAL_UNDEFINED;
extern const int VAL_MAXHOPCOUNT;
extern const int VAL_MAXCREATERETRIES;

/**
 * @brief Class representing flow object with attributes from specs
 * @authors Vladimir Vesely (ivesely@fit.vutbr.cz)
 * @date Last refactorized and documented on 2014-10-28
 */
class Flow : public cObject
{
  public:
    /**
     * @brief Constructor for the flow with undefined values
     */
    Flow();

    /**
     * @brief Default constructor for flow between two applications
     * @param src Source application naming info
     * @param dst Destination application naming info
     */
    Flow(APNamingInfo src, APNamingInfo dst);

    /**
     * @brief Destructor assigning default uninitialized values
     */
    virtual ~Flow();

    /**
     * @brief Equal operator overloading
     * @param other Flow for comparison
     * @return True if all atributes from this and other flow are equal
     */
    bool operator== (const Flow& other) const;

    /**
     * @brief Comparator taking into account src/dst addresses, src/dst APNIs, src-dst ConIds/PortIds
     */
    bool compare(const Flow& other) const;

    /**
     * @brief Flow object duplication method that creates copy with
     * @return
     */
    virtual Flow* dup() const;

    std::string info() const;
    std::string infoSource() const;
    std::string infoDestination() const;
    std::string infoOther() const;
    std::string infoQoS() const;

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

    const Address& getDstNeighbor() const;
    void setDstNeighbor(const Address& dstNeighbor);
    const Address& getSrcNeighbor() const;
    void setSrcNeighbor(const Address& srcNeighbor);


  protected:
    //Properties are based on RINA-Demo-2012-001.pdf page 6
    APNamingInfo srcApni;
    APNamingInfo dstApni;
    int srcPortId;
    int dstPortId;
    Address srcAddr;
    Address dstAddr;

    //TODO: Vesely - Pull neighbor addresses to child class
    Address srcNeighbor;
    Address dstNeighbor;

    ConnectionId conId;
    uint32_t createFlowRetries;
    uint32_t maxCreateFlowRetries;
    uint32_t hopCount;

    QosCube qosParameters;

    void swapPortIds();
    void swapAddresses();
    void swapCepIds();
    void swapApni();
};


//Free function
std::ostream& operator<< (std::ostream& os, const Flow& fl);

#endif /* FLOW_H_ */
