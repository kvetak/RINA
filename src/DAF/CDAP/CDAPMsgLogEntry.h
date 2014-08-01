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

#ifndef MESSAGELOGENTRY_H_
#define MESSAGELOGENTRY_H_

//Standard libraries
#include <omnetpp.h>

const int UNINIT_INVOKEID = -1;

class CDAPMsgLogEntry {
  public:
    enum CDAPMsgStatus {UNKNOWN, REQUESTED, RESPONDED};

    //(De)Constructor
    CDAPMsgLogEntry();
    virtual ~CDAPMsgLogEntry();

    std::string info() const;
    std::string getMessageStatusString() const;

    //Getters and Setters
    int getInvokeId() const;
    void setInvokeId(int invokeId);
    void setMsgStatus(CDAPMsgStatus msgStatus);
    const std::string& getOpCode() const;
    void setOpCode(const std::string& opCode);
    const simtime_t& getRequestedAt() const;
    void setRequestedAt(const simtime_t& requestedAt);
    const simtime_t& getRespondedAt() const;
    void setRespondedAt(const simtime_t& respondedAt);

  private:
    //FIXME: Vesely - Convert to enum
    std::string opCode;
    int invokeId;
    CDAPMsgStatus msgStatus;
    simtime_t requestedAt;
    simtime_t respondedAt;

};

//Free function
std::ostream& operator<< (std::ostream& os, const CDAPMsgLogEntry& mle);

#endif /* MESSAGELOGENTRY_H_ */
