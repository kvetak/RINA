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

package rina.DIF.RA;

import rina.DIF.RA.policies.QueueAlloc.IntQueueAlloc;
import rina.DIF.RA.policies.Forwarding.IntPDUFTGPolicy;

module ResourceAllocator
{
    parameters:
        @display("i=block/segm;bgb=299,274");
        string queueAllocPolicyName = default("SingleQueue");
        string pduftgPolicyName = default("StaticRoutingPolicy");

    submodules:
        ra: RA {
            @display("p=70,60");
        }
        pduFwdTabGenerator: PDUFwdTabGenerator {
            @display("p=70,130");
        }
        pduForwardingTable: PDUForwardingTable {
            @display("p=70,200");
        }
        flowTable: FlowTable {
            @display("p=150,60");
        }
        queueAllocPolicy: <queueAllocPolicyName> like IntQueueAlloc {
            @display("p=230,60");
        }
        PDUFTGPolicy: <pduftgPolicyName> like IntPDUFTGPolicy {
            @display("p=230,130");
        }
}
