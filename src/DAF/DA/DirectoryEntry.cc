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

#include "DAF/DA/DirectoryEntry.h"

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
    os << "APN: " << Apn << " is available via: ";
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
    return  getFlowAlloc() ? getFlowAlloc()->getModuleByPath("^.^") : NULL;
}
*/
