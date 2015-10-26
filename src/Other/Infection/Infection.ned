package rina.src.Other.Infection;

simple Infection {
        
    parameters:
        @class(Infection::Infection);
        
        string infectedIPC  = default("");
        
        xml data = default(xml("<flows></flows>"));
        
        double iniTime = default(10);
        
    gates:
        inout g;
}
