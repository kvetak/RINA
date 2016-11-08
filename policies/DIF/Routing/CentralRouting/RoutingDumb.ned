package rina.policies.DIF.Routing.CentralRouting;

import rina.src.DIF.Routing.IntRouting;

simple RoutingDumb like IntRouting {
    parameters:
        @display("i=block/socket");
        
        double status_updateInterval = default(0.001);
        double re_status_updateInterval = default(0.01);
        
        
        
        bool printAtEnd = default(false);
}
