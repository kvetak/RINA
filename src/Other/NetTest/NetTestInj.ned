package rina.src.Other.NetTest;

simple NetTestInj {
    parameters:
        string infectedIPC;
        
        xml data;
        string qos = default("BE");
        
        double ini = default(10); // start sending at
        double wait= default(0.1); // send each
        
    gates:
        inout g;
}
