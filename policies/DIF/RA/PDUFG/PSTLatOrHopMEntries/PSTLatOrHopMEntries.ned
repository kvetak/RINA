package rina.policies.DIF.RA.PDUFG.PSTLatOrHopMEntries;

import rina.src.DIF.RA.PDUFG.IntPDUFG;

simple PSTLatOrHopMEntries like IntPDUFG
{
    parameters:
        @class(NSPPSTLatOrHopMEntries::PSTLatOrHopMEntries);
        @display("i=block/socket");
        
        int infinite = default(32);
        
        xml data = default(xml("<Metrics />"));
        double latMultip = default(1);
        int maxLat = 30;
}
