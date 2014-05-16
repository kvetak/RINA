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


module BorderRouter
{
    @display("i=abstract/router;bgb=272,341");
    gates:
        inout medium[];
    submodules:
        relayingProcess: RelayingProcess {
            @display("p=141,50");
        }
        ipcProcess1: IPCProcess {
            @display("p=66,160");
        }
        ipcProcess2: IPCProcess {
            @display("p=206,157");
        }
        ipcProcess3: IPCProcess {
            @display("p=206,266");
        }
    connections:
        relayingProcess.southIo++ <--> ipcProcess1.northIo++;
        relayingProcess.southIo++ <--> ipcProcess2.northIo++;
        ipcProcess2.southIo <--> ipcProcess3.northIo++;
        ipcProcess3.southIo <--> medium++;
        ipcProcess1.southIo <--> medium++;
}
