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

#include <ConnectionTableEntry.h>

ConnectionTableEntry::ConnectionTableEntry() :  conStatus(UNKNOWN) {
}

ConnectionTableEntry::ConnectionTableEntry(APNamingInfo napni) {
    this->apni = napni;
}

ConnectionTableEntry::~ConnectionTableEntry() {
    this->conStatus = UNKNOWN;
}

const APNamingInfo& ConnectionTableEntry::getApni() const {
    return apni;
}

void ConnectionTableEntry::setApni(const APNamingInfo& apni) {
    this->apni = apni;
}

std::string ConnectionTableEntry::info() const {
    std::stringstream os;
    os << "APNI:" << apni << "\n"
       << "status: " << this->getConnectionStatusString();
    return os.str();
}

std::string ConnectionTableEntry::getConnectionStatusString() const {
    switch(this->conStatus)
    {
        case NIL:               return "NULL";
        case FLOWPENDING:       return "flowpending";
        case CONNECTPENDING:    return "connectpending";
        case AUTHENTICATING:    return "authenticating";
        case ESTABLISHED:       return "established";
        case RELEASING:         return "releasing";
        case UNKNOWN:
        default:                return "UNKNOWN";
    }
}


void ConnectionTableEntry::setConStatus(ConnectionStatus conStatus) {
    this->conStatus = conStatus;
}

std::ostream& operator <<(std::ostream& os, const ConnectionTableEntry& cte) {
    return os << cte.info();
}
