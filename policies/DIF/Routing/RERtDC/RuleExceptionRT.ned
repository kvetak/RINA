package rina.policies.DIF.Routing.RERtDC;

import rina.src.DIF.Routing.IntRouting;

moduleinterface RuleExceptionRT extends IntRouting
{
    parameters:
        @display("i=block/socket");
        
        bool printAtEnd;
        
        int nPod;
        int nTor;
        int nFab;
        int nSpine;
        int nEdgeP;
        
        double starttime;
        double oldAfter;
        double expiresAfter;
}
