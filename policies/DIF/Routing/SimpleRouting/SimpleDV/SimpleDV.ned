package rina.policies.DIF.Routing.SimpleRouting.SimpleDV;

import rina.policies.DIF.Routing.IntRouting;

simple SimpleDV like IntRouting
{
    parameters:
        @class(SimpleDV::SimpleDV);
        @display("i=block/socket");
        string myAddr = default("");
}
