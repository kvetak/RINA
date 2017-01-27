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

#include "DIF/RA/PDUFG/GRE/Simple/GRE_Simple.h"

namespace GRE_Simple {

Register_Class(GRE_Simple);

using namespace std;
using namespace common_GraphCL;

// A new flow has been inserted/or removed
void GRE_Simple::insertedFlow(const Address &addr, const QoSCube &qos, RMTPort * port){
    string dst = addr.getIpcAddress().getName();
    addr_t d = parseRawAddr(dst);
    index_t id = 0;
    if(neiIds.find(d) == neiIds.end()) {
        if(!unasignedIds.empty()) {
            id = unasignedIds.front();
            unasignedIds.pop();
        } else { id = nextIndex++; }
        neiIds[d] = id;
        fwd->setNeighbour(d, id);
    } else { id = neiIds[d]; }
    fwd->addPort(id, port);
    neiPortsCurrent[d] = port;
    neiPorts[d].insert(port);
    if(neiPorts[d].size() == 1){
        rt->insertFlow(addr, dst, "", 1);
        routingUpdated();
    }
}
void GRE_Simple::removedFlow(const Address &addr, const QoSCube& qos, RMTPort * port){
    std::string dst = addr.getIpcAddress().getName();
    addr_t d = parseRawAddr(dst);
    index_t id = neiIds[d];
    neiPorts[d].erase(port);
    if(neiPorts[d].size() <= 0){
        rt->removeFlow(addr, dst, "");
        fwd->removePort(id);
        fwd->unsetNeighbour(d);
        neiPorts.erase(d);
        neiPortsCurrent.erase(d);
        routingUpdated();

        unasignedIds.push(id);
    } else {
        if(neiPortsCurrent[d] == port) {
            port_t p = * neiPorts[d].begin();
            neiPortsCurrent[d] = p;
            fwd->addPort(id, port);
        }
    }
}

//Routing has processes a routing update
void GRE_Simple::routingUpdated(){
    map<string, map<string, nhLMetric<mType>  > > changes = rt->getChanges();

    for(const auto & entry : changes[""]){
        addr_t d = parseRawAddr(entry.first);
        vPortsIndex ports;
        for(string nextHop : entry.second.nh){
            if(nextHop != "") {
                addr_t n = parseRawAddr(nextHop);
                index_t id = neiIds[n];
                ports.push_back(id);
            }
        }
        if(ports.empty()) {
            fwd->removeException(mask_t(d, 0));
        } else {
            fwd->addException(mask_t(d, 0), exception_t(COMMON, 0, ports));
        }
    }
}

// Called after initialize
void GRE_Simple::onPolicyInit(){
    nextIndex = 0;
    //Set Forwarding policy
    fwd = getRINAModule<GREFWD *>(this, 2, {MOD_RELAYANDMUX, MOD_POL_RMT_PDUFWD});
    rt = getRINAModule<IntTSimpleRouting<mType> *>(this, 2, {MOD_POL_ROUTING});

    mType infMetric = par("infinite");
    rt->setInfinite(infMetric);
}

}
