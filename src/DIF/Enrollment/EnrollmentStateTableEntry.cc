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

#include "DIF/Enrollment/EnrollmentStateTableEntry.h"

const int VAL_NOCONRETRY    = 0;

EnrollmentStateTableEntry::EnrollmentStateTableEntry() :
    Source(APNamingInfo()), Destination(APNamingInfo()),
    conStatus(this->CON_NIL),
    enrollStatus(this->ENROLL_NIL), connectRetries(VAL_NOCONRETRY),
    immediateEnrollment(false)
{
}

EnrollmentStateTableEntry::EnrollmentStateTableEntry(APNamingInfo src, APNamingInfo dst, EnrollmentStateTableEntry::CACEConnectionStatus status) :
        Source(src), Destination(dst),
        conStatus(status),
        enrollStatus(ENROLL_NIL), connectRetries(VAL_NOCONRETRY)
{
}

EnrollmentStateTableEntry::EnrollmentStateTableEntry(APNamingInfo src,
        APNamingInfo dst,
        EnrollmentStateTableEntry::CACEConnectionStatus status,
        EnrollmentStateTableEntry::EnrollmentStatus enrstat) :
                Source(src), Destination(dst),
                conStatus(status),
                enrollStatus(enrstat), connectRetries(VAL_NOCONRETRY)
{
}

/*
EnrollmentStateTableEntry::EnrollmentStateTableEntry(Flow* flow) :
        EnrollmentStateTableEntry(flow->getSrcApni(), flow->getDstApni(),
                CON_CONNECTPENDING, false)
{
    this->flow = flow;
}

EnrollmentStateTableEntry::EnrollmentStateTableEntry(Flow* flow, EnrollmentStateTableEntry::CACEConnectionStatus status, bool isInitiator) :
        EnrollmentStateTableEntry(flow->getSrcApni(), flow->getDstApni(),
                status, isInitiator)
{
    this->flow = flow;
}
*/

EnrollmentStateTableEntry::~EnrollmentStateTableEntry() {
    //this->flow = NULL;
    Source = APNamingInfo();
    Destination = APNamingInfo();
    conStatus = CON_NIL;
    enrollStatus = ENROLL_NIL;
    connectRetries = VAL_NOCONRETRY;
}
/*
Flow* EnrollmentStateTableEntry::getFlow() {
    return flow;
}
*/

int EnrollmentStateTableEntry::getCurrentConnectRetries() {
    return connectRetries;
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

std::string EnrollmentStateTableEntry::getCACEConnectionStatusString() const {
    switch(this->conStatus) {
        case CON_ERROR:             return "error";
        case CON_NIL:               return "nil";
        case CON_FLOWPENDING:       return "flow pending";
        case CON_CONNECTPENDING:    return "connect pending";
        case CON_AUTHENTICATING:    return "authenticating";
        case CON_ESTABLISHED:       return "established";
        case CON_RELEASING:         return "releasing";

        default:                    return "UNKNOWN";
    }
}

std::string EnrollmentStateTableEntry::getEnrollmentStatusString() const {
    switch(this->enrollStatus) {
        case ENROLL_ERROR:                          return "error";
        case ENROLL_NIL:                            return "nil";
        case ENROLL_WAIT_START_ENROLLMENT:          return "wait start enrollment";
        case ENROLL_WAIT_START_RESPONSE_ENROLLMENT: return "wait start response enrollment";
        case ENROLL_WAIT_STOP_ENROLLMENT:           return "wait stop enrollment";
        case ENROLL_WAIT_STOP_RESPONSE_ENROLLMENT:  return "wait stop response enrollment";
        case ENROLL_WAIT_READ_RESPONSE:             return "wait read response";
        case ENROLL_WAIT_START_OPERATION:           return "wait start operation";
        case ENROLL_CREATING_OBJ:                   return "creating obj";
        case ENROLL_ENROLLED:                       return "enrolled";

        default:                                    return "UNKNOWN";
    }
}

std::string EnrollmentStateTableEntry::info() const {
    std::ostringstream os;
    if ( !(Source == Destination) ) {
        os << "Local> " << Source  << endl
           << "Remote> " << Destination << endl;
    }
    else {
        os << Source << " is self-enrolled" << endl;
    }
    os << "CACEConnectionStatus: " << this->getCACEConnectionStatusString() << endl;
    os << "EnrollmentStatus: " << this->getEnrollmentStatusString() << endl;
    //os << flow->info() <<  endl;
    return os.str();
}



std::ostream& operator <<(std::ostream& os, const EnrollmentStateTableEntry& este) {
    return os << este.info();
}

const APNamingInfo& EnrollmentStateTableEntry::getLocal() const {
    return Source;
}

void EnrollmentStateTableEntry::setLocal(const APNamingInfo& local) {
    Source = local;
}

const APNamingInfo& EnrollmentStateTableEntry::getRemote() const {
    return Destination;
}

void EnrollmentStateTableEntry::setRemote(const APNamingInfo& remote) {
    Destination = remote;
}

