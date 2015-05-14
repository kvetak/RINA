package rina.policies.DIF.RMT.PDUForwarding.QoSTable;

import rina.policies.DIF.RMT.PDUForwarding.IntPDUForwarding;

simple QoSTable like IntPDUForwarding
{
    parameters:
        @class(QoSTable::QoSTable);
        @display("i=block/socket");
        
        bool printAtEnd = default(false);
}
