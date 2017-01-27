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
 * @file DAFEnrollmentStateTableEntry.cc
 * @author Kamil Jerabek (xjerab18@stud.fit.vutbr.cz)
 * @date Apr 1, 2015
 * @brief DAFEnrollment state table entry
 * @detail
 */


#include "DAF/Enrollment/DAFEnrollmentStateTableEntry.h"

//const int VAL_NOCONRETRY    = 0;

DAFEnrollmentStateTableEntry::DAFEnrollmentStateTableEntry() :
    Source(APNamingInfo()), Destination(APNamingInfo()),
    conStatus(this->CON_NIL),
    enrollStatus(this->ENROLL_NIL), connectRetries(VAL_NOCONRETRY),
    immediateDAFEnrollment(false)
{
}

DAFEnrollmentStateTableEntry::DAFEnrollmentStateTableEntry(APNamingInfo src, APNamingInfo dst, DAFEnrollmentStateTableEntry::CACEConnectionStatus status) :
        Source(src), Destination(dst),
        conStatus(status),
        enrollStatus(ENROLL_NIL), connectRetries(VAL_NOCONRETRY)
{
}

DAFEnrollmentStateTableEntry::DAFEnrollmentStateTableEntry(APNamingInfo src,
        APNamingInfo dst,
        DAFEnrollmentStateTableEntry::CACEConnectionStatus status,
        DAFEnrollmentStateTableEntry::DAFEnrollmentStatus enrstat) :
                Source(src), Destination(dst),
                conStatus(status),
                enrollStatus(enrstat), connectRetries(VAL_NOCONRETRY)
{
}

/*
DAFEnrollmentStateTableEntry::DAFEnrollmentStateTableEntry(Flow* flow) :
        DAFEnrollmentStateTableEntry(flow->getSrcApni(), flow->getDstApni(),
                CON_CONNECTPENDING, false)
{
    this->flow = flow;
}

DAFEnrollmentStateTableEntry::DAFEnrollmentStateTableEntry(Flow* flow, DAFEnrollmentStateTableEntry::CACEConnectionStatus status, bool isInitiator) :
        DAFEnrollmentStateTableEntry(flow->getSrcApni(), flow->getDstApni(),
                status, isInitiator)
{
    this->flow = flow;
}
*/

DAFEnrollmentStateTableEntry::~DAFEnrollmentStateTableEntry() {
    //this->flow = NULL;
    Source = APNamingInfo();
    Destination = APNamingInfo();
    conStatus = CON_NIL;
    enrollStatus = ENROLL_NIL;
    connectRetries = VAL_NOCONRETRY;
}
/*
Flow* DAFEnrollmentStateTableEntry::getFlow() {
    return flow;
}
*/

int DAFEnrollmentStateTableEntry::getCurrentConnectRetries() {
    return connectRetries;
}

bool DAFEnrollmentStateTableEntry::getIsImmediateDAFEnrollment() {
    return immediateDAFEnrollment;
}

void DAFEnrollmentStateTableEntry::setIsImmediateDAFEnrollment(bool immediate) {
    this->immediateDAFEnrollment = immediate;
}

DAFEnrollmentStateTableEntry::CACEConnectionStatus DAFEnrollmentStateTableEntry::getCACEConStatus() const{
    return conStatus;
}

void DAFEnrollmentStateTableEntry::increaseCurrentConnectRetries() {
    connectRetries++;
}

void DAFEnrollmentStateTableEntry::setCACEConStatus(DAFEnrollmentStateTableEntry::CACEConnectionStatus status){
    conStatus = status;
}

void DAFEnrollmentStateTableEntry::setDAFEnrollmentStatus(DAFEnrollmentStateTableEntry::DAFEnrollmentStatus status) {
    enrollStatus = status;
}

DAFEnrollmentStateTableEntry::DAFEnrollmentStatus DAFEnrollmentStateTableEntry::getDAFEnrollmentStatus() const {
    return enrollStatus;
}

std::string DAFEnrollmentStateTableEntry::getCACEConnectionStatusString() const {
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

std::string DAFEnrollmentStateTableEntry::getDAFEnrollmentStatusString() const {
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

std::string DAFEnrollmentStateTableEntry::info() const {
    std::ostringstream os;
    if ( !(Source == Destination) ) {
        os << "Local> " << Source  << endl
           << "Remote> " << Destination << endl;
    }
    else {
        os << Source << " is self-enrolled" << endl;
    }
    os << "CACEConnectionStatus: " << this->getCACEConnectionStatusString() << endl;
    os << "DAFEnrollmentStatus: " << this->getDAFEnrollmentStatusString() << endl;
    //os << flow->info() <<  endl;
    return os.str();
}



std::ostream& operator <<(std::ostream& os, const DAFEnrollmentStateTableEntry& este) {
    return os << este.info();
}

const APNamingInfo& DAFEnrollmentStateTableEntry::getLocal() const {
    return Source;
}

void DAFEnrollmentStateTableEntry::setLocal(const APNamingInfo& local) {
    Source = local;
}

const APNamingInfo& DAFEnrollmentStateTableEntry::getRemote() const {
    return Destination;
}

void DAFEnrollmentStateTableEntry::setRemote(const APNamingInfo& remote) {
    Destination = remote;
}

