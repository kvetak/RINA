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

#include "DIF/RA/PDUFG/GRE/ClosRouting/GRE_Clos1R.h"

namespace GRE_Clos {

Register_Class(GRE_ClosR1);

// Called after initialize
void GRE_ClosR1::postPolicyInit() {
    //Set Forwarding policy
    fwd_ = dynamic_cast<Clos1 *>(fwd);

    fwd_->setZone(zone);
    fwd_->setIdentifier(ident);
    fwd_->setNumSpines(f);

    fwd->addPort(f + t - 1, nullptr);
    fwd->setGroup(1, vPortsIndex());
    fwd->setGroup(2, vPortsIndex());

    for (addr_t d = 0; d < t; d++) {
        aliveNeis.push_back(false);

        addr_t dst_addr = getAddr(zone, d + f);
        fwd->setNeighbour(dst_addr, d);

        elink_t dst_link = getELink(myaddr, dst_addr);
        neiLinks[dst_addr] = dst_link;
        linkNei[dst_link] = dst_addr;

        string dst_raw = getRaw(dst_addr);
        rt->registerLink(dst_link, Address(dst_raw.c_str(), dif.c_str()));

        if (FailureSimulation::instance) {
            FailureSimulation::instance->registerLink(to_string(dst_link), this);
        }
    }

    for (addr_t d = 0; d < s; d++) {
        aliveNeis.push_back(false);

        addr_t dst_addr = getAddr(ident, d);
        fwd->setNeighbour(dst_addr, d + t);

        elink_t dst_link = getELink(myaddr, dst_addr);
        neiLinks[dst_addr] = dst_link;
        linkNei[dst_link] = dst_addr;

        string dst_raw = getRaw(dst_addr);
        rt->registerLink(dst_link, Address(dst_raw.c_str(), dif.c_str()));

        if (FailureSimulation::instance) {
            FailureSimulation::instance->registerLink(to_string(dst_link), this);
        }
    }
}

index_t GRE_ClosR1::getNeiId(const addr_t & d) {
    index_t id = getIdentifier(d);
    addr_t z = getZone(d);

    if (z == zone) {
        return id - f;
    } else {
        return id + t;
    }
}

void GRE_ClosR1::resetNeiGroups() {
    vPortsIndex neis;
    for (addr_t d = 0; d < t; d++) {
        if (aliveNeis[d]) {
            neis.push_back(d);
        }
    }
    fwd->setGroup(1, neis);
    neis.clear();
    for (addr_t d = 0; d < s; d++) {
        if (aliveNeis[d + t]) {
            neis.push_back(d + t);
        }
    }
    fwd->setGroup(2, neis);
}

//Routing has processes a routing update
void GRE_ClosR1::routingUpdated() {
    nodesStatus st = rt->getProblems();
    Errors e;
    map<mask_t, exception_t> exceptions;
    vPortsIndex list;

    for (elink_t & l : st.othersFailures) {
        addr_s src = addr_s(getESrc(l));
        addr_s dst = addr_s(getEDst(l));

        if (src.Z < f) {
            // To Pod Error // Only same Spine set if spine alive
            if (src.Z != ident || !aliveNeis[src.Id + t]) {
                continue;
            }
            e.PF2S[dst.Z][dst.Id].insert(src.Id);
            e.FP2S[dst.Id][dst.Z].insert(src.Id);
            e.FS2P[src.Z][src.Id].insert(dst.Z);
        } else {
            // To Pod Error // Only same Spine set if spine alive
            if (dst.addr == myaddr) { // Don't record my own
                continue;
            }
            // In Pod Error
            e.PT2F[dst.Z][dst.Id].insert(src.Id);
            e.PF2T[src.Z][src.Id].insert(dst.Id);
            e.FP2T[src.Id][src.Z].insert(dst.Id);
        }
        //Spine to Pod errors in other spine-sets not considered
    }

    vector<bool> group1(aliveNeis.begin(), aliveNeis.begin() + t); // towards any ToR down
    vector<bool> group2(aliveNeis.begin() + t, aliveNeis.end()); // towards any Pod up

    // Check for unreachable ToRs in same Pod or distinct from group1
    auto & m2T = e.PF2T[zone][ident];
    if (!m2T.empty()) {
        int ok = t - m2T.size();
        if (ok > 0) {
            // Check if some ToR is connected only to me (err = f-1)
            for(auto t2F : e.PT2F[zone]) {
                if(t2F.second.size()+1 >= f) { // Not connected to others
                    group1[t2F.first - f] = false;
                }
            }
            bool superF = false;
            vector< vector<bool> > N(f, vector<bool>(t, true) ); // Reachable ToRs from neighbour fabrics
            for(addr_t i = 0; i < f; i++) {
                if(f == ident) { continue; }
                auto & f2T = e.PF2T[zone][i];
                if(f2T.empty()) {
                    superF = true; // Theres is at least one fabric neighbour connected to all ToRs
                    break;
                } else {
                    // Set all unreachable ToRs from neighbour
                    for(auto _t : f2T) {
                        N[i][_t-f] = false;
                    }
                }
            }

            if(!superF) {
                //Check if reachable from problematic ToR neis == groups1
                for(auto _t : m2T) {
                    auto & F = e.PT2F[zone][_t];
                    if(F.size() +1 >= f) {
                        //Disconnected ToR
                        /// Unreachable ToR
                        exceptions[mask_t(getAddr(zone, _t), 0)] =
                                exception_t();
                    } else {
                        //Check fabrics reachable through ToR
                        vector<bool>reachT(f, true);
                        reachT[ident] = false;
                        for(auto _f : F) {
                            reachT[_f] = false;
                        }
                        //Check ToRs reachables through some fabrics
                        vector<bool>reachF(t, false);
                        int k = 0;
                        for(addr_t i = 0; i < f; i++) {
                            if(reachT[i]) {
                                k = intersectBv(reachF, N[i], reachF);
                            }
                        }

                        if(k <= 0) {
                            //ToR unreachable (3 hops)
                            /// Unreachable ToR
                            exceptions[mask_t(getAddr(zone, _t), 0)] =
                                    exception_t();
                        } else if(! includedBv(group1, reachF)) {
                            // Tor reachable by some nodes of group 1 (reachF), not all
                            list.clear();
                            for (addr_t i = 0; i < t; i++) {
                                if (reachF[i]) {
                                    list.push_back(i);
                                }
                            }
                            exceptions[mask_t(getAddr(zone, _t), 0)] =
                                    exception_t(COMMON, 0, list);

                        } //Default group 1 rule works
                    }

                }
            } // Else, there is always a way to go to the "Super Fabric"
        } // Else disconnected down, nothing to do
    }

    //Check problems reaching other Pods
    //Remove spines disconnected to all other nodes from group 2
    for(auto s2F : e.FS2P[ident]) {
        if(s2F.second.size() + 1 >= p) {
            group2[s2F.first] = false;
        }
    }
    auto & m2S = e.FP2S[ident][zone];
    int m2Sc = m2S.size();

    set<addr_t> disP;
    //Search disconnected Fabrics
    for(auto p2T : e.FP2T[ident]) {
        if(p2T.first == zone) { continue; } // skip own pod
        if(p2T.second.size() >= t) {
            disP.insert(p2T.first);
        }
    }
    for(auto p2S : e.FP2S[ident]) {
        if(p2S.first == zone) { continue; } // skip own pod
        if(p2S.second.size() + m2Sc >= p) {
            disP.insert(p2S.first);
        }

        if(disP.find(p2S.first) == disP.end() ) {
            //Pod is not disconnected up nor down
            //Check good paths
            vector<bool> valids = group2;
            for(auto _s : p2S.second) {
                valids[_s] = false;
            }
            list.clear();

            for (addr_t i = 0; i < s; i++) {
                if (valids[i]) {
                    list.push_back(i+t);
                }
            }
            if(list.empty()) {
                ///Unreachable Pod p
                exceptions[mask_t(getAddr(p2S.first, 0), 8)] =
                        exception_t();
            } else {
                exceptions[mask_t(getAddr(p2S.first, 0), 8)] =
                        exception_t(COMMON, 0, list);
            }

        }
    }

    //Exceptions to disconnected Pods
    for(auto p : disP) {
        ///Unreachable Pod p
        exceptions[mask_t(getAddr(p, 0), 8)] =
                exception_t();
    }

    //Check problems reaching ToRs at other Pods
    // unreachable if Pod 2 hops reachable but fabric disconnected from ToR
    for(auto p2T : e.FP2T[ident]) {
        if(disP.find(p2T.first) == disP.end() ) {
            for(auto _t : p2T.second) {
                ///Unreachable ToR _t
                            exceptions[mask_t(getAddr(p2T.first, _t), 0)] =
                                    exception_t();
            }
        }
    }


    /// Replace group1
    list.clear();
    for (addr_t i = 0; i < t; i++) {
        if (group1[i]) {
            list.push_back(i);
        }
    }
    fwd->setGroup(1, list);

    /// Replace group2
    list.clear();
    for (addr_t i = 0; i < f; i++) {
        if (group2[i]) {
            list.push_back(i+t);
        }
    }
    fwd->setGroup(2, list);

    //Save Exceptions
    fwd->setExceptions(exceptions);
}

}
