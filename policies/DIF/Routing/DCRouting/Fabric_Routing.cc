#include "Fabric_Routing.h"



namespace NSPSimpleDC {
    void Fabric_Routing::activeNeigh(const DCAddr &dst) {
        if((dst.type != 0 || dst.a != Im.a)
                && (dst.type != 2 || dst.a != Im.b)) {
            cerr << "Invalid neighbour" << endl;
            return;
        }

        linkInfo * li;
        if(dst.type == 0) {
            li = &myLinks [linkId(0, Im.a, dst.b, Im.b)];
        } else {
            li = &myLinks [linkId(1, Im.a, Im.b, dst.b)];
        }

        if(!li->status) {
            li->status = true;
            li->timestamp = simTime();
            scheduleUpdate();
        }
    }

    void Fabric_Routing::inactiveNeigh(const DCAddr &dst) {
        if((dst.type != 0 || dst.a != Im.a)
                && (dst.type != 2 || dst.a != Im.b)) {
            cerr << "Invalid neighbour" << endl;
            return;
        }

        linkInfo & li = myLinks [linkId(0, Im.a, dst.b, Im.b)];

        if(li->status) {
            li->status = false;
            li->timestamp = simTime();
            scheduleUpdate();
        }
    }

    void Fabric_Routing::startMyLinks() {
        for(int i = 0; i < fabricXpod; i++) {
            linkId l = linkId(0, Im.a, i, Im.b);
            myLinks [l] = linkInfo(l, false, simTime());
        }
        for(int i = 0; i < spineXfabric; i++) {
            linkId l = linkId(1, Im.a, Im.b, i);
            myLinks [l] = linkInfo(l, false, simTime());
        }
    }

    vector<rtEntry>  Fabric_Routing::getChanges() {
        //TO-DO
        return vector<rtEntry>();
    }

    vector<rtEntry>  Fabric_Routing::getAll() {
        //TO-DO
        return vector<rtEntry>();
    }
}
