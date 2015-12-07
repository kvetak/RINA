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

#include <DirectoryEntry.h>

/*
DirectoryEntry::DirectoryEntry() :
    ipcPath(""), FlowAlloc(NULL)
{

}

DirectoryEntry::DirectoryEntry(APNamingInfo napni, Address naddr, std::string path,
        FABase* fa) :
                apni(napni),
                addr(naddr),
                ipcPath(path), FlowAlloc(fa)
{
}
*/
DirectoryEntry::DirectoryEntry(const APN& napn) :
        Apn(napn)
{
}

DirectoryEntry::~DirectoryEntry() {
    SupportedDifs.clear();
}

std::ostream& operator <<(std::ostream& os, const DirectoryEntry& dte) {
    return os << dte.info();
}

std::string DirectoryEntry::info() const {
    std::ostringstream os;
    os << "APN: " << Apn << ", supported DIFs: ";
    for (AddrCItem it = SupportedDifs.begin(); it != SupportedDifs.end(); ++it)
        os << "\n    DIF: " << it->getDifName() << ", IPCaddress: " << it->getIpcAddress();
    return os.str();
}

const APN& DirectoryEntry::getApn() const {
    return Apn;
}

void DirectoryEntry::setApn(const APN& apn) {
    Apn = apn;
}

const Addresses& DirectoryEntry::getSupportedDifs() const {
    return SupportedDifs;
}

void DirectoryEntry::setSupportedDifs(const Addresses& supportedDifs) {
    SupportedDifs = supportedDifs;
}



bool DirectoryEntry::hasDif(const Address& member) {
    for (AddrCItem it = SupportedDifs.begin(); it != SupportedDifs.end(); ++it) {
        if (*it == member)
            return true;
    }
    return false;
}

void DirectoryEntry::addDif(const Address& member) {
    SupportedDifs.push_back(member);
}

bool DirectoryEntry::operator ==(const DirectoryEntry& other) const {
    return Apn == other.Apn && SupportedDifs == other.SupportedDifs;
}
/*
const APNamingInfo& DirectoryEntry::getApni() const {
    return apni;
}

void DirectoryEntry::setApni(const APNamingInfo& apni) {
    this->apni = apni;
}

FABase* DirectoryEntry::getFlowAlloc() const {
    return FlowAlloc;
}

void DirectoryEntry::setFlowAlloc(FABase* flowAlloc) {
    FlowAlloc = flowAlloc;
}

const std::string& DirectoryEntry::getIpcPath() const {
    return ipcPath;
}

void DirectoryEntry::setIpcPath(const std::string& ipcPath) {
    this->ipcPath = ipcPath;
}
*/
/*
const Address& DirectoryEntry::getAddr() const {
    return addr;
}

void DirectoryEntry::setAddr(const Address& addr) {
    this->addr = addr;
}

cModule* DirectoryEntry::getIpc() {
    return  getFlowAlloc() ? getFlowAlloc()->getParentModule()->getParentModule() : NULL;
}
*/
