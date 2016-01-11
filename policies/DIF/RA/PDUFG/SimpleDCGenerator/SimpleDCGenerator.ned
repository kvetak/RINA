package rina.policies.DIF.RA.PDUFG.SimpleDCGenerator;

import rina.src.DIF.RA.PDUFG.IntPDUFG;

simple SimpleDCGenerator like IntPDUFG
{
    parameters:
        @class(NSPSimpleDC::SimpleDCGenerator);
        @display("i=block/socket");
        
        int infinite = default(32);
        
        double startUpdating = default(10);
}
