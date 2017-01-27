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

#include "DIF/RA/PDUFG/GRE/ClosRouting/GRE_ClosR.h"

namespace GRE_Clos {

using namespace std;
using namespace common_GraphCL;

// A new flow has been inserted/or removed
void GRE_ClosR::insertedFlow(const Address &addr, const QoSCube &qos, RMTPort * port){
    string dst = addr.getIpcAddress().getName();
    addr_t d = parseRawAddr(dst);
    index_t id = getNeiId(d);

    fwd->addPort(id, port);
    bool changeStatus = (neiPorts[d] == nullptr);
    aliveNeis[id] = true;
    neiPorts[d] = port;
    if(changeStatus){
        resetNeiGroups();

        rt->onLink(neiLinks[d]);
        routingUpdated();
    }

}
void GRE_ClosR::removedFlow(const Address &addr, const QoSCube& qos, RMTPort * port){
    std::string dst = addr.getIpcAddress().getName();
    addr_t d = parseRawAddr(dst);
    index_t id = getNeiId(d);

    if(neiPorts[d] != port) { return; }
    fwd->removePort(id);

    aliveNeis[id] = false;
    resetNeiGroups();

    rt->offLink(neiLinks[d]);
    routingUpdated();
}


// Called after initialize
void GRE_ClosR::onPolicyInit(){
    f = par("fabrics").longValue();
    p = par("pods").longValue();
    s = par("spines").longValue();
    t = par("tors").longValue();

    //Set Forwarding policy
    fwd = getRINAModule<GREFWD *>(this, 2, {MOD_RELAYANDMUX, MOD_POL_RMT_PDUFWD});

    rawAddr = getModuleByPath("^.^")->par("ipcAddress").stringValue();
    dif = getModuleByPath("^.^")->par("difName").stringValue();
    myaddr = parseRawAddr(rawAddr);
    zone = getZone(myaddr);
    ident = getIdentifier(myaddr);

    rt = getRINAModule<eRouting *>(this, 2, {MOD_POL_ROUTING});
    postPolicyInit();
}

void GRE_ClosR::killLink(const string & link) {
    elink_t l = stoi(link);
    addr_t d = linkNei[l];
    index_t id = getNeiId(d);
    fwd->removePort(id);

    aliveNeis[id] = false;
    resetNeiGroups();

    rt->offLink(l);
    routingUpdated();
}

void GRE_ClosR::resurrectLink(const string &  link) {
    elink_t l = stoi(link);
    addr_t d = linkNei[l];
    index_t id = getNeiId(d);
    fwd->addPort(id, neiPorts[d]);

    aliveNeis[id] = true;
    resetNeiGroups();

    rt->onLink(l);
    routingUpdated();
}


string GRE_ClosR::getRaw(const addr_t & dst_addr) {
    stringstream sstream;
    sstream << hex << dst_addr;
    string dst_raw = sstream.str();
    while(dst_raw.size()<4) { dst_raw = "0"+dst_raw; }
    return dst_raw;
}

//Routing has processes a routing update
void GRE_ClosR::routingUpdated(){
    nodesStatus st = rt->getProblems();

    cout << hex;
    cout << "Routing updated "<< (myaddr) << endl;
    for(elink_t & l : st.ownFailures) {
        cout << "  - Own " << l
                << " - "<< (getESrc(l))<< " -> "<< (getEDst(l))
                << endl;
    }
    for(elink_t & l : st.othersFailures) {
        cout <<"  - Others " << l
                << " - "<< (getESrc(l))<< " -> "<< (getEDst(l))
                << endl;
    }
    cout << dec;


}
}
