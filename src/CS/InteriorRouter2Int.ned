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

//
// <h1>Interior router simulation module with two interfaces</h1> 
//
// This models simulates interior router node that has three different rank DIFs:
//  * 1x (N)-DIF <i>relayIpc</i> is used as bridge between <i>ipcProccesses</i> for relaying 
//  * 2x (N-1)-DIF <i>ipcProccesses0/1</i> 
//
// It also contains <i>DIFAllocator</i> module as NameSpaceManager interface
//
// @author Vladimir Vesely (ivesely@fit.vutbr.cz), Tomas Hykel
// @date Last refactorized and documented on 2015-01-12


package rina.src.CS;

import rina.src.DAF.DA.DIFAllocator;
import rina.src.DIF.IPCProcess;


module InteriorRouter2Int
{
    @display("i=abstract/switch;bgb=290,230");
    @node;
    gates:
        inout medium[2];
    submodules:
        ipcProcess0: IPCProcess {
            @display("p=75,169");
        }
        ipcProcess1: IPCProcess {
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
        ipcProcess0.southIo++ <--> medium[0];
        ipcProcess1.southIo++ <--> medium[1];
        relayIpc.southIo++ <--> ipcProcess0.northIo++;
        relayIpc.southIo++ <--> ipcProcess1.northIo++;
}
