package rina.policies.DAF.Management.AdmCore;

import rina.src.DAF.AE.AE;
import rina.src.DAF.AE.IAE;

simple AdmCore extends AE like IAE
{
    parameters:
        @class(AdmCore);
        
        xml flows = default(xml("<Flows />"));
}
