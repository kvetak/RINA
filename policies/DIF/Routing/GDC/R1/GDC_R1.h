#pragma once

#include "GDC_RT_iface.h"

namespace GDC {
    using namespace std;

    class R1: public iface_RT {
    public:
        vecRawException getExceptions();

    protected:
        ushort mySons;
        void startMyNeis();
        ushort getNeiId(const Addr & addr);
    };

}
