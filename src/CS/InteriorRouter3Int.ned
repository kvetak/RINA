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

//
// <h1>Interior router simulation module with three interfaces</h1> 
//
// This models simulates interior router node that has four different rank DIFs:
//  * 1x (N)-DIF <i>relayIpc</i> is used as bridge between <i>ipcProccesses</i> for relaying 
//  * 3x (N-1)-DIF <i>ipcProccesses0/1/2</i> 
//
// It also contains <i>DIFAllocator</i> module as NameSpaceManager interface
//
// @author Vladimir Vesely (ivesely@fit.vutbr.cz), Tomas Hykel
// @date Last refactorized and documented on 2015-01-12


package rina.src.CS;

import rina.src.DAF.DA.DIFAllocator;
import rina.src.DIF.IPCProcess;


module InteriorRouter3Int
{
    @display("i=abstract/switch;bgb=282,267");
    @node;
    gates:
        inout medium[3];
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
        ipcProcess2: IPCProcess {
            @display("p=135,201");
        }
    connections allowunconnected:
        ipcProcess0.southIo++ <--> medium[0];
        ipcProcess1.southIo++ <--> medium[1];
        ipcProcess2.southIo++ <--> medium[2];
        relayIpc.southIo++ <--> ipcProcess0.northIo++;
        relayIpc.southIo++ <--> ipcProcess1.northIo++;
        relayIpc.southIo++ <--> ipcProcess2.northIo++;
}
