package rina.policies.DIF.RMT.PDUForwarding.SimpleTable;

import rina.policies.DIF.RMT.PDUForwarding.IntPDUForwarding;

simple SimpleTable like IntPDUForwarding
{
    parameters:
        @class(SimpleTable::SimpleTable);
        @display("i=block/socket");
    	@signal[PDUFT_Length](type="long");
    	@statistic[pduft-length](title="PDUFT Size"; source=PDUFT_Length; record=vector);
    	
    	
        bool printAtEnd = default(false);
}
