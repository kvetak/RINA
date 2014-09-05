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

#ifndef __RINA_RMTPORTMANAGER_H_
#define __RINA_RMTPORTMANAGER_H_

#include <omnetpp.h>

#include "RMTPort.h"

typedef std::map<ConnectionId, RMTPort*>  RMTPorts;

// TODO: move the whole thing into RA
class RMTPortManager : public cSimpleModule
{
  protected:
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);

  public:
    RMTPortManager();
    virtual ~RMTPortManager();

    typedef RMTPorts::iterator iterator;
    iterator begin();
    iterator end();

    RMTPort* getPort(ConnectionId conId);
    void addPort(ConnectionId conId);
    void removePort(ConnectionId conId);

  private:
    RMTPorts ports;
};

#endif
