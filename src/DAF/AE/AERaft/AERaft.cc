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

#include "AERaft.h"

Define_Module(AERaft);


AERaft::AERaft() {
}

AERaft::~AERaft() {

}

bool AERaft::onA_read(APIReqObj* obj) {
    CDAP_M_Read* ping = new CDAP_M_Read("M_READ(ping)");
    object_t object;
    object.objectName = obj->getObjName();
    object.objectClass = "int";
    object.objectInstance = -1;
    object.objectVal = NULL;
    ping->setObjectItem(object);
    ping->setByteLength((int)par("size").longValue());

    //Send message
    sendData(FlowObject, ping);

    return true;
}

bool AERaft::onA_write(APIReqObj* obj) {
    CDAP_M_Write* write = new CDAP_M_Write("M_WRITE");
    object_t tmpObj;
    tmpObj.objectClass = obj->getObj()->objectClass;
    tmpObj.objectInstance = obj->getObj()->objectInstance;
    tmpObj.objectName = obj->getObj()->objectName;
    tmpObj.objectVal = (obj->getObj()->objectVal);
    write->setObjectItem(tmpObj);
    write->setByteLength((int)par("size").longValue());

    //Send message
    sendData(FlowObject, write);

    return true;
}

bool AERaft::onA_create(APIReqObj* obj) {
    CDAP_M_Create* create = new CDAP_M_Create("M_CREATE");
    object_t tmpObj;
    tmpObj.objectClass = obj->getObj()->objectClass;
    tmpObj.objectInstance = obj->getObj()->objectInstance;
    tmpObj.objectName = obj->getObj()->objectName;
    tmpObj.objectVal = (obj->getObj()->objectVal);

    create->setObjectItem(tmpObj);
    create->setByteLength((int)par("size").longValue());

    //Send message
    sendData(FlowObject, create);

    return true;
}

void AERaft::processMRead(CDAPMessage* msg) {
    CDAP_M_Read* msg1 = check_and_cast<CDAP_M_Read*>(msg);
    object_t object = msg1->getObjectItem();

    if ( strstr(object.objectName.c_str(), objPing.objectName.c_str()) ) {
        std::string s(object.objectName.c_str());
        object_t *tmpObj = this->rib->readObj(cdapConId, s);
        CDAP_M_Read_R* pong = new CDAP_M_Read_R("M_READ_R");
        object_t object;
        object.objectName = tmpObj->objectName;
        object.objectClass = tmpObj->objectClass;
        object.objectInstance = tmpObj->objectInstance;
        object.objectVal = (cObject*)(tmpObj->objectVal);
        pong->setObjectItem(object);
        pong->setByteLength((int)par("size").longValue());

        //Send message
        sendData(FlowObject, pong);
    }
    else
        delete msg;
}

void AERaft::processMWrite(CDAPMessage* msg) {
    CDAPMessage* msg1 = this->raft->commandReceivedFromClient(msg);
    if (dynamic_cast<CDAP_M_Write_R*>(msg1)) {
        CDAP_M_Write_R *msg2 = check_and_cast<CDAP_M_Write_R*>(msg1);

        CDAP_M_Create_R *msg3 = new CDAP_M_Create_R(msg2->getName());
        msg3->setResult(msg2->getResult());

        //Send message
        sendData(FlowObject, msg1);
    }
}

void AERaft::processMReadR(CDAPMessage* msg) {
    CDAP_M_Read_R* msg1 = check_and_cast<CDAP_M_Read_R*>(msg);
    object_t object = msg1->getObjectItem();

    APIResult *res = new APIResult();
    res->setObj(&object);
    res->setCDAPConId(cdapConId);
    res->setAPIResType(APIResult::A_GET_READ);

    signalizeAEAPAPI(res);
}

void AERaft::processMWriteR(CDAPMessage* msg) {
    CDAP_M_Write_R* msg1 = check_and_cast<CDAP_M_Write_R*>(msg);
    object_t object = msg1->getObjectItem();

    APIResult *res = new APIResult();
    res->setObj(&object);
    res->setCDAPConId(cdapConId);
    res->setAPIResType(APIResult::A_GET_WRITE);

    signalizeAEAPAPI(res);
}

void AERaft::processMCreate(CDAPMessage* msg) {
    CDAPMessage* msg1 = this->raft->commandReceivedFromClient(msg);
    if (dynamic_cast<CDAP_M_Create_R*>(msg1)) {
        CDAP_M_Create_R *msg2 = check_and_cast<CDAP_M_Create_R*>(msg1);
        CDAP_M_Create_R *msg3 = new CDAP_M_Create_R(msg2->getName());
        msg3->setResult(msg2->getResult());

        sendData(FlowObject, msg3);
    }
}

void AERaft::processMCreateR(CDAPMessage* msg) {
    CDAP_M_Create_R* msg1 = check_and_cast<CDAP_M_Create_R*>(msg);
    object_t object = msg1->getObjectItem();

    APIResult *res = new APIResult();
    res->setObj(&object);
    res->setCDAPConId(cdapConId);
    res->setResult(&msg1->getResult());
    res->setAPIResType(APIResult::A_GET_CREATE);

    signalizeAEAPAPI(res);
}
