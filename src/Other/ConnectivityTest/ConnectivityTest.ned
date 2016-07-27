package rina.src.Other.ConnectivityTest;

simple ConnectivityTest {
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
