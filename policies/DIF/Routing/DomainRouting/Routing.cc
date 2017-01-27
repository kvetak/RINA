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

#include "DIF/Routing/DomainRouting/Routing.h"

#include "DIF/Routing/DomainRouting/DV/DV.h"
#include "DIF/Routing/DomainRouting/LS/LS.h"

namespace DMRnms {

Register_Class(Routing);

    Routing::~Routing() {
        for(std::map<std::string, rModule*>::iterator it = rModules.begin(); it!=rModules.end(); it++){
            delete it->second;
        }
    }

    bool Routing::processUpdate(IntRoutingUpdate * update) {
        RoutingUpdate * up = dynamic_cast<RoutingUpdate*>(update);
        if(up == NULL) {
            return false;
        }

        EV << "Received update from "<< up->getSource() << " for \""<< up->domain << "\" at "<< simTime() <<endl;


        if(rModules.find(up->domain) != rModules.end()){
            if(rModules[up->domain]->processUpdate(up)){
                changedModules.insert(up->domain);
                return true;
            }
        }
        return false;
    }

    //Add/Remove a domain
    void Routing::addDomain(const std::string &domain, const std::string &addr, const ModuleAlgs &alg) {
        switch(alg) {
        case DV :
            rModules[domain] = new DMRnmsDV::DV(this, myAddress, domain, addr);
            break;
        case LS :
            rModules[domain] = new DMRnmsLS::LS(this, myAddress, domain, addr);
            break;
        }
    }
    void Routing::removeDomain(const std::string &domain) {
        if(rModules.find(domain) != rModules.end()){
            delete rModules[domain];
            rModules.erase(domain);
        }
    }

    //Add/Remove flow to neighbour
    void Routing::addFlow(const Address &nAddr, const std::string &domain, const std::string &addr, const unsigned short &metric) {
        if(rModules.find(domain) != rModules.end()){
            rModules[domain]->addFlow(nAddr, addr, metric);
            changedModules.insert(domain);
        }
    }

    void Routing::removeFlow(const Address &nAddr, const std::string &domain, const std::string &addr) {
        if(rModules.find(domain) != rModules.end()){
            rModules[domain]->removeFlow(nAddr, addr);
            changedModules.insert(domain);
        }
    }

    // Add/Remove secondary addresses
    void Routing::addAddr(const std::string &domain, const std::string &addr) {
        if(rModules.find(domain) != rModules.end()){
            rModules[domain]->addAddr(addr);
            changedModules.insert(domain);
        }
    }
    void Routing::removeAddr(const std::string &domain, const std::string &addr) {
        if(rModules.find(domain) != rModules.end()){
            rModules[domain]->removeAddr(addr);
            changedModules.insert(domain);
        }
    }

    //Set Infinite
    void Routing::setInfMetric(const std::string &domain, const unsigned short &inf) {
        if(rModules.find(domain) != rModules.end()){
            rModules[domain]->setInfMetric(inf);
        }
    }

    // Sends a Routing Update
    void Routing::chSendUpdate(RoutingUpdate * update){
        EV << update->getDestination() << endl;
        sendUpdate(update);
    }

    //Get next hops
    dmUpdateM Routing::getChanges() {
        dmUpdateM dmu;

        for(std::set<std::string>::iterator it = changedModules.begin(); it!=changedModules.end(); it++){
            dmu.push_back(rModules[*it]->getChanges());
        }

        return dmu;
    }
    dmUpdateM Routing::getAll() {
        dmUpdateM dmu;

        for(std::map<std::string, rModule*>::iterator it = rModules.begin(); it!=rModules.end(); it++){
            dmu.push_back(it->second->getAll());
        }

        return dmu;
    }

    void Routing::onPolicyInit(){}


    void Routing::chScheduleAt(const std::string domain, const double & time, cMessage *msg){
        Enter_Method_Silent();
        RoutingSelf * m = new RoutingSelf();
        m->domain = domain;
        m->subM = msg;
        scheduleAt(simTime()+time, m);
    }
    void Routing::handleMessage(cMessage *msg){
        RoutingSelf * m = dynamic_cast<RoutingSelf * >(msg);
        if(m){
            if(rModules.find(m->domain) != rModules.end()){
                rModules[m->domain]->handleMessage(m->subM);
            } else {
                delete m->subM;
            }
        }
        delete msg;
    }


    void Routing::finish(){
        if(par("printAtEnd").boolValue()){
            EV<< "Routing at "<< myAddress <<endl;
            dmUpdateM dmu = getAll();

            for(DMRnms::dmUpdateMIt it = dmu.begin(); it!= dmu.end(); it++){
                EV << "Domain : \"" << it->domain<<"\"" << endl;
                for(DMRnms::s2AIt eIt = it->entries.begin(); eIt != it->entries.end(); eIt++){
                    EV << "  "<< eIt->first << " -> " << eIt->second << endl;
                }
            }
        }
    }

}
