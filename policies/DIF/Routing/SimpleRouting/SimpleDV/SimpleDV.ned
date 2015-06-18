package rina.policies.DIF.Routing.SimpleRouting.SimpleDV;

import rina.src.DIF.Routing.IntRouting;

simple SimpleDV like IntRouting
{
    parameters:
        @class(SimpleDV::SimpleDV);
        @display("i=block/socket");
        string myAddr = default("");
        int infMetric = default(32);
        
        bool printAtEnd = default(false);
        
}
