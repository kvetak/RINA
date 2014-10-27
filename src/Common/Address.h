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

class Address {
  public:
    Address();
    Address(std::string composite);
    Address(const char* ipcaddr, const char* difnam);
    virtual ~Address();

    bool operator== (const Address& other) const;

    std::string info() const;

    bool isUnspecified() const;
    const APN& getCompositeApn() const;

    const DAP& getDifName() const;
    void setDifName(const DAP& difName);
    const APN& getIpcAddress() const;
    void setIpcAddress(const APN& ipcAddress);

  private:
    APN ipcAddress;
    DAP difName;
    APN compositeAPN;
};

typedef std::list<Address> Addresses;
typedef Addresses::const_iterator AddrCItem;
typedef Addresses::iterator AddrItem;

//Free function
std::ostream& operator<< (std::ostream& os, const Address& addr);
std::ostream& operator<< (std::ostream& os, const Addresses& dims);

#endif /* ADDRESS_H_ */
