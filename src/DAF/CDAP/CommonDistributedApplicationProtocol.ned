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

package rina.src.DAF.CDAP;

module CommonDistributedApplicationProtocol
{
    parameters:
        @display("bgb=331,242;i=block/circle");
        int currentInvokeId = (intuniform(0,65535)*1000);
    gates:
        inout southIo;

    submodules:
        cace: CACE {
            @display("p=63,59");
        }
        auth: Auth {
            @display("p=163,60");
        }
        cdap: CDAP {
            @display("p=260,60");
        }
        cdapSplitter: CDAPSplitter {
            @display("p=163,156");
        }

        cdapMsgLog: CDAPMsgLog {
            @display("p=260,156");
        }

    connections allowunconnected:
        cace.splitterIo <--> cdapSplitter.caceIo;
        auth.splitterIo <--> cdapSplitter.authIo;
        cdap.splitterIo <--> cdapSplitter.cdapIo;
        cdapSplitter.southIo <--> southIo;
}
