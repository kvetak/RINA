#pragma once
#include "GDC_FWD_iface.h"


namespace GDC {
    using namespace std;

    class L1: public iface_FWD {
    public:
        bool setNeigh(const Addr & dst, Port port);

    protected:
        vecushort upList, downList, bothList;
        ushort mySons;

        void initializeSubPolicy();

        vecushort readException(const Exception & e);
        vecushort readRawException(const RawException & raw);
        vecushort executeRule(const Addr & dst);
        Exception computeException(const RawException & raw);

        bool useDefault(const Addr & dst);
    };

}
