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

#include "DAF/DA/NeighborTableEntry.h"

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
    os << "APN: " << Apn << ", Neighbors: ";
    for (auto n : Neigbors){
        os << "\n\t" << n.info();
    }
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
