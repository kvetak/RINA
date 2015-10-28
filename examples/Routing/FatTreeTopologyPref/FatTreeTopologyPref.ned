// The MIT License (MIT)
//
// Copyright (c) 2014-2016 Brno University of Technology, PRISTINE project
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
// Author: Kewin Rausch <kewin.rausch@create-net.org>
// Description: Provides a small DC example using RINA.

package rina.examples.Routing.FatTreeTopologyPref;

import ned.DatarateChannel;
import rina.src.CS.Host1AP;
import rina.src.CS.InteriorRouterNInt;


network FatTreeTopologyPref
{
    @display("bgb=1060,668");

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
