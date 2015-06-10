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

#include "AEMyPing.h"

Define_Module(AEMyPing);

void AEMyPing::initialize() {
    initPing();
}

void AEMyPing::handleMessage(cMessage* msg) {
    if ( msg->isSelfMessage() ) {
        this->handleSelfMessage(msg);
    }
}

void AEMyPing::onStart() {
    //Prepare flow's source and destination
    APNamingInfo src = this->getApni();
    APNamingInfo dst = APNamingInfo( APN(this->dstApName), this->dstApInstance,
                                     this->dstAeName, this->dstAeInstance);

    //Create a flow
    FlowObject = new Flow(src, dst);
    FlowObject->setQosRequirements(this->getQoSRequirements());

    //Notify IRM about a new flow
    insertFlow();

    //Call flow allocation request
    sendAllocationRequest(FlowObject);
}

void AEMyPing::onPing() {
    //Create PING messsage
    CDAP_M_Read* ping = new CDAP_M_Read("ping");

    //Prepare timestamp structure that is going to be carried via ping/pong
    timestamps_t* ts = new timestamps_t;
    ts->t1 = simTime();

    //Prepare object and put timestamp structure inside
    object_t obj;
    obj.objectName = "ping_time";
    obj.objectClass = "timestamps_t";
    obj.objectInstance = -1;
    obj.objectVal = (cObject*)(ts);
    ping->setObject(obj);
    ping->setByteLength(size);

    //Send message
    sendData(FlowObject, ping);
}

void AEMyPing::onStop() {
    //Call flow deallocation submit
    sendDeallocationRequest(FlowObject);
}

void AEMyPing::processMRead(CDAPMessage* msg) {
    CDAP_M_Read* msg1 = check_and_cast<CDAP_M_Read*>(msg);
    object_t object = msg1->getObject();

    //Produce message to the console
    EV << "Received M_Read with object '" << object.objectName
            << "' of class '" << object.objectClass << "'" << endl;

    //Based on object inside do something
    if ( strstr(object.objectName.c_str(), "ping_time") ) {
        //Get timestamp structure inside and update it
        timestamps_t* ts = (timestamps_t*)(object.objectVal);
        ts->t2 = simTime();

        //Produce message to the console
        EV << "PING sent at " << ts->t1
                << "s, received at " << ts->t2
                << "s, OWT1: " << (ts->t2 - ts->t1) << "s" << endl;

        //Create PING response
        CDAP_M_Read_R* pong = new CDAP_M_Read_R("pong");

        //Prepare object and put timestamp structure inside
        object_t obj;
        obj.objectName = "pong_time";
        obj.objectClass = "timestamps_t";
        obj.objectInstance = -1;
        obj.objectVal = (cObject*)(ts);
        pong->setObject(obj);
        pong->setByteLength(msg1->getByteLength());

        //Send message
        sendData(FlowObject, pong);
    }
}


void AEMyPing::processMReadR(CDAPMessage* msg) {
    CDAP_M_Read_R* msg1 = check_and_cast<CDAP_M_Read_R*>(msg);
    object_t object = msg1->getObject();

    EV << "Received M_Read with object '" << object.objectName
            << "' of class '" << object.objectClass << "'" << endl;

    //Based on object inside do something
    if ( strstr(object.objectName.c_str(), "pong_time") ) {
        //Get timestamp structure inside and update it
        timestamps_t* ts = (timestamps_t*)(object.objectVal);
        ts->t3 = simTime();

        //Produce message to the console
        EV << "PING sent at " << ts->t1
                << "s, received at " << ts->t2
                << "s, responded at " << ts->t3
                << "s, OWT1: " << (ts->t2 - ts->t1)
                << "s, OWT2: " << (ts->t3 - ts->t2)
                << "s, RTT: " << (ts->t3 - ts->t1) << "s" << endl;
    }
}
