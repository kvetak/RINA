package rina.policies.DAF.Management.ViFIB.Controller;

import rina.src.DAF.AE.AE;
import rina.src.DAF.AE.IAE;

simple Controller extends AE like IAE
{
    parameters:
        @class(ViFIB::Controller);
        
        //ViFIB node info
        string vifibId = default("");
		string baseIPC = default("^.^.^.relayIpc");
        
        //Master Agent
        string dstApName = default("AppErr");
        string dstApInstance = default("0");
        string dstAeName = default("MasterAgent");
        string dstAeInstance = default("0");
        
        double connectAt @unit(s) = default(-1s);
        double sayHelloAfter @unit(s) = default(1s);
         
        
        //
        bool printAtEnd = default(false);
}
