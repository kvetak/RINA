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

#ifndef FLOW_H_
#define FLOW_H_

//Standard libraries
#include <string>
#include <sstream>
//RINASim libraries
#include "Common/APNamingInfo.h"
#include "Common/ConnectionId.h"
#include "Common/Address.h"
#include "Common/QoSReq.h"

extern const int VAL_UNDEF_PORTID;
extern const int VAL_MGMT_PORTID;
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

    Flow* dupToMgmt() const;

    //Various string output functions
    /**
     * @brief Prints Flow information as string
     * Calls variety of other info functions to produce final output
     * @return String of Flow textual representation
     */
    std::string info() const;

    /**
     * @brief Prints Flow source information as string
     * Outputs source APNI, address, neigbor-address, PortId, CEP-Id
     * @return String representing Flow source
     */
    std::string infoSource() const;

    /**
     * @brief Prints Flow destination information as string
     * Outputs destination APNI, address, neigbor-address, PortId, CEP-Id
     * @return String representing Flow destination
     */
    std::string infoDestination() const;

    /**
     * @brief Prints Flow create flow information and hop-cpunt as string
     * @return String containing CreateFlow retries, MaxFlowRetries and hop-count numbers
     */
    std::string infoOther() const;

    /**
     * @brief Prints RA's QoSCube-id that FA choosed during Flow allocation phase
     * Accompanied QoSParameters could be find in AE that starts communication.
     * They are omitted in order to make debug outputs more readable.
     * @return String of RA's QoSCube-id
     */
    std::string infoQoS() const;

    /**
     * @brief Prints flow name consisting of source and destination APNI
     * Primary use is for OMNeT++ cMessage property to easily recognize which message is which
     * @return String with concatenated source and destination
     */
    std::string getFlowName() const;

    /**
     * @brief Function that swaps relevant source and destination Flow parameters
     * It is being used mainly for counterpart communication during Flow (de)allocation
     * @return Returns same flow but with swapped properties
     */
    Flow& swapFlow();

    /**
     * @brief Gets Flow's ConnectionId
     * @return ConnectionId instance
     */
    ConnectionId& getConnectionId();

    /**
     * @brief Gets read-only Flow's ConnectionId
     * @return Read-only ConnectionId instance
     */
    const ConnectionId& getConId() const;

    /**
     * @brief Sets Flow's ConnectionId
     * @param conId A new ConnectionId instance
     */
    void setConId(const ConnectionId& conId);


    void setQosCube(const QoSCube& qosCube);

    const QoSCube& getQosCube() const;

    /**
     * @brief Gets QoS parameters wanted by flow initiator
     * @return Read-only QoSReq instance
     */
    const QoSReq& getQosRequirements() const;

    QoSReq& getQosReqs();

    /**
     * @brief Sets QoS parameters wanted by flow initiator
     * @param qosParameters A new QoSReq instance that is accompanied with Flow
     */
    void setQosRequirements(const QoSReq& qosReqs);

    /**
     * @brief Gets read-only source APNamingInfo
     * @return Read-only APNamingInfo instance
     */
    const APNamingInfo& getSrcApni() const;

    /**
     * @brief Sets source APNamingInfo
     * @param srcApni A new source APNI instance
     */

    void setSrcApni(const APNamingInfo& srcApni);

    /**
     * @brief Gets read-only destination APNamingInfo
     * @return Read-only APNamingInfo instance
     */
    const APNamingInfo& getDstApni() const;

    /**
     * @brief Sets destination APNamingInfo
     * @param dstApni A new destination APNI instance
     */
    void setDstApni(const APNamingInfo& dstApni);

    /**
     * @brief Gets source PortId
     * @return Read-only PortId number
     */
    int getSrcPortId() const;

    /**
     * @brief Sets source PortId
     * @param srcPortId A new PortId number
     */
    void setSrcPortId(int srcPortId);

    /**
     * @brief Gets destination PortId
     * @return Read-only PortId number
     */
    int getDstPortId() const;

    /**
     * @brief Sets destination PortId
     * @param srcPortId A new PortId number
     */
    void setDstPortId(int dstPortId);

    /**
     * @brief Gets current number of CreateFlow retries
     * During Flow allocation phase, CreateFlow is incremented each time M_CREATE(flow) is sent
     * @return Unsigned number of CreateFlow retry occurences
     */
    uint32_t getCreateFlowRetries() const;

    /**
     * @brief Sets current number of CreateFlow retries
     * During Flow allocation phase, CreateFlow is incremented each time M_CREATE(flow) is sent
     */
    void setCreateFlowRetries(uint32_t createFlowRetries);

    /**
     * @brief Gets maximum allowed number CreateFlow retries
     * By default 3 (const VAL_MAXCREATERETRIES). Value is checked during Flow allocation.
     * @return Unsigned number of CreateFlow retry occurrences
     */
    uint32_t getMaxCreateFlowRetries() const;

    /**
     * @brief Sets maximum allowed number of CreateFlow retries
     * @param maxCreateFlowRetries Unsigned number specifying upper border
     */
    void setMaxCreateFlowRetries(uint32_t maxCreateFlowRetries);

    /**
     * @brief Gets hop-count, which is number of allowed message forwards from this device towards destination
     * By default its initial value is 16 (const VAL_MAXHOPCOUNT).
     * @return Unsigned number representing current hop-count
     */
    uint32_t getHopCount() const;

    /**
     * @brief Sets a new hop-count. Hop-count should be decremented each time message is forwarded within DIF.
     * @param hopCount Unsigned number representing new hop-count
     */
    void setHopCount(uint32_t hopCount);

    /**
     * @brief Gets source Address, which is the address of communication start-point
     * @return Read-only source Address instance
     */
    const Address& getSrcAddr() const;

    /**
     * @brief Sets (start-point) source Address
     * @param srcAddr A new source Address instance
     */
    void setSrcAddr(const Address& srcAddr);

    /**
     * @brief Gets source Address, which is the address of communication end-point
     * @return Read-only destination Address instance
     */
    const Address& getDstAddr() const;

    /**
     * @brief Sets (end-point) destination Address
     * @param dstAddr A new destination Address instance
     */
    void setDstAddr(const Address& dstAddr);

    //TODO: Vesely - Pull addresses to new Flow child class

    /**
     * @brief Gets neighbor source Address, which is the address of (interim) hop-by-hop source
     * Used during flow allocation to pass the M_CREATE(_R)(flow) messages
     * @return Read-only source Address instance
     */
    const Address& getSrcNeighbor() const;

    /**
     * @brief Sets neighbor source Address
     * @param srcNeighbor A new neighbor source Address instance
     */
    void setSrcNeighbor(const Address& srcNeighbor);

    /**
     * @brief Gets neighbor destination Address, which is the address of (interim) hop-by-hop destination
     * Used during flow allocation to pass the M_CREATE(_R)(flow) messages
     * @return Read-only destination Address instance
     */
    const Address& getDstNeighbor() const;

    /**
     * @brief Sets neighbor destination Address
     * @param dstNeighbor A new neighbor destination Address instance
     */
    void setDstNeighbor(const Address& dstNeighbor);

    /**
     * @brief Gets allocation InvokeId
     * Used inside M_CREATE(_R)(flow) messages
     * @return Read-only allocation InvokeId
     */
    long getAllocInvokeId() const;

    /**
     * @brief Sets allocation InvokeId
     * @param allocInvokeId A new allocation InvokeId
     */
    void setAllocInvokeId(long allocInvokeId);

    /**
     * @brief Gets deallocation InvokeId
     * Used inside M_DELETE(_R)(flow) messages
     * @return Read-only allocation InvokeId
     */
    long getDeallocInvokeId() const;

    /**
     * @brief Sets deallocation InvokeId
     * @param deallocInvokeId A new deallocation InvokeId
     */
    void setDeallocInvokeId(long deallocInvokeId);

    /**
     * @brief Gets whether flow is for Degenerate Data Transfer
     * @return True if DDT otherwise false
     */
    bool isDdtFlag() const;

    /**
     * @brief Sets Degenerate Data Transfer flag
     * @param ddtFlag True if DDT otherwise false
     */
    void setDdtFlag(bool ddtFlag);

    bool isManagementFlow() const;

    bool isManagementFlowLocalToIPCP() const;

  protected:
    //Properties are based on RINA-Demo-2012-001.pdf page 6

    /**
     * @brief Attribute holding source APNI
     */
    APNamingInfo srcApni;

    /**
     * @brief Attribute holding destination APNI
     */
    APNamingInfo dstApni;

    /**
     * @brief Attribute holding source PortId
     */
    int srcPortId;

    /**
     * @brief Attribute holding destination PortId
     */
    int dstPortId;

    /**
     * @brief Attribute holding source address (initiator of communication)
     */
    Address srcAddr;

    /**
     * @brief Attribute holding destination address (end-host for communication)
     */
    Address dstAddr;

    /**
     * @brief Attribute holding hop-by-hop source address
     */
    Address srcNeighbor;

    /**
     * @brief Attribute holding hop-by-hop destination address
     */
    Address dstNeighbor;

    /**
     * @brief Attribute holding ConnectionId containing source and destination CEP-Ids and chosen RA's QoSCube
     */
    ConnectionId conId;

    /**
     * @brief Attribute holding current number of allowed CreateFlow retries
     */
    uint32_t createFlowRetries;

    /**
     * @brief Attribute holding maximum allowed number of CreateFlow retries
     */
    uint32_t maxCreateFlowRetries;

    /**
     * @brief Attribute holding flow's hop-count
     */
    uint32_t hopCount;


    /**
     * @brief Attribute holding the assigned QoSCube
     */
    QoSCube qosCube;

    /**
     * @brief Attribute holding wanted QoS parameters in form of QoSReq
     */
    QoSReq qosReqs;

    /**
     * @brief Attribute holding persistant InvokeId used for allocation
     */
    long allocInvokeId;

    /**
     * @brief Attribute holding persistant InvokeId used for deallocation
     */
    long deallocInvokeId;

    /**
     * @brief Attribute representing whether flow is for Degenerate Data Transfer or not
     */
    bool ddtFlag;

    /**
     * @brief Auxiliary function swapping source and destination PortIds
     */
    void swapPortIds();

    /**
     * @brief Auxiliary function swapping source and destination Addresses
     */
    void swapAddresses();

    /**
     * @brief Auxiliary function swapping source and destination CEP-Ids
     */
    void swapCepIds();

    /**
     * @brief Auxiliary function swapping source and destinatio APNI
     */
    void swapApni();


};


//Free function
/**
 * << operator overload that feeds ostream with Flow string representation.
 * @param os Resulting ostream
 * @param fl Flow class that is being converted to string
 * @return Infotext representing Flow
 */
std::ostream& operator<< (std::ostream& os, const Flow& fl);

#endif /* FLOW_H_ */
