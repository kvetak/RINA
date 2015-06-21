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
//
// NOTES:
// This module describes an Aggregator Switch module in the DataCenter use-case.
//
// Colors of the IPC reflect the use case layers.
// Link: https://wiki.ict-pristine.eu/wp2/d21/D21-Datnet-RINA

package rina.src.CS;

import rina.src.DAF.DA.DIFAllocator;
import rina.src.DIF.IPCProcess;

module DC_AS
{
    @display("i=abstract/router2;bgb=177,325");
    @node;

    int nofInt = default(1);

    gates:
        inout medium[nofInt];

    submodules:
        ShimIPC[nofInt]: IPCProcess {
            @display("p=90,255;i=,#800000");
        }
        DCIPC: IPCProcess {
            @display("p=90,151;i=,#008000");
            relay = true;
        }
        difAllocator: DIFAllocator {
            @display("p=90,63;i=,grey");
        }
    connections allowunconnected:

        // Every IPC Process is connected to its medium and the Relay IPC.
        for i=0..nofInt-1 {
            DCIPC.southIo++ <--> ShimIPC[i].northIo++;
            ShimIPC[i].southIo++ <--> medium[i];
        }
}
