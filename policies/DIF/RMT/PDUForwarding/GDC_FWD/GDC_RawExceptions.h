#pragma once

#include "GDC_defines.h"

namespace GDC {
    using namespace std;

    struct RawException {
        Addr addr;
        bool OK;
        vecAddr validNeis;

        RawException(Addr _addr);
        RawException(Addr _addr, vecAddr _validNeis);
    };

    typedef vector<RawException> vecRawException;
}
