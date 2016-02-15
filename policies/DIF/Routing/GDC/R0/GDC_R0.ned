package rina.policies.DIF.Routing.GDC.R0;

import rina.policies.DIF.Routing.GDC.GDC_RT;

simple GDC_R0 like GDC_RT
{
    parameters:
        @class(GDC::R0);
        
        bool printAtEnd = default(false);
        
        int nSpines = default(0);
        int nPod = default(0);
        int nEdgeP = default(0);
        int nFab = default(0);
        int nTor = default(0);
        int nEdge = default(0);
        
        double starttime = default(10);
        double oldAfter = default(10);
        double expiresAfter = default(20);
}
