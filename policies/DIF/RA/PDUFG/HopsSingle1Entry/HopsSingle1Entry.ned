package rina.policies.DIF.RA.PDUFG.HopsSingle1Entry;

import rina.src.DIF.RA.PDUFG.IntPDUFG;

simple HopsSingle1Entry like IntPDUFG
{
    parameters:
        @class(HopsSingle1Entry::HopsSingle1Entry);
        @display("i=block/socket");
        
        int infinite = default(32);
}
