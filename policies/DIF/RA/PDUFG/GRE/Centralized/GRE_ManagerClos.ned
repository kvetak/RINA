package rina.policies.DIF.RA.PDUFG.GRE.Centralized;

import rina.src.DIF.RA.PDUFG.IntPDUFG;

simple GRE_ManagerClos like IntPDUFG
{
    parameters:
        @display("i=block/socket");
        
        int pods = default(10);
        int fabrics = default(4);
        int spines = default(10);
        int tors = default(20);
}
