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

import rina.DAF.RelayingProcess;
import rina.DIF.IPCProcess;


module InteriorRouter
{
    @display("i=abstract/switch;bgb=282,227");
    gates:
        inout medium[];
    submodules:
        relayingProcess: RelayingProcess {
            @display("p=138,51");
        }
        ipcProcess1: IPCProcess {
            @display("p=65,145");
        }
        ipcProcess2: IPCProcess {
            @display("p=205,145");
        }
    connections:
        relayingProcess.southIo++ <--> ipcProcess1.northIo++;
        relayingProcess.southIo++ <--> ipcProcess2.northIo++;
        ipcProcess1.southIo <--> medium++;
        ipcProcess2.southIo <--> medium++;
}
