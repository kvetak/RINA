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

package rina.examples.Routing.UnreliableLinks;

import ned.DatarateChannel;
import rina.src.CS.Host1AP;
import rina.src.CS.InteriorRouterNInt;


network UnreliableLinks
{
    @display("bgb=500,511");
    submodules:
        r1: InteriorRouterNInt {
            @display("p=238,159");
        }
        r2: InteriorRouterNInt {
            @display("p=143,256");
        }
        r3: InteriorRouterNInt {
            @display("p=238,348");
        }
        r4: InteriorRouterNInt {
            @display("p=328,256");
        }
        h1: Host1AP {
            @display("p=238,72");
        }
        h2: Host1AP {
            @display("p=64,256");
        }
        h3: Host1AP {
            @display("p=238,426");
        }
        h4: Host1AP {
            @display("p=405,256");
        }
    connections:
        h1.medium <--> DatarateChannel{datarate=100Mbps;} <--> r1.medium++;
        h2.medium <--> DatarateChannel{datarate=100Mbps;} <--> r2.medium++;
        h3.medium <--> DatarateChannel{datarate=100Mbps;} <--> r3.medium++;
        h4.medium <--> DatarateChannel{datarate=100Mbps;} <--> r4.medium++;
        
        r1.medium++ <--> DatarateChannel{datarate=200Mbps; per=0.01;} <--> r2.medium++;
        r2.medium++ <--> DatarateChannel{datarate=200Mbps; per=0.01;}  <--> r3.medium++;
        r3.medium++ <--> DatarateChannel{datarate=200Mbps; per=0.01;}  <--> r4.medium++;
        r4.medium++ <--> DatarateChannel{datarate=200Mbps; per=0.01;}  <--> r1.medium++;
        
}
