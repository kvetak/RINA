package rina.policies.DIF.RA.PDUFG.GRE.ClosRouting;

import rina.src.DIF.RA.PDUFG.IntPDUFG;

simple GRE_Clos1R like IntPDUFG
{
    parameters:
        @class("GRE_Clos::GRE_ClosR1");
        @display("i=block/socket");
        
        int pods = default(10);
        int fabrics = default(4);
        int spines = default(10);
        int tors = default(20);
}
