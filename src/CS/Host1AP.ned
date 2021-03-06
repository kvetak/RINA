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
// <h1>Host with one Application Process</h1> 
//
// This models simulates host node that has two different rank DIFs:
//  * 1x (N)-DIF <i>ipcProcess1</i> is used by AP for communication 
//  * 1x (N-1)-DIF <i>ipcProcess0</i> underlaying DIF for <i>ipcProcess1</i>   
//
// It contains one AP called <i>applicationProcces1</i>
// It also contains <i>DIFAllocator</i> module as NameSpaceManager interface
//
// @author Vladimir Vesely (ivesely@fit.vutbr.cz)
// @date Last refactorized and documented on 2015-01-12


package rina.src.CS;

import rina.src.DAF.ApplicationProcess;
import rina.src.DAF.DA.DIFAllocator;
import rina.src.DAF.IRM.IPCResourceManager;
import rina.src.DIF.IPCProcess;


module Host1AP
{
    parameters:
        @display("i=device/pc;bgb=255,400");
        @node;
        //int numOfDIFs = 1;
        //int numOfAPs = 1;

    gates:
        inout medium @loose;

    submodules:
        applicationProcess1: ApplicationProcess {
            @display("p=70,56");
            //numOfDIFs = numOfDIFs;            
        }

        difAllocator: DIFAllocator {
            @display("p=210,56");
        }

        ipcProcess0: IPCProcess {
            @display("p=133,323");
			//numOfAPs = numOfAPs;
        }

        ipcProcess1: IPCProcess {
            @display("p=133,241");
			//numOfAPs = numOfAPs;
        }

        ipcResourceManager: IPCResourceManager {
            @display("p=133,141");
        }
    connections allowunconnected:
        ipcProcess0.southIo++ <--> medium;
//        ipcProcess0.northIo++ <--> PushBackChannel <--> ipcProcess1.southIo++;
        ipcProcess0.northIo++ <--> ipcProcess1.southIo++;
}
