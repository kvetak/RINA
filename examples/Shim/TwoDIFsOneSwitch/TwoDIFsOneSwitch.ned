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

package rina.examples.Shim.TwoDIFsOneSwitch;

import rina.src.CS.EthShim.Host1APShim;

import inet.node.ethernet.Eth100M;
import inet.node.ethernet.EtherSwitch;


network TwoDIFsOneSwitch
{
    @display("bgb=366,339");
    submodules:
        host1: Host1APShim {
            @display("p=92,83");
        }
        host2: Host1APShim {
            @display("p=233,237");
        }
        host3: Host1APShim {
            @display("p=233,83");
        }
        host4: Host1APShim {
            @display("p=92,237");
        }
        switch: EtherSwitch {
            @display("p=163,157");
        }

    connections:
        switch.ethg++ <--> Eth100M <--> host1.medium;
        switch.ethg++ <--> Eth100M <--> host2.medium;
        switch.ethg++ <--> Eth100M <--> host3.medium;
        switch.ethg++ <--> Eth100M <--> host4.medium;
}
