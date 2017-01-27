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

#include "DAF/AE/AEMonitor/AEMonitor.h"

Define_Module(AEMonitor);

AEMonitor::AEMonitor() {
    object_t object;
    object.objectClass = "int";
    object.objectName = "ping";
    int time = 0;
    object.objectVal = (cObject*)(&time);
    objPing = object;
}

AEMonitor::~AEMonitor() {
}


bool AEMonitor::onA_read(APIReqObj* obj) {
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

bool AEMonitor::onA_write(APIReqObj* obj) {
    CDAP_M_Write* write = new CDAP_M_Write("M_WRITE(stream)");
    write->setObjectItem(*obj->getObj());
    write->setByteLength((int)par("size").longValue());

    //Send message
    sendData(FlowObject, write);

    return true;
}

void AEMonitor::processMRead(CDAPMessage* msg) {
    CDAP_M_Read* msg1 = check_and_cast<CDAP_M_Read*>(msg);
    object_t object = msg1->getObjectItem();

    if ( strstr(object.objectName.c_str(), objPing.objectName.c_str()) ) {
        CDAP_M_Read_R* pong = new CDAP_M_Read_R("M_READ_R(ping)");
        object_t object;
        object.objectName = objPing.objectName;
        object.objectClass = "int";
        object.objectInstance = -1;
        object.objectVal = (cObject*)(objPing.objectVal);
        pong->setObjectItem(object);
        pong->setByteLength((int)par("size").longValue());

        //inc object val
        objPing.objectVal += 1;

        //Send message
        sendData(FlowObject, pong);
    }
    else
        delete msg;
}

void AEMonitor::processMWrite(CDAPMessage* msg) {
    CDAP_M_Write* msg1 = check_and_cast<CDAP_M_Write*>(msg);
    object_t obj = msg1->getObjectItem();

    objStream = obj;

    CDAP_M_Write_R* wr = new CDAP_M_Write_R("M_WRITE_R(stream)");
    object_t object;
    object.objectName = objStream.objectName;
    object.objectClass = objStream.objectClass;
    object.objectInstance = objStream.objectInstance;
    object.objectVal = objStream.objectVal;

    result_t result;
    result.resultValue = 0;

    wr->setObjectItem(object);
    wr->setResult(result);

    //Send message
    sendData(FlowObject, wr);
}

void AEMonitor::processMReadR(CDAPMessage* msg) {
    CDAP_M_Read_R* msg1 = check_and_cast<CDAP_M_Read_R*>(msg);
    object_t object = msg1->getObjectItem();

    APIResult *res = new APIResult();
    res->setObj(&object);
    res->setCDAPConId(cdapConId);
    res->setAPIResType(APIResult::A_GET_READ);

    signalizeAEAPAPI(res);
}

void AEMonitor::processMWriteR(CDAPMessage* msg) {
    CDAP_M_Write_R* msg1 = check_and_cast<CDAP_M_Write_R*>(msg);
    object_t object = msg1->getObjectItem();

    APIResult *res = new APIResult();
    res->setObj(&object);
    res->setCDAPConId(cdapConId);
    res->setAPIResType(APIResult::A_GET_WRITE);

    signalizeAEAPAPI(res);
}
