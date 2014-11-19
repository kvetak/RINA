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

package rina.CS;

import rina.DAF.DA.DIFAllocator;
import rina.DIF.IPCProcess;


module InteriorRouter2Int
{
    @display("i=abstract/switch;bgb=282,227");
    @node;
    gates:
        inout medium[2];
    submodules:
        ipcProcess0: IPCProcess {
            @display("p=65,145");
        }
        ipcProcess1: IPCProcess {
            @display("p=205,145");
        }
        relayIpc: IPCProcess {
            @display("p=135,53;i=,#FFB000");
            relay = true;
        }
        difAllocator: DIFAllocator {
            @display("p=65,53");
        }
    connections:
        ipcProcess0.southIo++ <--> medium[0];
        ipcProcess1.southIo++ <--> medium[1];
        relayIpc.southIo++ <--> ipcProcess0.northIo++;
        relayIpc.southIo++ <--> ipcProcess1.northIo++;
}
