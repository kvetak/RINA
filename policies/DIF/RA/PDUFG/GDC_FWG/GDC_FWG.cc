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

#include "GDC_FWG.h"

namespace GDC {
    using namespace std;

    Register_Class(FWG);

    // A new flow has been inserted/or removed
    void FWG::insertedFlow(const Address &addr, const QoSCube &qos, Port port){
        string dst = addr.getIpcAddress().getName();
        Addr dst_addr = Addr(dst);
        neighsAddr[dst] = dst_addr;

        if(!fwd->setNeigh(dst, port)){ return; }

        bool first = ports[dst_addr].empty();
        ports[dst_addr].insert(port);

        if(first){
            rt->insertNeighbour(addr, dst_addr);
            routingUpdated();
        }
    }
    void FWG::removedFlow(const Address &addr, const QoSCube& qos, Port port){
        string dst = addr.getIpcAddress().getName();
        Addr dst_addr = Addr(dst);
        neighsAddr[dst] = dst_addr;

        ports[dst_addr].erase(port);
        bool last = ports[dst_addr].empty();

        Port p = nullptr;
        if(!last) { p = *ports[dst_addr].begin(); }
        else { ports.erase(dst_addr); }

        if(!fwd->setNeigh(dst, p)){ return; }

        if(last){
            rt->removeNeighbour(addr, dst_addr);
            routingUpdated();
        }
    }

    void FWG::routingUpdated(){
        if(!updateRoutes) { return; }
        auto exceptions = rt->getExceptions();

        setAddr newExceptions;
        for(auto & e : exceptions) { newExceptions.insert(e.addr); }
        for(auto & e : currentExceptions) {
            if(newExceptions.find(e) == newExceptions.end()) {
                exceptions.push_back(RawException(e));
            }
        }
        currentExceptions = newExceptions;
        fwd->setExceptions(exceptions);

    }

    void FWG::handleMessage(cMessage *msg) {
        delete msg;
        updateRoutes = true;
        routingUpdated();
    }


    // Called after initialize
    void FWG::onPolicyInit(){
        //Set Forwarding policy
        fwd = check_and_cast<iface_FWD *>
            (getModuleByPath("^.^.relayAndMux.pduForwardingPolicy"));

        rt = check_and_cast<iface_RT *>
            (getModuleByPath("^.^.routingPolicy"));

        simtime_t startUpdating = par("startUpdating").doubleValue();
        if(startUpdating > simTime()) {
            updateRoutes = false;
            scheduleAt(startUpdating, new cMessage("start"));
        } else {  updateRoutes = true; }
    }

}
