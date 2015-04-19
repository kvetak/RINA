package rina.src.policies.DIF.Routing.DomainRouting;

import rina.src.policies.DIF.Routing.IntRouting;

simple DomainRouting like IntRouting
{
    parameters:
        @display("i=block/socket");
        @class(DMRnms::Routing);
}
