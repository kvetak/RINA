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

#include "DIF/RA/PDUFG/HierarchicalGenerator/HierarchicalGenerator.h"
#include "Common/APN.h"
#include "Common/Utils.h"

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
    fwd->setTmp(addr, port);
}

void HierarchicalGenerator::removedFlow(const Address &addr, const QoSCube& qos, RMTPort * port){
    std::string dst = addr.getIpcAddress().getName();
    pAddr parsedA = parseAddr(dst);

    domNeighbours[parsedA.domId][parsedA.addr].insert(port);

    if(domNeighbours[parsedA.domId][parsedA.addr].size() <= 0){
        rt->removeFlow(addr, parsedA.addr, parsedA.domId);
        domNeighbours[parsedA.domId].erase(dst);
        routingUpdated();
    }
    fwd->removeTmp(addr, port);
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
            }
            if(entry.first == "*") {
                for(auto domain : domains){
                    fwd->addReplace(domain, "*", ps);
                    //fwd->addReplace("0", "", ps);
                }
             //   fwd->addReplace(domain.first, "", ps);
            } else {
                fwd->addReplace(domain.first, entry.first, ps);
            }
        }
    }
}

// Called after initialize
void HierarchicalGenerator::onPolicyInit(){
    //Set Forwarding policy
    fwd = getRINAModule<HierarchicalTable::HierarchicalTable *>(this, 2, {MOD_RELAYANDMUX, MOD_POL_RMT_PDUFWD});
    rt = getRINAModule<tDomain::TDomainRouting<mType> *>(this, 2, {MOD_POL_ROUTING});

    myAddr = getModuleByPath("^.^")->par("ipcAddress").stringValue();
    parsStr = split(myAddr, '.');

    string alg = par("alg").stdstringValue();
    tDomain::ModuleAlgs algT = (alg == "LS")? tDomain::LS : tDomain::DV;

    int k = 0;
    for(string tAddr : parsStr){
        string domId = to_string(k);
        string pref = "";
        if(k > 0) {
            pref = join(parsStr, k, '.');
            pref.append(".");
        }
        fwd->addDomain(domId,pref);
        rt->addDomain(domId, tAddr, 32, algT);
        domains.push_back(domId);
        k++;
    }
    domains.pop_back();

    string domId = to_string(k);
    string pref = join(parsStr, k, '.');
    pref.append(".");
    fwd->addDomain(domId,pref);
    rt->addDomain(domId, "*", 32, algT);
    k++;

    difA = getRINAModule<DA*>(this, 3, {MOD_DIFALLOC, MOD_DA});
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
        return pAddr(to_string(i), sep[i]);
    } else {
        return pAddr(to_string(i), "*");
    }
}

}
