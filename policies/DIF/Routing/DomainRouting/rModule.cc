/*
 * DomainModule.cc
 *
 *  Created on: Mar 23, 2015
 *      Author: gaixas1
 */

#include <DomainRouting/rModule.h>
#include <DomainRouting/Routing.h>

namespace DMRnms {

RoutingUpdate::RoutingUpdate(const Address &_addr, const std::string &_domain) :IntRoutingUpdate(_addr){
    domain = _domain;
}

rModule::rModule(Routing * _parent, const Address &_naddr, const std::string &_domain, const std::string &_addr)
    :parent(_parent), myNAddress(_naddr), domain(_domain), myAddr(_addr){}

void rModule::scheduleAt(const double & time, cMessage *msg){
    parent->chScheduleAt(domain, time, msg);
}

} /* namespace DomainRouting */
