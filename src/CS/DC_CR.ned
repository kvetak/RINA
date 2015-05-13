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

// Author: Kewin Rausch <kewin.rausch@create-net.org>
//
// NOTES:
// This module describes a cluster/core router in the DataCenter use-case.
// This router support the case 
//
// Colors of the IPC reflect the use case layers.
// Link: https://wiki.ict-pristine.eu/wp2/d21/D21-Datnet-RINA

package rina.src.CS;

import rina.src.Common.Test;
import rina.src.DAF.DA.DIFAllocator;
import rina.src.DIF.IPCProcess;

module DC_CR
{
    parameters:
        @display("i=abstract/router;bgb=294,396");
        @node;

        int nofInt = default(1);

    gates:
        // Types of gates out:
        // 0 - to/from the internet.
        // 1 to N - to/from the DC internals.
        inout medium[nofInt];

    submodules:
        difAllocator: DIFAllocator {
            @display("p=148,44;i=,grey");
        }

        TenantIPC: IPCProcess {
            @display("p=148,121;i=,#0080FF");
        }

        ShimIPC[nofInt]: IPCProcess {
            @display("p=74,313;i=,#800000");
        }

		// Should provide some sort of translation between TCP/IP and
		// Rina technologies. 
        DCIPC: IPCProcess {
            @display("p=74,214;i=,#008000");
        }

    connections allowunconnected:

        for i=0..nofInt-1 {
            ShimIPC[i].northIo++ <--> DCIPC.southIo++;
            ShimIPC[i].southIo++ <--> medium[i];
        }

        DCIPC.northIo++ <--> TenantIPC.southIo++;
}
