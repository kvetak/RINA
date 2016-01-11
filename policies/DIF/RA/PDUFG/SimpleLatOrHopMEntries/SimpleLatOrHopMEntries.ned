package rina.policies.DIF.RA.PDUFG.SimpleLatOrHopMEntries;

import rina.src.DIF.RA.PDUFG.IntPDUFG;

simple SimpleLatOrHopMEntries like IntPDUFG
{
    parameters:
        @class(NSPSimpleLatOrHopMEntries::SimpleLatOrHopMEntries);
        @display("i=block/socket");
        
        int infinite = default(32);
        
        xml data = default(xml("<Metrics />"));
        double latMultip = default(1);
        int maxLat = 30;
}
