package rina.policies.DAF.Management.ViFIB.Core;

import rina.src.DAF.AE.AE;
import rina.src.DAF.AE.IAE;

simple Core extends AE like IAE
{
    parameters:
        @class(ViFIB::Core);
        
        int waitUntil = default(10);
        
        //
        bool printAtEnd = default(false);
}
