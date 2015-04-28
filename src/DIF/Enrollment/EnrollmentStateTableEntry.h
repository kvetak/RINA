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

#ifndef ENROLLMENTSTATETABLEENTRY_H_
#define ENROLLMENTSTATETABLEENTRY_H_

#include <omnetpp.h>
#include <string>
#include "Flow.h"

class EnrollmentStateTableEntry {
public:
    enum CACEConnectionStatus {CON_ERROR,
                               CON_NIL,
                               CON_FLOWPENDING,
                               CON_CONNECTPENDING,
                               CON_AUTHENTICATING,
                               CON_ESTABLISHED,
                               CON_RELEASING};

    enum EnrollmentStatus {ENROLL_ERROR,
                            ENROLL_NIL,
                            ENROLL_WAIT_START_ENROLLMENT,
                            ENROLL_WAIT_START_RESPONSE_ENROLLMENT,
                            ENROLL_WAIT_STOP_ENROLLMENT,
                            ENROLL_WAIT_STOP_RESPONSE_ENROLLMENT,
                            ENROLL_WAIT_READ_RESPONSE,
                            ENROLL_WAIT_START_OPERATION,
                            ENROLL_CREATING_OBJ,
                            ENROLL_ENROLLED};

    EnrollmentStateTableEntry();
    EnrollmentStateTableEntry(Flow* flow);
    EnrollmentStateTableEntry(Flow* flow, EnrollmentStateTableEntry::CACEConnectionStatus status, bool isInitiator);
    virtual ~EnrollmentStateTableEntry();

    Flow* getFlow();
    int getCurrentConnectRetries();
    EnrollmentStateTableEntry::CACEConnectionStatus getCACEConStatus() const;
    EnrollmentStateTableEntry::EnrollmentStatus getEnrollmentStatus() const;
    bool getIsInitiator();
    bool getIsImmediateEnrollment();

    void setIsImmediateEnrollment(bool immediate);

    void increaseCurrentConnectRetries();
    void setCACEConStatus(EnrollmentStateTableEntry::CACEConnectionStatus status);
    void setEnrollmentStatus(EnrollmentStateTableEntry::EnrollmentStatus status);

    std::string info() const;
    std::string getCACEConnectionStatus() const;
    std::string getEnrollmentStatusInfo() const;

private:
    CACEConnectionStatus conStatus;
    EnrollmentStatus enrollStatus;
    int connectRetries;
    bool immediateEnrollment;
    bool isInitiator;
    Flow *flow;
};

//Free function
std::ostream& operator<< (std::ostream& os, const EnrollmentStateTableEntry& este);

#endif /* ENROLLMENTSTATETABLEENTRY_H_ */
