package rina.policies.DAF.Management.ViFIB.Management;

import rina.src.DAF.AE.AE;
import rina.src.DAF.AE.IAE;

simple Management extends AE like IAE
{
    parameters:
        @class(ViFIB::Management);
        
        //Master info
        string zoneId = default("");
		string baseIPC = default("^.^.^.relayIPC");
		
        int maxBorders = default(2);
        int maxDiameter = default(3);
        
        int waitUntil = default(10);
        
        //Master Agent
        string dstApName = default("AppErr");
        string dstApInstance = default("0");
        string dstAeName = default("CoreAgent");
        string dstAeInstance = default("0");
        
        double connectAt @unit(s) = default(-1s);
        double sayHelloAfter @unit(s) = default(1s);
         
        
        //
        bool printAtEnd = default(false);
}
