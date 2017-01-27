#include "DIF/Routing/DCRouting/Fabric_Routing.h"



namespace NSPSimpleDC {

    Register_Class(Fabric_Routing);

    void Fabric_Routing::activeNeigh(const DCAddr &dst) {
        if(dst.type == 1
                || (dst.type == 0 && dst.a != Im.a)
                || (dst.type == 2 && dst.a != Im.b)) {
            cerr << "I'm " << Im
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

    void Fabric_Routing::inactiveNeigh(const DCAddr &dst) {
        if((dst.type != 0 || dst.a != Im.a)
                && (dst.type != 2 || dst.a != Im.b)) {
            cerr << "Invalid neighbour" << endl;
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

    void Fabric_Routing::startMyLinks() {
        for(int i = 0; i < torXpod; i++) {
            linkId l = linkId(DCAddr(0, Im.a, i), Im);
            myLinks [l] = linkInfo(l, false, 0);
            linksKo[l] = linkInfo(l, false, 0);
        }
        for(int i = 0; i < spineXfabric; i++) {
            linkId l = linkId(Im, DCAddr(2, Im.b, i));
            myLinks [l] = linkInfo(l, false, 0);
            linksKo[l] = linkInfo(l, false, 0);
        }
    }

    set<DCAddr> Fabric_Routing::getNotOptimalDst(map<DCAddr, tableNode> *  table) {

        set<DCAddr> ret;

        for(auto & e : *table) {
            const DCAddr & dst = e.first;
            tableNode & tn = e.second;
            if(dst == Im) { continue; }
            switch(dst.type) {
                case 0: {
                    if(dst.a == Im.a) {
                        if(tn.d > 1 || (int)tn.L.size() != 1) {
                            ret.insert(dst);
                        } else {
                            const linkId & li = **(tn.L.begin());
                            if(li.src != dst) {
                                ret.insert(dst);
                            }
                        }
                    } else {
                        if(tn.d > 3 || (int)tn.L.size() != spineXfabric) {
                            ret.insert(dst);
                        } else for(auto & k : tn.L) {
                            if(k->dst.type != 2) {
                                ret.insert(dst);
                                break;
                            }
                        }
                    }
                } break;
                case 1:  {
                    if(dst.a == Im.a) {
                        if(tn.d > 2 || (int)tn.L.size() != torXpod) {
                            ret.insert(dst);
                        } else for(auto & k : tn.L) {
                            if(k->src.type != 0) {
                                ret.insert(dst);
                                break;
                            }
                        }
                    } else if(dst.b == Im.b) {
                        if(tn.d > 2 || (int)tn.L.size() != spineXfabric) {
                            ret.insert(dst);
                        } else for(auto & k : tn.L) {
                            if(k->dst.type != 2) {
                                ret.insert(dst);
                                break;
                            }
                        }
                    } else if(tn.d > 4 || (int)tn.L.size() != torXpod+spineXfabric) {
                            ret.insert(dst);
                    }
                }break;
                case 2: {
                    if(dst.a == Im.b) {
                        if(tn.d > 1 || (int)tn.L.size() != 1) {
                            ret.insert(dst);
                        } else {
                            const linkId & li = **(tn.L.begin());
                            if(li.dst != dst) {
                                ret.insert(dst);
                            }
                        }
                    } else {
                        if(tn.d > 3 || (int)tn.L.size() != torXpod) {
                            ret.insert(dst);
                        }else for(auto & k : tn.L) {
                            if(k->src.type != 0) {
                                ret.insert(dst);
                                break;
                            }
                        }
                    }
                }break;
                case 3: {
                    if((dst.b == Im.b)) {
                        if(tn.d > 2  || (int)tn.L.size() != spineXfabric) {
                            ret.insert(dst);
                        }
                    } else if(tn.d > 4  || (int)tn.L.size() != torXpod) {
                        ret.insert(dst);
                    }
                }break;

            }
        }

        return ret;
    }

    void Fabric_Routing::printAtEnd() {

    }
}
