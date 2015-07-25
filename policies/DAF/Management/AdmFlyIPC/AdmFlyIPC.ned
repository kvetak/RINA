package rina.policies.DAF.Management.AdmFlyIPC;

import rina.src.DAF.AE.AE;
import rina.src.DAF.AE.IAE;

simple AdmFlyIPC extends AE like IAE
{
    parameters:
        @class(AdmFlyIPC);
        
        string difName = default("Fly");
        string addr = default("");
        string myAddr = default("");
        
        string neigh = default("");
        string neighAddr = default("");
        
        int atTime = default(1);
        int conAtTime = default(2);
}
