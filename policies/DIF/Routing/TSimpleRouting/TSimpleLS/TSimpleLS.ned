package rina.policies.DIF.Routing.TSimpleRouting.TSimpleLS;

import rina.src.DIF.Routing.IntRouting;

simple TSimpleLS like IntRouting
{
    parameters:
        @class(ushort_TSimpleLS);
        @display("i=block/socket");
		//Mandatory signal to implement
        @signal[Routing-Update](type=IntRoutingUpdate?); 
        
        string myAddr = default("");
        
        bool printAtEnd = default(false);
}
