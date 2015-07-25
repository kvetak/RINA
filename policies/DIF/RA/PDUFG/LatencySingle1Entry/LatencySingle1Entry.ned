package rina.policies.DIF.RA.PDUFG.LatencySingle1Entry;

import rina.src.DIF.RA.PDUFG.IntPDUFG;

simple LatencySingle1Entry like IntPDUFG
{
    parameters:
        @class(LatencySingle1Entry::LatencySingle1Entry);
        @display("i=block/socket");
        
        int infinite = default(1000);
        int redLinkCost = default(1);
        int maxLinkCost = default(100);
        int minLinkCost = default(1);
}
