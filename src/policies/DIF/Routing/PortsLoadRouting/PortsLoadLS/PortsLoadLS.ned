package rina.policies.DIF.Routing.PortsLoadRouting.PortsLoadLS;

import rina.policies.DIF.Routing.IntRouting;

simple PortsLoadLS like IntRouting
{
    parameters:
        @display("i=block/socket");
        string myAddr = default("");
        int updateTimeout = default(0);
}
