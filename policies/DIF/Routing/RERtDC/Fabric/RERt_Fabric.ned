package rina.policies.DIF.Routing.RERtDC.Fabric;

import rina.policies.DIF.Routing.RERtDC.RuleExceptionRT;

simple RERt_Fabric like RuleExceptionRT
{
    parameters:
        @class(RERtDC::RERt_Fabric);
        
        bool printAtEnd = default(false);
        
        int nPod;
        int nTor;
        int nFab;
        int nSpine;
        int nEdgeP;
        
        double starttime = default(10);
        double oldAfter = default(10);
        double expiresAfter = default(20);
}
