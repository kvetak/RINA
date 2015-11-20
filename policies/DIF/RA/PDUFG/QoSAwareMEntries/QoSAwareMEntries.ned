package rina.policies.DIF.RA.PDUFG.QoSAwareMEntries;

import rina.src.DIF.RA.PDUFG.IntPDUFG;

simple QoSAwareMEntries like IntPDUFG
{
    parameters:
        @class(QoSAwareMEntries::QoSAwareMEntries);
        @display("i=block/socket");
        
        int infinite = default(32);
        
        xml data = default(xml("<Metrics />"));
        double latMultip = default(1);
        int maxLat = 30;
}
