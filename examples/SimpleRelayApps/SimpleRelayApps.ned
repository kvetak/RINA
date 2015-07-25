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

package rina.examples.SimpleRelayApps;
import ned.DatarateChannel;
import rina.src.CS.Host1AP;
import rina.src.CS.InteriorRouter2Int;


network SimpleRelayApps
{
    @display("bgb=368,202");
    submodules:
        host1: Host1AP {
            @display("p=70,101");
        }
        interiorRouter: InteriorRouter2Int {
            @display("p=180,101");
        }
        host2: Host1AP {
            @display("p=290,101");
        }
    connections allowunconnected:
        host1.medium  <--> DatarateChannel {datarate = 100Mbps; delay = 100us; ber = 0; } <--> interiorRouter.medium++;
        host2.medium  <--> DatarateChannel {datarate = 100Mbps; delay = 100us; ber = 0; } <--> interiorRouter.medium++;
}
