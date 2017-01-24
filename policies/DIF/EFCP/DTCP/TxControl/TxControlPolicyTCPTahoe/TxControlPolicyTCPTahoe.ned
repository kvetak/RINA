//
// Copyright © 2014 PRISTINE Consortium (http://ict-pristine.eu)
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
// 

package rina.policies.DIF.EFCP.DTCP.TxControl.TxControlPolicyTCPTahoe;
import rina.policies.DIF.EFCP.DTCP.TxControl.IntTxControlPolicy;

simple TxControlPolicyTCPTahoe
{
    parameters:
        @display("i=block/socket");
        string policyName = "TCP Tahoe";
        int packetSize = default(536);

        @signal[TCP_Tahoe_CWND](type=double);
        @statistic[TCP-Tahoe-CWND](title="TCP Tahoe CWND"; source=TCP_Tahoe_CWND; record=vector, mean);
}
