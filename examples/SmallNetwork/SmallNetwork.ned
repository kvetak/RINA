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

package rina.examples.SmallNetwork;
import rina.CS.*;


network SmallNetwork
{
    @display("bgb=586,372");
    submodules:
        host1: Host1AP {
            @display("p=92,83");
        }
        host2: Host1AP {
            @display("p=92,252");
        }
        host3: Host1AP {
            @display("p=275,83");
        }
        host4: Host1AP {
            @display("p=473,83");
        }
        host5: Host1AP {
            @display("p=473,252");
        }
        router1: InteriorRouter3Int {
            @display("p=166,165");
        }
        router2: InteriorRouter3Int {
            @display("p=275,165");
        }
        router3: InteriorRouter3Int {
            @display("p=388,165");
        }

    connections:
        router1.medium[0] <--> host1.medium;
        router1.medium[1] <--> host2.medium;
        router1.medium[2] <--> router2.medium[0];
        router2.medium[1] <--> router3.medium[0];
        router2.medium[2] <--> host3.medium;
        router3.medium[1] <--> host4.medium;
        router3.medium[2] <--> host5.medium;

}
