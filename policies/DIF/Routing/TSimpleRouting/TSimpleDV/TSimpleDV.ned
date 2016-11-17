package rina.policies.DIF.Routing.TSimpleRouting.TSimpleDV;

import rina.src.DIF.Routing.IntRouting;

simple TSimpleDV like IntRouting
{
    parameters:
        @class(ushort_TSimpleDV);
        @display("i=block/socket");
		//Mandatory signal to implement
        @signal[Routing-Update](type=IntRoutingUpdate?); 
        
        string myAddr = default("");
        
        bool printAtEnd = default(false);
}
