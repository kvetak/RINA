package rina.policies.DAF.Management.ViFIB.CoreAgent;

import rina.src.DAF.AE.AE;
import rina.src.DAF.AE.IAE;

simple CoreAgent extends AE like IAE
{
    parameters:
        @class(ViFIB::CoreAgent);
        
        //
        bool printAtEnd = default(false);
}
