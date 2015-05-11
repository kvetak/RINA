package rina.src.policies.DIF.Routing.SimpleRouting.SimpleLS;

import rina.src.policies.DIF.Routing.IntRouting;

simple SimpleLS like IntRouting
{
    parameters:
        @class(SimpleLS::SimpleLS);
        @display("i=block/socket");
        string myAddr = default("");
}
