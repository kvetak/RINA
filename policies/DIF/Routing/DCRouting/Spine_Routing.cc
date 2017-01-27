#include "DIF/Routing/DCRouting/Spine_Routing.h"



namespace NSPSimpleDC {

    Register_Class(Spine_Routing);

    void Spine_Routing::activeNeigh(const DCAddr &dst) {
        if((dst.type != 1 && dst.type != 3 )|| dst.b != Im.a) {
            cerr << "ADD - I'm " << Im
                 << " -- "
                 << "Invalid neighbour "<< dst
                 << endl;
            return;
        }

        linkId lid = linkId(dst, Im);
        linkInfo & li = myLinks [lid];

        if(!li.status) {
            li.status = true;
            if(start == nullptr) {
                li.timestamp = simTime();
            } else {
                li.timestamp = 0;
            }
            linksKo.erase(lid);
            scheduleUpdate();
        }
    }

    void Spine_Routing::inactiveNeigh(const DCAddr &dst) {
        if((dst.type != 1 && dst.type != 3 )|| dst.b != Im.a) {
            cerr << "REM - I'm " << Im
                 << " -- "
                 << "Invalid neighbour "<< dst
                 << endl;
            return;
        }

        linkId lid = linkId(dst, Im);
        linkInfo & li = myLinks [lid];

        if(li.status) {
            li.status = false;
            li.timestamp = simTime();
            linksKo[lid] = li;
            scheduleUpdate();
        }
    }

    void Spine_Routing::startMyLinks() {
        for(int i = 0; i < pods; i++) {
            linkId l = linkId(DCAddr(1, i, Im.a), Im);
            myLinks [l] = linkInfo(l, false, 0);
            linksKo[l] = linkInfo(l, false, 0);
        }
        for(int i = 0; i < edgeSets; i++) {
            linkId l = linkId(DCAddr(3, i, Im.a), Im);
            myLinks [l] = linkInfo(l, false, 0);
            linksKo[l] = linkInfo(l, false, 0);
        }
    }


    set<DCAddr> Spine_Routing::getNotOptimalDst(map<DCAddr, tableNode> *  table) {
        set<DCAddr> ret;

        for(auto & e : *table) {
            const DCAddr & dst = e.first;
            tableNode & tn = e.second;
            if(dst == Im) { continue; }
            switch(dst.type) {
                case 0: {
                    if(tn.d > 2 || (int)tn.L.size() != 1) {
                        ret.insert(dst);
                    } else {
                        const linkId & li = **(tn.L.begin());
                        if(li.src.a != dst.a) {
                            ret.insert(dst);
                        }
                    }

                }break;
                case 1: {
                    if(dst.b == Im.a) {
                        if(tn.d > 1 || (int)tn.L.size() != 1) {
                            ret.insert(dst);
                        } else {
                            const linkId & li = **(tn.L.begin());
                            if(li.src != dst) {
                                ret.insert(dst);
                            }
                        }
                    } else {
                        if(tn.d > 3 || (int)tn.L.size() != 1) {
                            ret.insert(dst);
                        } else {
                            const linkId & li = **(tn.L.begin());
                            if(li.src.a != dst.a) {
                                ret.insert(dst);
                            }
                        }
                    }
                }break;
                case 2: {
                    if(dst.a == Im.a) {
                        if(tn.d > 2 || (int)tn.L.size() != pods) {
                            ret.insert(dst);
                        }
                    } else {
                        if(tn.d > 4 || (int)tn.L.size() != pods) {
                            ret.insert(dst);
                        }
                    }
                }break;
                case 3: {
                    if(dst.b == Im.a) {
                        if(tn.d > 1 || (int)tn.L.size() != 1) {
                            ret.insert(dst);
                        } else {
                            const linkId & li = **(tn.L.begin());
                            if(li.dst != dst) {
                                ret.insert(dst);
                            }
                        }
                    } else {
                        if(tn.d > 5 || (int)tn.L.size() != pods) {
                            ret.insert(dst);
                        }
                    }
                }break;
            }
        }

        return ret;
    }


    void Spine_Routing::printAtEnd() {

    }
}
