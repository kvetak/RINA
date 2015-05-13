package rina.policies.DIF.RMT.PDUForwarding.DomainTable;

import rina.policies.DIF.RMT.PDUForwarding.IntPDUForwarding;

simple DomainTable like IntPDUForwarding
{
    parameters:
        @class(DomainTable::DomainTable);
        @display("i=block/socket");
}
