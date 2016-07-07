package rina.src.Other.MLONOFFInj;

simple MlONOFInj {
    parameters:
        string infectedIPC;
        
        xml data;
        
        double ini = default(10); // start sending at
        double fin= default(20); // stop sending at
        
        double infRate = default(1000000);
        int maxSimult = default(1);
        
        double rateMult = default(1.0);
        
    gates:
        inout g;
}
