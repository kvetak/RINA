package rina.policies.DIF.RA.PDUFG.GRE.ClosStatic;

import rina.src.DIF.RA.PDUFG.IntPDUFG;

simple GRE_Clos0S like IntPDUFG
{
    parameters:
        @class("GRE_Clos::GRE_ClosS0");
        @display("i=block/socket");
        
        
        int fabrics = default(4);
}
