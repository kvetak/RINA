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
// This module describes a Top of Rack module in the DataCenter use-case.
//
// Colors of the IPC reflect the use case layers.
// Link: https://wiki.ict-pristine.eu/wp2/d21/D21-Datnet-RINA

package rina.CS;

import rina.DAF.DA.DIFAllocator;
import rina.DIF.IPCProcess;

module DC_TOR
{
    @display("i=abstract/switch;bgb=177,325");
    @node;

    int nofInt = default(1);

    gates:
        inout medium[nofInt];

    submodules:
        ShimIPC[nofInt]: IPCProcess {
            @display("p=90,255;i=,#800000");
        }
        DCIPC: IPCProcess {
            @display("p=90,151;i=,#008000");
            relay = true;
        }
        difAllocator: DIFAllocator {
            @display("p=90,63;i=,grey");
        }
    connections allowunconnected:

        // Every IPC Process is connected to its medium and the Relay IPC.
        for i=0..nofInt-1 {
            DCIPC.southIo++ <--> ShimIPC[i].northIo++;
            ShimIPC[i].southIo++ <--> medium[i];
        }
}
