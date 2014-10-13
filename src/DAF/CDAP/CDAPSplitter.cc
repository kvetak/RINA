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

#include "CDAPSplitter.h"

Define_Module(CDAPSplitter);

void CDAPSplitter::initialize()
{
    MsgLog = dynamic_cast<CDAPMsgLog*>(this->getParentModule()->getSubmodule(MOD_CDAPMSGLOG));
    if (!MsgLog)
        error("Pointer to CDAPMsgLog is not initialized!");
}

void CDAPSplitter::handleMessage(cMessage *msg)
{
    //Output gate pointer
    cGate* out;

    //Received from south gates
    if ( strstr(msg->getArrivalGate()->getName(), GATE_SOUTHIO) != NULL ) {
        //Pass it to the CACE module
        if (dynamic_cast<CDAP_M_Connect*>(msg) ||  dynamic_cast<CDAP_M_Connect_R*>(msg) ||
            dynamic_cast<CDAP_M_Release*>(msg) ||  dynamic_cast<CDAP_M_Release_R*>(msg) )
        {
            out = gateHalf(GATE_CACEIO, cGate::OUTPUT, msg->getArrivalGate()->getIndex());
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
            out = gateHalf(GATE_CDAPIO, cGate::OUTPUT, msg->getArrivalGate()->getIndex());
        }

    }
    //Received from north gates
    else {
        out = gateHalf(GATE_SOUTHIO, cGate::OUTPUT, msg->getArrivalGate()->getIndex());
    }

    //Forward message
    send(msg, out);

/*
    //Unknown message
    else {
        EV << this->getFullPath() << " received unknown message" << endl;
        delete msg;
    }
*/
}
