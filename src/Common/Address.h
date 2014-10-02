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

#include <string>
#include <sstream>

class Address {
  public:
    Address();
    Address(const char* ipcaddr, const char* difnam);
    virtual ~Address();

    bool operator== (const Address& other) const;

    std::string info() const;

    const std::string& getDifName() const;
    void setDifName(const std::string& difName);
    const std::string& getIpcAddress() const;
    void setIpcAddress(const std::string& ipcAddress);

  private:
    std::string ipcAddress;
    std::string difName;
};

//Free function
std::ostream& operator<< (std::ostream& os, const Address& addr);

#endif /* ADDRESS_H_ */
