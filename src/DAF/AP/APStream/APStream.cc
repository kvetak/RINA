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

#include "DAF/AP/APStream/APStream.h"

Define_Module(APStream);

APStream::APStream() {

}

APStream::~APStream() {
}

void APStream::initialize() {
    AP::initialize();
    if (strcmp(par("dstApName").stringValue(),"AppErr")) {
        m1 = new cMessage("start");
        scheduleAt(simTime() + par("startAt").longValue(), m1);

        m2 = new cMessage("stop");
        scheduleAt(simTime() + par("stopAt").longValue(), m2);
    }
}

void APStream::handleMessage(cMessage *msg) {
    if(msg->isSelfMessage()) {
        if ( !strcmp(msg->getName(), "start") ) {
            invokeId = getNewInvokeID();
            a_open(invokeId, par("dstApName").stringValue(), "0", "AEMonitor", "-1");
        }
        else if (!strcmp(msg->getName(), "stop")){
            a_close(conID);
        }
        else if (!strcmp(msg->getName(), "stream")){
            if ((simTime().dbl()+1) < par("stopAt").doubleValue()) {
                object_t obj;
                obj.objectName = "stream";
                obj.objectVal = (cObject*)"tmp";
                a_write(conID, "stream", &obj, -1);

                m2 = new cMessage("stream");
                scheduleAt(simTime() + par("interval"), m2);
            }

        }
        else
            EV << this->getFullPath() << " received unknown self-message " << msg->getName();
        delete(msg);

    }
}

void APStream::onA_getOpen(APIResult* result) {
    if (result->getInvokeId() == invokeId) {
        conID = result->getCDAPConId();
        object_t obj;
        obj.objectName = "stream";
        obj.objectVal = (cObject*)"tmp";
        a_write(conID, "stream", &obj, -1);

        m2 = new cMessage("stream");
        scheduleAt(simTime() + par("interval"), m2);
    }
}
