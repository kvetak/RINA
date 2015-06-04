package rina.policies.DIF.RA.PDUFG.QoSDomainGenerator;

import rina.policies.DIF.RA.PDUFG.IntPDUFG;

simple QoSDomainGenerator like IntPDUFG
{
    parameters:
        @class(QoSDomainGenerator::QoSDomainGenerator);
        @display("i=block/socket");
        string alg = default("DV");
}
