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
    @display("bgb=621,378");
    submodules:
        host1: Host1AP {
            @display("p=72,166");
        }
        host2: Host1AP {
            @display("p=226,95");
        }
        host3: Host1AP {
            @display("p=231,251");
        }
        host4: Host1AP {
            @display("p=394,98");
        }
        host5: Host1AP {
            @display("p=393,253");
        }
        router1: InteriorRouter3Int {
            @display("p=174,165");
        }
        router2: InteriorRouter3Int {
            @display("p=305,166");
        }
    connections allowunconnected:
        host1.medium <--> router1.medium++;
        router1.medium++ <--> host2.medium;
        router1.medium++ <--> host3.medium;
        router2.medium++ <--> host4.medium;
        router2.medium++ <--> host5.medium;
        router1.medium++ <--> router2.medium++;
}
