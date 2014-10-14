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

#include <SearchTableEntry.h>

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
    std::stringstream os;
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
