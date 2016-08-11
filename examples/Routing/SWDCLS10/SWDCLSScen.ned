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

package rina.examples.Routing.SWDCLS10;

import ned.DatarateChannel;
import rina.src.CS.*;
import rina.src.DAF.IRM.ConnectionTable;
import rina.src.DIF.EFCP.DTCP.*;

network SWDCLSScen
{
    submodules:




        VIFIBN9: VIFIBNodeGL3 {
            @display("p=133,92");
        }
        VIFIBN8: VIFIBNode2 {
            @display("p=44,61");
        }
        VIFIBN2: VIFIBNode2 {
            @display("p=105,22");
        }
        VIFIBN1: VIFIBNode1 {
            @display("p=79,118");
        }
        VIFIBN6: VIFIBNodeGL3 {
            @display("p=278,319");
        }
        VIFIBN4: VIFIBNode1 {
            @display("p=215,319");
        }
        VIFIBN7: VIFIBNode4 {
            @display("p=441,118");
        }
        VIFIBN3: VIFIBNode1 {
            @display("p=493,144");
        }
        VIFIBN5: VIFIBNode2 {
            @display("p=511,79");
        }
        VIFIBN10: VIFIBNode1 {
            @display("p=461,48");
        }






    connections:
        VIFIBN2.medium++ <--> DatarateChannel {  delay = 25ms; datarate = 87Mbps; ber = 0; } <--> VIFIBN1.medium++;
        VIFIBN2.medium++ <--> DatarateChannel {  delay = 17ms; datarate = 94Mbps; ber = 0; } <--> VIFIBN8.medium++;
        VIFIBN3.medium++ <--> DatarateChannel {  delay = 42ms; datarate = 96Mbps; ber = 0; } <--> VIFIBN7.medium++;
        VIFIBN4.medium++ <--> DatarateChannel {  delay = 16ms; datarate = 84Mbps; ber = 0; } <--> VIFIBN6.medium++;
        VIFIBN5.medium++ <--> DatarateChannel {  delay = 15ms; datarate = 95Mbps; ber = 0; } <--> VIFIBN10.medium++;
        VIFIBN7.medium++ <--> DatarateChannel {  delay = 20ms; datarate = 91Mbps; ber = 0; } <--> VIFIBN5.medium++;
        VIFIBN8.medium++ <--> DatarateChannel {  delay = 14ms; datarate = 90Mbps; ber = 0; } <--> VIFIBN9.medium++;
        VIFIBN6.medium++ <--> DatarateChannel {  delay = 76ms; datarate = 100Mbps; ber = 0; } <--> VIFIBN7.medium++;
        VIFIBN9.medium++ <--> DatarateChannel {  delay = 83ms; datarate = 100Mbps; ber = 0; } <--> VIFIBN6.medium++;
        VIFIBN9.medium++ <--> DatarateChannel {  delay = 23ms; datarate = 100Mbps; ber = 0; } <--> VIFIBN7.medium++;


}
