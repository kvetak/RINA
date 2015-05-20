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

// Author: Sergio Leon Gaixas

package rina.src.CS;

import rina.src.DAF.DA.DIFAllocator;
import rina.src.DIF.IPCProcess;

module InteriorRouterNMInt
{
    @display("i=abstract/switch;bgb=579,325");
    @node;

    gates:
        inout mediumIntra[];
        inout mediumInter[];

    submodules:
        intraIpc[sizeof(mediumIntra)]: IPCProcess {
            @display("p=160,231");
        }
        interIpc[sizeof(mediumInter)]: IPCProcess {
            @display("p=422,231");
        }
        relayIpc: IPCProcess {
            @display("p=280,141;i=,#FFB000");
            relay = true;
        }
        difAllocator: DIFAllocator {
            @display("p=104,53");
        }
    connections allowunconnected:

        // Every IPC Process is connected to its medium and the Relay IPC.
        for i=0..sizeof(mediumIntra)-1 {
            relayIpc.southIo++ <--> intraIpc[i].northIo++;
            intraIpc[i].southIo++ <--> mediumIntra[i];
        }
        for i=0..sizeof(mediumInter)-1 {
            relayIpc.southIo++ <--> interIpc[i].northIo++;
            interIpc[i].southIo++ <--> mediumInter[i];
        }
}
