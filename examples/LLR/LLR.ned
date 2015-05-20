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

// Link-load routing example.

package rina.examples.LLR;

import rina.src.CS.*;

network LLR
{
    @display("bgb=731,489");
    submodules:
        N1: Host1AP {
            @display("p=148,150");
        }
        N2: Host1AP {
            @display("p=148,319");
        }
        N7: Host1AP {
            @display("p=581,150");
        }
        N8: Host1AP {
            @display("p=581,319");
        }
        N3: InteriorRouterNInt {
            @display("p=249,232");
        }
        N4: InteriorRouterNInt {
            @display("p=358,150");
        }
        N5: InteriorRouterNInt {
            @display("p=358,319");
        }
        N6: InteriorRouterNInt {
            @display("p=471,232");
        }

    connections:

		// Left to right(top to bottom) the topology of the network.

											// Node: medium used.
		N1.medium <--> N3.medium++;			// N3: 0
		N2.medium <--> N3.medium++; 		// N3: 1
		
		N3.medium++ <--> N4.medium++; 		// N3: 2, N4: 0
		N3.medium++ <--> N5.medium++;		// N3: 3, N5: 0
		
		N4.medium++ <--> N6.medium++;		// N4: 1, N6: 0
		N5.medium++ <--> N6.medium++; 		// N5: 1, N6: 1 
		
		N6.medium++ <--> N7.medium;			// N6: 2, N7: 0
		N6.medium++ <--> N8.medium;			// N6: 3, N7: 0
}
