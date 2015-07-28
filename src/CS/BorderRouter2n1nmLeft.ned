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
// <h1>BorderRouter simulation module</h1> 
//
// This models simulates border router node that has five different rank DIFs:
//  * 1x (N+1)-DIF <i>relayIpc</i> is used as bridge between <i>ipcProccesses</i> for relaying
//  * 2x (N)-DIF <i>ipcProcess1/2/3</i> 
//  * 1x (N-1)-DIF <i>bottomIpc</i> 
//
// It also contains <i>DIFAllocator</i> module as NameSpaceManager interface
//
// @author Vladimir Vesely (ivesely@fit.vutbr.cz)
// @date Last refactorized and documented on 2015-01-12

package rina.src.CS;

import rina.src.DAF.DA.DIFAllocator;
import rina.src.DIF.IPCProcess;

module BorderRouter2n1nmLeft
{
    @display("i=abstract/router;bgb=281,317");
    @node;
    gates:
        inout medium[2];
    submodules:
        ipcProcess1: IPCProcess {
            @display("p=214,165");
        }
        bottomIpc: IPCProcess {
            @display("p=65,248;i=,#FF4000");
        }
        relayIpc: IPCProcess {
            @display("p=144,78;i=,#FFB000");
            relay = true;
        }
        ipcProcess2: IPCProcess {
            @display("p=65,160");
        }
        difAllocator: DIFAllocator {
            @display("p=66,39");
        }
    connections:
        ipcProcess1.southIo++ <--> medium[0];
        bottomIpc.southIo++ <--> medium[1];
        relayIpc.southIo++ <--> ipcProcess1.northIo++;
        relayIpc.southIo++ <--> ipcProcess2.northIo++;
        ipcProcess2.southIo++ <--> bottomIpc.northIo++;
}
