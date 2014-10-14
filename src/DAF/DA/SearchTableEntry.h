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

#ifndef SEARCHTABLEENTRY_H_
#define SEARCHTABLEENTRY_H_

//RINASim libraries
#include "APN.h"

class SearchTableEntry {
  public:
    SearchTableEntry(const APN& napn);
    virtual ~SearchTableEntry();

    bool operator== (const SearchTableEntry& other) const;

    std::string info() const;

    const APN& getApn() const;
    void setApn(const APN& apn);
    const APNList& getPeers() const;
    void setPeers(const APNList& peerDas);

    void addPeer(const APN& peer);

  private:
    APN Apn;
    APNList PeerDAs;
};

//Free function
std::ostream& operator<< (std::ostream& os, const SearchTableEntry& ste);

#endif /* SEARCHTABLEENTRY_H_ */
