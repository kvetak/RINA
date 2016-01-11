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

package rina.src.CS;

import rina.src.DAF.ApplicationProcess;
import rina.src.DAF.DA.DIFAllocator;
import rina.src.DAF.IRM.IPCResourceManager;
import rina.src.DIF.IPCProcess;


module HostNAP
{
    parameters:
        @display("i=device/pc;bgb=255,400");
        @node;

        int nofAP = default(1);

    gates:
        inout medium @loose;

    submodules:
        AP[nofAP]: ApplicationProcess {
            @display("p=70,56");
        }

        difAllocator: DIFAllocator {
            @display("p=210,56");
        }

        ipcProcess0: IPCProcess {
            @display("p=133,323");
        }

        ipcProcess1: IPCProcess {
            @display("p=132,241");
        }

        ipcResourceManager: IPCResourceManager {
            @display("p=132,141");
        }
    connections allowunconnected:
        ipcProcess0.southIo++ <--> medium;
        ipcProcess0.northIo++ <--> ipcProcess1.southIo++;
}
