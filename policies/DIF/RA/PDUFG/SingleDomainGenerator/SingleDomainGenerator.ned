package rina.policies.DIF.RA.PDUFG.SingleDomainGenerator;

import rina.src.DIF.RA.PDUFG.IntPDUFG;

simple SingleDomainGenerator like IntPDUFG
{
    parameters:
        @class(SingleDomainGenerator::SingleDomainGenerator);
        @display("i=block/socket");
        string alg = default("DV");
}
