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
 * @file DAFEnrollmentStateTable.cc
 * @author Kamil Jerabek (xjerab18@stud.fit.vutbr.cz)
 * @date Apr 1, 2015
 * @brief DAFEnrollment state table
 * @detail
 */


#include "DAF/Enrollment/DAFEnrollmentStateTable.h"

const char* DAF_DAF_ELEM_ENSTATETAB   = "DAFEnrollmentStateTable";
const char* DAF_ELEM_ENSTATE      = "State";
const char* DAF_ATTR_CACE         = "cace";
const char* DAF_ATTR_ENROLL       = "enroll";

Define_Module(DAFEnrollmentStateTable);

void DAFEnrollmentStateTable::initialize()
{
    //Parse XML config
    parseConfig(par(PAR_CONFIGDATA).xmlValue());

    //Init watchers
    WATCH_LIST(StateTable);
}

bool DAFEnrollmentStateTable::isEmpty() {
    return StateTable.empty();
}

void DAFEnrollmentStateTable::insert(DAFEnrollmentStateTableEntry entry) {
    StateTable.push_back(entry);
}

DAFEnrollmentStateTableEntry* DAFEnrollmentStateTable::findEntryByDstAPN(const APN& apn) {
    for(auto it = StateTable.begin(); it != StateTable.end(); ++it) {
        DAFEnrollmentStateTableEntry est = *it;
        if (est.getRemote().getApn() == apn &&
                strstr(est.getRemote().getAename().c_str(), "mgmt")) {
            return &(*it);
        }
    }
    return NULL;
}

DAFEnrollmentStateTableEntry* DAFEnrollmentStateTable::findEntryByDstAPNI(const APNamingInfo& apni) {
    for(auto it = StateTable.begin(); it != StateTable.end(); ++it) {
        DAFEnrollmentStateTableEntry est = *it;

        if (est.getRemote().getApn() == apni.getApn() &&
            est.getRemote().getAeinstance() == apni.getAeinstance() &&
            est.getRemote().getAename() == apni.getAename() &&
            est.getRemote().getApinstance() == apni.getApinstance()) {
            return &(*it);
        }
    }
    return NULL;
}

void DAFEnrollmentStateTable::handleMessage(cMessage *msg)
{

}

bool DAFEnrollmentStateTable::isEnrolled(const APN& myApn) {
    for(auto it = StateTable.begin(); it != StateTable.end(); ++it) {
        DAFEnrollmentStateTableEntry est = *it;
        if (est.getLocal().getApn() == myApn
                && est.getDAFEnrollmentStatus() == DAFEnrollmentStateTableEntry::ENROLL_ENROLLED
                && strstr(est.getRemote().getAename().c_str(), "mgmt")) {
            return true;
        }
    }
    return false;
}

void DAFEnrollmentStateTable::parseConfig(cXMLElement* config) {
    cXMLElement* mainTag = NULL;
        if (config != NULL && config->hasChildren() && config->getFirstChildWithTag(DAF_DAF_ELEM_ENSTATETAB))
            mainTag = config->getFirstChildWithTag(DAF_DAF_ELEM_ENSTATETAB);
        else {
            EV << "configData parameter not initialized!" << endl;
            return;
        }

    cXMLElementList enrll = mainTag->getChildrenByTagName(DAF_ELEM_ENSTATE);
    for (cXMLElementList::const_iterator it = enrll.begin(); it != enrll.end(); ++it) {
        cXMLElement* m = *it;

        if (!(m->getAttribute(ATTR_SRC))
                && !(m->getAttribute(ATTR_DST))
           ) {
            EV << "\nError when parsing DAFEnrollmentState record" << endl;
            continue;
        }


        APNamingInfo src = APNamingInfo(APN(m->getAttribute(ATTR_SRC)));
        APNamingInfo dst = APNamingInfo(APN(m->getAttribute(ATTR_DST)));


        auto stat = DAFEnrollmentStateTableEntry::CON_ESTABLISHED;
        if ( m->getAttribute(DAF_ATTR_CACE) ) {
            std::string statstr(m->getAttribute(DAF_ATTR_CACE));
            if (!statstr.compare("CON_ERROR"))
                { stat = DAFEnrollmentStateTableEntry::CON_ERROR; }
            else if (!statstr.compare("CON_NIL"))
                { stat = DAFEnrollmentStateTableEntry::CON_NIL; }
            else if (!statstr.compare("CON_FLOWPENDING"))
                { stat = DAFEnrollmentStateTableEntry::CON_FLOWPENDING; }
            else if (!statstr.compare("CON_CONNECTPENDING"))
                { stat = DAFEnrollmentStateTableEntry::CON_CONNECTPENDING; }
            else if (!statstr.compare("CON_AUTHENTICATING"))
                { stat = DAFEnrollmentStateTableEntry::CON_AUTHENTICATING; }
            else if (!statstr.compare("CON_ESTABLISHED"))
                { stat = DAFEnrollmentStateTableEntry::CON_ESTABLISHED; }
            else if (!statstr.compare("CON_RELEASING"))
                { stat = DAFEnrollmentStateTableEntry::CON_RELEASING; }
        }

        auto enrl = DAFEnrollmentStateTableEntry::ENROLL_ENROLLED;
        if ( m->getAttribute(DAF_ATTR_ENROLL) ) {
            std::string enrlstr(m->getAttribute(DAF_ATTR_ENROLL));
            if (!enrlstr.compare("ENROLL_ERROR"))
                { enrl = DAFEnrollmentStateTableEntry::ENROLL_ERROR; }
            else if (!enrlstr.compare("ENROLL_NIL"))
                { enrl = DAFEnrollmentStateTableEntry::ENROLL_NIL; }
            else if (!enrlstr.compare("ENROLL_WAIT_START_ENROLLMENT"))
                { enrl = DAFEnrollmentStateTableEntry::ENROLL_WAIT_START_ENROLLMENT; }
            else if (!enrlstr.compare("ENROLL_WAIT_START_RESPONSE_ENROLLMENT"))
                { enrl = DAFEnrollmentStateTableEntry::ENROLL_WAIT_START_RESPONSE_ENROLLMENT; }
            else if (!enrlstr.compare("ENROLL_WAIT_STOP_ENROLLMENT"))
                { enrl = DAFEnrollmentStateTableEntry::ENROLL_WAIT_STOP_ENROLLMENT; }
            else if (!enrlstr.compare("ENROLL_WAIT_STOP_RESPONSE_ENROLLMENT"))
                { enrl = DAFEnrollmentStateTableEntry::ENROLL_WAIT_STOP_RESPONSE_ENROLLMENT; }
            else if (!enrlstr.compare("ENROLL_WAIT_READ_RESPONSE"))
                { enrl = DAFEnrollmentStateTableEntry::ENROLL_WAIT_READ_RESPONSE; }
            else if (!enrlstr.compare("ENROLL_WAIT_START_OPERATION"))
                { enrl = DAFEnrollmentStateTableEntry::ENROLL_WAIT_START_OPERATION; }
            else if (!enrlstr.compare("ENROLL_CREATING_OBJ"))
                { enrl = DAFEnrollmentStateTableEntry::ENROLL_CREATING_OBJ; }
            else if (!enrlstr.compare("ENROLL_ENROLLED"))
                { enrl = DAFEnrollmentStateTableEntry::ENROLL_ENROLLED; }
        }

        insert(DAFEnrollmentStateTableEntry(src, dst, stat, enrl));
    }
}
