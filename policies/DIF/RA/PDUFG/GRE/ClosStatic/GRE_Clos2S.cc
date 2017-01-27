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

#include "DIF/RA/PDUFG/GRE/ClosStatic/GRE_Clos2S.h"

namespace GRE_Clos {

Register_Class(GRE_ClosS2);

using namespace std;
using namespace common_GraphCL;

// A new flow has been inserted/or removed
void GRE_ClosS2::insertedFlow(const Address &addr, const QoSCube &qos, RMTPort * port){
    string dst = addr.getIpcAddress().getName();
    addr_t d = parseRawAddr(dst);
    index_t id = getZone(d)-s;

  //  cout << "At "<< rawAddr << " << "<< addr << " : "<< (int)id<<endl;

    fwd->addPort(id, port);

    neiPortsCurrent[d] = port;
    neiPorts[d].insert(port);
}
void GRE_ClosS2::removedFlow(const Address &addr, const QoSCube& qos, RMTPort * port){
    std::string dst = addr.getIpcAddress().getName();
    addr_t d = parseRawAddr(dst);
    index_t id = getZone(d)-s;

    neiPorts[d].erase(port);
    if(neiPorts[d].size() <= 0){
        fwd->removePort(id);
        fwd->unsetNeighbour(d);
        neiPortsCurrent[d] = nullptr;
    } else {
        if(neiPortsCurrent[d] == port) {
            port_t p = * neiPorts[d].begin();
            neiPortsCurrent[d] = p;
            fwd->addPort(id, port);
        }
    }
}

//Routing has processes a routing update
void GRE_ClosS2::routingUpdated(){}

// Called after initialize
void GRE_ClosS2::onPolicyInit(){
    p = par("pods").longValue();
    s = par("spineS").longValue();

    //Set Forwarding policy
    fwd = getRINAModule<Clos2 *>(this, 2, {MOD_RELAYANDMUX, MOD_POL_RMT_PDUFWD});

    rawAddr = getModuleByPath("^.^")->par("ipcAddress").stringValue();
    myaddr = parseRawAddr(rawAddr);
    zone = getZone(myaddr);

    fwd->setPadding(s);
    fwd->setNumPods(p);

    fwd->addPort(p-1, nullptr);
    for(addr_t d = 0; d < p; d++) {
        fwd->setNeighbour(getAddr(d+s, zone),d);
    }
}

}
