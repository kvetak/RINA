#pragma once

#include "GDC_RT_iface.h"

namespace GDC {
    using namespace std;

    class R0: public iface_RT {
    public:
        vecRawException getExceptions();

    protected:
        ushort nSets;

        void startMyNeis();
        ushort getNeiId(const Addr & addr);
    };

}
