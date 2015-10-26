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

package rina.examples.Congestion.CoreNet;


import ned.DatarateChannel;
import rina.src.Other.Infection.InfectedRouter;
import rina.src.CS.InteriorRouterNInt;

network CoreNet
{
    submodules:
        r1: InfectedRouter {
            @display("p=108,100");
        }
        r2: InfectedRouter {
            @display("p=219,100");
        }
        r3: InfectedRouter {
            @display("p=277,186");
        }
        r4: InfectedRouter {
            @display("p=186,265");
        }
        r5: InfectedRouter {
            @display("p=77,232");
        }

    connections:
        r1.medium++ <--> DatarateChannel{datarate=100Mbps;} <--> r2.medium++;
        r2.medium++ <--> DatarateChannel{datarate=100Mbps;}  <--> r3.medium++;
        r3.medium++ <--> DatarateChannel{datarate=100Mbps;}  <--> r4.medium++;
        r4.medium++ <--> DatarateChannel{datarate=100Mbps;}  <--> r5.medium++;
}
