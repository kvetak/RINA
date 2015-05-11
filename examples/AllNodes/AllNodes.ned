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

package rina.examples.AllNodes;

import rina.src.CS.BorderRouter;
import rina.src.CS.Host1AP;
import rina.src.CS.InteriorRouterNInt;


//
// TODO Auto-generated network
//
network AllNodes
{
    @display("bgb=527,319");
    submodules:
        BorderRouterA: BorderRouter {
            @display("p=139,143");
        }
        BorderRouterB: BorderRouter {
            @display("p=371,143");
        }
        HostA1: Host1AP {
            @display("p=41,50");
        }
        HostA2: Host1AP {
            @display("p=41,243");
        }
        HostB1: Host1AP {
            @display("p=478,60");
        }
        HostB2: Host1AP {
            @display("p=478,243");
        }
        InteriorRouter: InteriorRouterNInt {
            @display("p=251,143");
        }
    connections:
        HostA1.medium <--> BorderRouterA.medium[0];
        HostA2.medium <--> BorderRouterA.medium[1];
        BorderRouterA.medium[2] <--> InteriorRouter.medium++;
        BorderRouterB.medium[2] <--> InteriorRouter.medium++;
        HostB1.medium <--> BorderRouterB.medium[0];
        HostB2.medium <--> BorderRouterB.medium[1];
}
