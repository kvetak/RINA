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

#ifndef __RINA_SIMPLERIB_H_
#define __RINA_SIMPLERIB_H_

#include <omnetpp.h>
#include "DAF/RIB/RIB/SimpleRIB/SimpleRIBObj.h"
#include "DAF/CDAP/CDAPMessage_m.h"
#include "DAF/RIB/RIB/RIBBase.h"

using namespace omnetpp;

typedef std::list<SimpleRIBObj> ObjTable;
typedef ObjTable::iterator ObjTableIter;
typedef ObjTable::const_iterator ObjTableConstIter;

/**
 * TODO - Generated class
 */
class Simplerib : public RIBBase
{
public:
    bool createAE(std::string AEName);
    bool createIAE(std::string IAEName, AEBase* ae);
    bool deleteAE(std::string AEName);
    bool deleteIAE(std::string IAEName);

    object_t* createObj(int CDAPConn, object_t *obj);
    object_t* deleteObj(int CDAPConn, std::string objName);
    object_t* writeObj(int CDAPConn, object_t *obj);
    object_t* readObj(int CDAPConn, std::string objName);

  protected:
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);
      object_t* findObj(int CDAPConn, std::string objName);

      ObjTable objTable;
};

#endif
