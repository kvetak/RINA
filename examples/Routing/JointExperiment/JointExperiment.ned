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

package rina.examples.Routing.JointExperiment;

import ned.DatarateChannel;

import rina.src.CS.Host1AP;
import rina.src.CS.InteriorRouterNInt;

import rina.src.Other.FullPathMonitor.FullPathMonitor;
import rina.src.Other.Infection.InfectedRouter;
import rina.src.Other.Infection.IListener;

import rina.src.Other.Infection.IListener;
import rina.src.DAF.AE.AEConstant.AEConstantListener;
import rina.src.Other.FullPathMonitor.FullPathMonitor;
import rina.src.Other.ONOFFInj.OFInjRouter;
import rina.src.Other.ONOFFInj.InjListener;


network JointExperiment
{
    @display("bgb=1152,777");

    submodules:

        AS1: InteriorRouterNInt {
            @display("p=149,361");
        }
        AS2: InteriorRouterNInt {
            @display("p=422,361");
        }
        TOR1: InteriorRouterNInt {
            @display("p=149,549");
        }
        TOR2: InteriorRouterNInt {
            @display("p=422,549");
        }

        Server11: OFInjRouter {
            @display("p=80,722");
        }
        Server12: OFInjRouter {
            @display("p=220,722");
        }
        Server21: OFInjRouter {
            @display("p=353,722");
        }
        Server22: OFInjRouter {
            @display("p=489,722");
        }
        AS3: InteriorRouterNInt {
            @display("p=716,361");
        }
        AS4: InteriorRouterNInt {
            @display("p=989,361");
        }
        Server31: OFInjRouter {
            @display("p=650,722");
        }
        Server32: OFInjRouter {
            @display("p=785,722");
        }
        Server41: OFInjRouter {
            @display("p=920,722");
        }
        Server42: OFInjRouter {
            @display("p=1054,722");
        }
        TOR3: InteriorRouterNInt {
            @display("p=716,549");
        }
        TOR4: InteriorRouterNInt {
            @display("p=989,549");
        }

        AS5: InteriorRouterNInt {
            @display("p=495,108");
        }
        AS6: InteriorRouterNInt {
            @display("p=657,108");
        }
        fullPathMonitor: FullPathMonitor {
            @display("p=953,168");
        }
        listener: InjListener {

            @display("p=1037,111");
        }
        Exit: OFInjRouter {
            @display("p=580,41");
        }
    connections:

        AS1.medium++ <--> DatarateChannel {  datarate = 1Gbps; } <--> TOR1.medium++;
        AS1.medium++ <--> DatarateChannel {  datarate = 1Gbps; } <--> TOR2.medium++;
        AS1.medium++ <--> DatarateChannel {  datarate = 1Gbps; } <--> AS5.medium++;

        AS2.medium++ <--> DatarateChannel {  datarate = 1Gbps; } <--> TOR1.medium++;
        AS2.medium++ <--> DatarateChannel {  datarate = 1Gbps; } <--> TOR2.medium++;
        AS2.medium++ <--> DatarateChannel {  datarate = 1Gbps; } <--> AS6.medium++;

        AS3.medium++ <--> DatarateChannel {  datarate = 1Gbps; } <--> TOR3.medium++;
        AS3.medium++ <--> DatarateChannel {  datarate = 1Gbps; } <--> TOR4.medium++;
        AS3.medium++ <--> DatarateChannel {  datarate = 1Gbps; } <--> AS5.medium++;

        AS4.medium++ <--> DatarateChannel {  datarate = 1Gbps; } <--> TOR3.medium++;
        AS4.medium++ <--> DatarateChannel {  datarate = 1Gbps; } <--> TOR4.medium++;
        AS4.medium++ <--> DatarateChannel {  datarate = 1Gbps; } <--> AS6.medium++;

        Server11.medium++ <--> DatarateChannel {  datarate = 1Gbps; } <--> TOR1.medium++;
        Server12.medium++ <--> DatarateChannel {  datarate = 1Gbps; } <--> TOR1.medium++;
        Server21.medium++ <--> DatarateChannel {  datarate = 1Gbps; } <--> TOR2.medium++;
        Server22.medium++ <--> DatarateChannel {  datarate = 1Gbps; } <--> TOR2.medium++;
        Server31.medium++ <--> DatarateChannel {  datarate = 1Gbps; } <--> TOR3.medium++;
        Server32.medium++ <--> DatarateChannel {  datarate = 1Gbps; } <--> TOR3.medium++;
        Server41.medium++ <--> DatarateChannel {  datarate = 1Gbps; } <--> TOR4.medium++;
        Server42.medium++ <--> DatarateChannel {  datarate = 1Gbps; } <--> TOR4.medium++;
        AS1.medium++ <--> DatarateChannel {  datarate = 1Gbps; } <--> AS6.medium++;
        AS2.medium++ <--> DatarateChannel {  datarate = 1Gbps; } <--> AS5.medium++;
        AS3.medium++ <--> DatarateChannel {  datarate = 1Gbps; } <--> AS6.medium++;
        AS4.medium++ <--> DatarateChannel {  datarate = 1Gbps; } <--> AS5.medium++;
        AS5.medium++ <--> DatarateChannel {  datarate = 1Gbps; } <--> Exit.medium++;
        AS6.medium++ <--> DatarateChannel {  datarate = 1Gbps; } <--> Exit.medium++;

}
