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

#include "DIF/RA/PDUFG/GRE/Centralized/GRE_ManagerClos.h"

Register_Class(GRE_ManagerClos);

// A new flow has been inserted/or removed
void GRE_ManagerClos::insertedFlow(const Address &addr, const QoSCube &qos, RMTPort * port){
    string dst = addr.getIpcAddress().getName();
    addr_t a = parseRawAddr(dst);
    addr_t a_z = getZone(a);

    fwd->setGW(port);
    p = port;

    addr_t dstManA = getAddr(a_z, 255);

    Address dstMan(getRawAddr_t(dstManA).c_str(), addr.getDifName().getName().c_str());

    elink_t link = getELink(myaddr, a);
    rt->addNei(a, addr, zone == a_z, link);

    rt->onFlow(a);

    link2nei[link] = a;
/*
    if (FailureSimulation::instance) {
        FailureSimulation::instance->registerLink(to_string(link), this);
    }
*/
}
void GRE_ManagerClos::removedFlow(const Address &addr, const QoSCube& qos, RMTPort * port){
    string dst = addr.getIpcAddress().getName();
    addr_t a = parseRawAddr(dst);

    fwd->setGW(nullptr);
    p = nullptr;

    rt->offFlow(a);
}

void GRE_ManagerClos::killLink(const string & link) {
    elink_t l = stoi(link);
    addr_t a = link2nei[l];

    rt->offFlow(a);
    //fwd->setGW(nullptr);
}

void GRE_ManagerClos::resurrectLink(const string &  link) {
    elink_t l = stoi(link);
    addr_t a = link2nei[l];

    rt->onFlow(a);
    fwd->setGW(p);
}

//Routing has processes a routing update
void GRE_ManagerClos::routingUpdated(){

    // Learned about/ /*Forgot*/ other manager in the zone
    if(rt->r_stat & R_INZONE_CHANGES) {
        set<addr_t> temp = managers;

        for(auto & e : rt->inzone.neiState) {
            if(e.first == ident) { continue; }

            if(managers.find(e.first) == managers.end()){
                managers.insert(e.first);

                addr_t ManA = getAddr(zone, e.first);
                Address Man(getRawAddr_t(ManA).c_str(), dif.c_str());
                rt->addMasterNei(ManA, Man);
            }

            temp.erase(e.first);
        }

        for(auto & e : temp) {
            managers.erase(e);

            rt->removeMasterNei(getAddr(zone, e));
        }
    }
}

// Called after initialize
void GRE_ManagerClos::onPolicyInit(){
    rt = getRINAModule<RoutingManager *>(this, 2, {MOD_POL_ROUTING});
    fwd = getRINAModule<DefaultGW *>(this, 2, {MOD_RELAYANDMUX, MOD_POL_RMT_PDUFWD});

    rawAddr = getModuleByPath("^.^")->par("ipcAddress").stringValue();
    dif = getModuleByPath("^.^")->par("difName").stringValue();
    myaddr = parseRawAddr(rawAddr);
    zone = getZone(myaddr);
    ident = getIdentifier(myaddr);

    rt->setMyA(myaddr);
    rt->addAddr(ident);
    //addr_t ManA = getAddr(zone, 255);
    //rt->addAddr(ManA);

}
