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

#include <HierarchicalGenerator/HierarchicalGenerator.h>
#include "APN.h"
#include <Utils.h>

#include <stdio.h>
#include <stdlib.h>


namespace HierarchicalGenerator {

Register_Class(HierarchicalGenerator);

using namespace std;

// A new flow has been inserted/or removed
void HierarchicalGenerator::insertedFlow(const Address &addr, const QoSCube &qos, RMTPort * port){
    std::string dst = addr.getIpcAddress().getName();
    pAddr parsedA = parseAddr(dst);

    domNeighbours[parsedA.domId][parsedA.addr].insert(port);

    if(domNeighbours[parsedA.domId][parsedA.addr].size() == 1){
        rt->insertFlow(addr, parsedA.addr, parsedA.domId, 1);
        routingUpdated();
    }
}

void HierarchicalGenerator::removedFlow(const Address &addr, RMTPort * port){
    std::string dst = addr.getIpcAddress().getName();
    pAddr parsedA = parseAddr(dst);

    domNeighbours[parsedA.domId][parsedA.addr].insert(port);

    if(domNeighbours[parsedA.domId][parsedA.addr].size() <= 0){
        rt->removeFlow(addr, parsedA.addr, parsedA.domId);
        domNeighbours[parsedA.domId].erase(dst);
        routingUpdated();
    }
}

//Routing has processes a routing update
void HierarchicalGenerator::routingUpdated(){
    map<string, map<string, nhLMetric<mType>  > > changes = rt->getChanges();

    for(const auto & domain : changes){
        for(const auto & entry : domain.second){
            vector< RMTPort * > ps;
            for(string nextHop : entry.second.nh){
                RMTPort * p = NULL;
                if(nextHop != "") {
                    auto n = domNeighbours[domain.first].find(nextHop);
                    if(n != domNeighbours[domain.first].end()){
                        if(!n->second.empty()) {
                            p = *(n->second.begin());
                        }
                    }
                }
                if(p != NULL) {
                    ps.push_back(p);
                }
                fwd->addReplace(domain.first, entry.first, ps);
            }
        }
    }
}

// Called after initialize
void HierarchicalGenerator::onPolicyInit(){
    //Set Forwarding policy
    fwd = check_and_cast<HierarchicalTable::HierarchicalTable *>
        (getModuleByPath("^.^.relayAndMux.pduForwardingPolicy"));

    rt = check_and_cast<tDomain::TDomainRouting<mType> *>
        (getModuleByPath("^.^.routingPolicy"));

    string myAddr = getParentModule()->getParentModule()->par("ipcAddress").stringValue();
    parsStr = split(myAddr, '.');

    string alg = par("alg").stdstringValue();
    tDomain::ModuleAlgs algT = (alg == "LS")? tDomain::LS : tDomain::DV;

    int k = 0;
    for(string tAddr : parsStr){
        string domId = to_string(k);
        fwd->addDomain(domId,join(parsStr, k, '.'));
        rt->addDomain(domId, myAddr, tAddr, 32, algT);
        k++;
    }

    string domId = to_string(k);
    fwd->addDomain(domId,join(parsStr, k, '.'));
    rt->addDomain(domId, myAddr, "*", 32, algT);
    k++;

    difA = check_and_cast<DA *>(getModuleByPath("^.^.^.difAllocator.da"));
}

pAddr HierarchicalGenerator::parseAddr(const string &addr){
    vector<string> sep = split(addr, '.');
    int i = 0;
    for(; i < (int)parsStr.size() && i < (int)sep.size(); i++){
        if(parsStr[i] != sep[i]) {
            return pAddr(to_string(i), sep[i]);
        }
    }
    if(i < (int)sep.size()) {
        return pAddr(to_string(i), sep[1]);
    } else {
        return pAddr(to_string(i), "*");
    }
}

}
