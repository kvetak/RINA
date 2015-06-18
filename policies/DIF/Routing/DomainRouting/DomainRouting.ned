package rina.policies.DIF.Routing.DomainRouting;

import rina.src.DIF.Routing.IntRouting;

simple DomainRouting like IntRouting
{
    parameters:
        @display("i=block/socket");
        @class(DMRnms::Routing);
        
        bool printAtEnd = default(false);
}
