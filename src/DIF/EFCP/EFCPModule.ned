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


package rina.src.DIF.EFCP;

import rina.src.DIF.EFCP.EFCPTable.EFCPTable;

module EFCPModule
{
    
    parameters:
        @display("i=block/layer;bgb=405,261");
        bool interrupter = default(false);
        int maxSDUSize @unit(B) = default(150000B);
        int maxPDUSize @unit(B) = default(1500B);
        double delimitDelay @unit(s) = default (0s);
        
    gates:
        //        inout faIo[];
        //        inout rmtIo[];
        inout ribd;
        inout mockToRMT;

    submodules:
        efcpTable: EFCPTable {
            @display("p=151,44");
        }
        efcp: EFCP {
            @display("p=52,44;i=block/circle");
        }


        mockEFCPI: MockEFCPI {
            @display("p=261,44");
        }
    connections allowunconnected:
        //        efcp.rmtIo <--> rmtIo++;
        mockEFCPI.northIo <--> ribd;
        mockEFCPI.southIo <--> mockToRMT;

}
