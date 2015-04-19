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

package rina.src.CS;

import rina.src.DAF.DA.DIFAllocator;
import rina.src.DIF.IPCProcess;


module InteriorRouter4Int
{
    @display("i=abstract/switch;bgb=396,371");
    @node;
    gates:
        inout medium[4];
    submodules:
        ipcProcess0: IPCProcess {
            @display("p=93,147");
        }
        ipcProcess1: IPCProcess {
            @display("p=327,147");
        }
        relayIpc: IPCProcess {
            @display("p=209,215;i=,#FFB000");
            relay = true;
        }
        difAllocator: DIFAllocator {
            @display("p=65,53");
        }
        ipcProcess2: IPCProcess {
            @display("p=93,274");
        }
        ipcProcess3: IPCProcess {
            @display("p=327,274");
        }
    connections allowunconnected:
        ipcProcess0.southIo++ <--> medium[0];
        ipcProcess1.southIo++ <--> medium[1];
        ipcProcess2.southIo++ <--> medium[2];
        ipcProcess3.southIo++ <--> medium[3];
        relayIpc.southIo++ <--> ipcProcess0.northIo++;
        relayIpc.southIo++ <--> ipcProcess1.northIo++;
        relayIpc.southIo++ <--> ipcProcess2.northIo++;
        relayIpc.southIo++ <--> ipcProcess3.northIo++;
}
