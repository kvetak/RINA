#include "GDC_R2.h"

namespace GDC {
    using namespace std;

    Register_Class(R2);


    void R2::startMyNeis() {
        myNeisSize = nFab;
        myNeis = new nodeNeig[myNeisSize];

        for(ushort i = 0; i< nFab; i++) {
            auto & n = myNeis[i];
            Addr n_addr = Addr(Im.a, i+1);
            n.init(n_addr, Address(n_addr.toString().c_str(), myAddress.getDifName().getName().c_str()));

            linkInfo li(linkId(Im, n_addr), false, -1);
            linksStatus[li.link] = li;
        }
    }

    ushort R2::getNeiId(const Addr & addr) {
        if(addr.a == Im.a) {
            if(addr.b > 0 && addr.b <= nFab) {
                return addr.b -1;
            }
        }

        return myNeisSize;
    }

    vecRawException R2::getExceptions() {
        vecRawException ret;

        if(!preparseFailures()) { return ret; }
        if(fnd(R2Dead, Im)) { return ret; }

        //My neis
        vbool myNeis(nFab, true);

        Addr tNei(Im.a, 0);

        //Dead R2 nodes
        for(const Addr & d : R2Dead) { ret.push_back(RawException(d, vecAddr()) ); }

        //Problems within the group?
        if(fnd(groupProb, Im.a)) {
            ushort myTypeCount;
            if(Im.a <= nPod) { myTypeCount = nTor; }
            else { myTypeCount = nEdge; }

            //Parse myNeis array
            const setAddr & myFails = R2Fails[Im];
            for(const Addr & f : myFails) { myNeis[f.b-1] = false; }

            const uchar2setuchar & myGroupFails = R2GroupedFailures[Im.a];
            const setuchar & mypFails = R2GroupedFailures[Im.a][Im.b];

            //Problems at other R2 nodes
            for(const auto & fail : myGroupFails) {
                const uchar & f = fail.first;
                if(f == Im.b) { continue; } //I'm the failure
                if(mypFails == fail.second) { continue; } //Same errors
                if(fnd(R0Dead, Addr(Im.a, f))) { continue; } //Dead node

                //Parse dstNeis array
                vbool dstNeis(nFab, true);
                for(const uchar & fd : fail.second) { dstNeis[fd-1] = false; }

                vecAddr valids;
                if(!fullSet(mypFails, fail.second, nFab)) { //Some R1 in common
                    for(uchar i = 0; i < nFab; i++) {
                        if(myNeis[i] && dstNeis[i]) {
                            valids.push_back(Addr(Im.a, i+1));
                        }
                    }
                } else { //No R1 in common
                    for(uchar i = 0; i < nFab; i++) {
                        if(!myNeis[i]) { continue; }
                        bool foundSharedR0 = false;
                        tNei.b = i+1;
                        const setAddr & neiFails = R1FailsDown[tNei];
                        for(uchar j = 0; !foundSharedR0 && j < nFab; j++) {
                            if(!dstNeis[j]) { continue; }
                            tNei.b = j+1;
                            const setAddr & dstNeiFails = R1FailsDown[tNei];
                            foundSharedR0 = !fullSet(neiFails, dstNeiFails, myTypeCount);
                        }
                        if(foundSharedR0) {
                            tNei.b = i+1;
                            valids.push_back(tNei);
                        }
                    }
                }
                ret.push_back(RawException(Addr(Im.a, f), valids) );
            }
        }

        //Check valid R1 to reach distinct group
        vbool vNeis(nFab, false);
        uchar validNeis = 0;
        for(uchar i = 0; i < nFab; i++) {
            if(!myNeis[i]) { continue; }
            tNei.b = i+1;
            if(! fnd(R1DeadUp, tNei)) {
                validNeis++;
                vNeis[i] = true;
            }
        }

        if(validNeis <= 0) { //All R1 disconnected UP
            ret.push_back(RawException(Addr(0, 0), vecAddr()) );
            return ret;
        } else if(vNeis != myNeis){ //Some R1 disconnected UP
            vecAddr valids;
            for(uchar i = 0; i < nFab; i++) {
                if(!vNeis[i]) { continue; }
                tNei.b = i+1;
                valids.push_back(tNei);
            }
            ret.push_back(RawException(Addr(0, 0), valids) );
        }

        uchar2setuchar disconnGroup;
        uchar2setuchar disconnPath;
        map<uchar, uchar2setuchar>reachProblems;

        //Check for group problems
        for(uchar i = 0; i < nFab; i++) {
            if(!vNeis[i]) { continue; }

            tNei.b = i+1;
            if(!fnd(R1FailsUp, tNei)) { continue; } // Nei does not have problems

            const setAddr & neiFails = R1FailsUp[tNei];
            uchar2setuchar disconnPath;

            //Check if nei can reach failing R1
            for(const auto & fail : R1FailsUp) {
                const Addr & dst = fail.first;
                if(dst.a == Im.a || fnd(unreachGroup, dst.a)) { continue; } //Problem at same group or an unreachable one

                if(fnd(R1DeadDown, dst) // dst R1 already down dead
                        || fnd(R1DeadUp, dst)// dst R1 already up dead
                        || fullSet(neiFails,fail.second, nSpines)) { //nei and failing node don't share spines
                    disconnPath[dst.a].insert(dst.b);
                    if(fnd(groupProb, dst.a)) { //Store failing pair nei/dst, in case of problems within dst group
                        reachProblems[dst.a][i].insert(dst.b);
                    }
                }
            }

            //Check if nei can reach at least one R1 at groups with failing R1
            for(const auto & dp : disconnPath) {
                if(dp.second.size() >= nFab) { // Nei does not reach group
                    disconnGroup[dp.first].insert(i);
                }
            }
        }

        //Check if any nei can reach groups non-reachable via all neis
        for(const auto & dp : disconnGroup) {
            if(dp.second.size() < nFab) { // Some nei reach group
                vecAddr valids;
                for(uchar i = 0; i < nFab; i++) {
                    if(!vNeis[i]) { continue; }
                    if(!fnd(dp.second, i)) {
                        tNei.b = i+1;
                        valids.push_back(tNei);
                    }
                }
                ret.push_back(RawException(Addr(dp.first, 0), valids) );

            } else {
                unreachGroup.insert(dp.first);
            }
        }

        //Exceptions for unreachable groups
        for(const uchar & g : unreachGroup) {
            ret.push_back(RawException(Addr(g, 0), vecAddr()) );
        }

        //Exceptions for problems to reach R2 at distinct groups
        for(const uchar & g : groupProb) {
            //Check if group is unreachable all dst R1 already unreachable
            if(fnd(unreachGroup, g)) { continue; }
            //Check if there are no problems to reach the group, any nei R1 is valid to reach any dst R1
            if(!fnd(reachProblems, g)) { continue; }

            //Get failures to reach group
            uchar2setuchar & rProbs = reachProblems[g];

            //Parse current R1 neis to reach dst group
            vbool currentVNeis = vNeis;
            if(fnd(disconnGroup, g)) {
                const setuchar & gErr = disconnGroup[g];
                for(const uchar & fe : gErr) { currentVNeis[fe] = false; }
            }
            //Check failures at failing group
            const uchar2setuchar dstProbs = R2GroupedFailures[g];
            for(const auto & fail : dstProbs) {
                const uchar & f = fail.first;

                if(fnd(R2Dead, Addr(g, f) )) { continue; } // Dst R2 already dead


                vbool dstNeis(nFab, true);
                bool possibleEx = false;
                for(const uchar fd : fail.second) {
                    dstNeis[fd-1] = false;
                    if(!fnd(R1DeadDown, Addr(g, fd)) // error R1 not down dead
                        && !fnd(R1DeadUp, Addr(g, fd))) { // error R1 not up dead
                        possibleEx = true;
                    }
                }

                if(!possibleEx) { continue; } //All failures already considered

                bool reqex = false;
                vbool neiReach = currentVNeis;
                for(uchar i = 0; i < nFab; i++) {
                    if(!neiReach[i]) { continue; } // R1 not valid to reach dst group
                    if(!fnd(rProbs,i)) { continue; } // R1 has no problems to reach dst group

                    //Parse unerachable dst R1 from nei R1
                    const setuchar & neiRProbs = rProbs[i];
                    vbool neiReaches(nFab, true);
                    for(const uchar & p : neiRProbs) { neiReaches[p-1] = false; }


                    bool reachsome= false;
                    //Check if nei R1 reach some valid dst neis R1
                    for(uchar j = 0; j < nFab; j++) {
                        if(neiReaches[j] && dstNeis[j]) { reachsome = true; }
                    }
                    //If nei R1 cannot reach any dst nei R1, mark as invalid to reach dst
                    if(!reachsome) {
                        neiReach[i] = false;
                        reqex = true;
                    }
                }

                if(reqex) {
                    vecAddr valids;
                    for(uchar i = 0; i < nFab; i++) {
                        if(!neiReach[i]) { continue; }
                        tNei.b = i+1;
                        valids.push_back(tNei);
                    }
                    ret.push_back(RawException(Addr(g, f), valids) );
                }
            }

        }


        return ret;
    }
}
