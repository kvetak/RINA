package rina.policies.DIF.RA.PDUFG.GRE.Simple;

import rina.src.DIF.RA.PDUFG.IntPDUFG;

simple GRE_Simple like IntPDUFG
{
    parameters:
        @class("GRE_Simple::GRE_Simple");
        @display("i=block/socket");
        
        int infinite = default(32);
}
