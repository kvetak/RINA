package rina.src.Other.Infection;

simple Infection {
        
    parameters:
        @class(Infection::Infection);
        
        string infectedIPC  = default("");
        
        xml data = default(xml("<flows></flows>"));
        
        double iniTime = default(10);
        double finTime = default(20);
        
        double linkRate = default(1048576); // 1Mbps
        double usage = default(1);
        
        int inPorts = default(1);
        
        bool signal = default(true);
        
        double markIniT = default(12);
        double markFinT = default(18);
        
        
    gates:
        inout g;
}
