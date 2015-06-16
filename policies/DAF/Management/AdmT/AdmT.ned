package rina.policies.DAF.Management.AdmT;

import rina.src.DAF.AE.AE;
import rina.src.DAF.AE.IAE;

simple AdmT extends AE like IAE
{
    parameters:
        @class(AdmT);
        //Parent Management App
        string dstApName = default("AppErr");
        string dstApInstance = default("0");
        string dstAeName = default("AeErr");
        string dstAeInstance = default("0");
        
        int connectAt @unit(s) = default(-1s);
        int sayHelloAfter @unit(s) = default(1s);
        
        //Default Flows creation
        int startFlowsAt @unit(s) = default(-1s);
        string DIF = default("NET");
        string src = default("");
        string dsts = default("");
        
}
