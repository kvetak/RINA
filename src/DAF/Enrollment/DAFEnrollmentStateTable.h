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
 * @file DAFEnrollmentStateTable.h
 * @author Kamil Jerabek (xjerab18@stud.fit.vutbr.cz)
 * @date Apr 1, 2015
 * @brief DAFEnrollment state table
 * @detail
 */

#ifndef __RINA_DAFENROLLMENTSTATETABLE_H_
#define __RINA_DAFENROLLMENTSTATETABLE_H_

#include <omnetpp.h>
#include <string>
#include "Common/Flow.h"
#include "DAF/Enrollment/DAFEnrollmentStateTableEntry.h"

typedef std::list<DAFEnrollmentStateTableEntry> DAFEnrollStateTable;
typedef DAFEnrollStateTable::iterator DAFEnrollStateTableIter;
typedef DAFEnrollStateTable::const_iterator DAFEnrollStateTableConstIter;

class DAFEnrollmentStateTable : public cSimpleModule
{
  public:
    void insert(DAFEnrollmentStateTableEntry entry);
    DAFEnrollmentStateTableEntry* findEntryByDstAPN(const APN& apn);
    DAFEnrollmentStateTableEntry* findEntryByDstAPNI(const APNamingInfo& apni);
    bool isEnrolled(const APN& myApn);
    bool isEmpty();

  protected:
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);

    void parseConfig(cXMLElement* config);

  private:
    DAFEnrollStateTable StateTable;
};

#endif
