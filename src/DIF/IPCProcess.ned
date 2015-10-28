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

package rina.src.DIF;

import rina.src.DIF.EFCP.EFCPModule;
import rina.src.DIF.Enrollment.EnrollmentModule;
import rina.src.DIF.FA.FlowAllocator;
import rina.src.DIF.RA.ResourceAllocator;
import rina.src.DIF.RIB.RIBDaemon;
import rina.src.DIF.RMT.RelayAndMux;
import rina.src.DIF.Routing.IntRouting;

module IPCProcess
{
    parameters:
        @display("bgb=457,307;i=misc/square,#FF8000,50");
        string ipcAddress;
        string difName;
        string apName = default(ipcAddress + "_" + difName);
        bool relay = default(false);
        string routingPolicyName = default("DummyRouting");
        
        bool onWire = default(false);
        
    gates:
        inout southIo[];
        inout northIo[];
    submodules:
        flowAllocator: FlowAllocator {
            @display("p=167,50");
        }
        relayAndMux: RelayAndMux {
            @display("p=79,249;i=block/dispatch");
        }
        ribDaemon: RIBDaemon {
            @display("p=229,153");
        }

        efcp: EFCPModule {
            @display("p=79,50");
        }
        enrollment: EnrollmentModule {
            @display("p=390,50");
        }
        routingPolicy: <routingPolicyName> like IntRouting {
            @display("p=390,153");
        }
        resourceAllocator: ResourceAllocator {
            @display("p=390,249");
            onWire = onWire;
        }

    connections allowunconnected:
        relayAndMux.ribdIo <--> efcp.mockToRMT;
        ribDaemon.efcpIo <--> efcp.ribd;

}
