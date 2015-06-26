package rina.policies.DAF.Management.ViFIB.ManagementAgent;

import rina.src.DAF.AE.AE;
import rina.src.DAF.AE.IAE;

simple ManagementAgent extends AE like IAE
{
    parameters:
        @class(ViFIB::ManagementAgent);
        
        //
        bool printAtEnd = default(false);
}
