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

package rina.examples.Athens.Whatevercast;

import ned.DatarateChannel;
import rina.src.CS.Host1AP;
import rina.src.CS.Host1APNInt;
import rina.src.CS.InteriorRouterNInt;

network Whatevercast
{
    submodules:
        Switch0: InteriorRouterNInt {
            numOfInterfaces = 2;
            @display("p=231,90");
        }
        Switch1: InteriorRouterNInt {
            numOfInterfaces = 2;
            @display("p=231,274");
        }
        Switch2: InteriorRouterNInt {
            numOfInterfaces = 2;            
            @display("p=231,179");
        }
        HostA: Host1APNInt {
            @display("p=57,179");
            numOfInterfaces = 3;
        }
        HostB: Host1APNInt {
            @display("p=388,179");
            numOfInterfaces = 3;
        }
    connections:
        HostA.medium[0] <--> DatarateChannel {  datarate = 100Mbps; delay = 100us; ber = 0; } <--> Switch0.medium[0];
        HostA.medium[1] <--> DatarateChannel {  datarate = 100Mbps; delay = 100us; ber = 0; } <--> Switch1.medium[0];
        HostA.medium[2] <--> DatarateChannel {  datarate = 100Mbps; delay = 100us; ber = 0; } <--> Switch2.medium[0];
        Switch0.medium[1] <--> DatarateChannel {  datarate = 100Mbps; delay = 100us; ber = 0; } <--> HostB.medium[0];
        Switch1.medium[1] <--> DatarateChannel {  datarate = 100Mbps; delay = 100us; ber = 0; } <--> HostB.medium[1];
        Switch2.medium[1] <--> DatarateChannel {  datarate = 100Mbps; delay = 100us; ber = 0; } <--> HostB.medium[2];
}
