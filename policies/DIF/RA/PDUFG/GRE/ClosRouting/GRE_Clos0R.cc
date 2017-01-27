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

#include "DIF/RA/PDUFG/GRE/ClosRouting/GRE_Clos0R.h"

namespace GRE_Clos {

Register_Class(GRE_ClosR0);

// Called after initialize
void GRE_ClosR0::postPolicyInit() {
    //Set Forwarding policy
    fwd_ = dynamic_cast<Clos0 *>(fwd);
    fwd_->setSpines(f);
    fwd_->setZone(zone);

    fwd->addPort(f - 1, nullptr);
    fwd->setGroup(1, vPortsIndex());
    fwd->setGroup(2, vPortsIndex());

    for (addr_t d = 0; d < f; d++) {
        aliveNeis.push_back(false);

        addr_t dst_addr = getAddr(zone, d);
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
}

index_t GRE_ClosR0::getNeiId(const addr_t & d) {
    return getIdentifier(d);
}

void GRE_ClosR0::resetNeiGroups() {
    vPortsIndex neis;
    for (addr_t d = 0; d < f; d++) {
        if (aliveNeis[d]) {
            neis.push_back(d);
        }
    }
    fwd->setGroup(1, neis);
    fwd->setGroup(2, neis);
}

//Routing has processes a routing update
void GRE_ClosR0::routingUpdated() {
/*
    cout << hex;
    cout << "Routing updated " << (int) getZone(myaddr) << "."
            << (int) getIdentifier(myaddr) << endl;
*/

    nodesStatus st = rt->getProblems();
    Errors e;
    map<mask_t, exception_t> exceptions;

    for (elink_t & l : st.othersFailures) {
        addr_s src = addr_s(getESrc(l));
        addr_s dst = addr_s(getEDst(l));

        // Sort and Skip  shared Fab already unreachable
        if (src.Z < f) {
            // To Pod Error
            if (!aliveNeis[dst.Id]) {
                continue;
            }

            e.PF2S[dst.Z][dst.Id].insert(src.Id);
            e.FP2S[dst.Id][dst.Z].insert(src.Id);
            e.FS2P[src.Z][src.Id].insert(dst.Z);
        } else {
            // In Pod Error
            if (!aliveNeis[src.Id]) {
                continue;
            }

            e.PT2F[dst.Z][dst.Id].insert(src.Id);
            e.PF2T[src.Z][src.Id].insert(dst.Id);
            e.FP2T[src.Id][src.Z].insert(dst.Id);
        }
    }
    //Check in Pod errors
    vector<bool> group1 = aliveNeis;
    if (!e.PT2F[zone].empty()) {
        //Check connected down only to me -> Modify group 1
        for (auto f2t : e.PF2T[zone]) {
            if (f2t.second.size() + 1 >= t) {
                group1[f2t.first] = false;
            }
        }

        //Check ToRs not accessible through all group1
        for (auto t2f : e.PT2F[zone]) {
            vector<bool> valids = group1;
            bool changed = false;
            for (auto f : t2f.second) {
                if (group1[f]) {
                    valids[f] = false;
                    changed = true;
                }
            }

            if (changed) {
                vPortsIndex list;
                for (addr_t i = 0; i < f; i++) {
                    if (valids[i]) {
                        list.push_back(i);
                    }
                }
                /// Exception to zone.(t2f.first) = valids
                if (list.empty()) {
                    exceptions[mask_t(getAddr(zone, t2f.first), 0)] =
                            exception_t();
                } else {
                    exceptions[mask_t(getAddr(zone, t2f.first), 0)] =
                            exception_t(COMMON, 0, list);
                }
            }
        }
    }

    //Check to Pod errors
    vector<bool> group2 = aliveNeis;
    for (addr_t i = 0; i < s; i++) {
        if (!aliveNeis[i]) {
            continue;
        } // Already unreachable

        auto S = e.PF2S[zone][i];

        if (S.empty()) {
            //Case fabric without errors
            for (auto p2S : e.FP2S[i]) {
                if (p2S.second.size() >= s) {
                    // Pod unreachable from fabric i
                    e.F2P[i].insert(p2S.first);
                    e.P2F[p2S.first].insert(i);
                }
            }
        } else if (S.size() >= s) {
            //Case fabric disconnected up
            group2[i] = false; // Remove fabric from group 2
            continue;
        } else {
            //Case fabric with some errors
            unsigned int si = S.size();

            for (auto p2S : e.FP2S[i]) {
                if (p2S.first != zone && (si + p2S.second.size() >= s)) {
                    // Pod may be unreachable from fabric i, check in depth
                    set<addr_t> j = S;
                    j.insert(p2S.second.begin(), p2S.second.end()); // Join error set
                    if (j.size() >= s) {
                        // Pod unreachable from fabric i
                        e.F2P[i].insert(p2S.first);
                        e.P2F[p2S.first].insert(i);
                    }
                }
            }
        }

        //Check Pods with Fabrics down disconnected
        for (auto p2S : e.FP2T[i]) {
            if (p2S.first != zone && p2S.second.size() >= t) {
                // Pod with fabric i unreachable
                e.F2P[i].insert(p2S.first);
                e.P2F[p2S.first].insert(i);
            }
        }
    }

    //Check Pod exceptions
    for (auto p2F : e.P2F) {
        vector<bool> valids = group2;
        bool changed = false;
        for (auto f : p2F.second) {
            if (group2[f]) {
                valids[f] = false;
                changed = true;
            }
        }
        if (changed) {
            e.P[p2F.first] = valids;
            /// Exception to (p2F.first).* = valids
            vPortsIndex list;
            for (addr_t i = 0; i < f; i++) {
                if (valids[i]) {
                    list.push_back(i);
                }
            }
            if (list.empty()) {
                exceptions[mask_t(p2F.first, 8)] = exception_t();
            } else {
                exceptions[mask_t(p2F.first, 8)] = exception_t(COMMON, 0, list);
            }
        }
    }

    //Check ToR exceptions
    for (auto pT2F : e.PT2F) {
        if(pT2F.second.empty()) { continue; }
        if (pT2F.first == zone) {
//            cout << "  current = skip "<< endl;
//            continue;
        }
        vector<bool> validsPod;
        if(e.P.find(pT2F.first) != e.P.end()) {
            validsPod = e.P[pT2F.first];
        } else {
            validsPod = group2;
        }
        //Check if there are Tors with more invalid fabrics
        for (auto t2F : pT2F.second) {
            bool changed = false;
            vector<bool> valids = validsPod;

            for (auto f : t2F.second) {
                if (valids[f]) {
                    valids[f] = false;
                    changed = true;
                }
            }
            if (changed) {
                /// Exception to (pT2F.first).(t2F) = valids
                vPortsIndex list;
                for (addr_t i = 0; i < f; i++) {
                    if (valids[i]) {
                        list.push_back(i);
                    }
                }
                if (list.empty()) {
                    exceptions[mask_t(getAddr(pT2F.first, t2F.first), 0)] =
                            exception_t();
                } else {
                    exceptions[mask_t(getAddr(pT2F.first, t2F.first), 0)] =
                            exception_t(COMMON, 0, list);
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

    /// Replace group2list;
    list.clear();
    for (addr_t i = 0; i < f; i++) {
        if (group1[i]) {
            list.push_back(i);
        }
    }
    fwd->setGroup(2, list);

    //Save Exceptions
    fwd->setExceptions(exceptions);
/*
    cout << "Exceptions : "<<exceptions.size() << endl;

    cout << "  My Links :" << endl;
    for (addr_t d = 0; d < f; d++) {
        cout << "  -> " << zone << "." << d << " "
                << (aliveNeis[d] ? "LIVE" : "DOWN") << endl;
    }
    cout << "  Net DOWN links :" << endl;
    for (elink_t & l : st.ownFailures) {
        cout << "  - Own " << l << " - " << (getESrc(l)) << " <-> "
                << (getEDst(l)) << " || " << (int) getZone(getESrc(l)) << "."
                << (int) getIdentifier(getESrc(l)) << " <-> "
                << (int) getZone(getEDst(l)) << "."
                << (int) getIdentifier(getEDst(l)) << endl;
    }
    for (elink_t & l : st.othersFailures) {
        cout << "  - Others " << l << " - " << (getESrc(l)) << " <-> "
                << (getEDst(l)) << " || " << (int) getZone(getESrc(l)) << "."
                << (int) getIdentifier(getESrc(l)) << " <-> "
                << (int) getZone(getEDst(l)) << "."
                << (int) getIdentifier(getEDst(l)) << endl;
    }
    cout << dec;
    */
}

}
