package rina.policies.DIF.Routing.TSimpleRouting.TSimpleLS;

import rina.src.DIF.Routing.IntRouting;

simple TSimpleLS like IntRouting
{
    parameters:
        @class(ushort_TSimpleLS);
        @display("i=block/socket");
        string myAddr = default("");
        
        bool printAtEnd = default(false);
}
