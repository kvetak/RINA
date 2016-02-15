#pragma once

#include "RuleExceptionsRT.h"

namespace RERtDC {

using namespace std;
using namespace NSPSimpleDC;


    class RERt_Fabric: public RuleExceptionsRT {
    public:
        RawExceptionsList getExceptions();

    protected:
        void startMyNeis();
        portId getNeiId(DCAddr addr);
    };

}
