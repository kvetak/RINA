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


package rina.src.Addons.DataInjectors.CS;

import rina.playground.DAF.AE.AEVideo.AEVideo;
import rina.src.DAF.DA.DIFAllocator;
import rina.src.DIF.IPCProcess;

import rina.src.Addons.DataInjectors.Infection_t;

module Inf_Router
{
    parameters:
        @display("i=abstract/switch;bgb=391,325");
        @node;
        string InjectorName;

    gates:
        inout medium[];

    submodules:
        ipcProcess0[sizeof(medium)]: IPCProcess {
            @display("p=180,237");
        }
        ipcProcess1: IPCProcess {
            @display("p=180,155;i=,#FFB000");
            relay = true;
        }
        ipcProcess2: IPCProcess {
            @display("p=180,53;i=,#FFB000");
            relay = true;
        }
        difAllocator: DIFAllocator {
            @display("p=104,53");
        }

        Inj: <InjectorName> like Infection_t {
            @display("p=342,46");
            infectedIPC = default("ipcProcess2");
        }
    connections allowunconnected:
        ipcProcess2.southIo++ <--> ipcProcess1.northIo++;

        // Every IPC Process is connected to its medium and the Relay IPC.
        for i=0..sizeof(medium)-1 {
            ipcProcess1.southIo++ <--> ipcProcess0[i].northIo++;
            ipcProcess0[i].southIo++ <--> medium[i];
        }
}
