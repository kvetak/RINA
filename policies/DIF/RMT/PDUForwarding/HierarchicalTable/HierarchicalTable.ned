package rina.policies.DIF.RMT.PDUForwarding.HierarchicalTable;

import rina.policies.DIF.RMT.PDUForwarding.IntPDUForwarding;

simple HierarchicalTable like IntPDUForwarding
{
    parameters:
        @class(HierarchicalTable::HierarchicalTable);
        @display("i=block/socket");
        
        bool printAtEnd = default(false);
}
