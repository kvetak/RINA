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
import rina.src.CS.HostNAP;
import rina.src.Other.Infection.InfectedRouter;
import rina.src.Other.Infection.InfectedRouterGW;
import rina.src.CS.InteriorRouterNInt;

import rina.src.DAF.AE.AEConstant.AEConstantListener;

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
        A1: InfectedRouter {
            @display("p=54,42");
        }
        A2: InfectedRouter {
            @display("p=441,446");
        }
        A3: InfectedRouter {
            @display("p=775,36");
        }
        B1: InfectedRouter {
            @display("p=78,370");
        }
        B2: InfectedRouter {
            @display("p=395,105");
        }
        B3: InfectedRouter {
            @display("p=754,325");
        }

        ip1: HostNAP {
            @display("p=36,286");
        }
        ip2: HostNAP {
            @display("p=536,92");
        }
        ip3: HostNAP {
            @display("p=599,409");
        }
        ip4: HostNAP {
            @display("p=270,92");
        }
        hA1: HostNAP {
            @display("p=36,123");
        }
        hA2: HostNAP {
            @display("p=351,454");
        }
        hA3: HostNAP {
            @display("p=692,36");
        }
        hB1: HostNAP {
            @display("p=99,446");
        }
        hB2: HostNAP {
            @display("p=422,42");
        }
        hB3: HostNAP {
            @display("p=767,415");
        }

        listener: AEConstantListener {
            @display("p=240,415");
        }
    connections:
        r1.medium++ <--> DatarateChannel{datarate=5.0Gbps;} <--> r2.medium++;
        r1.medium++ <--> DatarateChannel{datarate=3.0Gbps;} <--> r3.medium++;
        r1.medium++ <--> DatarateChannel{datarate=10.0Gbps;} <--> r6.medium++;
        r2.medium++ <--> DatarateChannel{datarate=2.5Gbps;} <--> r3.medium++;
        r2.medium++ <--> DatarateChannel{datarate=7.0Gbps;} <--> r5.medium++;
        r3.medium++ <--> DatarateChannel{datarate=5.0Gbps;} <--> r4.medium++;
        r4.medium++ <--> DatarateChannel{datarate=5.0Gbps;} <--> r5.medium++;
        r4.medium++ <--> DatarateChannel{datarate=7.0Gbps;} <--> r6.medium++;
        r5.medium++ <--> DatarateChannel{datarate=8.5Gbps;} <--> r7.medium++;
        r6.medium++ <--> DatarateChannel{datarate=5.0Gbps;} <--> r7.medium++;
        r6.medium++ <--> DatarateChannel{datarate=11.0Gbps;} <--> r8.medium++;
        r7.medium++ <--> DatarateChannel{datarate=9.0Gbps;} <--> r9.medium++;
        r8.medium++ <--> DatarateChannel{datarate=3.5Gbps;} <--> r9.medium++;
        r8.medium++ <--> DatarateChannel{datarate=6.0Gbps;} <--> ra.medium++;
        r9.medium++ <--> DatarateChannel{datarate=4.0Gbps;} <--> ra.medium++;

        A1.medium++ <--> DatarateChannel{datarate=3.0Gbps;} <--> r1.mediumGW;
        B1.medium++ <--> DatarateChannel{datarate=3.0Gbps;} <--> r2.mediumGW;
        A2.medium++ <--> DatarateChannel{datarate=3.0Gbps;} <--> r5.mediumGW;
        B2.medium++ <--> DatarateChannel{datarate=3.0Gbps;} <--> r4.mediumGW;
        B3.medium++ <--> DatarateChannel{datarate=3.0Gbps;} <--> r9.mediumGW;
        A3.medium++ <--> DatarateChannel{datarate=3.0Gbps;} <--> ra.mediumGW;

        ip1.medium <--> DatarateChannel{datarate=3.0Gbps;} <--> r2.medium++;
        ip2.medium <--> DatarateChannel{datarate=3.0Gbps;} <--> r8.medium++;
        ip3.medium <--> DatarateChannel{datarate=3.0Gbps;} <--> r7.medium++;
        ip4.medium <--> DatarateChannel{datarate=3.0Gbps;} <--> r3.medium++;

        hA1.medium <--> DatarateChannel{datarate=3.0Gbps;} <--> A1.medium++;
        hA2.medium <--> DatarateChannel{datarate=3.0Gbps;} <--> A2.medium++;
        hA3.medium <--> DatarateChannel{datarate=3.0Gbps;} <--> A3.medium++;

        hB1.medium <--> DatarateChannel{datarate=3.0Gbps;} <--> B1.medium++;
        hB2.medium <--> DatarateChannel{datarate=3.0Gbps;} <--> B2.medium++;
        hB3.medium <--> DatarateChannel{datarate=3.0Gbps;} <--> B3.medium++;
}
