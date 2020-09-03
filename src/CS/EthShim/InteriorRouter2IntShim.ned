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


package rina.src.CS.EthShim;

import rina.src.DAF.DA.DIFAllocator;
import rina.src.DIF.IPCProcess;
import rina.src.EthShimDIF.IPCProcessShim;

module InteriorRouter2IntShim
{
    parameters:
        @display("i=abstract/switch;bgb=290,230");
        @networkNode;

    gates:
        inout medium[2];

    submodules:
        ipcProcessShim0: IPCProcessShim {
            @display("p=75,169");
        }

        ipcProcessShim1: IPCProcessShim {
            @display("p=215,169");
        }

        relayIpc: IPCProcess {
            @display("p=145,77;i=,#FFB000");
            relay = true;
        }

        difAllocator: DIFAllocator {
            @display("p=65,53");
        }

    connections:
        ipcProcessShim0.southIo <--> medium[0];
        ipcProcessShim1.southIo <--> medium[1];
        relayIpc.southIo++ <--> ipcProcessShim0.northIo;
        relayIpc.southIo++ <--> ipcProcessShim1.northIo;
}
