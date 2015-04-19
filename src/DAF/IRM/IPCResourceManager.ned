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

package rina.src.DAF.IRM;

module IPCResourceManager
{
    parameters:
        @display("i=misc/node2,#0080C0;bgb=281,170");

    gates:
        //Dynamically created
        inout northIo[];
		//inout southIo_;

    submodules:
        irm: IRM {
            @display("p=82,83");
        }
        connectionTable: ConnectionTable {
            @display("p=197,83");
        }

    connections allowunconnected:
}
