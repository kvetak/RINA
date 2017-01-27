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

#ifndef ADDRESS_H_
#define ADDRESS_H_

//Standard libraries
#include <string>
#include <sstream>
//RINASim libraries
#include "Common/APN.h"
#include "Common/DAP.h"

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
    static const Address UNSPECIFIED_ADDRESS;
    /**
     * @brief Constructor of blank Address
     */
    Address();

    /**
     * @brief Address constructor from unique APN
     * @param composite Expected is a string with following syntax @<ipcaddress@>_@<difname@>
     */
    Address(std::string composite);

    Address(APN apname);

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
    const APN& getApn() const;

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
