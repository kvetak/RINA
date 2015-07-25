package rina.policies.DIF.RA.PDUFG.HierarchicalGenerator;

import rina.src.DIF.RA.PDUFG.IntPDUFG;

simple HierarchicalGenerator like IntPDUFG
{
    parameters:
        @class(HierarchicalGenerator::HierarchicalGenerator);
        @display("i=block/socket");
        string alg = default("LS");
}
