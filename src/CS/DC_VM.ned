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
// This module describes a single VM in the DataCenter use-case.
// Servers can be owned by only one Tenant per time.
//
// Colors of the IPC reflect the use case layers.
// Link: https://wiki.ict-pristine.eu/wp2/d21/D21-Datnet-RINA

package rina.CS;

import rina.Common.Test;
import rina.DAF.ApplicationProcess;
import rina.DAF.DA.DIFAllocator;
import rina.DIF.IPCProcess;
import rina.DAF.IRM.IPCResourceManager;

module DC_VM
{
    parameters:
        @display("i=device/terminal;bgb=214,348");
        @node;

    gates:
        inout medium;

    submodules:
        AP: ApplicationProcess {
            @display("p=58,43");
        }

        difAllocator: DIFAllocator {
            @display("p=156,43;i=,grey");
        }

        ipcResourceManager: IPCResourceManager {
            @display("p=110,121");
        }

        TenantIPC: IPCProcess {
            @display("p=110,211;i=,#0080FF");
        }

        ShimIPC: IPCProcess {
            @display("p=110,293;i=,#800000");
        }

    connections allowunconnected:
        ShimIPC.southIo++ <--> medium;
        ShimIPC.northIo++ <--> TenantIPC.southIo++;
}
