package rina.policies.DIF.RMT.PDUForwarding.SimpleTable;

import rina.policies.DIF.RMT.PDUForwarding.IntPDUForwarding;

simple SimpleTable like IntPDUForwarding
{
    parameters:
        @class(SimpleTable::SimpleTable);
        @display("i=block/socket");
}
