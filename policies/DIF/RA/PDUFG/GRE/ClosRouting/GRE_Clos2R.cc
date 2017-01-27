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

#include "DIF/RA/PDUFG/GRE/ClosRouting/GRE_Clos2R.h"

namespace GRE_Clos {

Register_Class(GRE_ClosR2);

// Called after initialize
void GRE_ClosR2::postPolicyInit(){
    //Set Forwarding policy
    fwd_ = dynamic_cast<Clos2 *>(fwd);
    fwd_->setPadding(f);
    fwd_->setNumPods(p);

    fwd->addPort(p-1, nullptr);

    for(addr_t d = 0; d < p; d++) {
        aliveNeis.push_back(false);

        addr_t dst_addr = getAddr(d+f, zone);
        fwd->setNeighbour(dst_addr, d);

        elink_t dst_link = getELink(myaddr, dst_addr);
        neiLinks[dst_addr] = dst_link;
        linkNei[dst_link] = dst_addr;

        string dst_raw = getRaw(dst_addr);
        rt->registerLink(dst_link, Address(dst_raw.c_str(), dif.c_str()));

        if(FailureSimulation::instance) {
            FailureSimulation::instance->registerLink(to_string(dst_link), this);
        }
    }
}

index_t GRE_ClosR2::getNeiId(const addr_t & d) {
    return getZone(d)-f;
}


void GRE_ClosR2::resetNeiGroups() {}

//Routing has processes a routing update
void GRE_ClosR2::routingUpdated(){

    nodesStatus st = rt->getProblems();
    Errors e;
    map<mask_t, exception_t> exceptions;

    for (elink_t & l : st.othersFailures) {
        addr_s src = addr_s(getESrc(l));
        addr_s dst = addr_s(getEDst(l));

        // Sort and Skip  shared Fab already unreachable
        if (src.Z >= f) {
            // In Pod Error
            if (!aliveNeis[src.Z]) { // Pod already unreachable
                continue;
            }

            e.PT2F[dst.Z][dst.Id].insert(src.Id);
            e.PF2T[src.Z][src.Id].insert(dst.Id);
            e.FP2T[src.Id][src.Z].insert(dst.Id);
        }
        //Spine to Pod errors not considered, or already known (same node) or not useful
    }

    vector<bool> group1 = aliveNeis;
    for(auto p2T : e.FP2T[zone]) { // Check connected fabrics with down errors
        int fabOk = t-p2T.second.size();

        if(fabOk <= 0) {
            //Fabric node disconnected from all its ToRs. Unreachable Pod
            group1[p2T.first - f] = false;
        } else {
            //Fabrics reachable (in Pod) from connected fabric
            vector<bool> reachF(f, true);
            for(addr_t i = 0; i< f; i++) {
                if(i == zone) { continue; } // Same fabric
                auto & n2T = e.FP2T[i][p2T.first];

                if(n2T.empty()) { continue; } // Other fabric without problems
                if(p2T.second.size() + n2T.size() < t) { continue; } // Shared problems < num ToRs
                set<addr_t> shared = p2T.second;
                shared.insert(n2T.begin(), n2T.end());
                if(shared.size() >= t) { reachF[i] = false; } // No shared ToRs between fabrics
            }

            //Check problematic ToRs
            for(auto t : p2T.second) {
                auto & t2F =e.PT2F[p2T.first][t];
                if(t2F.size() >= f) {
                    // ToR disconnected from all nodes
                    /// Unreachable ToR
                        exceptions[mask_t(getAddr(p2T.first, t), 0)] =
                                exception_t();
                } else {
                    // Fabrics connected to unreachable ToR
                    vector<bool> reachT(f, true);
                    for(auto f : t2F) {
                        reachT[f] = false;
                    }
                    bool reachable = false;
                    for(addr_t i = 0; i< f; i++) {
                        if(reachF[i] && reachT[i]) {
                            reachable = true;
                        }
                    }
                    if(!reachable) {
                        /// Unreachable ToR
                        exceptions[mask_t(getAddr(p2T.first, t), 0)] =
                                exception_t();
                    }
                }
            }
        }
    }

    /// Replace group1
    vPortsIndex list;
    for (addr_t i = 0; i < f; i++) {
        if (group1[i]) {
            list.push_back(i);
        }
    }
    fwd->setGroup(1, list);

    //Save Exceptions
    fwd->setExceptions(exceptions);
/*
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
    */
}


}
