package rina.policies.DIF.RMT.PDUForwarding.MiniTable;

import rina.policies.DIF.RMT.PDUForwarding.IntPDUForwarding;

simple MiniTable like IntPDUForwarding
{
    parameters:
        @class(MiniTable::MiniTable);
        @display("i=block/socket");
        
        bool printAtEnd = default (false);
}
