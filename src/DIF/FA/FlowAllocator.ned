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

package rina.DIF.FA;

import rina.DIF.NSM.NameSpaceManager;


module FlowAllocator
{
    parameters:
        @display("i=block/fork;bgb=590,410");
        //int maxFaiLimit = default(1);
    gates:
        inout appIo[];
        inout efcpIo[];
    submodules:
        fa: FA {
            @display("p=114,84");
        }
        //fai[maxFaiLimit]: FAI {
        //    @display("p=227,84");
        // }

        nameSpaceManager: NameSpaceManager {
            @display("p=447,84");
        }
        faiTable: FAITable {
            @display("p=283,84");
        }
    connections:

        fa.irmIo <--> appIo++;
}
