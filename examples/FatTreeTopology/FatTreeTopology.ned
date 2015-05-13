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

package rina.examples.FatTreeTopology;

import rina.src.CS.*;
import rina.src.DAF.IRM.ConnectionTable;
import rina.src.DIF.EFCP.DTCP.*;


network FatTreeTopology
{
    @display("bgb=975,618");

    submodules:

        AS1: InteriorRouter2Int {
            @display("p=267,96");
        }
        AS2: InteriorRouter2Int {
            @display("p=667,96");
        }
        TOR1: InteriorRouter4Int {
            @display("p=267,268");
        }
        TOR2: InteriorRouter4Int {
            @display("p=667,268");
        }

        Server1: Host1AP {
            @display("p=185,441");
        }
        Server2: Host1AP {
            @display("p=349,441");
        }
        Server3: Host1AP {
            @display("p=585,441");
        }
        Server4: Host1AP {
            @display("p=749,441");
        }

    connections:

        AS1.medium[0] <--> TOR1.medium[0];
        AS1.medium[1] <--> TOR2.medium[0];

        AS2.medium[0] <--> TOR1.medium[1];
        AS2.medium[1] <--> TOR2.medium[1];

        Server1.medium <--> TOR1.medium[2];
        Server2.medium <--> TOR1.medium[3];

        Server3.medium <--> TOR2.medium[2];
        Server4.medium <--> TOR2.medium[3];
}
