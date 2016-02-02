package rina.src.Other.Infection;

simple DCInfection {
        
    parameters:
        @class(Infection::DCInfection);
        
        string infectedIPC;
        
        double iniTime = default(-1);
        double interTime = default(0.1);
        int loop = default(1);
        
        bool toTors = default(false);
        bool toFabric = default(false);
        bool toSpines = default(false);
        bool toEdges = default(false);
        
        string qosId = default("BE");
        
        int pods = default(1);
        int torXpod = default(1);
        int fabricXpod = default(1);
        int spineXfabric = default(1);
        int edgeSets = default(0);
        
    gates:
        inout g;
}
