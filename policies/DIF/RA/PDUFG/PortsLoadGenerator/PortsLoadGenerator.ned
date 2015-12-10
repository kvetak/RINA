package rina.policies.DIF.RA.PDUFG.PortsLoadGenerator;

import rina.src.DIF.RA.PDUFG.IntPDUFG;

simple PortsLoadGenerator like IntPDUFG
{
    parameters:
        @display("i=block/socket");
        int rateInterval 	= default(0);
        int updateInterval	= default(10);
}