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
}

EnrollmentStateTableEntry::EnrollmentStateTableEntry(Flow* flow, EnrollmentStateTableEntry::CACEConnectionStatus status, bool isInitiator) {
    this->flow = flow;
    this->conStatus = status;
    this->connectRetries = 0;
    this->isInitiator = isInitiator;
    this->enrollStatus = this->ENROLL_NIL;
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
    os << "CACEConnectionStatus: " << this->getCACEConnectionStatus() << endl;
    os << "EnrollmentStatus: " << this->getEnrollmentStatusInfo() << endl;

    return os.str();
}



std::ostream& operator <<(std::ostream& os, const EnrollmentStateTableEntry& este) {
    return os << este.info();
}

