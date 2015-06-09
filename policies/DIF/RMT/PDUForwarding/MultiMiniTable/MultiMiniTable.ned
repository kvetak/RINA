package rina.policies.DIF.RMT.PDUForwarding.MultiMiniTable;

import rina.policies.DIF.RMT.PDUForwarding.IntPDUForwarding;

simple MultiMiniTable like IntPDUForwarding
{
    parameters:
        @class(MultiMiniTable::MultiMiniTable);
        @display("i=block/socket");
        
        bool printAtEnd = default(false);
}
