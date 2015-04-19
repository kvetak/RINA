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
// This module describes a single server in the DataCenter use-case.
// Servers can be reached by multiple Tenants.
//
// Colors of the IPC reflect the use case layers.
// Link: https://wiki.ict-pristine.eu/wp2/d21/D21-Datnet-RINA

package rina.src.CS;

import rina.src.Common.Test;
import rina.src.DAF.ApplicationProcess;
import rina.src.DAF.DA.DIFAllocator;
import rina.src.DIF.IPCProcess;

module DC_Server
{
    parameters:
        @display("i=device/server;bgb=294,396");
        @node;

        int nofVM = default(1);

    gates:
        // Two gates out:
        // - 0 is TOR side medium.
        // - 1 to N are VM side mediums.
        inout medium[nofVM + 1];

    submodules:
        difAllocator: DIFAllocator {
            @display("p=148,44;i=,grey");
        }

        TenantIPC: IPCProcess {
            @display("p=148,121;i=,#0080FF");
        }

        VMShimIPC[nofVM]: IPCProcess {
            @display("p=73,213;i=,#800000");
        }

        ShimIPC: IPCProcess {
            @display("p=214,313;i=,#800000");
        }

        DCIPC: IPCProcess {
            @display("p=214,213;i=,#008000");
        }

    connections allowunconnected:

        for i=0..nofVM-1 {
            VMShimIPC[i].northIo++ <--> TenantIPC.southIo++;
            VMShimIPC[i].southIo++ <--> medium[i + 1];
        }

        // Static configuration for the connections.
        //
        DCIPC.northIo++ <--> TenantIPC.southIo++;
        DCIPC.southIo++ <--> ShimIPC.northIo++;
        ShimIPC.southIo++ <--> medium[0];
}
