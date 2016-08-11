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

package rina.examples.Routing.DCVfib;

import ned.DelayChannel;
import rina.src.CS.*;
import rina.src.DAF.IRM.ConnectionTable;
import rina.src.DIF.EFCP.DTCP.*;
import rina.src.CS.*;

network DistributedCloudsVfib
{
    submodules:
        VIFIBN10: VIFIBNode1 {
            @display("p=307,263");
        }
        VIFIBN1: VIFIBNodeGL3 {
            @display("p=245,200");
        }
        VIFIBN3: VIFIBNode2 {
            @display("p=187,263");
        }
        VIFIBN8: VIFIBNode1 {
            @display("p=405,56");
        }
        VIFIBN2: VIFIBNodeGL3 {
            @display("p=65,56");
        }
        VIFIBN5: VIFIBNode2 {
            @display("p=237,38");
        }
        VIFIBN4: VIFIBNode2 {
            @display("p=297,155");
        }
        VIFIBN9: VIFIBNode2 {
            @display("p=427,155");
        }
        VIFIBN6: VIFIBNode2 {
            @display("p=68,214");
        }
        VIFIBN7: VIFIBNode2 {
            @display("p=155,85");
        }
    connections:
        VIFIBN8.medium++ <--> DelayChannel {  delay = 80ms; } <--> VIFIBN4.medium++;
        VIFIBN4.medium++ <--> DelayChannel {  delay = 40ms; } <--> VIFIBN9.medium++;
        VIFIBN9.medium++ <--> DelayChannel {  delay = 30ms; } <--> VIFIBN5.medium++;
        VIFIBN5.medium++ <--> DelayChannel {  delay = 90ms; } <--> VIFIBN7.medium++;
        VIFIBN2.medium++ <--> DelayChannel {  delay = 80ms; } <--> VIFIBN7.medium++;
        VIFIBN1.medium++ <--> DelayChannel {  delay = 50ms; } <--> VIFIBN2.medium++;
        VIFIBN1.medium++ <--> DelayChannel {  delay = 50ms; } <--> VIFIBN3.medium++;
        VIFIBN2.medium++ <--> DelayChannel {  delay = 50ms; } <--> VIFIBN6.medium++;
        VIFIBN6.medium++ <--> DelayChannel {  delay = 50ms; } <--> VIFIBN3.medium++;
        VIFIBN1.medium++ <--> DelayChannel {  delay = 50ms; } <--> VIFIBN10.medium++;
}
