#pragma once

#include "IntDCRouting.h"


namespace NSPSimpleDC {

    class Fabric_Routing : public IntDCRouting {
        void activeNeigh(const DCAddr &dst);
        void inactiveNeigh(const DCAddr &dst);
        void startMyLinks();

        vector<rtEntry>  getChanges();
        vector<rtEntry>  getAll();
    };

}
