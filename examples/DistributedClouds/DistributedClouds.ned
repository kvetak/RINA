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
// Author: Kewin Rausch <kewin.rausch@create-net.org>
// Description: Provides a small DC example using RINA.

package rina.examples.DistributedClouds;

import rina.CS.*;
import rina.DAF.IRM.ConnectionTable;
import rina.DIF.EFCP.DTCP.*;
import rina.CS.VIFIBNodeGL2;
import rina.CS.VIFIBNode;

network DistributedClouds
{
    @display("bgb=738,618");

    submodules:

        VIFIBN1: VIFIBNode {
            @display("p=152,138");
        }
        VIFIBN2: VIFIBNode {
            @display("p=141,237");
        }

        VIFIBN5: VIFIBNode {
            @display("p=487,138");
        }
        VIFIBN6: VIFIBNode {
            @display("p=584,198");
        }
        VIFIBN7: VIFIBNode {
            @display("p=601,396");
        }
        VIFIBN8: VIFIBNode {
            @display("p=543,471");
        }

        VIFIBN11: VIFIBNode {
            @display("p=90,452");
        }
        VIFIBN12: VIFIBNode {
            @display("p=129,384");
        }
        
        VIFIBNGL1: VIFIBNodeGL2 {
            @display("p=246,214");
        }
        VIFIBNGL2: VIFIBNodeGL2 {
            @display("p=429,214");
        }
        VIFIBNGL3: VIFIBNodeGL2 {
            @display("p=478,407");
        }
        VIFIBNGL4: VIFIBNodeGL2 {
            @display("p=213,423");
        }
        
    connections:
		//Group 1 Connections
        VIFIBN1.medium[0] <--> VIFIBN2.medium[0];
        VIFIBN1.medium[1] <--> VIFIBNGL1.medium[0];
        VIFIBN2.medium[1] <--> VIFIBNGL1.medium[1];


		//Group 2 Connections
        VIFIBNGL2.medium[0] <--> VIFIBN5.medium[0];
        VIFIBNGL2.medium[1] <--> VIFIBN6.medium[0];
        VIFIBN5.medium[1] <--> VIFIBN6.medium[1];


		//Group 3 Connections
        VIFIBN7.medium[0] <--> VIFIBN8.medium[0];
        VIFIBN7.medium[1] <--> VIFIBNGL3.medium[0];
        VIFIBN8.medium[1] <--> VIFIBNGL3.medium[1];


		//Group 4 Connections
        VIFIBNGL4.medium[0] <--> VIFIBN11.medium[0];
        VIFIBNGL4.medium[1] <--> VIFIBN12.medium[0];
        VIFIBN11.medium[1] <--> VIFIBN12.medium[1];


        //Connections between the groups

        VIFIBNGL2.medium[2] <--> VIFIBNGL1.medium[2];
        VIFIBNGL3.medium[2] <--> VIFIBNGL4.medium[2];
  //     VIFIBN6.medium[2] <--> VIFIBN7.medium[2];
        VIFIBNGL2.medium[3] <--> VIFIBNGL4.medium[3];
        VIFIBNGL3.medium[3] <--> VIFIBNGL1.medium[3];

}
