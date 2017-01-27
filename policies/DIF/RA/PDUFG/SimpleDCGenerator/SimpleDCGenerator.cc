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

#include "DIF/RA/PDUFG/SimpleDCGenerator/SimpleDCGenerator.h"
#include "Common/APN.h"



namespace NSPSimpleDC {

Register_Class(SimpleDCGenerator);

using namespace std;
using namespace common_GraphCL;

// A new flow has been inserted/or removed
void SimpleDCGenerator::insertedFlow(const Address &addr, const QoSCube &qos, RMTPort * port){
    string dst = addr.getIpcAddress().getName();
    DCAddr dst_addr = DCAddr(dst);
    neighsAddr[dst] = dst_addr;

    if(!fwd->setNeigh(dst, port)){ return; }

    bool first = ports[dst_addr].empty();
    ports[dst_addr].insert(port);

    if(first){
        rt->insertFlow(addr, dst, "", 1);
        routingUpdated();
    }
}
void SimpleDCGenerator::removedFlow(const Address &addr, const QoSCube& qos, RMTPort * port){
    std::string dst = addr.getIpcAddress().getName();
    DCAddr dst_addr = DCAddr(dst);
    neighsAddr[dst] = dst_addr;


    ports[dst_addr].erase(port);
    bool last = ports[dst_addr].empty();
    RMTPort * p = nullptr;
    if(!last) {
        p = *ports[dst_addr].begin();
    } else {
        ports.erase(dst_addr);
    }

    if(!fwd->setNeigh(dst, p)){ return; }

    if(last){
        rt->removeFlow(addr, dst, "");
        routingUpdated();
    }
}

//Routing has processes a routing update
void SimpleDCGenerator::routingUpdated(){
    if(!updateRoutes) { return; }

    map<string, map<string, nhLMetric<mType>  > > changes = rt->getChanges();

    for(const auto & qosEntries : changes){
        for(const auto & entry : qosEntries.second){
            set<DCAddr> links;
            for(string nextHop : entry.second.nh){
                DCAddr n_addr = neighsAddr[nextHop];
                if(n_addr.type < 0) {
                    cerr << "Unknown neighbour "<< nextHop << endl;
                } else {
                    links.insert(n_addr);
                }
            }
            fwd->setDst(entry.first, links);
        }
    }
}

void SimpleDCGenerator::handleMessage(cMessage *msg) {
    delete msg;
    updateRoutes = true;

    map<string, map<string, nhLMetric<mType>  > > changes = rt->getAll();

    for(const auto & qosEntries : changes){
        for(const auto & entry : qosEntries.second){

            set<DCAddr> links;
            for(string nextHop : entry.second.nh){
                DCAddr n_addr = neighsAddr[nextHop];
                if(n_addr.type < 0) {
                    cerr << "Unknown neighbour "<< nextHop << endl;
                } else {
                    links.insert(n_addr);
                }
            }
            fwd->setDst(entry.first, links);
        }
    }
}

// Called after initialize
void SimpleDCGenerator::onPolicyInit(){
    //Set Forwarding policy
    fwd = check_and_cast<iSimpleDCForwarding *>
        (getModuleByPath("^.^.relayAndMux.pduForwardingPolicy"));
    rt = check_and_cast<IntTSimpleRouting<mType> *>
        (getModuleByPath("^.^.routingPolicy"));

    difA = check_and_cast<DA *>(getModuleByPath("^.^.^.difAllocator.da"));

    mType infMetric = par("infinite");
    rt->setInfinite(infMetric);

    string myAddr = getModuleByPath("^.^")->par("ipcAddress").stringValue();
    Im = DCAddr(myAddr);
    fwd->setNodeInfo(myAddr);

    simtime_t startUpdating = par("startUpdating").doubleValue();
    if(startUpdating > simTime()) {
        updateRoutes = false;
        scheduleAt(startUpdating, new cMessage("start"));
    } else {
        updateRoutes = true;
    }
}

}
