package rina.policies.DIF.Routing.TDomainRouting;

import rina.src.DIF.Routing.IntRouting;

simple TDomainRouting like IntRouting
{
    parameters:
        @class(ushort_TDomain);
        @display("i=block/socket");
        string myAddr = default("");
        
        bool printAtEnd = default(false);
}
