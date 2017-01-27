#include "DIF/Routing/DCRouting/TOR_Routing.h"



namespace NSPSimpleDC {

    Register_Class(TOR_Routing);

    void TOR_Routing::activeNeigh(const DCAddr &dst) {
        if(dst.type != 1 || dst.a != Im.a) {
            cerr << "I'm " << Im
                 << " -- "
                 << "Invalid neighbour "<< dst
                 << endl;
            return;
        }

        linkId lid = linkId(Im, dst);
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

    void TOR_Routing::inactiveNeigh(const DCAddr &dst) {
        if(dst.type != 1 || dst.a != Im.a) {
            cerr << "Invalid neighbour" << endl;
            return;
        }

        linkId lid = linkId(Im, dst);
        linkInfo & li = myLinks [linkId(Im, dst)];

        if(li.status) {
            li.status = false;
            li.timestamp = simTime();
            linksKo[lid] = li;
            scheduleUpdate();
        }
    }

    void TOR_Routing::startMyLinks() {
        for(int i = 0; i < fabricXpod; i++) {
            linkId l = linkId(Im, DCAddr(1, Im.a, i));
            myLinks [l] = linkInfo(l, false, 0);
            linksKo[l] = linkInfo(l, false, 0);
        }
    }

    set<DCAddr> TOR_Routing::getNotOptimalDst(map<DCAddr, tableNode> *  table) {
        set<DCAddr> ret;

        for(auto & e : *table) {
            const DCAddr & dst = e.first;
            tableNode & tn = e.second;
            if(dst == Im) { continue; }
            switch(dst.type) {
                case 0: {
                    if(dst.a == Im.a) {
                        if(tn.d > 2 || (int)tn.L.size() != fabricXpod) {
                            ret.insert(dst);
                        }
                    } else {
                        if(tn.d > 4 || (int)tn.L.size() != fabricXpod) {
                            ret.insert(dst);
                        }
                    }
                }break;
                case 1: {
                    if(dst.a == Im.a) {
                        if(tn.d > 1 || (int)tn.L.size() != 1) {
                            ret.insert(dst);
                        } else {
                            const linkId & li = **(tn.L.begin());
                            if(li.dst != dst) {
                                ret.insert(dst);
                            }
                        }
                    } else {
                        if(tn.d > 3 || (int)tn.L.size() != 1) {
                            ret.insert(dst);
                        } else {
                            const linkId & li = **(tn.L.begin());
                            if(li.dst.b != dst.b) {
                                ret.insert(dst);
                            }
                        }
                    }
                }break;
                case 2: {
                    if(tn.d > 2 || (int)tn.L.size() != 1) {
                        ret.insert(dst);
                    } else {
                        const linkId & li = **(tn.L.begin());
                        if(li.dst.b != dst.a) {
                            ret.insert(dst);
                        }
                    }
                }break;
                case 3: {
                    if(tn.d > 3 || (int)tn.L.size() != 1) {
                        ret.insert(dst);
                    }
                }break;

            }
        }

        return ret;
    }

    void TOR_Routing::printAtEnd() {
    }
}
