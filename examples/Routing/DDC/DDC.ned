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

package rina.examples.Routing.DDC;

import rina.src.CS.InteriorRouterNInt;


network DDC
{
    @display("bgb=1139.4337,563.45624");
    submodules:

        T_0_0: InteriorRouterNInt {
            @display("p=30,470");
        }
        T_0_1: InteriorRouterNInt {
            @display("p=93,470");
        }
        T_0_2: InteriorRouterNInt {
            @display("p=161,470");
        }
        T_0_3: InteriorRouterNInt {
            @display("p=223,470");
        }

        T_1_0: InteriorRouterNInt {
            @display("p=320,470");
        }
        T_1_1: InteriorRouterNInt {
            @display("p=383,470");
        }
        T_1_2: InteriorRouterNInt {
            @display("p=451,470");
        }
        T_1_3: InteriorRouterNInt {
            @display("p=513,470");
        }

        T_2_0: InteriorRouterNInt {
            @display("p=609,470");
        }
        T_2_1: InteriorRouterNInt {
            @display("p=672,470");
        }
        T_2_2: InteriorRouterNInt {
            @display("p=740,470");
        }
        T_2_3: InteriorRouterNInt {
            @display("p=802,470");
        }

        T_3_0: InteriorRouterNInt {
            @display("p=892,470");
        }
        T_3_1: InteriorRouterNInt {
            @display("p=955,470");
        }
        T_3_2: InteriorRouterNInt {
            @display("p=1023,470");
        }
        T_3_3: InteriorRouterNInt {
            @display("p=1085,470");
        }
        A_0_0: InteriorRouterNInt {
            @display("p=54,364");
        }
        A_0_1: InteriorRouterNInt {
            @display("p=121,364");
        }
        A_0_2: InteriorRouterNInt {
            @display("p=187,364");
        }
        A_1_2: InteriorRouterNInt {
            @display("p=477,364");
        }
        A_1_1: InteriorRouterNInt {
            @display("p=411,364");
        }
        A_1_0: InteriorRouterNInt {
            @display("p=344,364");
        }
        A_2_2: InteriorRouterNInt {
            @display("p=769,364");
        }
        A_2_1: InteriorRouterNInt {
            @display("p=703,364");
        }
        A_2_0: InteriorRouterNInt {
            @display("p=636,364");
        }
        A_3_2: InteriorRouterNInt {
            @display("p=1049,364");
        }
        A_3_0: InteriorRouterNInt {
            @display("p=916,364");
        }
        A_3_1: InteriorRouterNInt {
            @display("p=983,364");
        }

        S_0_0: InteriorRouterNInt {
            @display("p=100,172");
        }
        S_0_1: InteriorRouterNInt {
            @display("p=154,172");
        }
        S_0_2: InteriorRouterNInt {
            @display("p=210,172");
        }

        S_1_0: InteriorRouterNInt {
            @display("p=490,172");
        }
        S_1_1: InteriorRouterNInt {
            @display("p=542,172");
        }
        S_1_2: InteriorRouterNInt {
            @display("p=597,172");
        }

        S_2_0: InteriorRouterNInt {
            @display("p=853,172");
        }
        S_2_1: InteriorRouterNInt {
            @display("p=904,172");
        }
        S_2_2: InteriorRouterNInt {
            @display("p=954,172");
        }

    connections:
        T_0_0.medium++ <--> A_0_0.medium++;
        T_0_1.medium++ <--> A_0_0.medium++;
        T_0_2.medium++ <--> A_0_0.medium++;
        T_0_3.medium++ <--> A_0_0.medium++;
        T_0_0.medium++ <--> A_0_1.medium++;
        T_0_1.medium++ <--> A_0_1.medium++;
        T_0_2.medium++ <--> A_0_1.medium++;
        T_0_3.medium++ <--> A_0_1.medium++;
        T_0_0.medium++ <--> A_0_2.medium++;
        T_0_1.medium++ <--> A_0_2.medium++;
        T_0_2.medium++ <--> A_0_2.medium++;
        T_0_3.medium++ <--> A_0_2.medium++;
        T_1_0.medium++ <--> A_1_0.medium++;
        T_1_0.medium++ <--> A_1_1.medium++;
        T_1_0.medium++ <--> A_1_2.medium++;
        T_1_1.medium++ <--> A_1_0.medium++;
        T_1_1.medium++ <--> A_1_1.medium++;
        T_1_1.medium++ <--> A_1_2.medium++;
        T_1_2.medium++ <--> A_1_0.medium++;
        T_1_2.medium++ <--> A_1_1.medium++;
        T_1_2.medium++ <--> A_1_2.medium++;
        T_1_3.medium++ <--> A_1_0.medium++;
        T_1_3.medium++ <--> A_1_1.medium++;
        T_1_3.medium++ <--> A_1_2.medium++;
        T_2_0.medium++ <--> A_2_0.medium++;
        T_2_0.medium++ <--> A_2_1.medium++;
        T_2_0.medium++ <--> A_2_2.medium++;
        T_2_1.medium++ <--> A_2_0.medium++;
        T_2_1.medium++ <--> A_2_1.medium++;
        T_2_1.medium++ <--> A_2_2.medium++;
        T_2_2.medium++ <--> A_2_0.medium++;
        T_2_2.medium++ <--> A_2_1.medium++;
        T_2_2.medium++ <--> A_2_2.medium++;
        T_2_3.medium++ <--> A_2_0.medium++;
        T_2_3.medium++ <--> A_2_1.medium++;
        T_2_3.medium++ <--> A_2_2.medium++;
        T_3_0.medium++ <--> A_3_0.medium++;
        T_3_0.medium++ <--> A_3_1.medium++;
        T_3_0.medium++ <--> A_3_2.medium++;
        T_3_1.medium++ <--> A_3_0.medium++;
        T_3_1.medium++ <--> A_3_1.medium++;
        T_3_1.medium++ <--> A_3_2.medium++;
        T_3_2.medium++ <--> A_3_0.medium++;
        T_3_2.medium++ <--> A_3_1.medium++;
        T_3_2.medium++ <--> A_3_2.medium++;
        T_3_3.medium++ <--> A_3_0.medium++;
        T_3_3.medium++ <--> A_3_1.medium++;
        T_3_3.medium++ <--> A_3_2.medium++;
        A_0_0.medium++ <--> S_0_0.medium++;
        A_0_0.medium++ <--> S_0_1.medium++;
        A_0_0.medium++ <--> S_0_2.medium++;
        A_1_0.medium++ <--> S_0_0.medium++;
        A_1_0.medium++ <--> S_0_1.medium++;
        A_1_0.medium++ <--> S_0_2.medium++;
        A_2_0.medium++ <--> S_0_0.medium++;
        A_2_0.medium++ <--> S_0_1.medium++;
        A_2_0.medium++ <--> S_0_2.medium++;
        A_3_0.medium++ <--> S_0_0.medium++;
        A_3_0.medium++ <--> S_0_1.medium++;
        A_3_0.medium++ <--> S_0_2.medium++;
        A_0_1.medium++ <--> S_1_0.medium++;
        A_0_1.medium++ <--> S_1_1.medium++;
        A_0_1.medium++ <--> S_1_2.medium++;
        A_1_1.medium++ <--> S_1_0.medium++;
        A_1_1.medium++ <--> S_1_1.medium++;
        A_1_1.medium++ <--> S_1_2.medium++;
        A_2_1.medium++ <--> S_1_0.medium++;
        A_2_1.medium++ <--> S_1_1.medium++;
        A_2_1.medium++ <--> S_1_2.medium++;
        A_3_1.medium++ <--> S_1_0.medium++;
        A_3_1.medium++ <--> S_1_1.medium++;
        A_3_1.medium++ <--> S_1_2.medium++;
        A_0_2.medium++ <--> S_2_0.medium++;
        A_0_2.medium++ <--> S_2_1.medium++;
        A_0_2.medium++ <--> S_2_2.medium++;
        A_1_2.medium++ <--> S_2_0.medium++;
        A_1_2.medium++ <--> S_2_1.medium++;
        A_1_2.medium++ <--> S_2_2.medium++;
        A_2_2.medium++ <--> S_2_0.medium++;
        A_2_2.medium++ <--> S_2_1.medium++;
        A_2_2.medium++ <--> S_2_2.medium++;
        A_3_2.medium++ <--> S_2_0.medium++;
        A_3_2.medium++ <--> S_2_1.medium++;
        A_3_2.medium++ <--> S_2_2.medium++;
}
