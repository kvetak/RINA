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
//RINASim libraries
#include "CDAPMessage_m.h"
#include "ExternConsts.h"

class CDAPMsgLogEntry {
  public:


    //(De)Constructor
    CDAPMsgLogEntry(unsigned char opc, long invoke, bool srflag);
    virtual ~CDAPMsgLogEntry();

    std::string info() const;
    std::string getOpCodeString() const;

    //Getters and Setters
    long getInvokeId() const;
    void setInvokeId(long invokeId);

    const unsigned char getOpCode() const;
    void setOpCode(const unsigned char opCode);

    const simtime_t& getProcessedAt() const;
    void setProcessedAt(const simtime_t& requestedAt);

  private:
    //FIXME: Vesely - Convert to enum
    unsigned char opCode;
    long invokeId;
    simtime_t processedAt;
    bool sndFlag;

};

//Free function
std::ostream& operator<< (std::ostream& os, const CDAPMsgLogEntry& mle);

#endif /* MESSAGELOGENTRY_H_ */
