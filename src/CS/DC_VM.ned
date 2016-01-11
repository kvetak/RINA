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
// This module describes a single VM in the DataCenter use-case.
// Servers can be owned by only one Tenant per time.
//
// Colors of the IPC reflect the use case layers.
// Link: https://wiki.ict-pristine.eu/wp2/d21/D21-Datnet-RINA

package rina.src.CS;

import rina.src.DAF.ApplicationProcess;
import rina.src.DAF.DA.DIFAllocator;
import rina.src.DAF.IRM.IPCResourceManager;
import rina.src.DIF.IPCProcess;


module DC_VM
{
    parameters:
        @display("i=device/terminal;bgb=214,348");
        @node;

    gates:
        inout medium;

    submodules:
        AP: ApplicationProcess {
            @display("p=58,43");
        }

        difAllocator: DIFAllocator {
            @display("p=156,43;i=,grey");
        }

        ipcResourceManager: IPCResourceManager {
            @display("p=110,121");
        }

        TenantIPC: IPCProcess {
            @display("p=110,211;i=,#0080FF");
        }

        ShimIPC: IPCProcess {
            @display("p=110,293;i=,#800000");
        }

    connections allowunconnected:
        ShimIPC.southIo++ <--> medium;
        ShimIPC.northIo++ <--> TenantIPC.southIo++;
}
