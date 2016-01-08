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

#include <VoidDCGenerator/VoidDCGenerator.h>
#include "APN.h"



namespace NSPSimpleDC {

Register_Class(VoidDCGenerator);

using namespace std;

// A new flow has been inserted/or removed
void VoidDCGenerator::insertedFlow(const Address &addr, const QoSCube &qos, RMTPort * port){
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
        rt->insertNeighbour(addr, dst_addr);

        routingUpdated();
    } else {
        fwd->removeNeigh(dst_addr);
    }
}
void VoidDCGenerator::removedFlow(const Address &addr, const QoSCube& qos, RMTPort * port){
    std::string dst = addr.getIpcAddress().getName();
    DCAddr dst_addr = DCAddr(dst);
    neighsAddr[dst] = dst_addr;
/*
    cout << "At " << Im.type <<"."<<Im.a << "." << Im.b
            << " removed flow to "<< dst_addr.type <<"."<<dst_addr.a << "." << dst_addr.b <<endl;
*/
    bool last = false;
    set<RMTPort*> * ks = nullptr;

    switch(Im.type) {
        case 0 :
            if(dst_addr.type == 1 && dst_addr.a == Im.a) {
                ks = &up[dst_addr.b];
                ks->erase(port);
                last = ks->empty();
            } else {
                cerr << "Invalid neighbour " << dst <<" for TOR"
                        << Im.type <<"." << Im.a << "." << Im.b << endl;
            }
            break;
        case 1 :
            if(dst_addr.type == 0 && dst_addr.a == Im.a) {
                ks = &down[dst_addr.b];
                ks->erase(port);
                last = ks->empty();
            } else if(dst_addr.type == 2 && dst_addr.a == Im.b) {
                ks = &up[dst_addr.b];
                ks->erase(port);
                last = ks->empty();
            } else {
                cerr << "Invalid neighbour "
                        << dst
                        << " for AG "
                        << Im.type <<"." << Im.a << "." << Im.b << endl;
            }
            break;
        case 2 :
            if(dst_addr.type == 1 && dst_addr.b == Im.a) {
                ks = &down[dst_addr.a];
                ks->erase(port);
                last = ks->empty();
            } else {
                cerr << "Invalid neighbour " << dst << " for Spine"
                        << Im.type <<"." << Im.a << "." << Im.b << endl;
            }
            break;
    }

    if(last){
        rt->removeNeighbour(addr, dst_addr);
        routingUpdated();
        fwd->removeNeigh(dst);
    } else if(ks!= nullptr){
        RMTPort * sport = *ks->begin();
        fwd->replaceNeigh(dst, sport);
    }
}

//Routing has processes a routing update
void VoidDCGenerator::routingUpdated(){
    if(!updateRoutes) { return; }
    auto entries = rt->getChanges();

    for(auto & e : entries) {
        set<int> upP, downP;
        for(auto n_addr : e.next) {
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

        fwd->addDst(e.dst, upP, downP);
    }

}

void VoidDCGenerator::handleMessage(cMessage *msg) {
    delete msg;
    updateRoutes = true;
    routingUpdated();
}


// Called after initialize
void VoidDCGenerator::onPolicyInit(){
    //Set Forwarding policy
    fwd = check_and_cast<SimpleDCForwarding *>
        (getModuleByPath("^.^.relayAndMux.pduForwardingPolicy"));
    rt = check_and_cast<IntDCRouting *>
        (getModuleByPath("^.^.routingPolicy"));

    difA = check_and_cast<DA *>(getModuleByPath("^.^.^.difAllocator.da"));

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
