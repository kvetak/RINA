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

#include "DIF/RA/PDUFG/GRE/Centralized/GRE_ClosToR.h"

Register_Class(GRE_ClosToR);

// A new flow has been inserted/or removed
void GRE_ClosToR::insertedFlow(const Address &addr, const QoSCube &qos,
        RMTPort * port) {
    string dst = addr.getIpcAddress().getName();
    addr_t a = parseRawAddr(dst);
    //addr_t a_z      = getZone(a);
    addr_t a_i = getIdentifier(a);
    addr_t index = (a_i < f) ? a_i : f;

    //Check we expect the link
    if (neiLinks[a] == 0) {
        if (index < f) {
            error("This should never happen!!!!");
        } else {
            setNei(f, a);
        }
    }

    //Update port info and return if it's only a replacement
    port_t p = neiPorts[a];
    neiPorts[a] = port;
    fwd->addPort(index, port);
    if (p != nullptr && aliveNeis[index]) {
        return;
    }

    aliveNeis[index] = true;
    rt->onFlow(a);

    resetNeiGroups();

    routingUpdated();
}
void GRE_ClosToR::removedFlow(const Address &addr, const QoSCube& qos,
        RMTPort * port) {
    string dst = addr.getIpcAddress().getName();
    addr_t a = parseRawAddr(dst);
    //addr_t a_z      = getZone(a);
    addr_t a_i = getIdentifier(a);
    addr_t index = (a_i < f) ? a_i : f;

    //Check we expect the link
    if (neiLinks[a] <= 0) {
        error("This should never happen!!!!");
    }

    //Update port info and return if it's already null and port down
    port_t p = neiPorts[a];
    neiPorts[a] = port;
    if (p == nullptr && !aliveNeis[index]) {
        return;
    }

    fwd->removePort(index);
    aliveNeis[index] = false;
    rt->offFlow(a);

    resetNeiGroups();
}

void GRE_ClosToR::killLink(const string & link) {
    elink_t l = stoi(link);
    addr_t a = linkNei[l];
    //addr_t a_z      = getZone(a);
    addr_t a_i = getIdentifier(a);
    addr_t index = (a_i < f) ? a_i : f;

    //Do nothing if port is not set or already down
    if (neiPorts[a] == nullptr || !aliveNeis[index]) {
        return;
    }

    aliveNeis[index] = false;
    fwd->removePort(index);
    resetNeiGroups();

    rt->offFlow(a);
    routingUpdated();
}

void GRE_ClosToR::resurrectLink(const string & link) {
    elink_t l = stoi(link);
    addr_t a = linkNei[l];
    //addr_t a_z      = getZone(a);
    addr_t a_i = getIdentifier(a);
    addr_t index = (a_i < f) ? a_i : f;

    //Do nothing if port is not set or already down
    if (neiPorts[a] == nullptr || !aliveNeis[index]) {
        return;
    }

    fwd->addPort(index, neiPorts[a]);
    aliveNeis[index] = false;
    resetNeiGroups();

    rt->offFlow(a);
}

//Routing has processes a routing update
void GRE_ClosToR::routingUpdated() {

    vPortsIndex list;

    //Update entries to zone managers
    if (rt->r_stat & R_INZONE_CHANGES) {
        addr_t def_man = 0;

        in_exceptions.clear();

        for (auto & e : rt->inzone.neiState) {
            list.clear();

            if (e.second.m1 < 16) {
                for (auto & i : e.second.op1) {
                    addr_t index = (i < f) ? i : f;
                    if (aliveNeis[index]) {
                        list.push_back(index);
                    }
                }
            }

            if (list.empty()) {
                in_exceptions[mask_t(getAddr(zone, e.first), 0)] =
                        exception_t();
            } else {
                in_exceptions[mask_t(getAddr(zone, e.first), 0)] = exception_t(
                        COMMON, 0, list);
                if (def_man < e.first) {
                    def_man = e.first;
                    in_exceptions[mask_t(getAddr(zone, 255), 0)] = exception_t(
                            COMMON, 0, list);
                }
            }
        }
        if (def_man == 0) {
            in_exceptions[mask_t(getAddr(zone, 255), 0)] = exception_t();
        }
    }

    if (rt->r_stat & R_EXCEPTIONS_CHANGES) {
        r_v1 = rt->v1;
        r_v2 = rt->v2;
        resetNeiGroups();


        for (auto & e : rt->ex) {
            if(e.valid.empty()) {
                in_exceptions[mask_t(e.a, e.m)] = exception_t();
            } else {
                list.clear();
                for(auto & i : e.valid) {
                    list.push_back(i);
                }
               in_exceptions[mask_t(e.a, e.m)] = exception_t( COMMON, 0, list);
            }
        }

    }

    map<mask_t, exception_t> exceptions;
    exceptions.insert(in_exceptions.begin(), in_exceptions.end());      // To MA
    exceptions.insert(same_zone_exceptions.begin(), same_zone_exceptions.end()); // From zone Errors
    for (auto & eM : other_zones_exceptions) {         // To reach specific pods
        exceptions.insert(eM.second.begin(), eM.second.end());
    }

    fwd->setExceptions(exceptions);

    rt->r_stat = 0;
}

// Called after initialize
void GRE_ClosToR::onPolicyInit() {
    rt = getRINAModule<RoutingClient *>(this, 2, { MOD_POL_ROUTING });
    fwd = getRINAModule<Clos0 *>(this, 2,
            { MOD_RELAYANDMUX, MOD_POL_RMT_PDUFWD });

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

    addr_t ManA = getAddr(zone, 255);
    Address Man(getRawAddr_t(ManA).c_str(), dif.c_str());
    rt->setMasterAddr(Man);

    fwd->setZone(zone);
    fwd->setSpines(f);

    fwd->addPort(f, nullptr);
    fwd->setGroup(1, vPortsIndex());
    fwd->setGroup(2, vPortsIndex());

    aliveNeis = vector<bool>(f + 1, false);
    r_v1 =  vector<bool>(f, true);
    r_v2 =  vector<bool>(f, true);

    for (addr_t d = 0; d < f; d++) {
        setNei(d, getAddr(zone, d));
    }
}

void GRE_ClosToR::setNei(addr_t d, addr_t dst_addr) {
    elink_t dst_link = getELink(myaddr, dst_addr);
    Address dstAddr(getRawAddr_t(dst_addr).c_str(), dif.c_str());

    neiLinks[dst_addr] = dst_link;
    linkNei[dst_link] = dst_addr;
    neiAddr[dst_addr] = dstAddr;

    fwd->setNeighbour(dst_addr, d);
    rt->addNei(dst_addr, dstAddr, true, dst_link);

    if (d < f) {
        if (FailureSimulation::instance) {
            FailureSimulation::instance->registerLink(to_string(dst_link),
                    this);
        }
    }
}

void GRE_ClosToR::resetNeiGroups() {
    v1 = r_v1;
    v2 = r_v2;
    for (addr_t d = 0; d < f; d++) {
        if (!aliveNeis[d]) {
            v1[d] = false;
            v2[d] = false;
        }
    }

    vPortsIndex neis;
    for (addr_t d = 0; d < f; d++) {
        if (v1[d]) {
            neis.push_back(d);
        }
    }
    fwd->setGroup(1, neis);

    neis.clear();
    for (addr_t d = 0; d < f; d++) {
        if (v2[d]) {
            neis.push_back(d);
        }
    }
    fwd->setGroup(2, neis);
}
