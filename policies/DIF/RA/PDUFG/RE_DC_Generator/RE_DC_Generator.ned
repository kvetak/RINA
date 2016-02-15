package rina.policies.DIF.RA.PDUFG.RE_DC_Generator;

import rina.src.DIF.RA.PDUFG.IntPDUFG;

simple RE_DC_Generator like IntPDUFG
{
    parameters:
        @class(REFwdGDC::RE_DC_Generator);
        @display("i=block/socket");
        
        double startUpdating = default(10);
}
