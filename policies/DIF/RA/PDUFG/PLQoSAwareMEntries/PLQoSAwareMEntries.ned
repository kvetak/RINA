package rina.policies.DIF.RA.PDUFG.PLQoSAwareMEntries;

import rina.src.DIF.RA.PDUFG.IntPDUFG;

simple PLQoSAwareMEntries like IntPDUFG
{
    parameters:
        @class(PLQoSAwareMEntries::PLQoSAwareMEntries);
        @display("i=block/socket");
        
        int infinite = default(32);
        
        xml data = default(xml("<Metrics />"));
        double latMultip = default(1);
        int maxLat = 30;
}
