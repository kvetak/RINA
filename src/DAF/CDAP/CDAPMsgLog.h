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

#ifndef CDAPMSGLOG_H_
#define CDAPMSGLOG_H_

//Standard libraries
#include <omnetpp.h>
//RINASim libraries
#include "CDAPMsgLogEntry.h"

typedef std::list<CDAPMsgLogEntry> TMessageLog;
typedef TMessageLog::iterator TMLIter;
typedef TMessageLog::const_iterator TMLConstIter;

class CDAPMsgLog : public cSimpleModule {
  public:
    CDAPMsgLog();
    virtual ~CDAPMsgLog();

    std::string info() const;

    void insert();
    void remove();

  protected:
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);

  private:
    TMessageLog MsgLog;
};

#endif /* CDAPMSGLOG_H_ */
