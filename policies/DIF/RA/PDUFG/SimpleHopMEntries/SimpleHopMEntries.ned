package rina.policies.DIF.RA.PDUFG.SimpleHopMEntries;

import rina.src.DIF.RA.PDUFG.IntPDUFG;

simple SimpleHopMEntries like IntPDUFG
{
    parameters:
        @class(NSPSimpleHopMEntries::SimpleHopMEntries);
        @display("i=block/socket");
        
        int infinite = default(32);
}
