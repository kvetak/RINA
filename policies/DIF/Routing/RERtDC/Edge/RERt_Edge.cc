#include "RERt_Edge.h"

namespace RERtDC {
Register_Class(RERt_Edge);

using namespace std;
using namespace NSPSimpleDC;


    void RERt_Edge::startMyNeis() {
        myNeisSize = nSpine;
        myNeis = new nodeNeig[myNeisSize];

        for(int i = 0; i< myNeisSize; i++) {
            auto & n = myNeis[i];
            DCAddr n_addr = DCAddr(TYPEID_Spine, Im.b, i);
            n.init(n_addr, Address(n_addr.toString().c_str(), myAddress.getDifName().getName().c_str()));


            linkInfo li(linkId(Im, n_addr), false, -1);
            linksStatus[li.link] = li;
        }
    }

    portId RERt_Edge::getNeiId(DCAddr addr) {
        if(addr.type != TYPEID_Spine) { return myNeisSize; }
        if(addr.a != Im.b) { return myNeisSize; }
        return addr.b;
    }

    RawExceptionsList RERt_Edge::getExceptions() {
        RawExceptionsList ret;

        //parse failures -> up/down failure list + search dead nodes
        if(!preparseFailures()) { return ret; }


        const setDCAddr & myP = problemsDown[Im];
        vbool myNei(nSpine, true);
        for( auto & p : myP) { myNei[p.b] = false;}

        uchar myNeiCount = 0;
        for(uchar i = 0; i < nSpine; i++) {
            if(myNei[i]){ myNeiCount++; }
        }

        if(myNeiCount <= 0) { return ret; } // The node is disconnected


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

        DCAddr tNei = DCAddr(TYPEID_Spine, Im.b, 0);

        //Edge-Edge, same Spine-set
        for(auto & errN : problemsDown) {
            const DCAddr & dst = errN.first;
            //Only Edges of same Spine-set
            if(dst.type != TYPEID_Edge || dst.a == Im.a || dst.b != Im.b) { continue; }

            const setDCAddr & dstP = errN.second;
            //Problems with same spines, auto by rule
            if(myP == dstP) { continue; }

            //Compute dst neighbours
            vbool dstNei(nSpine, true);
            for( auto & p : dstP) { dstNei[p.b] = false; }

            //Check shared spines, only valid paths
            vAddr valids;
            for(uchar i = 0; i < nSpine; i++) {
                if(myNei[i] && dstNei[i]) {
                    tNei.b = i;
                    valids.push_back(tNei);
                }
            }
            //Create exception
            ret.push_back(RawException(dst, valids));
        }

        vbool vNei = myNei; //Spines with problems (down)
        setuchar nonOpPods;
        uchar2setuchar podProblems; //Invalid neis for opt-path to pods

        //Check for Fabrics "Down" disconnected - no ToR reachable
        for(auto dl : deadPodFabric){
            if(dl.second.find(Im.b) != dl.second.end()) { nonOpPods.insert(dl.first); }
        }
        //Check for Fabrics "UP" disconnected - no Spine reachable
        if(deadSpineFabric.find(Im.b) != deadSpineFabric.end()) {
            const setuchar & dsf = deadSpineFabric[Im.b];
            for(const uchar & f : dsf) { nonOpPods.insert(f); }
        }

        //Check neis dead-down
        vbool liveNeis = myNei;
        bool allNeisLive = true;
        for(auto dNei : deadSpineDown[Im.b]) {
            if(!myNei[dNei]) { continue; }
            for(uchar p = 0; p< nPod; p++) {
                podProblems[p].insert(dNei);
                liveNeis[dNei] = false;
                allNeisLive = false;
            }
        }

        //Check pods not reachable via all (live) spines
        for(auto & errN : problemsDown) {
            const DCAddr & dst = errN.first;
            //Only Edges of same Spine-set
            if(dst.type != TYPEID_Spine || dst.a != Im.b) { continue; }
            //Already disconnected nei
            if(!liveNeis[dst.b]) { continue; }

            vNei[dst.b] = false;
            for(auto & p : errN.second) { podProblems[p.a].insert(dst.b); }
        }

        //Exceptions for only some pods or all pods if some spines are down-dead
        if(allNeisLive) {
            //Exceptions to reach pods via opt-paths
            for(auto & poddErr : podProblems) {
                const uchar & p = poddErr.first;
                //Already non-valid for opt-paths ("Down" disconnected)
                if(nonOpPods.find(p) != nonOpPods.end()) { continue; }
                //Disconnected from all neis?
                if(myNeiCount <= poddErr.second.size()) {
                    nonOpPods.insert(p);
                    continue;
                }

                //Get valid neis
                vbool dstNeis = myNei;
                for(auto & err : poddErr.second) { dstNeis[err] = false; }

                //Create exception
                vAddr valids;
                for(uchar i = 0; i < nSpine; i++) {
                    if(dstNeis[i]) {
                        tNei.b = i;
                        valids.push_back(tNei);
                    }
                }
                DCAddr dst = DCAddr(AGID_Pod, p, 0);
                ret.push_back(RawException(dst, valids));
            }
        } else {
            uchar myLiveNeiCount = 0;
            vAddr defvalids;
            for(uchar i = 0; i < nSpine; i++) {
                if(liveNeis[i]) {
                    tNei.b = i;
                    defvalids.push_back(tNei);
                    myLiveNeiCount++;
                }
            }
            for(uchar p = 0; p < nPod; p++) {
                if(nonOpPods.find(p) != nonOpPods.end()) { continue; }

                if(podProblems.find(p) != podProblems.end()) {
                    //Already non-valid for opt-paths ("Down" disconnected)
                    if(nonOpPods.find(p) != nonOpPods.end()) { continue; }

                    const setuchar & poddErr = podProblems[p];
                    //Disconnected from all live neis?
                    if(myLiveNeiCount <= poddErr.size()) {
                        nonOpPods.insert(p);
                        continue;
                    }

                    //Get valid neis
                    vbool dstNeis = liveNeis;
                    for(auto & err : poddErr) { dstNeis[err] = false; }

                    //Create exception
                    vAddr valids;
                    for(uchar i = 0; i < nSpine; i++) {
                        if(dstNeis[i]) {
                            tNei.b = i;
                            valids.push_back(tNei);
                        }
                    }
                    DCAddr dst = DCAddr(AGID_Pod, p, 0);
                    ret.push_back(RawException(dst, valids));
                } else {
                    DCAddr dst = DCAddr(AGID_Pod, p, 0);
                    ret.push_back(RawException(dst, defvalids));
                }
            }
        }


        //Reach other Spine-sets
        for(uchar f = 0; f < nFab; f++) {
            if(f == Im.b) { continue; }

            setuchar remSpines;
            for(uchar s =0 ; s < nSpine; s++) { if(liveNeis[s]) { remSpines.insert(s); } }

            for(uchar p = 0;!remSpines.empty() && p < nSpine; p++) {
                //Pod p is opt-reachable?
                if(nonOpPods.find(p) != nonOpPods.end()) { continue; }
                //In/Out Fabrics at Pod p are connected DOWN
                if(deadPodFabric.find(p) != deadPodFabric.end()) {
                    auto & dpf = deadPodFabric[p];
                    if(dpf.find(f) != dpf.end() || dpf.find(Im.b) != dpf.end()) { continue; }
                }
                //Out Fabric at Pod p is connected UP
                if(deadSpineFabric.find(f) != deadSpineFabric.end()) {
                    auto & dsf = deadSpineFabric[f];
                    if(dsf.find(p) != dsf.end()) { continue; }
                }

                bool reach = false;
                //In and Out fabrics have errors
                DCAddr t(TYPEID_Fabric, p, Im.b);
                if(problemsDown.find(t) == problemsDown.end()) { reach = true; }
                t.b = f;
                if(problemsDown.find(t) == problemsDown.end()) { reach = true; }

                //In and Out fabrics share a ToR?
                const setDCAddr & fProbs = problemsDown[t];
                t.b = Im.b;
                const setDCAddr & bProbs = problemsDown[t];
                if(fProbs.size() + bProbs.size() < nTor) { reach = true; }
                else {
                    setDCAddr jProbs = fProbs;
                    jProbs.insert(bProbs.begin(), bProbs.end());
                    if(jProbs.size() < nTor) { reach = true; }
                }

                if(!reach) { continue; }

                //remaining non-opt spines \= opt spines to reach pod p
                if(podProblems.find(p) != podProblems.end()) {
                    const setuchar & pNonOpt = podProblems[p];
                    setucharIt it = remSpines.begin();
                    //Remove from remSpines those that opt-reach pod p
                    while(it != remSpines.end()) {
                        if(pNonOpt.find(*it) == pNonOpt.end()) { it = remSpines.erase(it); }
                        else { it++; }
                    }
                } else { remSpines.clear() ; }
            }

            if(allNeisLive){
                //Create exception if some neis are not valid
                if(!remSpines.empty()) {
                    vbool vNeis = myNei;
                    for(auto & n : remSpines) { vNeis[n] = false; }

                    //Create exception
                    vAddr valids;
                    for(uchar i = 0; i < nSpine; i++) {
                        if(vNeis[i]) {
                            tNei.b = i;
                            valids.push_back(tNei);
                        }
                    }
                    DCAddr dst = DCAddr(AGID_Spine, f, 0);
                    ret.push_back(RawException(dst, valids));
                }
            } else {
                uchar myLiveNeiCount = 0;
                vAddr defvalids;
                for(uchar i = 0; i < nSpine; i++) {
                    if(liveNeis[i]) {
                        tNei.b = i;
                        defvalids.push_back(tNei);
                        myLiveNeiCount++;
                    }
                }
                //Create exception if some neis are not valid
                if(!remSpines.empty()) {
                    vbool vNeis = liveNeis;
                    for(auto & n : remSpines) { vNeis[n] = false; }

                    //Create exception
                    vAddr valids;
                    for(uchar i = 0; i < nSpine; i++) {
                        if(vNeis[i]) {
                            tNei.b = i;
                            valids.push_back(tNei);
                        }
                    }
                    DCAddr dst = DCAddr(AGID_Spine, f, 0);
                    ret.push_back(RawException(dst, valids));
                } else {
                    DCAddr dst = DCAddr(AGID_Spine, f, 0);
                    ret.push_back(RawException(dst, defvalids));
                }
            }
        }


        //Reach Pods via sub-opt paths (going through another spine-sets)
        for(const uchar p : nonOpPods) {
            setuchar remSpines;
            for(uchar s =0 ; s < nSpine; s++) { if(liveNeis[s]) { remSpines.insert(s); } }

            //Iterate other pods until no remSpines left
            for(uchar q = 0; !remSpines.empty() && q < nPod; q++) {
                //Pod q is opt-reachable?
                if(nonOpPods.find(q) != nonOpPods.end()) { continue; }

                //In Fabrics at Pod q is connected DOWN
                if(deadPodFabric.find(q) != deadPodFabric.end()) {
                    auto & dpf = deadPodFabric[q];
                    if(dpf.find(Im.b) != dpf.end()) { continue; }
                }

                DCAddr t(TYPEID_Fabric, q, Im.b);
                setDCAddr * fProbs = nullptr;
                if(problemsDown.find(t) != problemsDown.end()) { fProbs = &problemsDown[t]; }

                bool reach = false;
                for(uchar f = 0; !reach && f < nFab; f++) {
                    if(f == Im.b) { continue; }
                    t.b = f;

                    //Out Fabrics at Pod q is connected DOWN
                    if(deadPodFabric.find(q) != deadPodFabric.end()) {
                        auto & dpf = deadPodFabric[q];
                        if(dpf.find(Im.b) != dpf.end()) { continue; }
                    }

                    setDCAddr * dstProbs = nullptr;
                    if(problemsDown.find(t) != problemsDown.end()) { dstProbs = &problemsDown[t]; }

                    //In/Out Fabrics at Pod p connected?
                    if(fProbs != nullptr && dstProbs != nullptr) {
                        setDCAddr jProbs = *fProbs;
                        jProbs.insert(dstProbs->begin(), dstProbs->end());
                        if(jProbs.size() >= nTor) { continue; }
                    }

                    //Fabric reach dst Pod?
                    setDCAddr * fUpProbs = nullptr;
                    if(problemsUp.find(t) != problemsUp.end()) { fUpProbs = &problemsUp[t]; }
                    t.a = p;
                    setDCAddr * dstUpProbs = nullptr;
                    if(problemsUp.find(t) != problemsUp.end()) { dstUpProbs = &problemsUp[t]; }

                    if(fUpProbs == nullptr || dstUpProbs == nullptr) { reach = true; }
                    else {
                        setDCAddr jProbs = *fUpProbs;
                        jProbs.insert(dstUpProbs->begin(), dstUpProbs->end());
                        if(jProbs.size() < nSpine) { reach = true; }
                    }
                }
                //If Pod q don't reach pod p, skip
                if(!reach) { continue; }

                //remaining non-opt spines \= opt spines to reach pod p
                if(podProblems.find(q) != podProblems.end()) {
                    const setuchar & pNonOpt = podProblems[q];
                    setucharIt it = remSpines.begin();
                    //Remove from remSpines those that opt-reach pod p
                    while(it != remSpines.end()) {
                        if(pNonOpt.find(*it) == pNonOpt.end()) { it = remSpines.erase(it); }
                        else { it++; }
                    }
                } else { remSpines.clear() ;}
            }

            if(allNeisLive){
                //Create exception if some neis are not valid
                if(!remSpines.empty()) {
                    vbool vNeis = myNei;
                    for(auto & n : remSpines) { vNeis[n] = false; }

                    //Create exception
                    vAddr valids;
                    for(uchar i = 0; i < nSpine; i++) {
                        if(vNeis[i]) {
                            tNei.b = i;
                            valids.push_back(tNei);
                        }
                    }
                    DCAddr dst = DCAddr(AGID_Pod, p, 0);
                    ret.push_back(RawException(dst, valids));
                }
            } else {
                uchar myLiveNeiCount = 0;
                vAddr defvalids;
                for(uchar i = 0; i < nSpine; i++) {
                    if(liveNeis[i]) {
                        tNei.b = i;
                        defvalids.push_back(tNei);
                        myLiveNeiCount++;
                    }
                }
                //Create exception if some neis are not valid
                if(!remSpines.empty()) {
                    vbool vNeis = liveNeis;
                    for(auto & n : remSpines) { vNeis[n] = false; }

                    //Create exception
                    vAddr valids;
                    for(uchar i = 0; i < nSpine; i++) {
                        if(vNeis[i]) {
                            tNei.b = i;
                            valids.push_back(tNei);
                        }
                    }
                    DCAddr dst = DCAddr(AGID_Pod, p, 0);
                    ret.push_back(RawException(dst, valids));
                } else {
                    DCAddr dst = DCAddr(AGID_Pod, p, 0);
                    ret.push_back(RawException(dst, defvalids));
                }
            }
        }


        clearParsedFailures();

        return ret;

    }
}
