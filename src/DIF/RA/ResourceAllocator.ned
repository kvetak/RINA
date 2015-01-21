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

import rina.policies.DIF.RA.QueueAlloc.IntQueueAlloc;
import rina.policies.DIF.RA.QueueIDGen.IntQueueIDGen;


module ResourceAllocator
{
    parameters:
        @display("i=block/segm;bgb=486,352");
        string queueAllocPolicyName = default("SingleQueue");
        string queueIdGenName = default("SingleID");

    submodules:
        pduForwardingTable: PDUForwardingTable {
            @display("p=60,60");
        }
        pduFwdTabGenerator: PDUFwdTabGenerator {
            @display("p=180,60");
        }
        ra: RA {
            @display("p=300,60");
        }
        nm1FlowTable: NM1FlowTable {
            @display("p=420,60");
        }

        queueAllocPolicy: <queueAllocPolicyName> like IntQueueAlloc {
            @display("p=60,163");
        }
        queueIdGenerator: <queueIdGenName> like IntQueueIDGen {
            @display("p=180,163");
        }
}
