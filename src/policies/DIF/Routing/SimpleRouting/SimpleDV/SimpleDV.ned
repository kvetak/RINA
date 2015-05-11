package rina.src.policies.DIF.Routing.SimpleRouting.SimpleDV;

import rina.src.policies.DIF.Routing.IntRouting;

simple SimpleDV like IntRouting
{
    parameters:
        @class(SimpleDV::SimpleDV);
        @display("i=block/socket");
        string myAddr = default("");
}
