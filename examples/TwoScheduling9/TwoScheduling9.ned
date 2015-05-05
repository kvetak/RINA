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

package rina.examples.TwoScheduling9;

import ned.DatarateChannel;
import rina.CS.HostNAP;
import rina.CS.InteriorRouter2Int;


network TwoScheduling9
{
    @display("bgb=325,196");
    submodules:
        host1: HostNAP {
            @display("p=82,92");
        }
        host2: HostNAP {
            @display("p=231,92");
        }
        router: InteriorRouter2Int {
            @display("p=154,121");
        }
    connections allowunconnected:
        host1.medium <--> DatarateChannel{datarate = 5 Gbps;} <--> router.medium[0];
        host2.medium <--> DatarateChannel{datarate = 5 Gbps;} <--> router.medium[1];
}
