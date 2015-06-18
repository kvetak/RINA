package rina.policies.DIF.RA.PDUFG.BiDomainGenerator;

import rina.src.DIF.RA.PDUFG.IntPDUFG;

simple BiDomainGenerator like IntPDUFG
{
    parameters:
        @class(BiDomainGenerator::BiDomainGenerator);
        @display("i=block/socket");
        string alg0 = default("DV");
        string alg1 = default("DV");
}
