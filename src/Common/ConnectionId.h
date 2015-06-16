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

#ifndef CONNECTIONID_H_
#define CONNECTIONID_H_

//Standard libraries
#include <cobject.h>
#include <string>

//RINASim libraries
#include "QoSCube.h"

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

#endif /* CONNECTIONID_H_ */
