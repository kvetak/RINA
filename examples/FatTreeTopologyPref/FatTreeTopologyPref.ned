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

package rina.examples.FatTreeTopologyPref;

import ned.DatarateChannel;
import rina.src.CS.*;
import rina.src.DAF.IRM.ConnectionTable;
import rina.src.DIF.EFCP.DTCP.*;


network FatTreeTopologyPref
{
    @display("bgb=1060,668");

    types:
    submodules:

        AS1: InteriorRouterNInt {
            @display("p=149,237");
        }
        AS2: InteriorRouterNInt {
            @display("p=422,237");
        }
        TOR1: InteriorRouterNInt {
            @display("p=149,425");
        }
        TOR2: InteriorRouterNInt {
            @display("p=422,425");
        }

        Server11: Host1AP {
            @display("p=67,598");
        }
        Server12: Host1AP {
            @display("p=149,598");
        }
        Server21: Host1AP {
            @display("p=340,598");
        }
        Server23: Host1AP {
            @display("p=504,598");
        }

        Server13: Host1AP {
            @display("p=225,598");
        }
        Server22: Host1AP {
            @display("p=422,598");
        }
        AS3: InteriorRouterNInt {
            @display("p=660,237");
        }
        AS4: InteriorRouterNInt {
            @display("p=933,237");
        }
        Server31: Host1AP {
            @display("p=578,598");
        }
        Server32: Host1AP {
            @display("p=660,598");
        }
        Server33: Host1AP {
            @display("p=736,598");
        }
        Server41: Host1AP {
            @display("p=851,598");
        }
        Server42: Host1AP {
            @display("p=933,598");
        }
        Server43: Host1AP {
            @display("p=1015,598");
        }

        TOR3: InteriorRouterNInt {
            @display("p=660,425");
        }
        TOR4: InteriorRouterNInt {
            @display("p=933,425");
        }

        AS5: InteriorRouterNInt {
            @display("p=420,67");
        }
        AS6: InteriorRouterNInt {
            @display("p=658,67");
        }
    connections:

        AS1.medium++ <--> DatarateChannel{delay = 1ms;} <--> TOR1.medium++;
        AS1.medium++ <--> DatarateChannel{delay = 1ms;} <--> TOR2.medium++;
        AS1.medium++ <--> DatarateChannel{delay = 1ms;} <--> AS5.medium++;

        AS2.medium++ <--> DatarateChannel{delay = 1ms;} <--> TOR1.medium++;
        AS2.medium++ <--> DatarateChannel{delay = 1ms;} <--> TOR2.medium++;
        AS2.medium++ <--> DatarateChannel{delay = 1ms;} <--> AS6.medium++;

        AS3.medium++ <--> DatarateChannel{delay = 1ms;} <--> TOR3.medium++;
        AS3.medium++ <--> DatarateChannel{delay = 1ms;} <--> TOR4.medium++;
        AS3.medium++ <--> DatarateChannel{delay = 1ms;} <--> AS5.medium++;

        AS4.medium++ <--> DatarateChannel{delay = 1ms;} <--> TOR3.medium++;
        AS4.medium++ <--> DatarateChannel{delay = 1ms;} <--> TOR4.medium++;
        AS4.medium++ <--> DatarateChannel{delay = 1ms;} <--> AS6.medium++;

        AS5.medium++ <--> DatarateChannel{delay = 1ms;} <--> AS6.medium++;

        Server11.medium <--> DatarateChannel{delay = 1ms;} <--> TOR1.medium++;
        Server12.medium <--> DatarateChannel{delay = 1ms;} <--> TOR1.medium++;
        Server13.medium <--> DatarateChannel{delay = 1ms;} <--> TOR1.medium++;

        Server21.medium <--> DatarateChannel{delay = 1ms;} <--> TOR2.medium++;
        Server22.medium <--> DatarateChannel{delay = 1ms;} <--> TOR2.medium++;
        Server23.medium <--> DatarateChannel{delay = 1ms;} <--> TOR2.medium++;

        Server31.medium <--> DatarateChannel{delay = 1ms;} <--> TOR3.medium++;
        Server32.medium <--> DatarateChannel{delay = 1ms;} <--> TOR3.medium++;
        Server33.medium <--> DatarateChannel{delay = 1ms;} <--> TOR3.medium++;

        Server41.medium <--> DatarateChannel{delay = 1ms;} <--> TOR4.medium++;
        Server42.medium <--> DatarateChannel{delay = 1ms;} <--> TOR4.medium++;
        Server43.medium <--> DatarateChannel{delay = 1ms;} <--> TOR4.medium++;

}
