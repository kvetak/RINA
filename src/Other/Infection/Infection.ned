package rina.src.Other.Infection;

simple Infection {
        
    parameters:
        @class(Infection::Infection);
        
        string infectedIPC;
        
        xml data;
        
        
        double linkRate = default(1048576); // 1Mbps
        double usage = default(1.0);
        
        bool signal = default(true);
        
        double iniTime = default(10);
        double finTime = default(20);
        
        double markIniT = default(12);
        double markFinT = default(18);
        
        bool randomIni = default(false);
        
    gates:
        inout g;
        input radioIn @directIn;
        
}
