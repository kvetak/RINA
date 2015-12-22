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

#include <SimpleDCGenerator/SimpleDCGenerator.h>
#include "APN.h"



namespace NSPSimpleDC {

Register_Class(SimpleDCGenerator);

using namespace std;
using namespace common_GraphCL;

// A new flow has been inserted/or removed
void SimpleDCGenerator::insertedFlow(const Address &addr, const QoSCube &qos, RMTPort * port){
    string dst = addr.getIpcAddress().getName();
    DCAddr dst_addr = DCAddr(dst);
    neighsAddr[dst] = dst_addr;

    bool first = false;

    switch(Im.type) {
        case 0 :
            if(dst_addr.type == 1 && dst_addr.a == Im.a) {
                first = up[dst_addr.b].empty();
                up[dst_addr.b].insert(port);
            } else {
                cerr << "Invalid neighbour " << dst << " at TOR ";
                cerr << Im.type << "." <<Im.a <<"." <<Im.b<<endl;
            }
            break;
        case 1 :
            if(dst_addr.type == 0 && dst_addr.a == Im.a) {
                first = down[dst_addr.b].empty();
                down[dst_addr.b].insert(port);
            } else if(dst_addr.type == 2 && dst_addr.a == Im.b) {
                first = up[dst_addr.b].empty();
                up[dst_addr.b].insert(port);
            } else {
                cerr << "Invalid neighbour " << dst << " at AG ";
                cerr << Im.type << "." <<Im.a <<"." <<Im.b<<endl;
            }
            break;
        case 2 :
            if(dst_addr.type == 1 && dst_addr.b == Im.a) {
                first = down[dst_addr.a].empty();
                down[dst_addr.a].insert(port);
            } else {
                cerr << "Invalid neighbour " << dst << " at Spine ";
                cerr << Im.type << "." <<Im.a <<"." <<Im.b<<endl;
            }
            break;
    }

    if(first){
        fwd->addNeigh(dst, port);
        rt->insertFlow(addr, dst, "hops", 1);
        routingUpdated();
    } else {
        fwd->replaceNeigh(dst, port);
    }
}
void SimpleDCGenerator::removedFlow(const Address &addr, const QoSCube& qos, RMTPort * port){
    std::string dst = addr.getIpcAddress().getName();
    DCAddr dst_addr = DCAddr(dst);
    neighsAddr[dst] = dst_addr;

    bool last = false;
    set<RMTPort*> * ks = nullptr;

    switch(Im.type) {
        case 0 :
            if(dst_addr.type == 1 && dst_addr.a == Im.a) {
                ks = &up[dst_addr.b];
                ks->erase(port);
                last = ks->empty();
            } else {
                cerr << "Invalid neighbour " << dst << endl;
            }
            break;
        case 1 :
            if(dst_addr.type == 0 && dst_addr.a == Im.a) {
                ks = &down[dst_addr.b];
                ks->erase(port);
                last = ks->empty();
            } if(dst_addr.type == 2 && dst_addr.a == Im.b) {
                ks = &up[dst_addr.b];
                ks->erase(port);
                last = ks->empty();
            } else {
                cerr << "Invalid neighbour " << dst << endl;
            }
            break;
        case 2 :
            if(dst_addr.type == 1 && dst_addr.b == Im.a) {
                ks = &down[dst_addr.a];
                ks->erase(port);
                last = ks->empty();
            } else {
                cerr << "Invalid neighbour " << dst << endl;
            }
            break;
    }

    if(last){
        rt->removeFlow(addr, dst, "hops");
        routingUpdated();
        fwd->removeNeigh(dst);
    } else if(ks!= nullptr){
        RMTPort * sport = *ks->begin();
        fwd->replaceNeigh(dst, sport);
    }
}

//Routing has processes a routing update
void SimpleDCGenerator::routingUpdated(){
    if(!updateRoutes) { return; }

    map<string, map<string, nhLMetric<mType>  > > changes = rt->getChanges();

    for(const auto & qosEntries : changes){
        for(const auto & entry : qosEntries.second){
            set<int> upP, downP;
            for(string nextHop : entry.second.nh){
                DCAddr n_addr = neighsAddr[nextHop];
                if(n_addr.type < 0) {
                    cerr << "Unknown neighbour "<< nextHop << endl;
                } else {
                    switch(Im.type) {
                        case 0 :
                            upP.insert(n_addr.b);
                            break;
                        case 1 :
                            if(n_addr.type == 0) {
                                downP.insert(n_addr.b);
                            } else {
                                upP.insert(n_addr.b);
                            }
                            break;
                        case 2 :
                            downP.insert(n_addr.a);
                            break;
                    }
                }
            }
            fwd->addDst(entry.first, upP, downP);
        }
    }
}

void SimpleDCGenerator::handleMessage(cMessage *msg) {
    delete msg;
    updateRoutes = true;

    map<string, map<string, nhLMetric<mType>  > > changes = rt->getAll();

    for(const auto & qosEntries : changes){
        for(const auto & entry : qosEntries.second){

            set<int> upP, downP;
            for(string nextHop : entry.second.nh){
                DCAddr n_addr = neighsAddr[nextHop];
                if(n_addr.type < 0) {
                    cerr << "Unknown neighbour "<< nextHop << endl;
                } else {
                    switch(Im.type) {
                        case 0 :
                            upP.insert(n_addr.b);
                            break;
                        case 1 :
                            if(n_addr.type == 0) {
                                downP.insert(n_addr.b);
                            } else {
                                upP.insert(n_addr.b);
                            }
                            break;
                        case 2 :
                            downP.insert(n_addr.a);
                            break;
                    }
                }
            }
            fwd->addDst(entry.first, upP, downP);
        }
    }
}

// Called after initialize
void SimpleDCGenerator::onPolicyInit(){
    //Set Forwarding policy
    fwd = check_and_cast<SimpleDCForwarding *>
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
