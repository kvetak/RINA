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

package rina.examples.Congestion.BB;


import ned.DatarateChannel;
import rina.src.Other.Infection.T2InfectedRouter;
import rina.src.Other.Infection.IListener;

import rina.src.Other.Infection.IListener;
import rina.src.DAF.AE.AEConstant.AEConstantListener;

network BB
{
    @display("bgb=838,510");
    submodules:
        r1: T2InfectedRouter {
            @display("p=117,112");
        }
        r2: T2InfectedRouter {
            @display("p=156,301");
        }
        r3: T2InfectedRouter {
            @display("p=215,202");
        }
        r4: T2InfectedRouter {
            @display("p=395,231");
        }
        r5: T2InfectedRouter {
            @display("p=441,364");
        }
        r6: T2InfectedRouter {
            @display("p=518,192");
        }
        r7: T2InfectedRouter {
            @display("p=599,311");
        }
        r8: T2InfectedRouter {
            @display("p=629,131");
        }
        r9: T2InfectedRouter {
            @display("p=715,221");
        }
        ra: T2InfectedRouter {
            @display("p=767,105");
        }
        listener: IListener {
            @display("p=240,415");
        }
    connections:
        r1.medium++ <--> DatarateChannel {  datarate = 10Gbps; } <--> r2.medium++;
        r1.medium++ <--> DatarateChannel {  datarate = 10Gbps; } <--> r3.medium++;
        r1.medium++ <--> DatarateChannel {  datarate = 10Gbps; } <--> r6.medium++;
        r2.medium++ <--> DatarateChannel {  datarate = 10Gbps; } <--> r3.medium++;
        r2.medium++ <--> DatarateChannel {  datarate = 10Gbps; } <--> r5.medium++;
        r3.medium++ <--> DatarateChannel {  datarate = 10Gbps; } <--> r4.medium++;
        r4.medium++ <--> DatarateChannel {  datarate = 10Gbps; } <--> r5.medium++;
        r4.medium++ <--> DatarateChannel {  datarate = 10Gbps; } <--> r6.medium++;
        r5.medium++ <--> DatarateChannel {  datarate = 10Gbps; } <--> r7.medium++;
        r6.medium++ <--> DatarateChannel {  datarate = 10Gbps; } <--> r7.medium++;
        r6.medium++ <--> DatarateChannel {  datarate = 10Gbps; } <--> r8.medium++;
        r7.medium++ <--> DatarateChannel {  datarate = 10Gbps; } <--> r9.medium++;
        r8.medium++ <--> DatarateChannel {  datarate = 10Gbps; } <--> r9.medium++;
        r8.medium++ <--> DatarateChannel {  datarate = 10Gbps; } <--> ra.medium++;
        r9.medium++ <--> DatarateChannel {  datarate = 10Gbps; } <--> ra.medium++;
}
