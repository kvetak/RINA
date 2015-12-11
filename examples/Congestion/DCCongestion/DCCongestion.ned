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

package rina.examples.Congestion.DCCongestion;
import ned.DatarateChannel;
import rina.src.CS.*;

network DCCongestion
{
    parameters:
        @display("bgb=367,296");

    types:
        channel FastChannel extends ned.DatarateChannel
        {
            @defaultname(FChan);
            datarate = 20Mbps;
            delay = 10ms;
            ber = 0;
        }
        channel SlowChannel extends ned.DatarateChannel
        {
            @defaultname(SChan);
            datarate = 10Mbps;
            delay = 10ms;
            ber = 0;
        }

    submodules:
        host11: Host1AP {
            @display("p=70,61");
        }
        host12: Host1AP {
            @display("p=70,151");
        }
        host13: Host1AP {
            @display("p=70,241");
        }
        interiorRouter: InteriorRouterNInt {
            @display("p=180,101");
        }
        host21: HostNAP {
            @display("p=290,101");
        }

    connections allowunconnected:
        host11.medium <--> e1: SlowChannel <--> interiorRouter.medium++;
        host21.medium <--> e2: SlowChannel <--> interiorRouter.medium++;
        host12.medium <--> e3: SlowChannel <--> interiorRouter.medium++;
        host13.medium <--> e4: SlowChannel <--> interiorRouter.medium++;
}
