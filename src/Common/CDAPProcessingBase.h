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

#include "CDAPMessage_m.h"
#include "ExternConsts.h"

class CDAPProcessingBase {
  public:
    virtual void receiveMessage(CDAPMessage* msg);

    virtual bool isMessageProcessable(CDAPMessage* msg) = 0;

  protected:
    virtual void signalizeMessage(CDAPMessage* msg) = 0;

    virtual void processMConnect(CDAP_M_Connect* msg);
    virtual void processMConnectR(CDAP_M_Connect_R* msg);

    virtual void processMRelease(CDAP_M_Release* msg);
    virtual void processMReleaseR(CDAP_M_Release_R* msg);

    virtual void processMCreate(CDAP_M_Create* msg);
    virtual void processMCreateR(CDAP_M_Create_R* msg);

    virtual void processMDelete(CDAP_M_Delete* msg);
    virtual void processMDeleteR(CDAP_M_Delete_R* msg);

    virtual void processMRead(CDAP_M_Read* msg);
    virtual void processMReadR(CDAP_M_Read_R* msg);

    virtual void processMWrite(CDAP_M_Write* msg);
    virtual void processMWriteR(CDAP_M_Write_R* msg);

    virtual void processMStart(CDAP_M_Start* msg);
    virtual void processMStartR(CDAP_M_Start_R* msg);

    virtual void processMStop(CDAP_M_Stop* msg);
    virtual void processMStopR(CDAP_M_Stop_R* msg);

  private:
    std::string infoMessage(CDAPMessage* msg);
};

#endif /* CDAPPROCESSING_H_ */
