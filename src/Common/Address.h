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

#ifndef ADDRESS_H_
#define ADDRESS_H_

//Standard libraries
#include <string>
#include <sstream>
//RINASim libraries
#include "APN.h"
#include "DAP.h"

/**
 * @brief Address class holds IPC Process identification
 *
 * Class contains three attributes: IPC address identifier, common DIF name
 * and concatenation of previous two that should be used as unique APN.
 *
 * @authors Vladimir Vesely (ivesely@fit.vutbr.cz)
 * @date Last refactorized and documented on 2014-10-29
 */
class Address {
  public:

    /**
     * @brief Constructor of blank Address
     */
    Address();

    /**
     * @brief Address constructor from unique APN
     * @param composite Expected is a string with following syntax @<ipcaddress@>_@<difname@>
     */
    Address(std::string composite);

    /**
     * @brief Address constructor from both IPC address and DIF name
     * @param ipcaddr IPC Process address unambiguos inside a given DIF
     * @param difnam DIF name that this IPC Process is a member
     */
    Address(const char* ipcaddr, const char* difnam);

    /**
     * @brief Destructor assigning default values
     */
    virtual ~Address();

    /**
     * Equal operator overload
     * @param other Address for comparison
     * @return Returns true if IPC address, DIF name and AP Name
     *         are equal between this and other Address
     */
    bool operator== (const Address& other) const;

    /**
     * LesTan operator overload
     * @param other Address for comparison
     * @return Returns true if IPC address, DIF name and AP Name
     *         is smaller in this and other Address
     */
    bool operator< (const Address& other) const;

    /**
     * @brief Info text output suitable for << string streams and  WATCH
     * @return Address string representation
     */
    std::string info() const;

    /**
     * @brief Checks whether a given Address is unspecified which means that it has
     * empty attributes
     * @return True if it is unspecified, else returns false
     */
    bool isUnspecified() const;

    /**
     * @brief Getter of unique APN which is initialized during object construction
     * @return Returns APN in form of @<ipcaddress@>_@<difname@>
     */
    const APN& getApname() const;

    /**
     * @brief Getter of common DIF name
     * @return DIF name as string
     */
    const DAP& getDifName() const;

    /**
     * @brief Setter of common DIF name
     * @param difName A new DIF name value
     */
    void setDifName(const DAP& difName);

    /**
     * @brief Getter of IPC Process address which should be unambiguous within DIF
     * @return IPC Process address
     */
    const APN& getIpcAddress() const;

    /**
     * @brief Setter of IPC Process address which should be unambiguous within DIF
     * @param ipcAddress A new IPC Process address value
     */
    void setIpcAddress(const APN& ipcAddress);

  protected:
    /**
     * @brief IPC Process address represented by APN
     */
    APN ipcAddress;

    /**
     * @brief Commong DIF name represented by DAP
     */
    DAP difName;

    /**
     * @brief Concatenation of IPC Process address and DIF name represented as APN
     */
    APN apname;
};

typedef std::list<Address> Addresses;
typedef Addresses::const_iterator AddrCItem;
typedef Addresses::iterator AddrItem;

//Free function
/**
 * @brief << operator overload that calls Address.info() method
 * @param os Resulting ostream
 * @param addr Address class that is being converted to string
 * @return Infotext representing Address
 */
std::ostream& operator<< (std::ostream& os, const Address& addr);

/**
 * @brief << operator overload that calls Address.info() method for each and every list member
 * @param os Resulting ostream
 * @param dims List of Addresses
 * @return Infotext representing Address
 */
std::ostream& operator<< (std::ostream& os, const Addresses& dims);

#endif /* ADDRESS_H_ */
