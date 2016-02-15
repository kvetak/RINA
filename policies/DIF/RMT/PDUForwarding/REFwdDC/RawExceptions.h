#pragma once

#include "DCAddr.h"
#include <vector>


namespace REFwdDC {

    using namespace std;
    using namespace NSPSimpleDC;

    typedef vector<DCAddr> vAddr;

    struct RawException {
        DCAddr addr;
        bool OK;
        vector<DCAddr> validNeis;

        RawException(DCAddr addr);
        RawException(DCAddr addr, vAddr validNeis);
    };

    typedef vector<RawException> RawExceptionsList;

}
