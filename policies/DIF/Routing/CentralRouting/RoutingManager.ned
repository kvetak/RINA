package rina.policies.DIF.Routing.CentralRouting;

import rina.src.DIF.Routing.IntRouting;

simple RoutingManager like IntRouting {
    parameters:
        @display("i=block/socket");
        
        double in_updateInterval = default(0.01);
        double in_sincro_updateInterval = default(0.01);
        double out_sincro_updateInterval = default(0.01);
        double toout_sincro_updateInterval = default(0.01);
        double exceptions_timer_updateInterval = default(0.01);
        
        double start_Time = default(10.0);
        
        bool printAtEnd = default(false);
        
        
        int pods = default(10);
        int fabrics = default(4);
        int spines = default(10);
        int tors = default(20);
}
