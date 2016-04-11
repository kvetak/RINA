package rina.src.Other.Infection;

simple T2Infection {
        
    parameters:
        @class(T2Infection::T2Infection);
        
        string infectedIPC;
        
        xml data;
        
        string defaultQoS = default(""); // default QoS if not configured
        
        int pduSize = default(8000); // b, default 1KB
        double pduVar = default(0.0); // pdu length : [(1-pduVar)*pduSize, (1+pduVar)*pduSize]
        
        double rateMult = default(1000000.0); // bps -> Mbps
        double rateVar = default(0.0); // realRate : [(1-rateVar)*rate*rateMult, (1+rateVar)*rate*rateMult]
        double probRateChange = default(0.0); // prob change direction 1/-1 <-> 0
        double rateVarVar = default(0.00); //realRate += direction*rateVarVar, at each pdu
        
        int nFlows = default(1); // number of flows per flowset
        double inRate = default(1.0); // inRate*rateMult bps
        
        double iniTime = default(10); // start sending at
        double finTime = default(20); // stop sending at
        
        double markIniT = default(12); // start marking pdus at
        double markFinT = default(18); // stop marking pdus at
        
    gates:
        inout g;
}
