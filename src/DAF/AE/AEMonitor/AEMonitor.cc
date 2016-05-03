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

#include <AEMonitor/AEMonitor.h>

Define_Module(AEMonitor);

AEMonitor::AEMonitor() {
    object_t object;
    object.objectClass = "int";
    object.objectName = "time";
    int time = 0;
    object.objectVal = (cObject*)(&time);
    obj = object;
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
    ping->setObject(object);
    ping->setByteLength(50);

    //Send message
    sendData(FlowObject, ping);
}


void AEMonitor::processMRead(CDAPMessage* msg) {
    CDAP_M_Read* msg1 = check_and_cast<CDAP_M_Read*>(msg);
    object_t object = msg1->getObject();

    if ( strstr(object.objectName.c_str(), obj.objectName.c_str()) ) {
        CDAP_M_Read_R* pong = new CDAP_M_Read_R("M_READ_R(ping)");
        object_t object;
        object.objectName = obj.objectName;
        object.objectClass = "int";
        object.objectInstance = -1;
        object.objectVal = (cObject*)(obj.objectVal);
        pong->setObject(object);
        pong->setByteLength(50);

        //inc object val
        obj.objectVal += 1;

        //Send message
        sendData(FlowObject, pong);
    }
    else
        delete msg;
}

void AEMonitor::processMReadR(CDAPMessage* msg) {
    CDAP_M_Read_R* msg1 = check_and_cast<CDAP_M_Read_R*>(msg);
    object_t object = msg1->getObject();

    APIResult *res = new APIResult();
    res->setObj(&object);
    res->setCDAPConId(cdapConId);
    res->setAPIResType(APIResult::A_GET_READ);

    signalizeAEAPAPI(res);
}
