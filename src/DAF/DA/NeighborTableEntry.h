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

#ifndef NEIGHBORTABLEENTRY_H_
#define NEIGHBORTABLEENTRY_H_

//RINASim libraries
#include "APN.h"

class NeighborTableEntry {
  public:
    NeighborTableEntry(const APN& napn);
    virtual ~NeighborTableEntry();

    bool operator== (const NeighborTableEntry& other) const;

    std::string info() const;

    const APN& getApn() const;
    void setApn(const APN& apn);
    const APNList& getNeigbors() const;
    void setNeigbors(const APNList& neigbors);

    void addNeighbor(const APN& neighbor);

  private:
    APN Apn;
    APNList Neigbors;
};

//Free function
std::ostream& operator<< (std::ostream& os, const NeighborTableEntry& nte);

#endif /* NEIGHBORTABLEENTRY_H_ */
