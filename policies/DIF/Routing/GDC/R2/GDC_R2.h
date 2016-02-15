#pragma once

#include "GDC_RT_iface.h"

namespace GDC {
    using namespace std;

    class R2: public iface_RT {
    public:
        vecRawException getExceptions();

    protected:
        void startMyNeis();
        ushort getNeiId(const Addr & addr);
    };

}
