#include "GDC_R0.h"

namespace GDC {
    using namespace std;

    Register_Class(R0);


    void R0::startMyNeis() {
        nSets = nPod+ nEdgeP;
        myNeisSize = nFab * nSets;
        myNeis = new nodeNeig[myNeisSize];

        ushort k = 0;
        for(ushort i = 0; i< nSets; i++) {
            for(ushort j = 0; j< nFab; j++) {
                auto & n = myNeis[k++];
                Addr n_addr = Addr(i+1, j+1);
                n.init(n_addr, Address(n_addr.toString().c_str(), myAddress.getDifName().getName().c_str()));

                linkInfo li(linkId(Im, n_addr), false, -1);
                linksStatus[li.link] = li;
            }
        }
    }

    ushort R0::getNeiId(const Addr & addr) {
        if(addr.a > 0 && addr.a <= nSets && addr.b > 0 && addr.b <= nFab){
            return (addr.a - 1) * nFab + addr.b - 1;
        }

        return myNeisSize;
    }

    vecRawException R0::getExceptions() {
        vecRawException ret;

        if(!preparseFailures()) { return ret; }
        if(fnd(R0Dead, Im)) { return ret; }

        Addr tNei(0,0);


        //Dead R2 nodes
        for(const Addr & d : R2Dead) { ret.push_back(RawException(d, vecAddr()) ); }

        //Check problems reaching groups
        const setAddr & myFails = R0Fails[Im];

        uchar2setuchar groupFail;
        for(const Addr & e: myFails) { groupFail[e.a].insert(e.b); }
        for(const Addr & e: R1DeadDown) { groupFail[e.a].insert(e.b); }

        //Exceptions for problematic groups
        for(const auto & gf : groupFail) {
            uchar g = gf.first;
            if(fnd(unreachGroup, g)) { continue; }
            if(gf.second.size() >= nFab) { // If group unreachable, skip here
                unreachGroup.insert(g);
                continue;
            }

            vbool vneis(nFab, true);
            for(const uchar c : gf.second) { vneis[c-1] = false; }

            vecAddr valids;
            tNei.a = g;
            for(uchar i = 0; i< nFab; i++) {
                if(!vneis[i]) { continue; }
                tNei.b = i+1;
                valids.push_back(tNei);
            }
            ret.push_back(RawException(Addr(g,0), valids) );
        }

        //Exceptions for unreachable groups
        for(const uchar & g : unreachGroup) {
            ret.push_back(RawException(Addr(g, 0), vecAddr()) );
        }

        //Exceptions to reach R2
        for(const auto & fail : R2Fails) {
            const Addr & dst = fail.first;
            if(fnd(unreachGroup, dst.a)) { continue; } // Dst R2 in an unreachable group
            if(fnd(R2Dead, dst)) { continue; } // Dst R2 already dead

            vbool myneis(nFab, true); // My R1 neis to group
            if(!fnd(groupFail,dst.a)) {//Some problems to reach group
                const setuchar & fs = groupFail[dst.a];
                for(const uchar & fl : fs) {myneis[fl-1] = false; }

            }

            vbool vneis = myneis; //Shared R1 neis
            vbool dstneis(nFab, true); //Dst R1 neis

            //Add invalid dst neis
            bool reqex = false;
            for(const Addr & f : fail.second) {
                if(vneis[f.b-1]) {
                    reqex = true;
                    vneis[f.b-1] = false;
                }
                dstneis[f.b-1] = false;
            }

            //add exception if distint of group
            if(reqex) {
                vecAddr valids;
                tNei.a = dst.a;
                for(uchar i = 0; i< nFab; i++) {
                    if(!vneis[i]) { continue; }
                    tNei.b = i+1;
                    valids.push_back(tNei);
                }

                if(valids.empty()){ //Check for subOptPaths R0->(R1->R2->R1)->R2
                    vneis = myneis;
                    for(uchar i = 0; i < nFab; i++) {
                        if(!myneis[i]) { continue; }
                        bool pathfound = false;
                        tNei.b = i+1;
                        const setAddr & neiFails = R1FailsDown[tNei];

                        for(uchar j = 0; !pathfound && j < nFab; j++) {
                            if(!dstneis[j]) { continue; }
                            tNei.b = j+1;
                            const setAddr & dstNeiFails = R1FailsDown[tNei];
                            if(!fullSet(neiFails, dstNeiFails, nFab)) { pathfound = true;}
                        }
                        if(pathfound) {
                            tNei.b = i+1;
                            valids.push_back(tNei);
                        }
                    }
                }
                ret.push_back(RawException(dst, valids) );
            }
        }


        return ret;
    }
}
