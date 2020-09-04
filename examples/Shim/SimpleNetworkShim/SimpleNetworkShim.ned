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

package rina.examples.Shim.SimpleNetworkShim;

import rina.src.CS.EthShim.Host1APShim;
import rina.src.CS.EthShim.InteriorRouter2IntShim;

import inet.node.ethernet.Eth100M;
import inet.node.ethernet.EtherSwitch;


network SimpleNetworkShim
{
    @display("bgb=492,282");
    submodules:
        host11: Host1APShim {
            @display("p=64,62");
        }
        host12: Host1APShim {
            @display("p=64,123");
        }
        host13: Host1APShim {
            @display("p=64,187");
        }
        switch1: EtherSwitch {
            @display("p=151,122");
        }
        interiorRouter: InteriorRouter2IntShim {
            @display("p=250,123");
        }
        switch2: EtherSwitch {
            @display("p=349,122");
        }
        host21: Host1APShim {
            @display("p=441,62");
        }
        host22: Host1APShim {
            @display("p=441,123");
        }
        host23: Host1APShim {
            @display("p=441,187");
        }
    connections allowunconnected:
        host11.medium <--> Eth100M <--> switch1.ethg++;
        host12.medium <--> Eth100M <--> switch1.ethg++;
        host13.medium <--> Eth100M <--> switch1.ethg++;
        interiorRouter.medium++ <--> Eth100M <--> switch1.ethg++;
        interiorRouter.medium++ <--> Eth100M <--> switch2.ethg++;
        host21.medium <--> Eth100M <--> switch2.ethg++;
        host22.medium <--> Eth100M <--> switch2.ethg++;
        host23.medium <--> Eth100M <--> switch2.ethg++;
}
