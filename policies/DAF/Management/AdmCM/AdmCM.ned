package rina.policies.DAF.Management.AdmCM;

import rina.src.DAF.AE.AE;
import rina.src.DAF.AE.IAE;

simple AdmCM extends AE like IAE
{
    parameters:
        @class(AdmCM);
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
