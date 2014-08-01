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

import rina.DIF.IPCProcess;


module InteriorRouter
{
    @display("i=abstract/switch;bgb=282,227");
    @node;
    gates:
        inout medium[];
    submodules:
        ipcProcess1: IPCProcess {
            @display("p=65,145");
        }
        ipcProcess2: IPCProcess {
            @display("p=205,145");
        }
        ipcProcess0: IPCProcess {
            @display("p=135,48;i=,#FFB000");
        }
    connections allowunconnected:
        ipcProcess0.southIo++ <--> ipcProcess1.northIo++;
        ipcProcess0.southIo++ <--> ipcProcess2.northIo++;
        ipcProcess1.southIo++ <--> medium++;
        ipcProcess2.southIo++ <--> medium++;
}
