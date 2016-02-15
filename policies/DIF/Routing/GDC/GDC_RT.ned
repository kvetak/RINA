package rina.policies.DIF.Routing.GDC;

import rina.src.DIF.Routing.IntRouting;

moduleinterface GDC_RT extends IntRouting
{
    parameters:
        @display("i=block/socket");
        
        bool printAtEnd;
        
        int nSpines;
        int nPod;
        int nEdgeP;
        int nFab;
        int nTor;
        int nEdge;
        
        double starttime;
        double oldAfter;
        double expiresAfter;
}
