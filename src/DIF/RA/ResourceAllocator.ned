//
// The MIT License (MIT)
//
// Copyright (c) 2014-2016 Brno University of Technology, PRISTINE project
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.

package rina.src.DIF.RA;

import rina.policies.DIF.RA.QueueAlloc.IntRAQueueAlloc;
import rina.policies.DIF.RA.QueueIDGen.IntRAQueueIDGen;
import rina.policies.DIF.RA.AddressComparator.IntAddressComparator;
import rina.src.DIF.RA.PDUFG.IntPDUFG;


module ResourceAllocator
{
    parameters:
        @display("i=block/segm;bgb=503,223");
        string queueAllocPolicyName = default("SingleQueue");
        string pduftType = default("SimplePDUForwardingTable");
        string pdufgPolicyName = default("StaticGenerator");
        string queueIdGenName = default("SingleID");
        string addrComparatorName = default("ExactMatch");

		bool onWire = default(false);

    submodules:
        ra: RA {
            @display("p=69,55");
            onWire = onWire;
        }
        nm1FlowTable: NM1FlowTable {
            @display("p=189,55");
        }
        pduFwdGenerator: <pdufgPolicyName> like IntPDUFG {
            @display("p=69,150");
        }
        queueAllocPolicy: <queueAllocPolicyName> like IntRAQueueAlloc {
            @display("p=189,150");
        }
        queueIdGenerator: <queueIdGenName> like IntRAQueueIDGen {
            @display("p=309,150");
        }
        addressComparator: <addrComparatorName> like IntAddressComparator {
            @display("p=429,150");
        }
}
