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

#include "APRaft.h"

Define_Module(APRaft);



APRaft::APRaft() {
}

APRaft::~APRaft() {
}

void APRaft::initialize() {
    AP::initialize();
    long t1 = par("startAt").longValue();
    long t2 = par("stopAt").longValue();
    this->currentID = 0;

    if (strcmp(par("dstApName").stringValue(),"AppERROR") &&
            t2 > t1 && t1 > 0 && t2 > 0
       ) {
        //get all names
        dstApNames = cStringTokenizer(par("dstApName").stringValue()).asVector();
        dstApInstances = cStringTokenizer(par("dstApInstance").stringValue()).asVector();
        dstAeNames = cStringTokenizer(par("dstAeName").stringValue()).asVector();
        dstAeInstances = cStringTokenizer(par("dstAeInstance").stringValue()).asVector();

        //TODO: solve this
        /*if (dstApNames.size() != dstApInstances.size() ||
                dstApInstances.size() != dstAeNames.size() ||
                dstAeNames.size() != dstAeInstances.size())
        {
            EV << "Number of destination data is not equal" << endl;
            return;
        }*/

        connections = dstApInstances.size();

        m1 = new cMessage("start");
        scheduleAt(simTime() + t1, m1);

        m2 = new cMessage("stop");
        scheduleAt(simTime() + t2, m2);
    }
}

void APRaft::handleMessage(cMessage *msg) {
    int connID;

    if(msg->isSelfMessage()) {
        if ( !strcmp(msg->getName(), "start") ) {

            std::vector<std::string>::iterator itApNames = dstApNames.begin();
            std::vector<std::string>::iterator itApInstances = dstApInstances.begin();
            std::vector<std::string>::iterator itAeNames = dstAeNames.begin();
            std::vector<std::string>::iterator itAeInstances = dstAeInstances.begin();
            int i = 0;

            invokeId = new int[connections];
            conID = new unsigned long[connections];
            int invId;

            while(itApNames != dstApNames.end()){
                invId = getNewInvokeID();
                invokeId[i] = invId;
                i++;

                a_open(invId, *itApNames, *itApInstances,
                                *itAeNames, *itAeInstances);

                itApNames++;
                if (dstApInstances.size() > 1) {
                    itApInstances++;
                }
                if (dstApInstances.size() > 1) {
                    itAeNames++;
                }
                if (dstApInstances.size() > 1) {
                    itAeInstances++;
                }
            }
        }
        else if (!strcmp(msg->getName(), "stop")) {
            for (int i = 0; i < connections; i++){
                a_close(conID[i]);
            }


        }
        else if (!strcmp(msg->getName(), "create")) {
            if ((simTime().dbl()+1) < par("stopAt").doubleValue() ) {
                object_t *obj = new object_t();
                obj->objectClass = "int";
                obj->objectInstance = 0;
                obj->objectName = "raft";
                cObject* x = (cObject*)(new int(10));
                obj->objectVal = x;
                a_create(conID[0], "int", "raft", obj);
            }
        }
        else if (!strcmp(msg->getName(), "write")) {
            if ((simTime().dbl()+1) < par("stopAt").doubleValue() ) {
                object_t *obj = new object_t();
                obj->objectClass = "int";
                obj->objectInstance = 1;
                obj->objectName = "raft";
                cObject* x = (cObject*)(new int(5));
                obj->objectVal = x;
                a_write(conID[0], "raft", obj);
            }
        }
        else
            EV << this->getFullPath() << " received unknown self-message " << msg->getName();
        delete(msg);
    }
}


void APRaft::onA_getOpen(APIResult* result) {
    int connID;

    this->conID[currentID] = result->getCDAPConId();
    this->currentID++;

    m3 = new cMessage("create");
    scheduleAt(simTime() + 10, m3);
}

void APRaft::onA_getRead(APIResult* result) {

}

void APRaft::onA_getCreate(APIResult* result) {
    cMessage *msg = new cMessage("write");
    scheduleAt(simTime()+1, msg);
}
