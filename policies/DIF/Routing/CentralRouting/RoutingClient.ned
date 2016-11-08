package rina.policies.DIF.Routing.CentralRouting;

import rina.src.DIF.Routing.IntRouting;

simple RoutingClient like IntRouting {
    parameters:
        @display("i=block/socket");
        
        double status_updateInterval = default(0.001);
        double re_status_updateInterval = default(0.01);
        
        double in_updateInterval = default(0.001);
        
        double requestInfoAt = default(2.0);
        double re_requestInfoAt = default(0.5);
        
        bool printAtEnd = default(false);
}
