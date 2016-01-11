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

package rina.examples.Congestion.StopAndWait;


import ned.DatarateChannel;
import rina.src.Other.Infection.InfectedRouter;
import rina.src.Other.Infection.IListener;

import rina.src.Other.Infection.IListener;
import rina.src.DAF.AE.AEConstant.AEConstantListener;

network StopAndWait
{
    @display("bgb=838,510");
    submodules:
        r1: InfectedRouter {
            @display("p=117,112");
        }
        r2: InfectedRouter {
            @display("p=156,301");
        }
        listener: IListener {
            @display("p=240,415");
        }
    connections:
        r1.medium++ <--> DatarateChannel {  datarate = 10Gbps; } <--> r2.medium++;

}
