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

package rina.examples.Congestion.L;


import ned.DatarateChannel;
import rina.src.Other.Infection.T2InfectedRouter;
import rina.src.Other.Infection.IListener;

import rina.src.Other.Infection.IListener;
import rina.src.DAF.AE.AEConstant.AEConstantListener;

network L
{
    submodules:
        A: T2InfectedRouter {
            @display("p=156,47");
        }
        B: T2InfectedRouter {
            @display("p=156,234");
        }
        C: T2InfectedRouter {
            @display("p=273,234");
        }
        listener: IListener {
            @display("p=273,47");
        }
    connections:
        A.medium++ <--> DatarateChannel {  datarate = 10Gbps; } <--> B.medium++;
        B.medium++ <--> DatarateChannel {  datarate = 10Gbps; } <--> C.medium++;
}
