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

#include <Address.h>

Address::Address() : ipcAddress(APN()), difName("")
{
}

Address::Address(const char* ipcaddr, const char* difnam) :
        ipcAddress(APN(ipcaddr)), difName(DAP(difnam))
{
}

Address::~Address()
{
}

const DAP& Address::getDifName() const {
    return difName;
}

void Address::setDifName(const DAP& difName) {
    this->difName = difName;
}

const APN& Address::getIpcAddress() const {
    return ipcAddress;
}

bool Address::operator ==(const Address& other) const {
    return ipcAddress == other.ipcAddress && difName == other.difName;
}

std::string Address::info() const {
    std::stringstream os;
    if (!ipcAddress.getName().empty() && !difName.getName().empty())
        os << ipcAddress << "(" << difName << ")";
    return os.str();
}

void Address::setIpcAddress(const APN& ipcAddress) {
    this->ipcAddress = ipcAddress;
}

std::ostream& operator <<(std::ostream& os, const Address& addr) {
    return os << addr.info();
}

std::ostream& operator <<(std::ostream& os, const Addresses& dims) {
    for (AddrCItem it = dims.begin(); it != dims.end(); ++it)
        os << it->info() << endl;
    return os;
}
