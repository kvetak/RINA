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
//#include "APNamingInfo.h"
//#include "FABase.h"
#include "Address.h"



class DirectoryEntry {
  public:
/*
    DirectoryEntry();
    DirectoryEntry(APNamingInfo napni, Address naddr, std::string path, FABase* fa);
*/
    DirectoryEntry(const APN& napn);
    virtual ~DirectoryEntry();

    bool operator== (const DirectoryEntry& other) const;

    const APN& getApn() const;
    void setApn(const APN& apn);
    const Addresses& getSupportedDifs() const;
    void setSupportedDifs(const Addresses& supportedDifs);

    std::string info() const;

    void addDif(const Address& member);
    bool hasDif(const Address& member);

/*
    const APNamingInfo& getApni() const;
    FABase* getFlowAlloc() const;
    const std::string& getIpcPath() const;
    const Address& getAddr() const;
    cModule* getIpc();
*/

  private:
    APN Apn;
    Addresses SupportedDifs;

};

//Free function
std::ostream& operator<< (std::ostream& os, const DirectoryEntry& dte);


#endif /* DIRECTORYENTRY_H_ */
