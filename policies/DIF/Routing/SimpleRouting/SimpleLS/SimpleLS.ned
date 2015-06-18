package rina.policies.DIF.Routing.SimpleRouting.SimpleLS;

import rina.src.DIF.Routing.IntRouting;

simple SimpleLS like IntRouting
{
    parameters:
        @class(SimpleLS::SimpleLS);
        @display("i=block/socket");
        string myAddr = default("");
        int infMetric = default(32);
        
        bool printAtEnd = default(false);
}
