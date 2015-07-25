package rina.policies.DAF.Management.AdmTimedCore;

import rina.src.DAF.AE.AE;
import rina.src.DAF.AE.IAE;

simple AdmTimedCore extends AE like IAE
{
    parameters:
        @class(AdmTimedCore);
        
        xml flows = default(xml("<Flows />"));
}
