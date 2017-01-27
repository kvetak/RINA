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

#ifndef CDAPPROCESSING_H_
#define CDAPPROCESSING_H_

#include "DAF/CDAP/CDAPMessage_m.h"
#include "Common/ExternConsts.h"
#include "Common/Utils.h"

/**
 * @brief Abstract class implementing processing of any CDAP message
 *
 * @authors Vladimir Vesely (ivesely@fit.vutbr.cz)
 * @date Last refactorized and documented on 2015-10-07
 */
class CDAPProcessingBase {
  public:
    /**
     * @brief Function checks the type of CDAP message and passes it to appropriate processing method
     * @param msg Incoming CDAP message
     */
    virtual void receiveMessage(CDAPMessage* msg);

    /**
     * @brief Function checks whether CDAP message can be processed by notifier
     * @param msg Incoming CDAP message
     * @return True if CDAP message (and object inside) matches with what is supported by notifier
     */
    virtual bool isMessageProcessable(CDAPMessage* msg) = 0;

  protected:

    /**
     * @brief Function asks for notifies about CDAP message ready to be sent
     * @param msg Outgoing CDAP message
     */
    virtual void signalizeMessage(CDAPMessage* msg) = 0;

    /**
     * @brief Function crunching supported M_CONNECT message
     * @param msg Incoming CDAP M_CONNECT message
     */
    virtual void processMConnect(CDAP_M_Connect* msg);

    /**
     * @brief Function crunching supported M_CONNECT_R message
     * @param msg Incoming CDAP M_CONNECT_R message
     */
    virtual void processMConnectR(CDAP_M_Connect_R* msg);

    /**
     * @brief Function crunching supported M_RELEASE message
     * @param msg Incoming CDAP M_RELEASE message
     */
    virtual void processMRelease(CDAP_M_Release* msg);

    /**
     * @brief Function crunching supported M_RELEASE_R message
     * @param msg Incoming CDAP M_RELEASE_R message
     */
    virtual void processMReleaseR(CDAP_M_Release_R* msg);

    /**
     * @brief Function crunching supported M_CREATE message
     * @param msg Incoming CDAP M_CREATE  message
     */
    virtual void processMCreate(CDAP_M_Create* msg);

    /**
     * @brief Function crunching supported M_CREATE_R message
     * @param msg Incoming CDAP M_CREATE_R  message
     */
    virtual void processMCreateR(CDAP_M_Create_R* msg);

    /**
     * @brief Function crunching supported M_DELETE message
     * @param msg Incoming CDAP M_DELETE  message
     */
    virtual void processMDelete(CDAP_M_Delete* msg);

    /**
     * @brief Function crunching supported M_DELETE_R message
     * @param msg Incoming CDAP M_DELETE_R  message
     */
    virtual void processMDeleteR(CDAP_M_Delete_R* msg);

    /**
     * @brief Function crunching supported M_READ message
     * @param msg Incoming CDAP M_READ  message
     */
    virtual void processMRead(CDAP_M_Read* msg);

    /**
     * @brief Function crunching supported M_READ_R message
     * @param msg Incoming CDAP M_READ_R  message
     */
    virtual void processMReadR(CDAP_M_Read_R* msg);

    /**
     * @brief Function crunching supported M_WRITE message
     * @param msg Incoming CDAP M_WRITE  message
     */
    virtual void processMWrite(CDAP_M_Write* msg);

    /**
     * @brief Function crunching supported M_WRITE_R message
     * @param msg Incoming CDAP M_WRITE_R  message
     */
    virtual void processMWriteR(CDAP_M_Write_R* msg);

    /**
     * @brief Function crunching supported M_START message
     * @param msg Incoming CDAP M_START  message
     */
    virtual void processMStart(CDAP_M_Start* msg);

    /**
     * @brief Function crunching supported M_START_R message
     * @param msg Incoming CDAP M_START_R  message
     */
    virtual void processMStartR(CDAP_M_Start_R* msg);

    /**
     * @brief Function crunching supported M_STOP message
     * @param msg Incoming CDAP M_STOP  message
     */
    virtual void processMStop(CDAP_M_Stop* msg);

    /**
     * @brief Function crunching supported M_STOP_R message
     * @param msg Incoming CDAP M_STOP_R message
     */
    virtual void processMStopR(CDAP_M_Stop_R* msg);

  private:
    /**
     * Prints out and returns textual representation of general CDAP message header
     * @param msg
     * @return String representing header of general CDAP message
     */
    std::string infoMessage(CDAPMessage* msg);
    std::string infoObject(object_t obj);
};

#endif /* CDAPPROCESSING_H_ */
