#include "RERt_ToR.h"

#include <map>

namespace RERtDC {
Register_Class(RERt_ToR);

using namespace std;
using namespace NSPSimpleDC;


    void RERt_ToR::startMyNeis() {
        myNeisSize = nFab;
        myNeis = new nodeNeig[myNeisSize];

        for(int i = 0; i< myNeisSize; i++) {
            auto & n = myNeis[i];
            DCAddr n_addr = DCAddr(TYPEID_Fabric, Im.a, i);
            n.init(n_addr, Address(n_addr.toString().c_str(), myAddress.getDifName().getName().c_str()));

            linkInfo li(linkId(Im, n_addr), false, -1);
            linksStatus[li.link] = li;
        }
    }

    portId RERt_ToR::getNeiId(DCAddr addr) {
        if(addr.type != TYPEID_Fabric) { return myNeisSize; }
        if(addr.a != Im.a) { return myNeisSize; }
        return addr.b;
    }

    RawExceptionsList RERt_ToR::getExceptions() {

        RawExceptionsList ret;

        //parse failures -> up/down failure list + search dead nodes
        if(!preparseFailures()) { return ret; }

        //Entries for dead ToRs
        for(auto & PodN : deadToR) {
            for(const auto & d : PodN.second) {
                ret.push_back(RawException(DCAddr(TYPEID_ToR, PodN.first, d), vAddr()));
            }
        }
        //Entries for dead Edges
        for(auto & EdgeN : deadEdge) {
            for(const auto & d : EdgeN.second) {
                ret.push_back(RawException(DCAddr (TYPEID_Edge, d, EdgeN.first), vAddr()));
            }
        }

        const setDCAddr & myP = problemsUp[Im];
        vbool myNei(nFab, true);
        for( auto & p : myP) { myNei[p.b] = false; }

        DCAddr tNei = DCAddr(TYPEID_Fabric, Im.a, 0);

        //ToR-ToR, same Pod (not dead)
        for(auto & errN : problemsUp) {
            const DCAddr & dst = errN.first;
            //Only ToRs of same Pod
            if(dst.type != TYPEID_ToR || dst.a != Im.a || dst.b == Im.b) { continue; }

            const setDCAddr & dstP = errN.second;
            //Problems with same fabrics, auto by rule
            if(myP == dstP) { continue; }

            //Compute dst neighbours
            vbool dstNei(nFab, true);
            for( auto & p : dstP) { dstNei[p.b] = false; }

            //Check shared fabrics
            vAddr valids;
            for(uchar i = 0; i < nFab; i++) {
                if(myNei[i] && dstNei[i]) {
                    tNei.b = i;
                    valids.push_back(tNei);
                }
            }

            //No opt paths available
            if(valids.empty()) {
                //Check sub-opt +2hops paths
                for(uchar i = 0; i < nFab; i++) {
                    if(!myNei[i]) { continue; }

                    //is valid nei
                    bool v = false;

                    //get nei problems
                    tNei.b = i;
                    const setDCAddr & myNeiProbs = problemsDown[tNei];

                    for(uchar j = 0; j < nFab && !v; j++) {
                        if(!dstNei[j]) { continue; }

                        //get dst nei problems
                        tNei.b = j;
                        const setDCAddr & dstNeiProbs = problemsDown[tNei];

                        //check if at least one common ToR
                        if(myNeiProbs.size() + dstNeiProbs.size() < nTor) { v = true; }
                        else {
                            setDCAddr joinProbs = myNeiProbs;
                            joinProbs.insert(dstNeiProbs.begin(), dstNeiProbs.end());
                            if(joinProbs.size() < nTor) { v = true; }
                        }
                    }

                    if(v) { tNei.b = i; valids.push_back(tNei); }
                }
            }

            //Create exception
            ret.push_back(RawException(dst, valids));
        }

        //Check Spine-set reachability
        vbool vNei = myNei; // Opt reachable spine-set
        vbool nonOptFab(nFab, false); // Disconnected from spine-set fabric

        bool defAllNeisValid = true;//All neis are valids to reach other pods/spine-sets

        //Search Spines that require exceptions
        for(uchar i = 0; i < nFab; i++) {
            bool connUp = deadPodFabric[Im.a].find(i)==deadPodFabric[Im.a].end();
            connUp &= deadSpineFabric[i].find(Im.a)==deadSpineFabric[i].end();
            if(!connUp) {
                vNei[i] = false;
                nonOptFab[i] = true;
                if(myNei[i]) { defAllNeisValid = false; }
            }

            if(vNei[i] || !connUp) { continue; } //Already opt reachable or disconnected fabric
            //For disconnected fabric, check later sub-opt +4 path via other Pod

            // Try to reach fabric with sub-opt +2 path / Within same Pod
            vAddr valids;
            //get dst problems
            tNei.b = i;
            const setDCAddr & dstFabPros = problemsDown[tNei];

            for(uchar j = 0; j < nFab; j++) {
                if(!myNei[j]) { continue; }
                //is valid nei
                bool v = false;
                //get nei problems
                tNei.b = j;
                const setDCAddr & myNeiProbs = problemsDown[tNei];
                //check if at least one common ToR
                if(myNeiProbs.size() + dstFabPros.size() < nTor) { v = true; }
                else {
                    setDCAddr joinProbs = myNeiProbs;
                    joinProbs.insert(dstFabPros.begin(), dstFabPros.end());
                    if(joinProbs.size() < nTor) { v = true; }
                }
                //insert if valid nei
                if(v) { valids.push_back(tNei); }
            }
            //Create exception
            ret.push_back(RawException(DCAddr(AGID_Spine, i, 0), valids));
        }

        //Store pods non-opt reachable via neis with opt path,
        //don't count pods non-opt reachable via non-nei fabric or disconnected from the spine
        uchar2setuchar nonOptNeiToPod;
        for(uchar i = 0; i < nFab; i++) {
            if(!vNei[i]) { continue; }

            //Get nei problems
            tNei.b = i;
            const setDCAddr & neiProbs = problemsUp[tNei];

            //Search Pods in same spine-set with problems
            for(auto & pNodes : problemsUp) {
                const DCAddr & dst = pNodes.first;
                const setDCAddr & dstProbs = pNodes.second;
                if(dst.type != TYPEID_Fabric || dst.a == Im.a || dst.b != i) { continue; }

                //Search opt paths between fabrics
                bool v = false;
                if(neiProbs.size() + dstProbs.size() < nSpine) { v =true; }
                else {
                    setDCAddr joinProblems = neiProbs;
                    joinProblems.insert(dstProbs.begin(), dstProbs.end());
                    if(joinProblems.size() < nSpine) { v = true; }
                }
                if(!v){ nonOptNeiToPod[dst.a].insert(i); }
            }
        }

        //Add exceptions to reach pods
        if(!defAllNeisValid) {
            //Default valid neighbours to reach other pods
            vecDCAddr defValids;
            for(uchar i = 0; i < nFab; i++) {
                if(vNei[i]) { tNei.b = i; defValids.push_back(tNei); }
            }

            for(uchar podId = 0; podId < nPod; podId++){
                if(nonOptNeiToPod.find(podId) == nonOptNeiToPod.end()) {
                    ret.push_back(RawException(DCAddr(AGID_Pod, podId, 0), defValids));
                } else {
                    const setuchar & nonValids = nonOptNeiToPod[podId];
                    vecDCAddr valids;
                    for(uchar i = 0; i < nFab; i++) {
                        if(vNei[i] && nonValids.find(i) == nonValids.end()) {
                            tNei.b = i; valids.push_back(tNei);
                            ret.push_back(RawException(DCAddr(AGID_Pod, podId, 0), valids));
                        }
                    }
                }
            }
        } else {
            for(auto & nonOptPod : nonOptNeiToPod) {
                const uchar & podId = nonOptPod.first;
                const setuchar & nonValids = nonOptPod.second;
                vecDCAddr valids;
                for(uchar i = 0; i < nFab; i++) {
                    if(vNei[i] && nonValids.find(i) == nonValids.end()) {
                        tNei.b = i; valids.push_back(tNei);
                        ret.push_back(RawException(DCAddr(AGID_Pod, podId, 0), valids));
                    }
                }
            }
        }

        //Try to reach spine-set of disconnected Fabrics with sub-opt +4 path / Via other Pod
        for(uchar i = 0; i < nFab; i++) {
            if(!nonOptFab[i]) { continue; }
            vAddr valids;

            //Check if any other nei is valid
            for(uchar j = 0; j < nFab; j++) {
                if(!myNei[j]) { continue; }
                if(deadSpineFabric[j].find(Im.a)!=deadSpineFabric[j].end()) {continue;}

                //is valid
                bool v = false;
                //Search distinct Pods
                for(uchar k = 0; !v && k< nPod; k++) {
                    //Check if path nei -> Pod k fabric is opt
                    if(nonOptNeiToPod.find(k) != nonOptNeiToPod.end()) {
                        auto & nonValidFabs = nonOptNeiToPod[k];
                        if(nonValidFabs.find(j) != nonValidFabs.end()) { continue; }
                    }

                    //Check for opt paths in Pod k between Fab j -> Fab i
                    const setDCAddr & dstINProblems = problemsDown[DCAddr(TYPEID_Fabric, k, j)];
                    const setDCAddr & dstOUTProblems = problemsDown[DCAddr(TYPEID_Fabric, k, i)];
                    if(dstINProblems.size() + dstOUTProblems.size() < nTor) { v =true; }
                    else {
                        setDCAddr joinProblems = dstINProblems;
                        joinProblems.insert(dstOUTProblems.begin(), dstOUTProblems.end());
                        if(joinProblems.size() < nTor) { v = true; }
                    }
                }

                if(v) { tNei.b = j; valids.push_back(tNei); }
            }

            //Create exception
            tNei.b = i;
            ret.push_back(RawException(DCAddr(AGID_Spine, i, 0), valids));
        }

        //ToR-ToR, distinct Pod
        for(auto & errN : problemsUp) {
            const DCAddr & dst = errN.first;
            //Only problematic ToRs of distinct Pod
            if(dst.type != TYPEID_ToR || dst.a == Im.a) { continue; }

            //get Tor Problems
            const setDCAddr & dstProbs = errN.second;

            //Get default neis to reach dst pod
            vbool defValids = vNei;
            //Problems to reach all the pod?
            if(nonOptNeiToPod.find(dst.a) != nonOptNeiToPod.end()) {
                const setuchar & nonValid = nonOptNeiToPod[dst.a];
                for(auto & nv : nonValid) { defValids[nv] = false; }
            }

            //Get neis to reach dst
            vbool dstValids(nFab, true);
            for(auto & nv : dstProbs) { dstValids[nv.b] = false; }

            //Skip exception if neis to reach pod = to reach dst
            if(defValids == dstValids) { continue; }

            //Add exception
            vAddr valids;
            for(uchar i = 0; i < nFab; i++) {
                if(dstValids[i]){ tNei.b = i; valids.push_back(tNei); }
            }
            ret.push_back(RawException(dst, valids));

        }
        clearParsedFailures();

        return ret;
    }
}
