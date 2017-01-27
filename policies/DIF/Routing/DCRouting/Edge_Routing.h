#pragma once

#include "DIF/Routing/DCRouting/IntDCRouting.h"


namespace NSPSimpleDC {

    class Edge_Routing : public IntDCRouting {
        void activeNeigh(const DCAddr &dst);
        void inactiveNeigh(const DCAddr &dst);
        void startMyLinks();

        set<DCAddr> getNotOptimalDst(map<DCAddr, tableNode> *  table);

        void printAtEnd();
    };

}
