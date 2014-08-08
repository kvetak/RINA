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

DirectoryEntry::DirectoryEntry() : ipcPath(""), FlowAlloc(NULL) {

}

DirectoryEntry::DirectoryEntry(APNamingInfo napni, std::string path,
        FABase* fa) : apni(napni), ipcPath(path), FlowAlloc(fa) {
}

DirectoryEntry::~DirectoryEntry() {
    FlowAlloc = NULL;
    ipcPath = "";
}

std::string DirectoryEntry::info() const {
    std::stringstream os;
    os << "APNI>\t" << apni << endl
       << "IPC>\t" << ipcPath << endl
       << " FA>\t" << FlowAlloc << " id=" << FlowAlloc->getId();
    return os.str();
}

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

std::ostream& operator <<(std::ostream& os, const DirectoryEntry& fte) {
    return os << fte.info();
}


