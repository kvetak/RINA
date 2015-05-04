package rina.policies.DIF.RA.PDUFG.RatesGenerator;

import rina.policies.DIF.RA.PDUFG.IntPDUFG;

simple RatesGenerator like IntPDUFG
{
    parameters:
        @display("i=block/socket");
        int interval = default(1);
}