package rina.policies.DIF.RA.PDUFG.LatGenerator;

import rina.src.DIF.RA.PDUFG.IntPDUFG;

simple LatGenerator like IntPDUFG
{
    parameters:
        @class(LatGenerator::LatGenerator);
        @display("i=block/socket");
        
        int redLinkCost = default(1);
        int maxLinkCost = default(100);
        int minLinkCost = default(1);
}
