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

#include "DIF/RA/PDUFG/GRE/Centralized/GRE_ClosSpine.h"

Register_Class(GRE_ClosSpine);

// A new flow has been inserted/or removed
void GRE_ClosSpine::insertedFlow(const Address &addr, const QoSCube &qos, RMTPort * port){
    string dst      = addr.getIpcAddress().getName();
    addr_t a        = parseRawAddr(dst);
    addr_t a_z      = getZone(a);
    //addr_t a_i      = getIdentifier(a);
    addr_t index    = a_z-f;

    //Check we expect the link
    if(neiLinks[a] == 0) {  error("This should never happen!!!!"); }

    //Update port info and return if it's only a replacement
    port_t p = neiPorts[a];
    neiPorts[a] = port;
    fwd->addPort(index, port);
    if(p != nullptr && aliveNeis[index]) { return; }

    aliveNeis[index] = true;
    rt->onFlow(a);
}
void GRE_ClosSpine::removedFlow(const Address &addr, const QoSCube& qos, RMTPort * port){
    string dst      = addr.getIpcAddress().getName();
    addr_t a        = parseRawAddr(dst);
    addr_t a_z      = getZone(a);
    //addr_t a_i      = getIdentifier(a);
    addr_t index    = a_z-f;

    //Check we expect the link
    if(neiLinks[a] == 0) {  error("This should never happen!!!!"); }

    //Update port info and return if it's already null and port down
    port_t p = neiPorts[a];
    neiPorts[a] = port;
    if(p == nullptr && !aliveNeis[index]) { return; }

    fwd->removePort(index);
    aliveNeis[index] = false;
    rt->offFlow(a);
}

void GRE_ClosSpine::killLink(const string & link) {
    elink_t l       = stoi(link);
    addr_t a        = linkNei[l];
    addr_t a_z      = getZone(a);
    //addr_t a_i      = getIdentifier(a);
    addr_t index    = a_z-f;

    //Do nothing if port is not set or already down
    if(neiPorts[a] == nullptr || !aliveNeis[index]) { return; }

    fwd->removePort(index);
    aliveNeis[index] = false;

    rt->offFlow(a);
}

void GRE_ClosSpine::resurrectLink(const string &  link) {
    elink_t l       = stoi(link);
    addr_t a        = linkNei[l];
    addr_t a_z      = getZone(a);
    //addr_t a_i      = getIdentifier(a);
    addr_t index    = a_z-f;

    //Do nothing if port is not set or already alive
    if(neiPorts[a] == nullptr || aliveNeis[index]) { return; }

    aliveNeis[index] = true;
    fwd->addPort(index, neiPorts[a]);

    rt->onFlow(a);
}

//Routing has processes a routing update
void GRE_ClosSpine::routingUpdated(){ }

// Called after initialize
void GRE_ClosSpine::onPolicyInit(){
    rt = getRINAModule<RoutingDumb *>(this, 2, {MOD_POL_ROUTING});
    fwd = getRINAModule<Clos2 *>(this, 2, {MOD_RELAYANDMUX, MOD_POL_RMT_PDUFWD});

    f = par("fabrics").longValue();
    p = par("pods").longValue();
    s = par("spines").longValue();
    t = par("tors").longValue();

    rawAddr = getModuleByPath("^.^")->par("ipcAddress").stringValue();
    dif = getModuleByPath("^.^")->par("difName").stringValue();
    myaddr = parseRawAddr(rawAddr);
    zone = getZone(myaddr);
    ident = getIdentifier(myaddr);

    rt->setMyA(myaddr);

    // Start default config:
    fwd->setPadding(f);
    fwd->setNumPods(p);
    fwd->addPort(p-1, nullptr);

    aliveNeis = vector<bool>(p, false);

    for(addr_t d = 0; d < p; d++) {
        setNei(d, getAddr(d+f, zone));
    }
}

void GRE_ClosSpine::setNei(addr_t d, addr_t dst_addr) {
    addr_t dst_man = getAddr(d+f, 255);

    elink_t dst_link = getELink(myaddr, dst_addr);
    Address dstAddr (getRawAddr_t(dst_addr).c_str(), dif.c_str());
    Address dstMan  (getRawAddr_t(dst_man ).c_str(), dif.c_str());

    neiLinks[dst_addr] = dst_link;
    linkNei[dst_link] = dst_addr;
    neiAddr[dst_addr] = dstAddr;

    fwd->setNeighbour(dst_addr, d);
    rt->addNei(dst_addr, dstAddr, dstMan, dst_link);

    if(FailureSimulation::instance) {
        FailureSimulation::instance->registerLink(to_string(dst_link), this);
    }
}
