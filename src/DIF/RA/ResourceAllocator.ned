//
// Copyright © 2014 - 2015 PRISTINE Consortium (http://ict-pristine.eu)
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

package rina.src.DIF.RA;

import rina.policies.DIF.RA.QueueAlloc.IntRAQueueAlloc;
import rina.policies.DIF.RA.QueueIDGen.IntRAQueueIDGen;
import rina.policies.DIF.RA.AddressComparator.IntAddressComparator;
import rina.policies.DIF.RA.PDUFG.IntPDUFG;


module ResourceAllocator
{
    parameters:
        @display("i=block/segm;bgb=470,352");
        string queueAllocPolicyName = default("SingleQueue");
        string pduftType = default("SimplePDUForwardingTable");
        string pdufgPolicyName = default("StaticGenerator");
        string queueIdGenName = default("SingleID");
        string addrComparatorName = default("ExactMatch");

    submodules:
        ra: RA {
            @display("p=55,55");
        }
        nm1FlowTable: NM1FlowTable {
            @display("p=175,55");
        }
        pduFwdGenerator: <pdufgPolicyName> like IntPDUFG {
            @display("p=55,150");
        }
        queueAllocPolicy: <queueAllocPolicyName> like IntRAQueueAlloc {
            @display("p=175,150");
        }
        queueIdGenerator: <queueIdGenName> like IntRAQueueIDGen {
            @display("p=295,150");
        }
        addressComparator: <addrComparatorName> like IntAddressComparator {
            @display("p=415,150");
        }
}
