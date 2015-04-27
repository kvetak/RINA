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

#include <EnrollmentObj.h>

EnrollmentObj::EnrollmentObj() {
}

EnrollmentObj::EnrollmentObj(const Address& srcAddr, const Address& dstAddr) {
    this->srcAddr = srcAddr;
    this->dstAddr = dstAddr;
}

EnrollmentObj::~EnrollmentObj() {
}

EnrollmentObj* EnrollmentObj::dup() const {

    EnrollmentObj* obj = new EnrollmentObj();
    obj->setAddress(this->getAddress());
    obj->setAddressExpirationTime(this->getAddressExpirationTime());
    obj->setApName(this->getApName());
    obj->setCurrentAddress(this->getCurrentAddress());
    obj->setIsImmediate(this->getIsImmediate());
    obj->setSrcAddress(this->getSrcAddress());
    obj->setDstAddress(this->getDstAddress());

    return obj;
}

void EnrollmentObj::setAddress(const APN& address) {
    this->address = address;
}

void EnrollmentObj::setApName(const APN& apName) {
    this->apName = apName;
}

void EnrollmentObj::setCurrentAddress(const APN& currentAddress) {
    this->currentAddress = currentAddress;
}

void EnrollmentObj::setAddressExpirationTime(int addressExpirationTime) {
    this->addressExpirationTime = addressExpirationTime;
}

void EnrollmentObj::setIsImmediate(bool immediate) {
    this->immediate = immediate;
}

void EnrollmentObj::setSrcAddress(const Address& srcAddr) {
    this->srcAddr = srcAddr;
}

void EnrollmentObj::setDstAddress(const Address& dstAddr) {
    this->dstAddr = dstAddr;
}

const APN& EnrollmentObj::getAddress() const {
    return this->address;
}

const APN& EnrollmentObj::getApName() const {
    return this->apName;
}

const APN& EnrollmentObj::getCurrentAddress() const {
    return this->currentAddress;
}

int EnrollmentObj::getAddressExpirationTime() const {
    return this->addressExpirationTime;
}

bool EnrollmentObj::getIsImmediate() const {
    return this->immediate;
}

const Address& EnrollmentObj::getSrcAddress() const {
    return srcAddr;
}

const Address& EnrollmentObj::getDstAddress() const {
    return dstAddr;
}
