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

/**
 * @file EnrollmentObj.cc
 * @author Kamil Jerabek (xjerab18@stud.fit.vutbr.cz)
 * @date Apr 1, 2015
 * @brief Enrollment object
 * @detail
 */


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
