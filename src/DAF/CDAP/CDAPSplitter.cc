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

#include "DAF/CDAP/CDAPSplitter.h"

Define_Module(CDAPSplitter);

void CDAPSplitter::initialize()
{
    MsgLog = dynamic_cast<CDAPMsgLog*>(this->getParentModule()->getSubmodule(MOD_CDAPMSGLOG));
    if (!MsgLog)
        error("Pointer to CDAPMsgLog is not initialized!");
}

CDAPSplitter::CDAPSplitter() {
    MsgLog = NULL;
}

CDAPSplitter::~CDAPSplitter() {
    MsgLog = NULL;
}

void CDAPSplitter::handleMessage(cMessage *msg)
{
    //Process message
    if (!dynamic_cast<CDAPMessage*>(msg)) {
        EV << this->getFullPath() << " received unknown message" << endl;
        delete msg;
        return;
    }


    CDAPMessage* cdapmsg = check_and_cast<CDAPMessage*>(msg);

    //Check for unsolicited response
    if (cdapmsg->getOpCode() % 2 == 0                               //is *_R message
        && !MsgLog->findRequestByInvId(cdapmsg))     //does not have request with appropriate invokeId
    {
        EV << "Cannot send/received unsolicited CDAP response thus discarding message" <<  endl;
        delete msg;
        return;
    }

    //Output gate pointer
    cGate* out = nullptr;

    //Received from south gates
    if ( strstr(msg->getArrivalGate()->getName(), GATE_SOUTHIO) != NULL ) {
        MsgLog->insert(cdapmsg, false);

        //Pass it to the CACE module
        if (dynamic_cast<CDAP_M_Connect*>(msg) ||  dynamic_cast<CDAP_M_Connect_R*>(msg) ||
            dynamic_cast<CDAP_M_Release*>(msg) ||  dynamic_cast<CDAP_M_Release_R*>(msg) )
        {
            out = gateHalf(GATE_CDAPIO, cGate::OUTPUT);
        }

        //Pass it to the Auth module

        //Pass it to the CDAP module
        else if (dynamic_cast<CDAP_M_Create*>(msg) || dynamic_cast<CDAP_M_Create_R*>(msg) ||
                 dynamic_cast<CDAP_M_Delete*>(msg) || dynamic_cast<CDAP_M_Delete_R*>(msg) ||
                 dynamic_cast<CDAP_M_Start*>(msg) || dynamic_cast<CDAP_M_Start_R*>(msg)   ||
                 dynamic_cast<CDAP_M_Stop*>(msg) || dynamic_cast<CDAP_M_Stop_R*>(msg)     ||
                 dynamic_cast<CDAP_M_Write*>(msg) || dynamic_cast<CDAP_M_Write_R*>(msg)   ||
                 dynamic_cast<CDAP_M_Read*>(msg) || dynamic_cast<CDAP_M_Read_R*>(msg)     ||
                 dynamic_cast<CDAP_M_CancelRead*>(msg) || dynamic_cast<CDAP_M_CancelRead_R*>(msg) )
        {
            //EV <<"XXXXXXXX "<< msg->getArrivalGate()->getFullName() << "-" << msg->getArrivalGate()->getIndex() << endl;
            out = gateHalf(GATE_CDAPIO, cGate::OUTPUT);
        }

    }
    //Received from north gates
    else if (strstr(msg->getArrivalGate()->getName(), GATE_SOUTHIO) == NULL) {
        MsgLog->insert(check_and_cast<CDAPMessage*>(msg), true);

        out = gateHalf(GATE_SOUTHIO, cGate::OUTPUT);
    }


    //Forward message
    send(msg, out);
}
