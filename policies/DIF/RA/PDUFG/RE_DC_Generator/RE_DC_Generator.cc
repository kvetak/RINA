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

#include <RE_DC_Generator/RE_DC_Generator.h>
#include "APN.h"



namespace REFwdGDC {

Register_Class(RE_DC_Generator);

using namespace std;
using namespace REFwdDC;

// A new flow has been inserted/or removed
void RE_DC_Generator::insertedFlow(const Address &addr, const QoSCube &qos, RMTPort * port){
    string dst = addr.getIpcAddress().getName();
    DCAddr dst_addr = DCAddr(dst);
    neighsAddr[dst] = dst_addr;

    if(!fwd->setNeigh(dst, port)){ return; }

    bool first = ports[dst_addr].empty();
    ports[dst_addr].insert(port);

    if(first){
        rt->insertNeighbour(addr, dst_addr);
        routingUpdated();
    }
}
void RE_DC_Generator::removedFlow(const Address &addr, const QoSCube& qos, RMTPort * port){
    std::string dst = addr.getIpcAddress().getName();
    DCAddr dst_addr = DCAddr(dst);
    neighsAddr[dst] = dst_addr;

    ports[dst_addr].erase(port);
    bool last = ports[dst_addr].empty();

    RMTPort * p = nullptr;
    if(!last) { p = *ports[dst_addr].begin(); }
    else { ports.erase(dst_addr); }

    if(!fwd->setNeigh(dst, p)){ return; }

    if(last){
        rt->removeNeighbour(addr, dst_addr);
        routingUpdated();
    }
}

void RE_DC_Generator::routingUpdated(){
    if(!updateRoutes) { return; }
    auto exceptions = rt->getExceptions();

    set<DCAddr> newExceptions;
    for(auto & e : exceptions) {
        newExceptions.insert(e.addr);
    }
    for(auto & e : currentExceptions) {
        if(newExceptions.find(e) == newExceptions.end()) {
            exceptions.push_back(RawException(e));
        }
    }
    currentExceptions = newExceptions;
    fwd->setExceptions(exceptions);

}

void RE_DC_Generator::handleMessage(cMessage *msg) {
    delete msg;
    updateRoutes = true;
    routingUpdated();
}


// Called after initialize
void RE_DC_Generator::onPolicyInit(){
    //Set Forwarding policy
    fwd = check_and_cast<RuleExceptionsFWD *>
        (getModuleByPath("^.^.relayAndMux.pduForwardingPolicy"));

    string myAddr = getModuleByPath("^.^")->par("ipcAddress").stringValue();
    Im = DCAddr(myAddr);
    fwd->setNodeInfo(myAddr);

    rt = check_and_cast<RuleExceptionsRT *>
        (getModuleByPath("^.^.routingPolicy"));

    simtime_t startUpdating = par("startUpdating").doubleValue();
    if(startUpdating > simTime()) {
        updateRoutes = false;
        scheduleAt(startUpdating, new cMessage("start"));
    } else {  updateRoutes = true; }
}

}
