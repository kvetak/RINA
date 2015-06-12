package rina.policies.DIF.RA.PDUFG.HopsSingleMEntries;

import rina.policies.DIF.RA.PDUFG.IntPDUFG;

simple HopsSingleMEntries like IntPDUFG
{
    parameters:
        @class(HopsSingleMEntries::HopsSingleMEntries);
        @display("i=block/socket");
        
        int infinite = default(32);
}
