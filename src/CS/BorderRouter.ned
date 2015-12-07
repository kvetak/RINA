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
// <h1>BorderRouter simulation module</h1> 
//
// This models simulates border router node that has five different rank DIFs:
//  * 1x (N+1)-DIF <i>relayIpc</i> is used as bridge between <i>ipcProccesses</i> for relaying
//  * 3x (N)-DIF <i>ipcProcess1/2/3</i> 
//  * 1x (N-1)-DIF <i>bottomIpc</i> 
//
// It also contains <i>DIFAllocator</i> module as NameSpaceManager interface
//
// @author Vladimir Vesely (ivesely@fit.vutbr.cz)
// @date Last refactorized and documented on 2015-01-12

package rina.CS;

import rina.DAF.DA.DIFAllocator;
import rina.DIF.IPCProcess;

module BorderRouter
{
    @display("i=abstract/router;bgb=281,341");
    @node;
    gates:
        inout medium[3];
    submodules:
        ipcProcess1: IPCProcess {
            @display("p=66,160");
        }
        ipcProcess2: IPCProcess {
            @display("p=223,160");
        }
        bottomIpc: IPCProcess {
            @display("p=146,280;i=,#FF4000");
        }
        relayIpc: IPCProcess {
            @display("p=146,39;i=,#FFB000");
            relay = true;
        }
        ipcProcess3: IPCProcess {
            @display("p=146,192");
        }
        difAllocator: DIFAllocator {
            @display("p=66,39");
        }
    connections:
        ipcProcess1.southIo++ <--> medium[0];
        ipcProcess2.southIo++ <--> medium[1];
        bottomIpc.southIo++ <--> medium[2];
        relayIpc.southIo++ <--> ipcProcess1.northIo++;
        relayIpc.southIo++ <--> ipcProcess2.northIo++;
        relayIpc.southIo++ <--> ipcProcess3.northIo++;
        ipcProcess3.southIo++ <--> bottomIpc.northIo++;
}
