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

#ifndef APN_H_
#define APN_H_

#include <omnetpp.h>
#include <string>
#include <sstream>

/**
 * @brief Application Process Name class
 *
 * @authors Vladimir Vesely (ivesely@fit.vutbr.cz)
 * @date Last refactorized and documented on 2014-10-28
 */
class APN
{
  public:
    /**
     * @brief Constructor creating unspecified APN
     */
    APN();

    /**
     * @brief Constructor creating APN of given name
     * @param nam Represents APN string name
     */
    APN(std::string nam);

    /**
     * @brief Destructor assigning empty string to name
     */
    virtual ~APN();

    /**
     * @brief Equal operator overloading
     * @param other APN for comparison
     * @return True if APNs string names are equal, otherwise returns false.
     */
    bool operator== (const APN& other) const
    {
        return !name.compare(other.getName());
    }

    /**
     * @brief Info text output suitable for << string streams and  WATCH
     * @return APN string name
     */
    std::string info() const;

    /**
     * @brief Gets APN string name representation
     * @return APN string
     */
    const std::string& getName() const;

    /**
     * @brief Sets APN string representation to a new value
     * @param name New APN string
     */
    void setName(const std::string& name);

  protected:
    /**
     * @brief Attribute holding APN name
     * APN is basically wrapper around string
     */
    std::string name;

};

/**
 * @brief APNList represents the list of APNs
 * @typedef APNList
 */
typedef std::list<APN> APNList;


/**
 * @brief APNList constant iterator
 * @typedef ApnCItem
 */
typedef APNList::const_iterator ApnCItem;

/**
 * @brief APNList iterator
 * @typedef ApnItem
 */
typedef APNList::iterator ApnItem;

//Free functions

/**
 * @brief << operator overload that calls APN.info() method
 * @param os Resulting ostream
 * @param apn APN class that is being converted to string
 * @return Infotext representing APN
 */
std::ostream& operator<< (std::ostream& os, const APN& apn);

/**
 * @brief << operator overload that feeds ostream with infotext of all contained APNs.
 * @param os Resulting ostream
 * @param apns APNList class that is being converted to string
 * @return Infotext representing APNList
 */
std::ostream& operator<< (std::ostream& os, const APNList& apns);

#endif /* APN_H_ */
