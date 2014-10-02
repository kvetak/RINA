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

#ifndef DIRECTORYENTRY_H_
#define DIRECTORYENTRY_H_

//RINASim libraries
#include "APNamingInfo.h"
#include "FABase.h"
#include "Address.h"

class DirectoryEntry {
  public:
    DirectoryEntry();
    DirectoryEntry(APNamingInfo napni, Address naddr, std::string path, FABase* fa);
    virtual ~DirectoryEntry();

    std::string info() const;

    const APNamingInfo& getApni() const;
    void setApni(const APNamingInfo& apni);
    FABase* getFlowAlloc() const;
    void setFlowAlloc(FABase* flowAlloc);
    const std::string& getIpcPath() const;
    void setIpcPath(const std::string& ipcPath);
    const Address& getAddr() const;
    void setAddr(const Address& addr);

  private:
    APNamingInfo apni;
    Address addr;
    std::string ipcPath;
    FABase* FlowAlloc;
};

//Free function
std::ostream& operator<< (std::ostream& os, const DirectoryEntry& fte);

#endif /* DIRECTORYENTRY_H_ */
