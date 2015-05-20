/*
 * DomainModule.h
 *
 *  Created on: Mar 23, 2015
 *      Author: gaixas1
 */

#ifndef DOMAINMODULE_H_
#define DOMAINMODULE_H_

#include <omnetpp.h>
#include <IntRouting.h>

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
