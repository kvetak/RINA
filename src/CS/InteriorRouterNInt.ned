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

package rina.CS;

import rina.DAF.DA.DIFAllocator;
import rina.DIF.IPCProcess;

module InteriorRouterNInt
{
    @display("i=abstract/switch;bgb=206,325");
    @node;
    
    gates:
        inout medium[];

    submodules:
        ipcProcess[sizeof(medium)]: IPCProcess {
            @display("p=104,245");
        }
        relayIpc: IPCProcess {
            @display("p=104,141;i=,#FFB000");
            relay = true;
        }
        difAllocator: DIFAllocator {
            @display("p=104,53");
        }
    connections allowunconnected:

        // Every IPC Process is connected to its medium and the Relay IPC.
        for i=0..sizeof(medium)-1 {
            relayIpc.southIo++ <--> ipcProcess[i].northIo++;
            ipcProcess[i].southIo++ <--> medium[i];
        }
}
