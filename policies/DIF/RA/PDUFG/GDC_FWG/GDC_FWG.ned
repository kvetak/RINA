package rina.policies.DIF.RA.PDUFG.GDC_FWG;

import rina.src.DIF.RA.PDUFG.IntPDUFG;

simple GDC_FWG like IntPDUFG
{
    parameters:
        @class(GDC::FWG);
        @display("i=block/socket");
        
        double startUpdating = default(10);
}
