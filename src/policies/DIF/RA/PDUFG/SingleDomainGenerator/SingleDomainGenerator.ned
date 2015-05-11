package rina.src.policies.DIF.RA.PDUFG.SingleDomainGenerator;

import rina.src.policies.DIF.RA.PDUFG.IntPDUFG;

simple SingleDomainGenerator like IntPDUFG
{
    parameters:
        @class(SingleDomainGenerator::SingleDomainGenerator);
        @display("i=block/socket");
        string alg = default("DV");
}
