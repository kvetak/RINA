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
 * @file DAFEnrollmentStateTableEntry.h
 * @author Kamil Jerabek (xjerab18@stud.fit.vutbr.cz)
 * @date Apr 1, 2015
 * @brief DAFEnrollment state table entry
 * @detail
 */


#ifndef DAFENROLLMENTSTATETABLEENTRY_H_
#define DAFENROLLMENTSTATETABLEENTRY_H_

#include <omnetpp.h>
#include <string>
#include "Common/Flow.h"

extern const int VAL_NOCONRETRY;

class DAFEnrollmentStateTableEntry {
public:
    enum CACEConnectionStatus {CON_ERROR,
                               CON_NIL,
                               CON_FLOWPENDING,
                               CON_CONNECTPENDING,
                               CON_AUTHENTICATING,
                               CON_ESTABLISHED,
                               CON_RELEASING};

    enum DAFEnrollmentStatus {ENROLL_ERROR,
                            ENROLL_NIL,
                            ENROLL_WAIT_START_ENROLLMENT,
                            ENROLL_WAIT_START_RESPONSE_ENROLLMENT,
                            ENROLL_WAIT_STOP_ENROLLMENT,
                            ENROLL_WAIT_STOP_RESPONSE_ENROLLMENT,
                            ENROLL_WAIT_READ_RESPONSE,
                            ENROLL_WAIT_START_OPERATION,
                            ENROLL_CREATING_OBJ,
                            ENROLL_ENROLLED};

    DAFEnrollmentStateTableEntry();
    DAFEnrollmentStateTableEntry(APNamingInfo src, APNamingInfo dst, DAFEnrollmentStateTableEntry::CACEConnectionStatus status);
    DAFEnrollmentStateTableEntry(APNamingInfo src, APNamingInfo dst, DAFEnrollmentStateTableEntry::CACEConnectionStatus status, DAFEnrollmentStateTableEntry::DAFEnrollmentStatus enrstat);
    //DAFEnrollmentStateTableEntry(Flow* flow);
    //DAFEnrollmentStateTableEntry(Flow* flow, DAFEnrollmentStateTableEntry::CACEConnectionStatus status, bool isInitiator);
    virtual ~DAFEnrollmentStateTableEntry();

    //Flow* getFlow();
    int getCurrentConnectRetries();
    DAFEnrollmentStateTableEntry::CACEConnectionStatus getCACEConStatus() const;
    DAFEnrollmentStateTableEntry::DAFEnrollmentStatus getDAFEnrollmentStatus() const;
    bool getIsImmediateDAFEnrollment();

    void setIsImmediateDAFEnrollment(bool immediate);

    void increaseCurrentConnectRetries();
    void setCACEConStatus(DAFEnrollmentStateTableEntry::CACEConnectionStatus status);
    void setDAFEnrollmentStatus(DAFEnrollmentStateTableEntry::DAFEnrollmentStatus status);

    std::string info() const;
    std::string getCACEConnectionStatusString() const;
    std::string getDAFEnrollmentStatusString() const;
    const APNamingInfo& getLocal() const;
    void setLocal(const APNamingInfo& local);
    const APNamingInfo& getRemote() const;
    void setRemote(const APNamingInfo& remote);

private:
    APNamingInfo Source;
    APNamingInfo Destination;
    CACEConnectionStatus conStatus;
    DAFEnrollmentStatus enrollStatus;
    int connectRetries;
    bool immediateDAFEnrollment;
    //Flow *flow;

};

//Free function
std::ostream& operator<< (std::ostream& os, const DAFEnrollmentStateTableEntry& este);

#endif /* ENROLLMENTSTATETABLEENTRY_H_ */
