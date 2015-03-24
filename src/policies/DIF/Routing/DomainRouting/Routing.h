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

#ifndef DomainRouting_H_
#define DomainRouting_H_

#include <IntRouting.h>

#include "Address.h"

#include <vector>
#include <map>
#include <string>

#include <DomainRouting/rModule.h>

namespace DMRnms {

enum ModuleAlgs { DV, LS };



class RoutingSelf: public cMessage {
public:
    RoutingSelf():cMessage("RoutingSelf"){}
    std::string domain;
    cMessage * subM;
};

class Routing: public IntRouting {
public:

    //Finish and delete modules
    ~Routing();

    void finish();


    // Process a Routing Update, return true => inform FWDG of the update
    bool processUpdate(IntRoutingUpdate * update);

    // Add/Remove a domain
    void addDomain(const std::string &domain, const std::string &addr, const ModuleAlgs &alg);
    void removeDomain(const std::string &domain);

    // Add/Remove flow to neighbour
    void addFlow(const Address &nAddr, const std::string &domain, const std::string &addr, const unsigned short &metric);
    void removeFlow(const Address &nAddr, const std::string &domain, const std::string &addr);

    // Add/Remove secondary addresses
    void addAddr(const std::string &domain, const std::string &addr);
    void removeAddr(const std::string &domain, const std::string &addr);

    // Set Infinite Metric
    void setInfMetric(const std::string &domain, const unsigned short &inf);

    // Sends a Routing Update
    void chSendUpdate(RoutingUpdate * update);

    // Get next hops
    dmUpdateM getChanges();
    dmUpdateM getAll();


    void chScheduleAt(const std::string domain, const double & time, cMessage *msg);
    virtual void handleMessage(cMessage *msg);

protected:
    // Called after initialize
    void onPolicyInit();
    std::map<std::string, rModule*> rModules;
    std::set<std::string> changedModules;
};

}

#endif /* DomainRouting_H_ */
