// The MIT License (MIT)
//
// Copyright (c) 2014-2016 Brno University of Technology, PRISTINE project
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.

#ifndef DomainRouting_H_
#define DomainRouting_H_

#include "DIF/Routing/IntRouting.h"

#include "Common/Address.h"

#include <vector>
#include <map>
#include <string>

#include "DIF/Routing/DomainRouting/rModule.h"

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
