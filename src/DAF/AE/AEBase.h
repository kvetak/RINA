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

#ifndef __RINA_AEBASE_H_
#define __RINA_AEBASE_H_

//Standard libraries
#include <omnetpp.h>
//RINASim libraries
#include "APNamingInfo.h"
#include "Flow.h"

typedef std::list<Flow> Flows;
typedef Flows::iterator TFlowsIter;

class AEBase : public cSimpleModule
{
  public:
    bool isFlowUsed(const Flow* flow);
    void insert(const Flow& flow);

    const APNamingInfo& getApni() const;
    void setApni(const APNamingInfo& apni);
    const Flows& getFlows() const;
    void setFlows(const Flows& flows);
    const std::string& getSrcAeInstance() const;
    void setSrcAeInstance(const std::string& srcAeInstance);
    const std::string& getSrcAeName() const;
    void setSrcAeName(const std::string& srcAeName);
    const std::string& getSrcApInstance() const;
    void setSrcApInstance(const std::string& srcApInstance);
    const std::string& getSrcApName() const;
    void setSrcApName(const std::string& srcApName);

  protected:
    Flows flows;
    APNamingInfo apni;

    std::string srcApName;
    std::string srcApInstance;
    std::string srcAeName;
    std::string srcAeInstance;

    virtual void initialize();
    virtual void handleMessage(cMessage *msg);

    void initNamingInfo();
};

#endif
