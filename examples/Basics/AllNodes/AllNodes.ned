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

package rina.examples.Basics.AllNodes;

import ned.DelayChannel;
import rina.src.CS.BorderRouter;
import rina.src.CS.Host1AP;
import rina.src.CS.InteriorRouterNInt;

network AllNodes
{
    @display("bgb=527,319");
    submodules:
        BorderRouterA: BorderRouter {
            @display("p=139,143");
        }
        BorderRouterB: BorderRouter {
            @display("p=371,143");
        }
        HostA1: Host1AP {
            @display("p=41,50");
        }
        HostA2: Host1AP {
            @display("p=41,243");
        }
        HostB1: Host1AP {
            @display("p=478,60");
        }
        HostB2: Host1AP {
            @display("p=478,243");
        }
        InteriorRouter: InteriorRouterNInt {
            @display("p=251,143");
        }
    connections:
        HostA1.medium <--> DelayChannel{delay=1us;} <--> BorderRouterA.medium[0];
        HostA2.medium <--> DelayChannel{delay=1us;} <--> BorderRouterA.medium[1];
        BorderRouterA.medium[2] <--> DelayChannel{delay=1us;} <--> InteriorRouter.medium++;
        BorderRouterB.medium[2] <--> DelayChannel{delay=1us;} <--> InteriorRouter.medium++;
        HostB1.medium <--> DelayChannel{delay=1us;} <--> BorderRouterB.medium[0];
        HostB2.medium <--> DelayChannel{delay=1us;} <--> BorderRouterB.medium[1];
}
