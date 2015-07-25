package rina.policies.DIF.RA.PDUFG.LatencySingleMEntries;

import rina.src.DIF.RA.PDUFG.IntPDUFG;

simple LatencySingleMEntries like IntPDUFG
{
    parameters:
        @class(LatencySingleMEntries::LatencySingleMEntries);
        @display("i=block/socket");
        
        int infinite = default(1000);
        int redLinkCost = default(1);
        int maxLinkCost = default(100);
        int minLinkCost = default(1);
}
