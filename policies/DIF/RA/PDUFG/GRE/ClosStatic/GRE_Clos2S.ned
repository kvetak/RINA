package rina.policies.DIF.RA.PDUFG.GRE.ClosStatic;

import rina.src.DIF.RA.PDUFG.IntPDUFG;

simple GRE_Clos2S like IntPDUFG
{
    parameters:
        @class("GRE_Clos::GRE_ClosS2");
        @display("i=block/socket");
        
        
        int pods = default(10);
        int spineS = default(4);
}
