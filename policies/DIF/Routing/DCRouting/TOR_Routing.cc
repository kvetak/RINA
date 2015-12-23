#include "TOR_Routing.h"



namespace NSPSimpleDC {
    void TOR_Routing::activeNeigh(const DCAddr &dst) {
        if(dst.type != 1 || dst.a != Im.a) {
            cerr << "Invalid neighbour" << endl;
            return;
        }

        linkInfo & li = myLinks [linkId(0, Im.a, Im.b, dst.b)];

        if(!li.status) {
            li.status = true;
            li.timestamp = simTime();
            scheduleUpdate();
        }
    }

    void TOR_Routing::inactiveNeigh(const DCAddr &dst) {
        if(dst.type != 1 || dst.a != Im.a) {
            cerr << "Invalid neighbour" << endl;
            return;
        }

        linkInfo & li = myLinks [linkId(0, Im.a, Im.b, dst.b)];

        if(li.status) {
            li.status = false;
            li.timestamp = simTime();
            scheduleUpdate();
        }
    }

    void TOR_Routing::startMyLinks() {
        for(int i = 0; i < fabricXpod; i++) {
            linkId l = linkId(0, Im.a, Im.b, i);
            myLinks [l] = linkInfo(l, false, simTime());
        }
    }

    vector<rtEntry>  TOR_Routing::getChanges() {
        //TO-DO
        return vector<rtEntry>();
    }

    vector<rtEntry>  TOR_Routing::getAll() {
        //TO-DO
        return vector<rtEntry>();
    }
}
