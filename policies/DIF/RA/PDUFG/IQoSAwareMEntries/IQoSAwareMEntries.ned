package rina.policies.DIF.RA.PDUFG.IQoSAwareMEntries;

import rina.src.DIF.RA.PDUFG.IntPDUFG;

simple IQoSAwareMEntries like IntPDUFG
{
    parameters:
        @class(IQoSAwareMEntries::IQoSAwareMEntries);
        @display("i=block/socket");
        
        int infinite = default(32);
        
        xml data = default(xml("<Metrics />"));
        double latMultip = default(1);
        int maxLat = 30;
}
