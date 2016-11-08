package rina.src.Addons.DataInjectors.ReachabilityTest;

import rina.src.Addons.DataInjectors.Infection_t;

simple ReachabilityTest like Infection_t {
    parameters:
        string infectedIPC;
        string nodes = default("");
        
        double ini = default(10); // start sending at
        double interval= default(0.1); // send one each
       	
       	string QoS;
       	int header_size = default(80); //B
        
    gates:
        inout g;
}
