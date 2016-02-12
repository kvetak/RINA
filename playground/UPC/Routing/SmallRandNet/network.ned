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

package rina.playground.UPC.Routing.SmallRandNet;

import ned.DelayChannel;
import rina.src.CS.BorderRouter;
import rina.src.CS.HostNAP;
import rina.src.CS.InteriorRouterNInt;

network SmallRandNet
{
    @display("bgb=600,600");
    submodules:

        H0 : HostNAP {
            @display("p=300.000000,500.000000");
        }

        H1 : HostNAP {
            @display("p=400.000000,473.205081");
        }

        H2 : HostNAP {
            @display("p=473.205081,400.000000");
        }

        H3 : HostNAP {
            @display("p=500.000000,300.000000");
        }

        H4 : HostNAP {
            @display("p=473.205081,200.000000");
        }

        H5 : HostNAP {
            @display("p=400.000000,126.794919");
        }

        H6 : HostNAP {
            @display("p=300.000000,100.000000");
        }

        H7 : HostNAP {
            @display("p=200.000000,126.794919");
        }

        H8 : HostNAP {
            @display("p=126.794919,200.000000");
        }

        H9 : HostNAP {
            @display("p=100.000000,300.000000");
        }

        H10 : HostNAP {
            @display("p=126.794919,400.000000");
        }

        H11 : HostNAP {
            @display("p=200.000000,473.205081");
        }

        R12 : InteriorRouterNInt {
            @display("p=300.000000,420.000000");
        }

        R13 : InteriorRouterNInt {
            @display("p=384.852814,384.852814");
        }

        R14 : InteriorRouterNInt {
            @display("p=420.000000,300.000000");
        }

        R15 : InteriorRouterNInt {
            @display("p=384.852814,215.147186");
        }

        R16 : InteriorRouterNInt {
            @display("p=300.000000,180.000000");
        }

        R17 : InteriorRouterNInt {
            @display("p=215.147186,215.147186");
        }

        R18 : InteriorRouterNInt {
            @display("p=180.000000,300.000000");
        }

        R19 : InteriorRouterNInt {
            @display("p=215.147186,384.852814");
        }


    connections:

        H0.medium <--> DelayChannel{delay=1us;} <--> R12.medium++;
        H1.medium <--> DelayChannel{delay=1us;} <--> R13.medium++;
        H2.medium <--> DelayChannel{delay=1us;} <--> R14.medium++;
        H3.medium <--> DelayChannel{delay=1us;} <--> R15.medium++;
        H4.medium <--> DelayChannel{delay=1us;} <--> R16.medium++;
        H5.medium <--> DelayChannel{delay=1us;} <--> R17.medium++;
        H6.medium <--> DelayChannel{delay=1us;} <--> R18.medium++;
        H7.medium <--> DelayChannel{delay=1us;} <--> R19.medium++;
        H8.medium <--> DelayChannel{delay=1us;} <--> R12.medium++;
        H9.medium <--> DelayChannel{delay=1us;} <--> R13.medium++;
        H10.medium <--> DelayChannel{delay=1us;} <--> R14.medium++;
        H11.medium <--> DelayChannel{delay=1us;} <--> R15.medium++;
        R12.medium++ <--> DelayChannel{delay=1us;} <--> R17.medium++;
        R13.medium++ <--> DelayChannel{delay=1us;} <--> R18.medium++;
        R14.medium++ <--> DelayChannel{delay=1us;} <--> R19.medium++;
        R15.medium++ <--> DelayChannel{delay=1us;} <--> R12.medium++;
        R16.medium++ <--> DelayChannel{delay=1us;} <--> R13.medium++;
        R17.medium++ <--> DelayChannel{delay=1us;} <--> R14.medium++;
        R18.medium++ <--> DelayChannel{delay=1us;} <--> R15.medium++;
}
