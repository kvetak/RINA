package rina.policies.DIF.RA.PDUFG.SingleDomainGenerator;

import rina.policies.DIF.RA.PDUFG.IntPDUFG;

simple SingleDomainGenerator like IntPDUFG
{
    parameters:
        @class(SingleDomainGenerator::SingleDomainGenerator);
        @display("i=block/socket");
        string alg = default("DV");
}
