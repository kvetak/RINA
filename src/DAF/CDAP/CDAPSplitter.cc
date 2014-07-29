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
    // TODO - Generated method body
}

void CDAPSplitter::handleMessage(cMessage *msg)
{
    //Pass it to the CACE module
    if (dynamic_cast<CDAP_M_Connect*>(msg) ||  dynamic_cast<CDAP_M_Connect_R*>(msg) ||
        dynamic_cast<CDAP_M_Release*>(msg) ||  dynamic_cast<CDAP_M_Release_R*>(msg) )
    {

        send(msg, "caceIo");
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
        send(msg, "cdapIo");
    }

    //Unknown message
    else {
        EV << this->getFullPath() << " received unknown message" << endl;
        delete msg;
    }
}
