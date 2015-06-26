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

package rina.examples.Demos.UseCase3;

import rina.src.CS.Host1AP;
import ned.DatarateChannel;

network UseCase3
{
    @display("bgb=309,194");
    submodules:
        hostA: Host1AP {
            @display("p=72,78");
        }
        hostB: Host1AP {
            @display("p=213,78");
        }
    connections:
        hostB.medium <--> DatarateChannel {delay = 0.1s; ber = 0; datarate = 10Mbps; } <--> hostA.medium;
}
