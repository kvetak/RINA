#include "DIF/Routing/DCRouting/Edge_Routing.h"



namespace NSPSimpleDC {

    Register_Class(Edge_Routing);

    void Edge_Routing::activeNeigh(const DCAddr &dst) {
        if(dst.type != 2 || dst.a != Im.b) {
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

    void Edge_Routing::inactiveNeigh(const DCAddr &dst) {
        if(dst.type != 2 || dst.a != Im.b) {
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

    void Edge_Routing::startMyLinks() {
        for(int i = 0; i < spineXfabric; i++) {
            linkId l = linkId(Im, DCAddr(2, Im.b, i));
            myLinks [l] = linkInfo(l, false, 0);
            linksKo[l] = linkInfo(l, false, 0);
        }
    }

    set<DCAddr> Edge_Routing::getNotOptimalDst(map<DCAddr, tableNode> *  table) {
        set<DCAddr> ret;

        for(auto & e : *table) {
            const DCAddr & dst = e.first;
            tableNode & tn = e.second;
            if(dst == Im) { continue; }
            switch(dst.type) {
                case 0: {
                    if(tn.d > 3 || (int)tn.L.size() != edgeSets) {
                        ret.insert(dst);
                    }
                }break;
                case 1:{
                    if((dst.b == Im.b && tn.d > 2)
                            || (dst.b != Im.b && tn.d > 4)
                            || (int)tn.L.size() != spineXfabric) {
                        ret.insert(dst);
                    }
                }break;
                case 2: {
                    if(dst.a == Im.b) {
                        if(tn.d > 1 || (int)tn.L.size() != 1) {
                            ret.insert(dst);
                        }
                    } else if ((dst.a != Im.a && tn.d > 5)
                            || (int)tn.L.size() != edgeSets) {
                        ret.insert(dst);
                    }
                }break;
                case 3: {
                    if((dst.b == Im.b && tn.d > 2)
                            || (dst.a != Im.a && tn.d > 6)
                            || (int)tn.L.size() != edgeSets) {
                        ret.insert(dst);
                    }
                }break;
            }
        }

        return ret;
    }

    void Edge_Routing::printAtEnd() {
    }
}
