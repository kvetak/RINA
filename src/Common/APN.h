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
