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

#ifndef CONNECTIONID_H_
#define CONNECTIONID_H_

//Standard libraries
#include <omnetpp.h>
#include <string>

//RINASim libraries
#include "Common/QoSCube.h"

//Consts
extern const int VAL_UNDEF_CEPID;
extern const int VAL_MGMT_CEPID;

/**
 * @brief Connection identifier as defined in specifications
 * @authors Vladimir Vesely (ivesely@fit.vutbr.cz)
 * @date Last refactorized and documented 2014-10-28
 */
class ConnectionId: public cObject {
  public:

    /**
     * @brief Constructor of blank ConnectionId
     */
    ConnectionId();

    /**
     * @brief Destructor assigning undefined values
     */
    virtual ~ConnectionId();

    /**
     * @brief Getter of destination Connection-Endpoint identifier
     * @return Returns destination CEP-id
     */
    int getDstCepId() const;

    /**
     * @brief Setter of destination Connection-Endpoint identifier
     * @param destCepId A new destination CEP-id value
     */
    void setDstCepId(int destCepId);

    /**
     * @brief Getter of selected QoS-cube identifier
     * @return Returns QoS-cube identifier
     */
    std::string getQoSId() const;

    /**
     * @brief Setter of selected QoS-cube identifier
     * @param qoSId A new QoS-cube id value
     */
    void setQoSId(std::string qoSId);

    /**
     * @brief Getter of source Connection-Endpoint identifier
     * @return Returns source CEP-id
     */
    int getSrcCepId() const;

    /**
     * @brief Setter of source Connection-Endpoint identifier
     * @param srcCepId A new source CEP-id value
     */
    void setSrcCepId(int srcCepId);

    /**
     * @brief Less operator overload
     * @param other ConnectionId for comparison
     * @return True if this QosId, dstCEPid, srcCEPid are lesser than others.
     *         Otherwise returns false
     */
    bool operator<(const ConnectionId other) const;

    /**
     * @brief Equal operator overload
     * @param other ConnectionId for comparison
     * @return True if this QosId, dstCEPid, srcCEPid are equal with others.
     *         Otherwise returns false
     */
    bool operator==(const ConnectionId other) const;

    /**
     * @brief Duplicate overload creates exact copy of ConnectionId
     * @return Pointer to a copy
     */
    virtual ConnectionId *dup() const;

    /**
     * @brief Exchanges source and destination CEP identifiers
     * @return Pointer to this object
     */
    ConnectionId& swapCepIds();


    /**
     * @brief Info text outpu suitable for << strinng streams and WATCH
     * @return
     */
    std::string info() const;

  protected:
    /**
     * @brief QoS-cube identifier
     */
    std::string qosId;

    /**
     * @brief Source Connection-Endpoint identifier
     */
    int srcCEPId;

    /**
     * @brief Destination Connection-Endpoint identifier
     */
    int dstCEPId;

};


std::ostream& operator<< (std::ostream& os, const ConnectionId& connId);

#endif /* CONNECTIONID_H_ */
