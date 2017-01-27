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

#include "DAF/DA/SearchTableEntry.h"

SearchTableEntry::SearchTableEntry(const APN& napn) : Apn(napn)
{
}

SearchTableEntry::~SearchTableEntry() {
    PeerDAs.clear();
}

const APN& SearchTableEntry::getApn() const {
    return Apn;
}

void SearchTableEntry::setApn(const APN& apn) {
    Apn = apn;
}

const APNList& SearchTableEntry::getPeers() const {
    return PeerDAs;
}

bool SearchTableEntry::operator ==(const SearchTableEntry& other) const {
    return Apn == other.Apn && PeerDAs == other.PeerDAs;
}

std::string SearchTableEntry::info() const {
    std::ostringstream os;
    os << "APN: " << Apn << ", Peer DifAllocs: " << PeerDAs;
    return os.str();
}

void SearchTableEntry::setPeers(const APNList& peerDas) {
    PeerDAs = peerDas;
}

void SearchTableEntry::addPeer(const APN& peer) {
    PeerDAs.push_back(peer);
}

std::ostream& operator <<(std::ostream& os, const SearchTableEntry& ste) {
    return os << ste.info();
}
