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

package rina.examples.Basics.SimpleRelay;

import ned.DatarateChannel;
import rina.src.CS.Host1AP;
import rina.src.CS.InteriorRouter2Int;


network SimpleRelay
{
    @display("bgb=368,202");
    submodules:
        host1: Host1AP {
            @display("p=70,101");
        }
        interiorRouter: InteriorRouter2Int {
            @display("p=180,101");
        }
        host2: Host1AP {
            @display("p=290,101");
        }
    connections allowunconnected:
        host1.medium  <--> DatarateChannel {datarate = 100Mbps; delay = 100us; ber = 0; } <--> interiorRouter.medium++;
        host2.medium  <--> DatarateChannel {datarate = 100Mbps; delay = 100us; ber = 0; } <--> interiorRouter.medium++;
}
