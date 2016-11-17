package rina.policies.DIF.Routing.TDomainRouting;

import rina.src.DIF.Routing.IntRouting;

simple TDomainRouting like IntRouting
{
    parameters:
        @class(ushort_TDomain);
        @display("i=block/socket");
		//Mandatory signal to implement
        @signal[Routing-Update](type=IntRoutingUpdate?); 
        
        string myAddr = default("");
        
        bool printAtEnd = default(false);
}
