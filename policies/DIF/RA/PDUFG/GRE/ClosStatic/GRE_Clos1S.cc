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

#include "DIF/RA/PDUFG/GRE/ClosStatic/GRE_Clos1S.h"

namespace GRE_Clos {

Register_Class(GRE_ClosS1);

using namespace std;
using namespace common_GraphCL;

// A new flow has been inserted/or removed
void GRE_ClosS1::insertedFlow(const Address &addr, const QoSCube &qos, RMTPort * port){
    string dst = addr.getIpcAddress().getName();
    addr_t d = parseRawAddr(dst);

    index_t id = getIdentifier(d);
    addr_t z = getZone(d);
    if(z == zone) { id -= f; }
    else { id += t; }

//    cout << "At "<< rawAddr << " << "<< addr << " : "<< (int)id<<endl;

    fwd->addPort(id, port);

    neiPortsCurrent[d] = port;
    neiPorts[d].insert(port);
    if(neiPorts[d].size() == 1){
        aliveNeis[id] = true;
        if(z == zone) { resetNeiGroups1(); }
        else { resetNeiGroups2(); }
    }
}
void GRE_ClosS1::removedFlow(const Address &addr, const QoSCube& qos, RMTPort * port){
    std::string dst = addr.getIpcAddress().getName();
    addr_t d = parseRawAddr(dst);

    index_t id = getIdentifier(d);
    index_t z = getZone(d);
    if(z == zone) { id -= f; }
    else { id += t; }

    neiPorts[d].erase(port);
    if(neiPorts[d].size() <= 0){
        fwd->removePort(id);
        fwd->unsetNeighbour(d);
        neiPortsCurrent[d] = nullptr;
        aliveNeis[id] = false;
        if(z == zone) { resetNeiGroups1(); }
        else { resetNeiGroups2(); }
    } else {
        if(neiPortsCurrent[d] == port) {
            port_t p = * neiPorts[d].begin();
            neiPortsCurrent[d] = p;
            fwd->addPort(id, port);
        }
    }
}

//Routing has processes a routing update
void GRE_ClosS1::routingUpdated(){}

// Called after initialize
void GRE_ClosS1::onPolicyInit(){
    f = par("spineS").longValue();
    t = par("TEs").longValue();
    s = par("spines").longValue();

    //Set Forwarding policy
    fwd = getRINAModule<Clos1 *>(this, 2, {MOD_RELAYANDMUX, MOD_POL_RMT_PDUFWD});

    rawAddr = getModuleByPath("^.^")->par("ipcAddress").stringValue();
    myaddr = parseRawAddr(rawAddr);
    zone = getZone(myaddr);
    ident = getIdentifier(myaddr);

    fwd->setZone(zone);
    fwd->setIdentifier(ident);
    fwd->setNumSpines(f);

    fwd->addPort(t+s-1, nullptr);
    for(addr_t d = 0; d < t; d++) {
        fwd->setNeighbour(getAddr(zone, d+f), d);
        aliveNeis.push_back(false);
    }
    fwd->setGroup(1, vPortsIndex());
    for(addr_t d = 0; d < s; d++) {
        fwd->setNeighbour(getAddr(ident, d), d+t);
        aliveNeis.push_back(false);
    }
    fwd->setGroup(2, vPortsIndex());
}

void GRE_ClosS1::resetNeiGroups1() {
    vPortsIndex neis;
    for(addr_t d = 0; d < t; d++) {
        if(aliveNeis[d]) { neis.push_back(d); }
    }
    fwd->setGroup(1, neis);
}


void GRE_ClosS1::resetNeiGroups2() {
    vPortsIndex neis;
    for(addr_t d = 0; d < s; d++) {
        if(aliveNeis[d+t]) { neis.push_back(d+t); }
    }
    fwd->setGroup(2, neis);
}

}
