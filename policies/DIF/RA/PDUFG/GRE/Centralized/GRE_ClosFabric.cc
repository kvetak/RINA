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

#include "DIF/RA/PDUFG/GRE/Centralized/GRE_ClosFabric.h"

Register_Class(GRE_ClosFabric);

// A new flow has been inserted/or removed
void GRE_ClosFabric::insertedFlow(const Address &addr, const QoSCube &qos,
        RMTPort * port) {
    string dst = addr.getIpcAddress().getName();
    addr_t a = parseRawAddr(dst);
    addr_t a_z = getZone(a);
    addr_t a_i = getIdentifier(a);
    addr_t index = (a_z == zone) ? (a_i - f) : (a_i + t);

    //Check we expect the link
    if (neiLinks[a] == 0) {
        error("This should never happen!!!!");
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
}
void GRE_ClosFabric::removedFlow(const Address &addr, const QoSCube& qos,
        RMTPort * port) {
    string dst = addr.getIpcAddress().getName();
    addr_t a = parseRawAddr(dst);
    addr_t a_z = getZone(a);
    addr_t a_i = getIdentifier(a);
    addr_t index = (a_z == zone) ? (a_i - f) : (a_i + t);

    //Check we expect the link
    if (neiLinks[a] == 0) {
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

void GRE_ClosFabric::killLink(const string & link) {
    elink_t l = stoi(link);
    addr_t a = linkNei[l];
    addr_t a_z = getZone(a);
    addr_t a_i = getIdentifier(a);
    addr_t index = (a_z == zone) ? (a_i - f) : (a_i + t);

    //Do nothing if port is not set or already down
    if (neiPorts[a] == nullptr || !aliveNeis[index]) {
        return;
    }

    fwd->removePort(index);
    aliveNeis[index] = false;
    resetNeiGroups();

    rt->offFlow(a);
    routingUpdated();
}

void GRE_ClosFabric::resurrectLink(const string & link) {
    elink_t l = stoi(link);
    addr_t a = linkNei[l];
    addr_t a_z = getZone(a);
    addr_t a_i = getIdentifier(a);
    addr_t index = (a_z == zone) ? (a_i - f) : (a_i + t);

    //Do nothing if port is not set or already down
    if (neiPorts[a] == nullptr || !aliveNeis[index]) {
        return;
    }

    aliveNeis[index] = false;
    fwd->addPort(index, neiPorts[a]);
    resetNeiGroups();

    rt->offFlow(a);
}

//Routing has processes a routing update
void GRE_ClosFabric::routingUpdated() {

    vPortsIndex list;

    //Update entries to zone managers
    if (rt->r_stat & R_INZONE_CHANGES) {
        addr_t def_man = 0;

        in_exceptions.clear();

        for (auto & e : rt->inzone.neiState) {
            list.clear();

            if (e.second.m1 < 16) {
                for (auto & i : e.second.op1) {
                    addr_t index = i - f;
                    if (aliveNeis[index]) {
                        list.push_back(index);
                    }
                }
                if (list.empty() && e.second.m2 < 16) {
                    for (auto & i : e.second.op2) {
                        addr_t index = i - f;
                        if (aliveNeis[index]) {
                            list.push_back(index);
                        }
                    }
                }
            }

            if (list.empty()) {
                endSimulation();
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
            if (e.valid.empty()) {
                in_exceptions[mask_t(e.a, e.m)] = exception_t();
            } else {
                list.clear();
                for (auto & i : e.valid) {
                    list.push_back(i);
                }
                in_exceptions[mask_t(e.a, e.m)] = exception_t(COMMON, 0, list);
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
void GRE_ClosFabric::onPolicyInit() {
    rt = getRINAModule<RoutingClient *>(this, 2, { MOD_POL_ROUTING });
    fwd = getRINAModule<Clos1 *>(this, 2,
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
    fwd->setIdentifier(ident);
    fwd->setNumSpines(f);

    fwd->addPort(f + t - 1, nullptr);
    fwd->setGroup(1, vPortsIndex());
    fwd->setGroup(2, vPortsIndex());

    aliveNeis = vector<bool>(t + s, false);
    r_v1 = vector<bool>(t, true);
    r_v2 = vector<bool>(s, true);

    for (addr_t d = 0; d < t; d++) {
        setNeiDown(d, getAddr(zone, d + f));
    }

    for (addr_t d = 0; d < s; d++) {
        setNeiUp(d, getAddr(ident, d));
    }
}

void GRE_ClosFabric::setNeiDown(addr_t d, addr_t dst_addr) {
    elink_t dst_link = getELink(myaddr, dst_addr);
    Address dstAddr(getRawAddr_t(dst_addr).c_str(), dif.c_str());

    neiLinks[dst_addr] = dst_link;
    linkNei[dst_link] = dst_addr;
    neiAddr[dst_addr] = dstAddr;

    fwd->setNeighbour(dst_addr, d);
    rt->addNei(dst_addr, dstAddr, true, dst_link);

    if (FailureSimulation::instance) {
        FailureSimulation::instance->registerLink(to_string(dst_link), this);
    }
}

void GRE_ClosFabric::setNeiUp(addr_t d, addr_t dst_addr) {
    elink_t dst_link = getELink(myaddr, dst_addr);
    Address dstAddr(getRawAddr_t(dst_addr).c_str(), dif.c_str());

    neiLinks[dst_addr] = dst_link;
    linkNei[dst_link] = dst_addr;
    neiAddr[dst_addr] = dstAddr;

    fwd->setNeighbour(dst_addr, d + t);
    rt->addNei(dst_addr, dstAddr, false, dst_link);

    if (FailureSimulation::instance) {
        FailureSimulation::instance->registerLink(to_string(dst_link), this);
    }
}

void GRE_ClosFabric::resetNeiGroups() {
    v1 = r_v1;
    v2 = r_v2;
    for (addr_t d = 0; d < t; d++) {
        if (!aliveNeis[d]) {
            v1[d] = false;
        }
    }

    for (addr_t d = 0; d < s; d++) {
        if (!aliveNeis[d + t]) {
            v2[d] = false;
        }
    }

    vPortsIndex neis;
    for (addr_t d = 0; d < t; d++) {
        if (v1[d]) {
            neis.push_back(d);
        }
    }
    /*
    if(simTime() > 99.0 && neis.empty()) {
        cout << "I'm " << getFullPath()<<endl;

        for (addr_t d = 0; d < t; d++) {
            cout << r_v1[d]<< " & " << aliveNeis[d] << " -> " << v1[d] << endl;
        }
    }
    */
    fwd->setGroup(1, neis);

    neis.clear();
    for (addr_t d = 0; d < s; d++) {
        if (v2[d]) {
            neis.push_back(d + t);
        }
    }
    fwd->setGroup(2, neis);
}
