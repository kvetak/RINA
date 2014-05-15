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

package rina.DIF;

import rina.DIF.DFF.DirectoryForwardingTable;
import rina.DIF.FA.FlowAllocator;
import rina.DIF.RIB.RIBDaemon;
import rina.DIF.RMT.RMT;


module IPCProcess
{
    @display("bgb=492,307;i=misc/square,#FF8000,50");
    gates:
        inout rmtIo;
        inout appIo[];

    submodules:
        directoryForwardingTable: DirectoryForwardingTable {
            @display("p=378,116");
        }
        flowAllocator: FlowAllocator {
            @display("p=226,116");
        }
        rmt: RMT {
            @display("p=226,240");
        }
        ribDaemon: RIBDaemon {
            @display("p=85,116");
        }

    connections:
        rmt.rmtIo <--> rmtIo;

}
