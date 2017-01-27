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
 * @file EnrollmentStateTable.cc
 * @author Kamil Jerabek (xjerab18@stud.fit.vutbr.cz)
 * @date Apr 1, 2015
 * @brief Enrollment state table
 * @detail
 */


#include "DIF/Enrollment/EnrollmentStateTable.h"

const char* ELEM_ENSTATETAB   = "EnrollmentStateTable";
const char* ELEM_ENSTATE      = "State";
const char* ATTR_CACE         = "cace";
const char* ATTR_ENROLL       = "enroll";

Define_Module(EnrollmentStateTable);

void EnrollmentStateTable::initialize()
{
    //Parse XML config
    parseConfig(par(PAR_CONFIGDATA).xmlValue());

    //Init watchers
    WATCH_LIST(StateTable);
}

void EnrollmentStateTable::insert(EnrollmentStateTableEntry entry) {
    if (!findEntryByDstAPN(entry.getRemote().getApn())) {
        StateTable.push_back(entry);
    }
}

EnrollmentStateTableEntry* EnrollmentStateTable::findEntryByDstAPN(const APN& apn) {
    for(auto it = StateTable.begin(); it != StateTable.end(); ++it) {
        EnrollmentStateTableEntry est = *it;
        if (est.getRemote().getApn() == apn) {
            return &(*it);
        }
    }
    return NULL;
}


void EnrollmentStateTable::handleMessage(cMessage *msg)
{

}


bool EnrollmentStateTable::isEnrolled(const APN& myApn) {
    for(auto it = StateTable.begin(); it != StateTable.end(); ++it) {
        EnrollmentStateTableEntry est = *it;
        //EV << est.getLocal().getApn()  << " " << est.getEnrollmentStatusString() << endl;
        if (est.getLocal().getApn() == myApn
                && est.getEnrollmentStatus() == EnrollmentStateTableEntry::ENROLL_ENROLLED) {
            return true;
        }
    }
    return false;
}

void EnrollmentStateTable::parseConfig(cXMLElement* config) {
    cXMLElement* mainTag = NULL;
        if (config != NULL && config->hasChildren() && config->getFirstChildWithTag(ELEM_ENSTATETAB))
            mainTag = config->getFirstChildWithTag(ELEM_ENSTATETAB);
        else {
            EV << "configData parameter not initialized!" << endl;
            return;
        }

    cXMLElementList enrll = mainTag->getChildrenByTagName(ELEM_ENSTATE);
    for (cXMLElementList::const_iterator it = enrll.begin(); it != enrll.end(); ++it) {
        cXMLElement* m = *it;

        if (!(m->getAttribute(ATTR_SRC))
                && !(m->getAttribute(ATTR_DST))
           ) {
            EV << "\nError when parsing EnrollmentState record" << endl;
            continue;
        }


        APNamingInfo src = APNamingInfo(APN(m->getAttribute(ATTR_SRC)));
        APNamingInfo dst = APNamingInfo(APN(m->getAttribute(ATTR_DST)));


        auto stat = EnrollmentStateTableEntry::CON_ESTABLISHED;
        if ( m->getAttribute(ATTR_CACE) ) {
            std::string statstr(m->getAttribute(ATTR_CACE));
            if (!statstr.compare("CON_ERROR"))
                { stat = EnrollmentStateTableEntry::CON_ERROR; }
            else if (!statstr.compare("CON_NIL"))
                { stat = EnrollmentStateTableEntry::CON_NIL; }
            else if (!statstr.compare("CON_FLOWPENDING"))
                { stat = EnrollmentStateTableEntry::CON_FLOWPENDING; }
            else if (!statstr.compare("CON_CONNECTPENDING"))
                { stat = EnrollmentStateTableEntry::CON_CONNECTPENDING; }
            else if (!statstr.compare("CON_AUTHENTICATING"))
                { stat = EnrollmentStateTableEntry::CON_AUTHENTICATING; }
            else if (!statstr.compare("CON_ESTABLISHED"))
                { stat = EnrollmentStateTableEntry::CON_ESTABLISHED; }
            else if (!statstr.compare("CON_RELEASING"))
                { stat = EnrollmentStateTableEntry::CON_RELEASING; }
        }

        auto enrl = EnrollmentStateTableEntry::ENROLL_ENROLLED;
        if ( m->getAttribute(ATTR_ENROLL) ) {
            std::string enrlstr(m->getAttribute(ATTR_ENROLL));
            if (!enrlstr.compare("ENROLL_ERROR"))
                { enrl = EnrollmentStateTableEntry::ENROLL_ERROR; }
            else if (!enrlstr.compare("ENROLL_NIL"))
                { enrl = EnrollmentStateTableEntry::ENROLL_NIL; }
            else if (!enrlstr.compare("ENROLL_WAIT_START_ENROLLMENT"))
                { enrl = EnrollmentStateTableEntry::ENROLL_WAIT_START_ENROLLMENT; }
            else if (!enrlstr.compare("ENROLL_WAIT_START_RESPONSE_ENROLLMENT"))
                { enrl = EnrollmentStateTableEntry::ENROLL_WAIT_START_RESPONSE_ENROLLMENT; }
            else if (!enrlstr.compare("ENROLL_WAIT_STOP_ENROLLMENT"))
                { enrl = EnrollmentStateTableEntry::ENROLL_WAIT_STOP_ENROLLMENT; }
            else if (!enrlstr.compare("ENROLL_WAIT_STOP_RESPONSE_ENROLLMENT"))
                { enrl = EnrollmentStateTableEntry::ENROLL_WAIT_STOP_RESPONSE_ENROLLMENT; }
            else if (!enrlstr.compare("ENROLL_WAIT_READ_RESPONSE"))
                { enrl = EnrollmentStateTableEntry::ENROLL_WAIT_READ_RESPONSE; }
            else if (!enrlstr.compare("ENROLL_WAIT_START_OPERATION"))
                { enrl = EnrollmentStateTableEntry::ENROLL_WAIT_START_OPERATION; }
            else if (!enrlstr.compare("ENROLL_CREATING_OBJ"))
                { enrl = EnrollmentStateTableEntry::ENROLL_CREATING_OBJ; }
            else if (!enrlstr.compare("ENROLL_ENROLLED"))
                { enrl = EnrollmentStateTableEntry::ENROLL_ENROLLED; }
        }

        insert(EnrollmentStateTableEntry(src, dst, stat, enrl));
    }
}
