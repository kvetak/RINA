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
import rina.src.Other.Infection.InfectedRouterGW;
import rina.src.CS.InteriorRouterNInt;

network CoreNet
{
    @display("bgb=838,510");
    submodules:
        r1: InfectedRouterGW {
            @display("p=117,112");
        }
        r2: InfectedRouterGW {
            @display("p=156,301");
        }
        r3: InfectedRouter {
            @display("p=215,202");
        }
        r4: InfectedRouterGW {
            @display("p=395,231");
        }
        r5: InfectedRouterGW {
            @display("p=441,364");
        }
        r6: InfectedRouter {
            @display("p=518,192");
        }
        r7: InfectedRouter {
            @display("p=599,311");
        }
        r8: InfectedRouter {
            @display("p=629,131");
        }
        r9: InfectedRouterGW {
            @display("p=715,221");
        }
        ra: InfectedRouterGW {
            @display("p=767,105");
        }
        A1: InteriorRouterNInt {
            @display("p=54,42");
        }
        A2: InteriorRouterNInt {
            @display("p=441,446");
        }
        A3: InteriorRouterNInt {
            @display("p=775,36");
        }
        B1: InteriorRouterNInt {
            @display("p=78,370");
        }
        B2: InteriorRouterNInt {
            @display("p=395,105");
        }
        B3: InteriorRouterNInt {
            @display("p=754,325");
        }
    connections:
        r1.medium++ <--> DatarateChannel <--> r2.medium++;
        r1.medium++ <--> DatarateChannel <--> r3.medium++;
        r1.medium++ <--> DatarateChannel <--> r6.medium++;
        r2.medium++ <--> DatarateChannel <--> r3.medium++;
        r2.medium++ <--> DatarateChannel <--> r5.medium++;
        r3.medium++ <--> DatarateChannel <--> r4.medium++;
        r4.medium++ <--> DatarateChannel <--> r5.medium++;
        r4.medium++ <--> DatarateChannel <--> r6.medium++;
        r5.medium++ <--> DatarateChannel <--> r7.medium++;
        r6.medium++ <--> DatarateChannel <--> r7.medium++;
        r6.medium++ <--> DatarateChannel <--> r8.medium++;
        r7.medium++ <--> DatarateChannel <--> r9.medium++;
        r8.medium++ <--> DatarateChannel <--> r9.medium++;
        r8.medium++ <--> DatarateChannel <--> ra.medium++;
        r9.medium++ <--> DatarateChannel <--> ra.medium++;

        A1.medium++ <--> DatarateChannel <--> r1.mediumGW;
        B1.medium++ <--> DatarateChannel <--> r2.mediumGW;
        A2.medium++ <--> DatarateChannel <--> r5.mediumGW;
        B2.medium++ <--> DatarateChannel <--> r4.mediumGW;
        B3.medium++ <--> DatarateChannel <--> r9.mediumGW;
        A3.medium++ <--> DatarateChannel <--> ra.mediumGW;
}
