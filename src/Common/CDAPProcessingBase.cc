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

#include "Common/CDAPProcessingBase.h"

void CDAPProcessingBase::receiveMessage(CDAPMessage* msg) {
    //M_CONNECT_Request
    if (dynamic_cast<CDAP_M_Connect*>(msg)) {
        processMConnect(check_and_cast<CDAP_M_Connect*>(msg));
    }
    //M_CONNECT_Response
    else if (dynamic_cast<CDAP_M_Connect_R*>(msg)) {
        processMConnectR(check_and_cast<CDAP_M_Connect_R*>(msg));
    }
    //M_RELEASE_Request
    else if (dynamic_cast<CDAP_M_Release*>(msg)) {
        processMRelease(check_and_cast<CDAP_M_Release*>(msg));
    }
    //M_RELEASE_Response
    else if (dynamic_cast<CDAP_M_Release_R*>(msg)) {
        processMReleaseR(check_and_cast<CDAP_M_Release_R*>(msg));
    }
    //M_CREATE_Request
    else if (dynamic_cast<CDAP_M_Create*>(msg)) {
        processMCreate(check_and_cast<CDAP_M_Create*>(msg));
    }
    //M_CREATE_Response
    else if (dynamic_cast<CDAP_M_Create_R*>(msg)) {
        processMCreateR(check_and_cast<CDAP_M_Create_R*>(msg));
    }
    //M_DELETE_Request
    else if (dynamic_cast<CDAP_M_Delete*>(msg)) {
        processMDelete(check_and_cast<CDAP_M_Delete*>(msg));
    }
    //M_DELETE_Request
    else if (dynamic_cast<CDAP_M_Delete_R*>(msg)) {
        processMDeleteR(check_and_cast<CDAP_M_Delete_R*>(msg));
    }
    //M_WRITE_Request
    else if (dynamic_cast<CDAP_M_Read*>(msg)) {
        processMRead(check_and_cast<CDAP_M_Read*>(msg));
    }
    //M_WRITE_Response
    else if (dynamic_cast<CDAP_M_Read_R*>(msg)) {
        processMReadR(check_and_cast<CDAP_M_Read_R*>(msg));
    }
    //M_WRITE_Request
    else if (dynamic_cast<CDAP_M_Write*>(msg)) {
        processMWrite(check_and_cast<CDAP_M_Write*>(msg));
    }
    //M_WRITE_Response
    else if (dynamic_cast<CDAP_M_Write_R*>(msg)) {
        processMWriteR(check_and_cast<CDAP_M_Write_R*>(msg));
    }
    //M_START_Request
    else if (dynamic_cast<CDAP_M_Start*>(msg)) {
        processMStart(check_and_cast<CDAP_M_Start*>(msg));
    }
    //M_START_Response
    else if (dynamic_cast<CDAP_M_Start_R*>(msg)) {
        processMStartR(check_and_cast<CDAP_M_Start_R*>(msg));
    }
    //M_Stop_Request
    else if (dynamic_cast<CDAP_M_Stop*>(msg)) {
        processMStop(check_and_cast<CDAP_M_Stop*>(msg));
    }
    //M_Stop_Response
    else if (dynamic_cast<CDAP_M_Stop_R*>(msg)) {
        processMStopR(check_and_cast<CDAP_M_Stop_R*>(msg));
    }
    delete msg;
}

void CDAPProcessingBase::processMConnect(CDAP_M_Connect* msg) {
    infoMessage(msg);
}

void CDAPProcessingBase::processMConnectR(CDAP_M_Connect_R* msg) {
    infoMessage(msg);
}

void CDAPProcessingBase::processMRelease(CDAP_M_Release* msg) {
    infoMessage(msg);
}

void CDAPProcessingBase::processMReleaseR(CDAP_M_Release_R* msg) {
    infoMessage(msg);
}

void CDAPProcessingBase::processMCreate(CDAP_M_Create* msg) {
    infoMessage(msg);
}

void CDAPProcessingBase::processMCreateR(CDAP_M_Create_R* msg) {
}

void CDAPProcessingBase::processMDelete(CDAP_M_Delete* msg) {
}

void CDAPProcessingBase::processMDeleteR(CDAP_M_Delete_R* msg) {
    infoMessage(msg);
}

void CDAPProcessingBase::processMRead(CDAP_M_Read* msg) {
    infoMessage(msg);
}

void CDAPProcessingBase::processMReadR(CDAP_M_Read_R* msg) {
    infoMessage(msg);
}

void CDAPProcessingBase::processMWrite(CDAP_M_Write* msg) {
    infoMessage(msg);
}

void CDAPProcessingBase::processMWriteR(CDAP_M_Write_R* msg) {
    infoMessage(msg);
}

void CDAPProcessingBase::processMStart(CDAP_M_Start* msg) {
    infoMessage(msg);
}

void CDAPProcessingBase::processMStartR(CDAP_M_Start_R* msg) {
    infoMessage(msg);
}

void CDAPProcessingBase::processMStop(CDAP_M_Stop* msg) {
    infoMessage(msg);
}

void CDAPProcessingBase::processMStopR(CDAP_M_Stop_R* msg) {
    infoMessage(msg);
}

std::string CDAPProcessingBase::infoMessage(CDAPMessage* msg) {
    std::ostringstream os;
    os << "MESSAGE PROCESSING NOT DEFINED!" << endl
       << "OpCode: "  << msg->getOpCode();
    std::string type;
    switch (msg->getOpCode()) {
        case 1:     type = "M_CONNECT";     break;
        case 2:     type = "M_CONNECT_R";   break;
        case 3:     type = "M_RELEASE";     break;
        case 4:     type = "M_RELEASE_R";   break;
        case 5:     type = "M_CREATE";      break;
        case 6:     type = "M_CREATE_R";    break;
        case 7:     type = "M_DELETE";      break;
        case 8:     type = "M_DELETE_R";    break;
        case 9:     type = "M_READ";        break;
        case 10:    type = "M_READ_R";      break;
        case 11:    type = "M_CANCELREAD";  break;
        case 12:    type = "M_CANCELREAD_R";break;
        case 13:    type = "M_WRITE";       break;
        case 14:    type = "M_WRITE_R";     break;
        case 15:    type = "M_START";       break;
        case 16:    type = "M_START_R";     break;
        case 17:    type = "M_STOP";        break;
        case 18:    type = "M_STOP_R";      break;
        case 0:
        default:    type = "UNKNOWNN";
    }

    os << type << endl;
    os << "SrcAddr: " << msg->getSrcAddr() << endl
       << "DstAddr: " << msg->getDstAddr() << endl
       << "InvokeId: " << msg->getInvokeID() << endl
       << "Size: " << msg->getHeaderBitLength() << " bits" << endl;
    EV << os.str();
    return os.str();
}

bool CDAPProcessingBase::isMessageProcessable(CDAPMessage* msg) {
    return false;
}

std::string CDAPProcessingBase::infoObject(object_t obj) {
    std::ostringstream os;
    os << "Object: '" << obj.objectClass << "'" << endl;
    EV << os.str();
    return os.str();
}
