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

#ifndef __RINA_CONNECTIONTABLE_H_
#define __RINA_CONNECTIONTABLE_H_

//Standard libraries
#include <omnetpp.h>
//RINASim libraries
#include <ConnectionTableEntry.h>

typedef std::list<ConnectionTableEntry> TConTable;
typedef TConTable::iterator TCTIter;
typedef TConTable::const_iterator TCTConstIter;

class ConnectionTable : public cSimpleModule
{
  public:
    std::string info() const;

    void insertNew(Flow* flow);
    void insertNew(Flow* flow, cGate* nIn, cGate* nOut);
    void insert(const ConnectionTableEntry& entry);
    void remove();

    ConnectionTableEntry* findEntryByFlow(Flow* flow);

    cGate* findOutputGate(cGate* input, bool& isGoingUp);

    bool setSouthGates(Flow* flow, cGate* sIn, cGate* sOut);
    bool setNorthGates(Flow* flow, cGate* nIn, cGate* nOut);
    bool setFa(Flow* flow, FABase* fa);
    bool setStatus(Flow* flow, ConnectionTableEntry::ConnectionStatus status);

    FABase* getFa(Flow* flow);

  protected:
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);

  private:
    TConTable ConTable;
};

#endif
