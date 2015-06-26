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

#ifndef DAP_H_
#define DAP_H_
//Standard libraries
#include <string>
#include <sstream>

/**
 * @brief Distributed Application Process name a.k.a. DAP class
 * @authors Vladimir Vesely (ivesely@fit.vutbr.cz)
 * @date Last refactorized and documented on 2014-10-28
 */
class DAP {
  public:
    /**
     * @brief Constructor creating unspecified DAP
     */
    DAP();

    /**
     * @brief Constructor creating DAP of given name
     * @param nam Represents DAP string name
     */
    DAP(std::string nam);

    /**
     * @brief Destructor assigning empty string to name
     */
    virtual ~DAP();

    /**
     * @brief Equal operator overloading
     * @param other DAP for comparison
     * @return True if DAPs string names are equal, otherwise returns false.
     */
    bool operator== (const DAP& other) const;

    /**
     * @brief Info text output suitable for << string streams and WATCH
     * @return DAP string name
     */
    std::string info() const;

    /**
     * @brief Gets DAP string name representation
     * @return DAP string
     */
    const std::string& getName() const;

    /**
     * @brief Sets DAP string representation to a new value
     * @param name A new DAP string value
     */
    void setName(const std::string& name);

  protected:
    /**
     * @brief Attribute holding DAP name
     * DAP is basically wrapper around string.
     */
    std::string name;
};

//Free function
/**
 * << operator overload that feeds ostream DAP string representation.
 * @param os Resulting ostream
 * @param dap APNList class that is being converted to string
 * @return Infotext representing DAP
 */
std::ostream& operator<< (std::ostream& os, const DAP& dap);


#endif /* DAP_H_ */
