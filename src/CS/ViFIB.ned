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

package rina.src.CS;

import rina.src.DAF.DA.DIFAllocator;
import rina.src.DIF.IPCProcess;
import rina.src.DAF.ApplicationProcess;
import rina.src.DAF.IRM.IPCResourceManager;

module ViFIB
{
    parameters:
        @display("i=abstract/switch;bgb=355,537");
        @node;
        int numOfAdminAPs = default(1);

    gates:
        inout medium[];

    submodules:
        adminApps[numOfAdminAPs]: ApplicationProcess {
            @display("p=186,34;i=,#FF7000");
        }

        ipcProcess[sizeof(medium)]: IPCProcess {
            @display("p=165,467");
        }
        relayIpc: IPCProcess {
            @display("p=165,361;i=,#FFB000");
            relay = true;
        }

        vifibIpc: IPCProcess {
            @display("p=129,197;i=,#0085FF");
            relay = true;
        }
        vifibBorderIpc: IPCProcess {
            @display("p=237,256;i=,#002DFF");
            relay = true;
        }

        difAllocator: DIFAllocator {
            @display("p=285,94");
        }
        ipcResourceManager: IPCResourceManager {
            @display("p=90,94");
        }
    connections allowunconnected:

        // Every IPC Process is connected to its medium and the Relay IPC.
        for i=0..sizeof(medium)-1 {
            relayIpc.southIo++ <--> ipcProcess[i].northIo++;
            ipcProcess[i].southIo++ <--> medium[i];
        }
        vifibBorderIpc.southIo++ <--> relayIpc.northIo++;
        vifibIpc.southIo++ <--> relayIpc.northIo++;
        vifibIpc.southIo++ <--> vifibBorderIpc.northIo++;
}
