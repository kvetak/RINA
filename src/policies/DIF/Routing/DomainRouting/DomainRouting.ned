package rina.policies.DIF.Routing.DomainRouting;

import rina.policies.DIF.Routing.IntRouting;

simple DomainRouting like IntRouting
{
    parameters:
        @display("i=block/socket");
        @class(DMRnms::Routing);
}
