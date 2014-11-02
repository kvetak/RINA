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

package rina.DIF.RMT;

module RMTModule
{
    @display("i=block/classifier;bgb=590,145");
    gates:
        inout southIo[];
        inout efcpIo[];
        inout ribdIo;

    submodules:
        rmt: RMT {
            @display("p=55,55");
        }
        rmtQueueManager: RMTQueueManager {
            @display("p=543,53");
        }


    connections allowunconnected:
        ribdIo <--> rmt.ribdIo;
}
