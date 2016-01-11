package rina.policies.DIF.RA.PDUFG.VoidDCGenerator;

import rina.src.DIF.RA.PDUFG.IntPDUFG;

simple VoidDCGenerator like IntPDUFG
{
    parameters:
        @class(NSPSimpleDC::VoidDCGenerator);
        @display("i=block/socket");
        
        int infinite = default(32);
        
        double startUpdating = default(10);
}
