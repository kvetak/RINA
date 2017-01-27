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
 * @file EnrollmentStateTableEntry.h
 * @author Kamil Jerabek (xjerab18@stud.fit.vutbr.cz)
 * @date Apr 1, 2015
 * @brief Enrollment state table entry
 * @detail
 */


#ifndef ENROLLMENTSTATETABLEENTRY_H_
#define ENROLLMENTSTATETABLEENTRY_H_

#include <omnetpp.h>
#include <string>
#include "Common/Flow.h"

extern const int VAL_NOCONRETRY;

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
    EnrollmentStateTableEntry(APNamingInfo src, APNamingInfo dst, EnrollmentStateTableEntry::CACEConnectionStatus status);
    EnrollmentStateTableEntry(APNamingInfo src, APNamingInfo dst, EnrollmentStateTableEntry::CACEConnectionStatus status, EnrollmentStateTableEntry::EnrollmentStatus enrstat);
    //EnrollmentStateTableEntry(Flow* flow);
    //EnrollmentStateTableEntry(Flow* flow, EnrollmentStateTableEntry::CACEConnectionStatus status, bool isInitiator);
    virtual ~EnrollmentStateTableEntry();

    //Flow* getFlow();
    int getCurrentConnectRetries();
    EnrollmentStateTableEntry::CACEConnectionStatus getCACEConStatus() const;
    EnrollmentStateTableEntry::EnrollmentStatus getEnrollmentStatus() const;
    bool getIsImmediateEnrollment();

    void setIsImmediateEnrollment(bool immediate);

    void increaseCurrentConnectRetries();
    void setCACEConStatus(EnrollmentStateTableEntry::CACEConnectionStatus status);
    void setEnrollmentStatus(EnrollmentStateTableEntry::EnrollmentStatus status);

    std::string info() const;
    std::string getCACEConnectionStatusString() const;
    std::string getEnrollmentStatusString() const;
    const APNamingInfo& getLocal() const;
    void setLocal(const APNamingInfo& local);
    const APNamingInfo& getRemote() const;
    void setRemote(const APNamingInfo& remote);

private:
    APNamingInfo Source;
    APNamingInfo Destination;
    CACEConnectionStatus conStatus;
    EnrollmentStatus enrollStatus;
    int connectRetries;
    bool immediateEnrollment;
    //Flow *flow;

};

//Free function
std::ostream& operator<< (std::ostream& os, const EnrollmentStateTableEntry& este);

#endif /* ENROLLMENTSTATETABLEENTRY_H_ */
