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

#include <BiDomainGenerator/BiDomainGenerator.h>
#include "APN.h"
#include <Utils.h>



namespace BiDomainGenerator {

Register_Class(BiDomainGenerator);

using namespace std;

// A new flow has been inserted/or removed
void BiDomainGenerator::insertedFlow(const Address &addr, const unsigned short &qos, RMTPort * port){
    std::string dst = addr.getIpcAddress().getName();
    neighbours[dst].insert(port);
    if(neighbours[dst].size() == 1){
        pAddr parsedA = parseAddr(dst);
        if(parsedA.domain != ""){
            rt->addFlow(addr, "", parsedA.domain, 1);
            rt->addFlow(addr, parsedA.domain, parsedA.addr,1);
        } else {
            rt->addFlow(addr, parsedA.domain, parsedA.addr,1);
        }

        routingUpdated();
    }
}
void BiDomainGenerator::removedFlow(const Address &addr, const unsigned short &qos, RMTPort * port){
    std::string dst = addr.getIpcAddress().getName();
    neighbours[dst].erase(port);
    if(neighbours[dst].size() <= 0){
        pAddr parsedA = parseAddr(dst);

        if(parsedA.domain != ""){
            rt->removeFlow(addr, "", parsedA.domain);
            rt->removeFlow(addr, parsedA.domain, parsedA.addr);
        } else {
            rt->removeFlow(addr, parsedA.domain, parsedA.addr);
        }

        neighbours.erase(dst);

        routingUpdated();
    }
}

//Routing has processes a routing update
void BiDomainGenerator::routingUpdated(){
    DMRnms::dmUpdateM changes = rt->getChanges();
    for(DMRnms::dmUpdateMIt it = changes.begin(); it!= changes.end(); it++){
        for(DMRnms::s2AIt eIt = it->entries.begin(); eIt != it->entries.end(); eIt++){
            std::string dst = eIt->first;
            std::string nextHop = eIt->second.getIpcAddress().getName();

            EV << "Entry ::: \""<< it->domain << "\"/\""<< dst << "\" -> " << nextHop << " ("<< eIt->second<<")" <<endl;
            RMTPort * p = NULL;

            NTableIt n = neighbours.find(nextHop);
            if(nextHop != "" && n != neighbours.end()){
                p = *(n->second.begin());
            }

            if(p == NULL) {
                fwd->remove(it->domain, dst);
            } else {
                fwd->insert(it->domain, dst, p);
            }
        }
    }
}

// Called after initialize
void BiDomainGenerator::onPolicyInit(){
    //Set Forwarding policy
    fwd = check_and_cast<DomainTable::DomainTable *>
        (getModuleByPath("^.^.relayAndMux.pduForwardingPolicy"));

    rt = check_and_cast<DMRnms::Routing *>
        (getModuleByPath("^.^.routingPolicy"));

    string myAddr = getParentModule()->getParentModule()->par("ipcAddress").stringValue();

    vector<string> parsStr = split(myAddr, '.');
    if(parsStr.size() != 2) {
        error("BiDomainGenerator own address must be on the form A.B");
    }
    myPrefix = parsStr[0];
    mySufix = parsStr[1];

    string alg0 = par("alg0").stdstringValue();
    string alg1 = par("alg1").stdstringValue();

    fwd->addDomain(myPrefix);
    fwd->addDomain("");

    if(alg0 == "LS"){
        rt->addDomain("", myPrefix, DMRnms::ModuleAlgs::LS);
    } else {
        rt->addDomain("", myPrefix, DMRnms::ModuleAlgs::DV);
    }

    if(alg1 == "LS"){
        rt->addDomain(myPrefix, mySufix, DMRnms::ModuleAlgs::LS);
    } else {
        rt->addDomain(myPrefix, mySufix, DMRnms::ModuleAlgs::DV);
    }


    difA = check_and_cast<DA *>(getModuleByPath("^.^.^.difAllocator.da"));
}

pAddr BiDomainGenerator::parseAddr(const string &addr){
    vector<string> sep = split(addr, '.');
    if(isPrefix(myPrefix, addr)){
        if(sep.size()>=2) {
            return pAddr(myPrefix, sep[1]);
        } else {
            return pAddr(myPrefix, "");
        }
    } else {
        return pAddr("", sep[0]);
    }
}

}
