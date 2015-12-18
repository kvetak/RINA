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
        @display("bgb=1080,303");

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
            @display("p=70,62");
        }
        host12: Host1AP {
            @display("p=120,62");
        }
        host13: Host1AP {
            @display("p=170,62");
        }
        host14: Host1AP {
            @display("p=220,62");
        }
        host15: Host1AP {
            @display("p=270,62");
        }
        host16: Host1AP {
            @display("p=320,62");
        }
        host17: Host1AP {
            @display("p=370,62");
        }
        host18: Host1AP {
            @display("p=420,62");
        }
        host19: Host1AP {
            @display("p=470,62");
        }
        host110: Host1AP {
            @display("p=520,62");
        }
        host111: Host1AP {
            @display("p=570,62");
        }
        host112: Host1AP {
            @display("p=620,62");
        }
        host113: Host1AP {
            @display("p=670,62");
        }
        host114: Host1AP {
            @display("p=720,62");
        }
        host115: Host1AP {
            @display("p=770,62");
        }
        host116: Host1AP {
            @display("p=820,62");
        }
        host117: Host1AP {
            @display("p=870,62");
        }
        host118: Host1AP {
            @display("p=920,62");
        }
        host119: Host1AP {
            @display("p=970,62");
        }
        host120: Host1AP {
            @display("p=1020,62");
        }
        interiorRouter: InteriorRouterNInt {
            @display("p=556,166");
        }
        host21: HostNAP {
            @display("p=556,249");
        }

    connections allowunconnected:
        host11.medium <--> e1: SlowChannel <--> interiorRouter.medium++;
        host21.medium <--> e2: SlowChannel <--> interiorRouter.medium++;
        host12.medium <--> e3: SlowChannel <--> interiorRouter.medium++;
        host13.medium <--> e4: SlowChannel <--> interiorRouter.medium++;
        host14.medium <--> e5: SlowChannel <--> interiorRouter.medium++;
        host15.medium <--> e6: SlowChannel <--> interiorRouter.medium++;
        host16.medium <--> e7: SlowChannel <--> interiorRouter.medium++;
        host17.medium <--> e8: SlowChannel <--> interiorRouter.medium++;
        host18.medium <--> e9: SlowChannel <--> interiorRouter.medium++;
        host19.medium <--> e10: SlowChannel <--> interiorRouter.medium++;
        host110.medium <--> e11: SlowChannel <--> interiorRouter.medium++;
        host111.medium <--> e12: SlowChannel <--> interiorRouter.medium++;
        host112.medium <--> e13: SlowChannel <--> interiorRouter.medium++;
        host113.medium <--> e14: SlowChannel <--> interiorRouter.medium++;
        host114.medium <--> e15: SlowChannel <--> interiorRouter.medium++;
        host115.medium <--> e16: SlowChannel <--> interiorRouter.medium++;
        host116.medium <--> e17: SlowChannel <--> interiorRouter.medium++;
        host117.medium <--> e18: SlowChannel <--> interiorRouter.medium++;
        host118.medium <--> e19: SlowChannel <--> interiorRouter.medium++;
        host119.medium <--> e120: SlowChannel <--> interiorRouter.medium++;
        host120.medium <--> e121: SlowChannel <--> interiorRouter.medium++;
}
