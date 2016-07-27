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

module Switch
{
    parameters:
        @display("i=abstract/switch;bgb=355,325");
        @node;

    gates:
        inout medium[];

    submodules:
        ipcProcess0[sizeof(medium)]: IPCProcess {
            @display("p=186,242");
        }
        ipcProcess1: IPCProcess {
            @display("p=186,157;i=,#FFB000");
            relay = true;
        }
        difAllocator: DIFAllocator {
            @display("p=285,94");
        }
        ipcResourceManager: IPCResourceManager {
            @display("p=90,94");
        }
    connections allowunconnected:
        for i=0..sizeof(medium)-1 {
            ipcProcess1.southIo++ <--> ipcProcess0[i].northIo++;
            ipcProcess0[i].southIo++ <--> medium[i];
        }
}
