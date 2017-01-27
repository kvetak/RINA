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

/*
 * DomainModule.h
 *
 *  Created on: Mar 23, 2015
 *      Author: gaixas1
 */

#ifndef DOMAINMODULE_H_
#define DOMAINMODULE_H_

#include <omnetpp.h>
#include "DIF/Routing/IntRouting.h"

#include <string>

namespace DMRnms {

class Routing;

typedef std::map<std::string, std::string> s2s;
typedef std::map<std::string, Address> s2A;
struct dmNxt {
    std::string domain;
    s2A entries;
    dmNxt(const std::string &_domain)
        :domain(_domain){}
    dmNxt(const std::string &_domain, const s2A &_entries)
        :domain(_domain), entries(_entries){}
};
typedef std::vector<dmNxt> dmUpdateM;

typedef s2A::iterator s2AIt;
typedef s2s::iterator s2sIt;
typedef dmUpdateM::iterator dmUpdateMIt;

class RoutingUpdate : public IntRoutingUpdate {
public:
    RoutingUpdate(const Address &_addr, const std::string &_domain);
    std::string domain;
};

//Predefining class


class rModule {
public:
    rModule(Routing * _parent, const Address &_nAddr, const std::string &_domain, const std::string &_addr);
    virtual ~rModule(){};

    virtual bool processUpdate(RoutingUpdate * update) = 0;
    virtual void addFlow(const Address &_nAddr, const std::string &_addr, const unsigned short &_metric) = 0;
    virtual void removeFlow(const Address &_nAddr, const std::string &_addr) = 0;

    virtual void addAddr(const std::string &_addr) = 0;
    virtual void removeAddr(const std::string &_addr) = 0;

    virtual void setInfMetric(const unsigned short &inf) = 0;

    virtual dmNxt getChanges() = 0;
    virtual dmNxt getAll() = 0;

    virtual void handleMessage(cMessage *msg) = 0;

protected:
    Routing * parent;
    Address myNAddress;
    std::string domain;
    std::string myAddr;

    void scheduleAt(const double & time, cMessage *);
};

} /* namespace DomainRouting */

#endif /* DOMAINMODULE_H_ */
