package rina.policies.DIF.RA.PDUFG.HopsQoSMEntries;

import rina.src.DIF.RA.PDUFG.IntPDUFG;

simple HopsQoSMEntries like IntPDUFG
{
    parameters:
        @class(HopsQoSMEntries::HopsQoSMEntries);
        @display("i=block/socket");
        
        int infinite = default(32);
}
