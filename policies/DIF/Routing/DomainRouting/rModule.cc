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
 * DomainModule.cc
 *
 *  Created on: Mar 23, 2015
 *      Author: gaixas1
 */

#include "DIF/Routing/DomainRouting/rModule.h"
#include "DIF/Routing/DomainRouting/Routing.h"

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
