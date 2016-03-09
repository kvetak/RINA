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

package rina.examples.Routing.InfectedMultipathFatTree;

import ned.DatarateChannel;

import rina.src.CS.Host1AP;
import rina.src.CS.InteriorRouterNInt;

import rina.src.Other.Infection.InfectedRouter;
import rina.src.Other.Infection.IListener;

import rina.src.Other.Infection.IListener;
import rina.src.DAF.AE.AEConstant.AEConstantListener;


network InfectedMultipathFatTree
{
    @display("bgb=1152,727");

    submodules:

        AS1: InteriorRouterNInt {
            @display("p=149,321");
        }
        AS2: InteriorRouterNInt {
            @display("p=422,321");
        }
        TOR1: InteriorRouterNInt {
            @display("p=149,509");
        }
        TOR2: InteriorRouterNInt {
            @display("p=422,509");
        }

        Server11: InfectedRouter {
            @display("p=67,682");
        }
        Server12: InfectedRouter {
            @display("p=242,682");
        }
        Server21: Host1AP {
            @display("p=340,682");
        }
        Server22: Host1AP {
            @display("p=513,682");
        }
        AS3: InteriorRouterNInt {
            @display("p=716,321");
        }
        AS4: InteriorRouterNInt {
            @display("p=989,321");
        }
        Server31: Host1AP {
            @display("p=634,682");
        }
        Server32: Host1AP {
            @display("p=814,682");
        }
        Server41: Host1AP {
            @display("p=888,682");
        }
        Server42: Host1AP {
            @display("p=1085,682");
        }
        TOR3: InteriorRouterNInt {
            @display("p=716,509");
        }
        TOR4: InteriorRouterNInt {
            @display("p=989,509");
        }

        AS5: InteriorRouterNInt {
            @display("p=495,68");
        }
        AS6: InteriorRouterNInt {
            @display("p=657,68");
        }
    connections:

        AS1.medium++ <--> DatarateChannel { datarate = 10Gbps;} <--> TOR1.medium++;
        AS1.medium++ <--> DatarateChannel { datarate = 10Gbps;} <--> TOR2.medium++;
        AS1.medium++ <--> DatarateChannel { datarate = 10Gbps;} <--> AS5.medium++;

        AS2.medium++ <--> DatarateChannel { datarate = 10Gbps;} <--> TOR1.medium++;
        AS2.medium++ <--> DatarateChannel { datarate = 10Gbps;} <--> TOR2.medium++;
        AS2.medium++ <--> DatarateChannel { datarate = 10Gbps;} <--> AS6.medium++;

        AS3.medium++ <--> DatarateChannel { datarate = 10Gbps;} <--> TOR3.medium++;
        AS3.medium++ <--> DatarateChannel { datarate = 10Gbps;} <--> TOR4.medium++;
        AS3.medium++ <--> DatarateChannel { datarate = 10Gbps;} <--> AS5.medium++;

        AS4.medium++ <--> DatarateChannel { datarate = 10Gbps;} <--> TOR3.medium++;
        AS4.medium++ <--> DatarateChannel { datarate = 10Gbps;} <--> TOR4.medium++;
        AS4.medium++ <--> DatarateChannel { datarate = 10Gbps;} <--> AS6.medium++;

        Server11.medium++ <--> DatarateChannel { datarate = 10Gbps;} <--> TOR1.medium++;
        Server12.medium++ <--> DatarateChannel { datarate = 10Gbps;} <--> TOR1.medium++;
        Server21.medium <--> DatarateChannel { datarate = 10Gbps;} <--> TOR2.medium++;
        Server22.medium <--> DatarateChannel { datarate = 10Gbps;} <--> TOR2.medium++;
        Server31.medium <--> DatarateChannel { datarate = 10Gbps;} <--> TOR3.medium++;
        Server32.medium <--> DatarateChannel { datarate = 10Gbps;} <--> TOR3.medium++;
        Server41.medium <--> DatarateChannel { datarate = 10Gbps;} <--> TOR4.medium++;
        Server42.medium <--> DatarateChannel { datarate = 10Gbps;} <--> TOR4.medium++;
        AS1.medium++ <--> DatarateChannel { datarate = 10Gbps;} <--> AS6.medium++;
        AS2.medium++ <--> DatarateChannel { datarate = 10Gbps;} <--> AS5.medium++;
        AS3.medium++ <--> DatarateChannel { datarate = 10Gbps;} <--> AS6.medium++;
        AS4.medium++ <--> DatarateChannel { datarate = 10Gbps;} <--> AS5.medium++;

}
