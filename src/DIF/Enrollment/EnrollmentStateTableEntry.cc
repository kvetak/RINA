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
 * @file EnrollmentStateTableEntry.cc
 * @author Kamil Jerabek (xjerab18@stud.fit.vutbr.cz)
 * @date Apr 1, 2015
 * @brief Enrollment state table entry
 * @detail
 */


#include <EnrollmentStateTableEntry.h>

EnrollmentStateTableEntry::EnrollmentStateTableEntry() :
    conStatus(this->CON_NIL), enrollStatus(this->ENROLL_NIL), connectRetries(0),
    immediateEnrollment(false), isInitiator(false),flow(NULL)
{
}

EnrollmentStateTableEntry::EnrollmentStateTableEntry(Flow* flow) {
    this->flow = flow;
    this->conStatus = this->CON_CONNECTPENDING;
    this->connectRetries = 0;
    this->isInitiator = false;
    this->enrollStatus = this->ENROLL_NIL;
    Local = flow->getSrcApni();
    Remote = flow->getDstApni();
}

EnrollmentStateTableEntry::EnrollmentStateTableEntry(Flow* flow, EnrollmentStateTableEntry::CACEConnectionStatus status, bool isInitiator) {
    this->flow = flow;
    this->conStatus = status;
    this->connectRetries = 0;
    this->isInitiator = isInitiator;
    this->enrollStatus = this->ENROLL_NIL;
    Local = flow->getSrcApni();
    Remote = flow->getDstApni();
}

EnrollmentStateTableEntry::~EnrollmentStateTableEntry() {
    this->flow = NULL;
}

Flow* EnrollmentStateTableEntry::getFlow() {
    return flow;
}

int EnrollmentStateTableEntry::getCurrentConnectRetries() {
    return connectRetries;
}

bool EnrollmentStateTableEntry::getIsInitiator() {
    return isInitiator;
}

bool EnrollmentStateTableEntry::getIsImmediateEnrollment() {
    return immediateEnrollment;
}

void EnrollmentStateTableEntry::setIsImmediateEnrollment(bool immediate) {
    this->immediateEnrollment = immediate;
}

EnrollmentStateTableEntry::CACEConnectionStatus EnrollmentStateTableEntry::getCACEConStatus() const{
    return conStatus;
}

void EnrollmentStateTableEntry::increaseCurrentConnectRetries() {
    connectRetries++;
}

void EnrollmentStateTableEntry::setCACEConStatus(EnrollmentStateTableEntry::CACEConnectionStatus status){
    conStatus = status;
}

void EnrollmentStateTableEntry::setEnrollmentStatus(EnrollmentStateTableEntry::EnrollmentStatus status) {
    enrollStatus = status;
}

EnrollmentStateTableEntry::EnrollmentStatus EnrollmentStateTableEntry::getEnrollmentStatus() const {
    return enrollStatus;
}

std::string EnrollmentStateTableEntry::getCACEConnectionStatus() const {
    switch(this->conStatus) {
        case CON_ERROR: return "error";
        case CON_NIL: return "nil";
        case CON_FLOWPENDING: return "flow pending";
        case CON_CONNECTPENDING: return "connect pending";
        case CON_AUTHENTICATING: return "authenticating";
        case CON_ESTABLISHED: return "established";
        case CON_RELEASING: return "releasing";

        default: return "UNKNOWN";
    }
}

std::string EnrollmentStateTableEntry::getEnrollmentStatusInfo() const {
    switch(this->enrollStatus) {
        case ENROLL_ERROR: return "error";
        case ENROLL_NIL: return "nil";
        case ENROLL_WAIT_START_ENROLLMENT: return "wait start enrollment";
        case ENROLL_WAIT_START_RESPONSE_ENROLLMENT: return "wait start response enrollment";
        case ENROLL_WAIT_STOP_ENROLLMENT: return "wait stop enrollment";
        case ENROLL_WAIT_STOP_RESPONSE_ENROLLMENT: return "wait stop response enrollment";
        case ENROLL_WAIT_READ_RESPONSE: return "wait read response";
        case ENROLL_WAIT_START_OPERATION: return "wait start operation";
        case ENROLL_CREATING_OBJ: return "creating obj";
        case ENROLL_ENROLLED: return "enrolled";

        default: return "UNKNOWN";
    }
}

std::string EnrollmentStateTableEntry::info() const {
    std::ostringstream os;
    os << "Src> " << Local  << endl
       << "Dst> " << Remote << endl;
    os << "CACEConnectionStatus: " << this->getCACEConnectionStatus() << endl;
    os << "EnrollmentStatus: " << this->getEnrollmentStatusInfo() << endl;
    return os.str();
}



std::ostream& operator <<(std::ostream& os, const EnrollmentStateTableEntry& este) {
    return os << este.info();
}

const APNamingInfo& EnrollmentStateTableEntry::getLocal() const {
    return Local;
}

void EnrollmentStateTableEntry::setLocal(const APNamingInfo& local) {
    Local = local;
}

const APNamingInfo& EnrollmentStateTableEntry::getRemote() const {
    return Remote;
}

void EnrollmentStateTableEntry::setRemote(const APNamingInfo& remote) {
    Remote = remote;
}
