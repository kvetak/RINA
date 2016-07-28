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

#include "GRE_Clos1R.h"

namespace GRE_Clos {

Register_Class(GRE_ClosR1);

// Called after initialize
void GRE_ClosR1::postPolicyInit(){
    //Set Forwarding policy
    fwd_ = dynamic_cast<Clos1 *>(fwd);

    fwd_->setZone(zone);
    fwd_->setIdentifier(ident);
    fwd_->setNumSpines(f);

    fwd->addPort(f+t-1, nullptr);
    fwd->setGroup(1, vPortsIndex());
    fwd->setGroup(2, vPortsIndex());

    for(addr_t d = 0; d < t; d++) {
        aliveNeis.push_back(false);

        addr_t dst_addr = getAddr(zone, d+f);
        fwd->setNeighbour(dst_addr, d);

        elink_t dst_link = getELink(myaddr, dst_addr);
        neiLinks[dst_addr] = dst_link;
        linkNei[dst_link] = dst_addr;

        string dst_raw = getRaw(dst_addr);
        rt->registerLink(dst_link, Address(dst_raw.c_str(), dif.c_str()));

        if(FailureTest::instance) { FailureTest::instance->registerLink(to_string(dst_link), this); }
    }

    for(addr_t d = 0; d < s; d++) {
        aliveNeis.push_back(false);

        addr_t dst_addr = getAddr(ident, d);
        fwd->setNeighbour(dst_addr, d+t);

        elink_t dst_link = getELink(myaddr, dst_addr);
        neiLinks[dst_addr] = dst_link;
        linkNei[dst_link] = dst_addr;

        string dst_raw = getRaw(dst_addr);
        rt->registerLink(dst_link, Address(dst_raw.c_str(), dif.c_str()));

        if(FailureTest::instance) { FailureTest::instance->registerLink(to_string(dst_link), this); }
    }
}

index_t GRE_ClosR1::getNeiId(const addr_t & d) {
    index_t id = getIdentifier(d);
    addr_t z = getZone(d);

    if(z == zone) { return id - f; }
    else { return id + t; }
}


void GRE_ClosR1::resetNeiGroups() {
    vPortsIndex neis;
    for(addr_t d = 0; d < t; d++) {
        if(aliveNeis[d]) { neis.push_back(d); }
    }
    fwd->setGroup(1, neis);
    neis.clear();
    for(addr_t d = 0; d < s; d++) {
        if(aliveNeis[d+t]) { neis.push_back(d+t); }
    }
    fwd->setGroup(2, neis);
}

//Routing has processes a routing update
void GRE_ClosR1::routingUpdated(){
    cout << hex;
    cout << "Routing updated "<< (myaddr) << endl;
    nodesStatus st = rt->getProblems();
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
