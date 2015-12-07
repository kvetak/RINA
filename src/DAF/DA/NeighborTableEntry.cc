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

#include <NeighborTableEntry.h>

NeighborTableEntry::NeighborTableEntry(const APN& napn) :
    Apn(napn)
{
}

NeighborTableEntry::~NeighborTableEntry() {
    Neigbors.clear();
}

const APN& NeighborTableEntry::getApn() const {
    return Apn;
}

void NeighborTableEntry::setApn(const APN& apn) {
    Apn = apn;
}

const APNList& NeighborTableEntry::getNeigbors() const {
    return Neigbors;
}

bool NeighborTableEntry::operator ==(const NeighborTableEntry& other) const {
    return Apn == other.Apn && Neigbors == other.Neigbors;
}

std::string NeighborTableEntry::info() const {
    std::ostringstream os;
    os << "APN: " << Apn << ", Neighbors: " << Neigbors;
    return os.str();
}

void NeighborTableEntry::setNeigbors(const APNList& neigbors) {
    Neigbors = neigbors;
}

void NeighborTableEntry::addNeighbor(const APN& neighbor) {
    Neigbors.push_back(neighbor);
}

std::ostream& operator <<(std::ostream& os, const NeighborTableEntry& nte) {
    return os << nte.info();
}

bool NeighborTableEntry::hasNeighbor(const APN& neighbor) const
{
    for (ApnCItem it = Neigbors.begin(); it != Neigbors.end(); ++it) {
        if (*it == neighbor)
            return true;
    }
    return false;

}
