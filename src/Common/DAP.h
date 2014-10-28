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

#ifndef DAP_H_
#define DAP_H_
//Standard libraries
#include <string>
#include <sstream>

/**
 * @brief Distributed Application Process name a.k.a. DAP class
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
     * @brief Info text output suitable for << string streams and  WATCH
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
