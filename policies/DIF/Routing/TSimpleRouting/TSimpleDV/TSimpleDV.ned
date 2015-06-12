package rina.policies.DIF.Routing.TSimpleRouting.TSimpleDV;

import rina.policies.DIF.Routing.IntRouting;

simple TSimpleDV like IntRouting
{
    parameters:
        @class(ushort_TSimpleDV);
        @display("i=block/socket");
        string myAddr = default("");
        
        bool printAtEnd = default(false);
}
