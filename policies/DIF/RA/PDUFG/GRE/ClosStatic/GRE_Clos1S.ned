package rina.policies.DIF.RA.PDUFG.GRE.ClosStatic;

import rina.src.DIF.RA.PDUFG.IntPDUFG;

simple GRE_Clos1S like IntPDUFG
{
    parameters:
        @class("GRE_Clos::GRE_ClosS1");
        @display("i=block/socket");
        
        int spineS = default(4);
        int spines = default(10);
        int TEs = default(20);
}
