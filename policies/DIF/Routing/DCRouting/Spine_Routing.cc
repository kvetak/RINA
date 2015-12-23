#include "Spine_Routing.h"



namespace NSPSimpleDC {
    void Spine_Routing::activeNeigh(const DCAddr &dst) {
        if(dst.type != 2 || dst.b != Im.a) {
            cerr << "Invalid neighbour" << endl;
            return;
        }

        linkInfo & li = myLinks [linkId(1, dst.a, dst.b, Im.b)];

        if(!li.status) {
            li.status = true;
            li.timestamp = simTime();
            scheduleUpdate();
        }
    }

    void Spine_Routing::inactiveNeigh(const DCAddr &dst) {
        if(dst.type != 2 || dst.b != Im.a) {
            cerr << "Invalid neighbour" << endl;
            return;
        }

        linkInfo & li = myLinks [linkId(1, dst.a, dst.b, Im.b)];

        if(li.status) {
            li.status = false;
            li.timestamp = simTime();
            scheduleUpdate();
        }
    }

    void Spine_Routing::startMyLinks() {
        for(int i = 0; i < pods; i++) {
            linkId l = linkId(1, i, Im.a, Im.b);
            myLinks [l] = linkInfo(l, false, simTime());
        }
    }

    vector<rtEntry>  Spine_Routing::getChanges() {
        //TO-DO
        return vector<rtEntry>();
    }

    vector<rtEntry>  Spine_Routing::getAll() {
        //TO-DO
        return vector<rtEntry>();
    }
}
