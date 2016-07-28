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

#include "GRE_Clos0R.h"

namespace GRE_Clos {

Register_Class(GRE_ClosR0);

// Called after initialize
void GRE_ClosR0::postPolicyInit(){
    //Set Forwarding policy
    fwd_ = dynamic_cast<Clos0 *>(fwd);
    fwd_->setSpines(f);
    fwd_->setZone(zone);

    fwd->addPort(f-1, nullptr);
    fwd->setGroup(1, vPortsIndex());
    fwd->setGroup(2, vPortsIndex());

    for(addr_t d = 0; d < f; d++) {
        aliveNeis.push_back(false);

        addr_t dst_addr = getAddr(zone, d);
        fwd->setNeighbour(dst_addr, d);

        elink_t dst_link = getELink(myaddr, dst_addr);
        neiLinks[dst_addr] = dst_link;
        linkNei[dst_link] = dst_addr;

        string dst_raw = getRaw(dst_addr);
        rt->registerLink(dst_link, Address(dst_raw.c_str(), dif.c_str()));

        if(FailureTest::instance) { FailureTest::instance->registerLink(to_string(dst_link), this); }
    }
}

index_t GRE_ClosR0::getNeiId(const addr_t & d) {
    return getIdentifier(d);
}


void GRE_ClosR0::resetNeiGroups() {
    vPortsIndex neis;
    for(addr_t d = 0; d < f; d++) {
        if(aliveNeis[d]) { neis.push_back(d); }
    }
    fwd->setGroup(1, neis);
    fwd->setGroup(2, neis);
}

//Routing has processes a routing update
void GRE_ClosR0::routingUpdated(){
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
