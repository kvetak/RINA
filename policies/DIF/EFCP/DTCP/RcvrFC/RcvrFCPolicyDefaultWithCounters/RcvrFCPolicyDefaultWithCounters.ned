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

package rina.policies.DIF.EFCP.DTCP.RcvrFC.RcvrFCPolicyDefaultWithCounters;

import rina.policies.DIF.EFCP.DTCP.RcvrFC.IntRcvrFCPolicy;


//
// TODO auto-generated type
//
simple RcvrFCPolicyDefaultWithCounters like IntRcvrFCPolicy
{
    parameters:
        string policyName = "RcvrFC Default with counters";
        @display("i=block/socket");
        
        @signal[packets_received](type=unsigned long);
        @statistic[packets-received](title="Number os packets received"; source=packets_received; record=last);
        
        @signal[goodput](type=unsigned long);
        @statistic[goodput](title="Goodput"; source=goodput; record=vector);
}
