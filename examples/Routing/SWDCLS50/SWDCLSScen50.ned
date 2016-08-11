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

package rina.examples.Routing.SWDCLS50;

import ned.DatarateChannel;
import rina.src.CS.*;
import rina.src.DAF.IRM.ConnectionTable;
import rina.src.DIF.EFCP.DTCP.*;

network SWDCLSScen50
{
    submodules:






        VIFIBN1: VIFIBNode23 {
            @display("p=104,87");
        }
        VIFIBN6: VIFIBNode13 {
            @display("p=100,18");
        }
        VIFIBN2: VIFIBNode24 {
            @display("p=179,559");
        }
        VIFIBN7: VIFIBNode13 {
            @display("p=184,513");
        }
        VIFIBN20: VIFIBNode13 {
            @display("p=184,502");
        }
        VIFIBN3: VIFIBNode11 {
            @display("p=185,537");
        }
        VIFIBN5: VIFIBNode13 {
            @display("p=177,585");
        }
        VIFIBN9: VIFIBNode22 {
            @display("p=302,44");
        }
        VIFIBN15: VIFIBNode11 {
            @display("p=302,55");
        }
        VIFIBN14: VIFIBNode23 {
            @display("p=381,596");
        }
        VIFIBN4: VIFIBNode10 {
            @display("p=373,584");
        }
        VIFIBN10: VIFIBNode13 {
            @display("p=381,537");
        }
        VIFIBN12: VIFIBNode12 {
            @display("p=372,566");
        }
        VIFIBN22: VIFIBNode22 {
            @display("p=501,42");
        }
        VIFIBN17: VIFIBNode10 {
            @display("p=504,70");
        }
        VIFIBN13: VIFIBNode11 {
            @display("p=507,90");
        }
        VIFIBN21: VIFIBNode12 {
            @display("p=508,70");
        }
        VIFIBN18: VIFIBNode21 {
            @display("p=736,565");
        }
        VIFIBN11: VIFIBNode13 {
            @display("p=741,596");
        }
        VIFIBN8: VIFIBNode13 {
            @display("p=740,548");
        }
        VIFIBN19: VIFIBNode19 {
            @display("p=702,37");
        }
        VIFIBN16: VIFIBNode13 {
            @display("p=705,77");
        }
        VIFIBN28: VIFIBNode25 {
            @display("p=1181,559");
        }
        VIFIBN37: VIFIBNode10 {
            @display("p=1186,576");
        }
        VIFIBN26: VIFIBNode10 {
            @display("p=1181,531");
        }
        VIFIBN32: VIFIBNode10 {
            @display("p=1180,567");
        }
        VIFIBN27: VIFIBNode23 {
            @display("p=906,90");
        }
        VIFIBN33: VIFIBNode12 {
            @display("p=907,92");
        }
        VIFIBN35: VIFIBNode22 {
            @display("p=1343,602");
        }
        VIFIBN29: VIFIBNode10 {
            @display("p=1389,602");
        }
        VIFIBN46: VIFIBNode6 {
            @display("p=1466,596");
        }
        VIFIBN31: VIFIBNode22 {
            @display("p=1101,68");
        }
        VIFIBN48: VIFIBNode3 {
            @display("p=1109,58");
        }
        VIFIBN43: VIFIBNode9 {
            @display("p=1100,64");
        }
        VIFIBN40: VIFIBNode8 {
            @display("p=1106,97");
        }
        VIFIBN49: VIFIBNode3 {
            @display("p=1105,89");
        }
        VIFIBN45: VIFIBNode8 {
            @display("p=1106,31");
        }
        VIFIBN44: VIFIBNode9 {
            @display("p=1103,70");
        }
        VIFIBN25: VIFIBNode21 {
            @display("p=1530,368");
        }
        VIFIBN41: VIFIBNode7 {
            @display("p=1539,383");
        }
        VIFIBN50: VIFIBNode8 {
            @display("p=1535,347");
        }
        VIFIBN38: VIFIBNode10 {
            @display("p=1574,440");
        }
        VIFIBN24: VIFIBNode21 {
            @display("p=1306,13");
        }
        VIFIBN23: VIFIBNode11 {
            @display("p=1301,18");
        }
        VIFIBN39: VIFIBNode8 {
            @display("p=1308,33");
        }
        VIFIBN30: VIFIBNode10 {
            @display("p=1304,12");
        }
        VIFIBN34: VIFIBNode22 {
            @display("p=1020,602");
        }
        VIFIBN42: VIFIBNode10 {
            @display("p=1028,579");
        }
        VIFIBN36: VIFIBNode22 {
            @display("p=1516,55");
        }
        VIFIBN47: VIFIBNode7 {
            @display("p=1551,109");
        }






    connections:
        VIFIBN1.medium++ <--> DatarateChannel {  delay = 50ms; datarate = 93Mbps; ber = 0; } <--> VIFIBN5.medium++;
        VIFIBN1.medium++ <--> DatarateChannel {  delay = 10ms; datarate = 83Mbps; ber = 0; } <--> VIFIBN6.medium++;
        VIFIBN1.medium++ <--> DatarateChannel {  delay = 48ms; datarate = 86Mbps; ber = 0; } <--> VIFIBN15.medium++;
        VIFIBN1.medium++ <--> DatarateChannel {  delay = 49ms; datarate = 87Mbps; ber = 0; } <--> VIFIBN17.medium++;
        VIFIBN1.medium++ <--> DatarateChannel {  delay = 37ms; datarate = 97Mbps; ber = 0; } <--> VIFIBN18.medium++;
        VIFIBN1.medium++ <--> DatarateChannel {  delay = 44ms; datarate = 97Mbps; ber = 0; } <--> VIFIBN20.medium++;
        VIFIBN1.medium++ <--> DatarateChannel {  delay = 32ms; datarate = 96Mbps; ber = 0; } <--> VIFIBN22.medium++;
        VIFIBN1.medium++ <--> DatarateChannel {  delay = 35ms; datarate = 97Mbps; ber = 0; } <--> VIFIBN25.medium++;
        VIFIBN1.medium++ <--> DatarateChannel {  delay = 50ms; datarate = 94Mbps; ber = 0; } <--> VIFIBN32.medium++;
        VIFIBN1.medium++ <--> DatarateChannel {  delay = 28ms; datarate = 81Mbps; ber = 0; } <--> VIFIBN35.medium++;
        VIFIBN1.medium++ <--> DatarateChannel {  delay = 17ms; datarate = 89Mbps; ber = 0; } <--> VIFIBN39.medium++;
        VIFIBN1.medium++ <--> DatarateChannel {  delay = 54ms; datarate = 85Mbps; ber = 0; } <--> VIFIBN11.medium++;
        VIFIBN2.medium++ <--> DatarateChannel {  delay = 43ms; datarate = 98Mbps; ber = 0; } <--> VIFIBN7.medium++;
        VIFIBN2.medium++ <--> DatarateChannel {  delay = 13ms; datarate = 91Mbps; ber = 0; } <--> VIFIBN11.medium++;
        VIFIBN2.medium++ <--> DatarateChannel {  delay = 40ms; datarate = 82Mbps; ber = 0; } <--> VIFIBN12.medium++;
        VIFIBN2.medium++ <--> DatarateChannel {  delay = 14ms; datarate = 87Mbps; ber = 0; } <--> VIFIBN16.medium++;
        VIFIBN2.medium++ <--> DatarateChannel {  delay = 38ms; datarate = 82Mbps; ber = 0; } <--> VIFIBN19.medium++;
        VIFIBN2.medium++ <--> DatarateChannel {  delay = 55ms; datarate = 91Mbps; ber = 0; } <--> VIFIBN4.medium++;
        VIFIBN2.medium++ <--> DatarateChannel {  delay = 53ms; datarate = 98Mbps; ber = 0; } <--> VIFIBN14.medium++;
        VIFIBN3.medium++ <--> DatarateChannel {  delay = 21ms; datarate = 86Mbps; ber = 0; } <--> VIFIBN1.medium++;
        VIFIBN3.medium++ <--> DatarateChannel {  delay = 38ms; datarate = 91Mbps; ber = 0; } <--> VIFIBN2.medium++;
        VIFIBN3.medium++ <--> DatarateChannel {  delay = 17ms; datarate = 83Mbps; ber = 0; } <--> VIFIBN4.medium++;
        VIFIBN3.medium++ <--> DatarateChannel {  delay = 14ms; datarate = 86Mbps; ber = 0; } <--> VIFIBN5.medium++;
        VIFIBN3.medium++ <--> DatarateChannel {  delay = 29ms; datarate = 90Mbps; ber = 0; } <--> VIFIBN6.medium++;
        VIFIBN3.medium++ <--> DatarateChannel {  delay = 11ms; datarate = 93Mbps; ber = 0; } <--> VIFIBN7.medium++;
        VIFIBN3.medium++ <--> DatarateChannel {  delay = 44ms; datarate = 98Mbps; ber = 0; } <--> VIFIBN12.medium++;
        VIFIBN3.medium++ <--> DatarateChannel {  delay = 11ms; datarate = 89Mbps; ber = 0; } <--> VIFIBN13.medium++;
        VIFIBN3.medium++ <--> DatarateChannel {  delay = 17ms; datarate = 81Mbps; ber = 0; } <--> VIFIBN15.medium++;
        VIFIBN3.medium++ <--> DatarateChannel {  delay = 41ms; datarate = 96Mbps; ber = 0; } <--> VIFIBN16.medium++;
        VIFIBN3.medium++ <--> DatarateChannel {  delay = 42ms; datarate = 91Mbps; ber = 0; } <--> VIFIBN17.medium++;
        VIFIBN4.medium++ <--> DatarateChannel {  delay = 26ms; datarate = 92Mbps; ber = 0; } <--> VIFIBN8.medium++;
        VIFIBN4.medium++ <--> DatarateChannel {  delay = 46ms; datarate = 99Mbps; ber = 0; } <--> VIFIBN10.medium++;
        VIFIBN5.medium++ <--> DatarateChannel {  delay = 19ms; datarate = 94Mbps; ber = 0; } <--> VIFIBN4.medium++;
        VIFIBN5.medium++ <--> DatarateChannel {  delay = 50ms; datarate = 91Mbps; ber = 0; } <--> VIFIBN6.medium++;
        VIFIBN5.medium++ <--> DatarateChannel {  delay = 19ms; datarate = 92Mbps; ber = 0; } <--> VIFIBN7.medium++;
        VIFIBN5.medium++ <--> DatarateChannel {  delay = 36ms; datarate = 82Mbps; ber = 0; } <--> VIFIBN8.medium++;
        VIFIBN5.medium++ <--> DatarateChannel {  delay = 35ms; datarate = 99Mbps; ber = 0; } <--> VIFIBN9.medium++;
        VIFIBN5.medium++ <--> DatarateChannel {  delay = 41ms; datarate = 82Mbps; ber = 0; } <--> VIFIBN13.medium++;
        VIFIBN5.medium++ <--> DatarateChannel {  delay = 29ms; datarate = 88Mbps; ber = 0; } <--> VIFIBN14.medium++;
        VIFIBN5.medium++ <--> DatarateChannel {  delay = 56ms; datarate = 85Mbps; ber = 0; } <--> VIFIBN10.medium++;
        VIFIBN5.medium++ <--> DatarateChannel {  delay = 54ms; datarate = 98Mbps; ber = 0; } <--> VIFIBN12.medium++;
        VIFIBN5.medium++ <--> DatarateChannel {  delay = 49ms; datarate = 88Mbps; ber = 0; } <--> VIFIBN15.medium++;
        VIFIBN5.medium++ <--> DatarateChannel {  delay = 47ms; datarate = 85Mbps; ber = 0; } <--> VIFIBN17.medium++;
        VIFIBN6.medium++ <--> DatarateChannel {  delay = 19ms; datarate = 87Mbps; ber = 0; } <--> VIFIBN2.medium++;
        VIFIBN6.medium++ <--> DatarateChannel {  delay = 44ms; datarate = 93Mbps; ber = 0; } <--> VIFIBN4.medium++;
        VIFIBN6.medium++ <--> DatarateChannel {  delay = 48ms; datarate = 80Mbps; ber = 0; } <--> VIFIBN7.medium++;
        VIFIBN6.medium++ <--> DatarateChannel {  delay = 40ms; datarate = 91Mbps; ber = 0; } <--> VIFIBN12.medium++;
        VIFIBN6.medium++ <--> DatarateChannel {  delay = 24ms; datarate = 99Mbps; ber = 0; } <--> VIFIBN13.medium++;
        VIFIBN6.medium++ <--> DatarateChannel {  delay = 29ms; datarate = 88Mbps; ber = 0; } <--> VIFIBN14.medium++;
        VIFIBN6.medium++ <--> DatarateChannel {  delay = 53ms; datarate = 93Mbps; ber = 0; } <--> VIFIBN9.medium++;
        VIFIBN6.medium++ <--> DatarateChannel {  delay = 58ms; datarate = 81Mbps; ber = 0; } <--> VIFIBN10.medium++;
        VIFIBN6.medium++ <--> DatarateChannel {  delay = 19ms; datarate = 91Mbps; ber = 0; } <--> VIFIBN20.medium++;
        VIFIBN6.medium++ <--> DatarateChannel {  delay = 28ms; datarate = 94Mbps; ber = 0; } <--> VIFIBN26.medium++;
        VIFIBN7.medium++ <--> DatarateChannel {  delay = 32ms; datarate = 99Mbps; ber = 0; } <--> VIFIBN4.medium++;
        VIFIBN7.medium++ <--> DatarateChannel {  delay = 22ms; datarate = 81Mbps; ber = 0; } <--> VIFIBN8.medium++;
        VIFIBN7.medium++ <--> DatarateChannel {  delay = 37ms; datarate = 91Mbps; ber = 0; } <--> VIFIBN9.medium++;
        VIFIBN7.medium++ <--> DatarateChannel {  delay = 45ms; datarate = 82Mbps; ber = 0; } <--> VIFIBN10.medium++;
        VIFIBN7.medium++ <--> DatarateChannel {  delay = 41ms; datarate = 80Mbps; ber = 0; } <--> VIFIBN13.medium++;
        VIFIBN7.medium++ <--> DatarateChannel {  delay = 33ms; datarate = 93Mbps; ber = 0; } <--> VIFIBN21.medium++;
        VIFIBN8.medium++ <--> DatarateChannel {  delay = 22ms; datarate = 85Mbps; ber = 0; } <--> VIFIBN14.medium++;
        VIFIBN8.medium++ <--> DatarateChannel {  delay = 57ms; datarate = 81Mbps; ber = 0; } <--> VIFIBN9.medium++;
        VIFIBN8.medium++ <--> DatarateChannel {  delay = 25ms; datarate = 99Mbps; ber = 0; } <--> VIFIBN23.medium++;
        VIFIBN10.medium++ <--> DatarateChannel {  delay = 13ms; datarate = 82Mbps; ber = 0; } <--> VIFIBN14.medium++;
        VIFIBN10.medium++ <--> DatarateChannel {  delay = 23ms; datarate = 93Mbps; ber = 0; } <--> VIFIBN24.medium++;
        VIFIBN10.medium++ <--> DatarateChannel {  delay = 36ms; datarate = 87Mbps; ber = 0; } <--> VIFIBN26.medium++;
        VIFIBN10.medium++ <--> DatarateChannel {  delay = 14ms; datarate = 85Mbps; ber = 0; } <--> VIFIBN27.medium++;
        VIFIBN10.medium++ <--> DatarateChannel {  delay = 26ms; datarate = 82Mbps; ber = 0; } <--> VIFIBN29.medium++;
        VIFIBN11.medium++ <--> DatarateChannel {  delay = 33ms; datarate = 84Mbps; ber = 0; } <--> VIFIBN4.medium++;
        VIFIBN11.medium++ <--> DatarateChannel {  delay = 30ms; datarate = 94Mbps; ber = 0; } <--> VIFIBN8.medium++;
        VIFIBN11.medium++ <--> DatarateChannel {  delay = 20ms; datarate = 85Mbps; ber = 0; } <--> VIFIBN9.medium++;
        VIFIBN11.medium++ <--> DatarateChannel {  delay = 13ms; datarate = 93Mbps; ber = 0; } <--> VIFIBN16.medium++;
        VIFIBN11.medium++ <--> DatarateChannel {  delay = 19ms; datarate = 93Mbps; ber = 0; } <--> VIFIBN19.medium++;
        VIFIBN11.medium++ <--> DatarateChannel {  delay = 17ms; datarate = 88Mbps; ber = 0; } <--> VIFIBN23.medium++;
        VIFIBN11.medium++ <--> DatarateChannel {  delay = 41ms; datarate = 85Mbps; ber = 0; } <--> VIFIBN24.medium++;
        VIFIBN12.medium++ <--> DatarateChannel {  delay = 24ms; datarate = 95Mbps; ber = 0; } <--> VIFIBN4.medium++;
        VIFIBN12.medium++ <--> DatarateChannel {  delay = 38ms; datarate = 82Mbps; ber = 0; } <--> VIFIBN8.medium++;
        VIFIBN12.medium++ <--> DatarateChannel {  delay = 14ms; datarate = 99Mbps; ber = 0; } <--> VIFIBN14.medium++;
        VIFIBN12.medium++ <--> DatarateChannel {  delay = 26ms; datarate = 95Mbps; ber = 0; } <--> VIFIBN31.medium++;
        VIFIBN13.medium++ <--> DatarateChannel {  delay = 13ms; datarate = 85Mbps; ber = 0; } <--> VIFIBN21.medium++;
        VIFIBN13.medium++ <--> DatarateChannel {  delay = 13ms; datarate = 84Mbps; ber = 0; } <--> VIFIBN24.medium++;
        VIFIBN13.medium++ <--> DatarateChannel {  delay = 44ms; datarate = 83Mbps; ber = 0; } <--> VIFIBN26.medium++;
        VIFIBN13.medium++ <--> DatarateChannel {  delay = 17ms; datarate = 99Mbps; ber = 0; } <--> VIFIBN27.medium++;
        VIFIBN13.medium++ <--> DatarateChannel {  delay = 54ms; datarate = 83Mbps; ber = 0; } <--> VIFIBN28.medium++;
        VIFIBN14.medium++ <--> DatarateChannel {  delay = 77ms; datarate = 91Mbps; ber = 0; } <--> VIFIBN47.medium++;
        VIFIBN15.medium++ <--> DatarateChannel {  delay = 38ms; datarate = 85Mbps; ber = 0; } <--> VIFIBN4.medium++;
        VIFIBN15.medium++ <--> DatarateChannel {  delay = 44ms; datarate = 99Mbps; ber = 0; } <--> VIFIBN7.medium++;
        VIFIBN15.medium++ <--> DatarateChannel {  delay = 27ms; datarate = 88Mbps; ber = 0; } <--> VIFIBN8.medium++;
        VIFIBN15.medium++ <--> DatarateChannel {  delay = 19ms; datarate = 98Mbps; ber = 0; } <--> VIFIBN9.medium++;
        VIFIBN15.medium++ <--> DatarateChannel {  delay = 46ms; datarate = 84Mbps; ber = 0; } <--> VIFIBN12.medium++;
        VIFIBN15.medium++ <--> DatarateChannel {  delay = 50ms; datarate = 99Mbps; ber = 0; } <--> VIFIBN13.medium++;
        VIFIBN15.medium++ <--> DatarateChannel {  delay = 29ms; datarate = 82Mbps; ber = 0; } <--> VIFIBN20.medium++;
        VIFIBN15.medium++ <--> DatarateChannel {  delay = 52ms; datarate = 99Mbps; ber = 0; } <--> VIFIBN2.medium++;
        VIFIBN16.medium++ <--> DatarateChannel {  delay = 14ms; datarate = 93Mbps; ber = 0; } <--> VIFIBN8.medium++;
        VIFIBN16.medium++ <--> DatarateChannel {  delay = 46ms; datarate = 97Mbps; ber = 0; } <--> VIFIBN9.medium++;
        VIFIBN16.medium++ <--> DatarateChannel {  delay = 39ms; datarate = 93Mbps; ber = 0; } <--> VIFIBN10.medium++;
        VIFIBN16.medium++ <--> DatarateChannel {  delay = 20ms; datarate = 92Mbps; ber = 0; } <--> VIFIBN14.medium++;
        VIFIBN16.medium++ <--> DatarateChannel {  delay = 10ms; datarate = 89Mbps; ber = 0; } <--> VIFIBN19.medium++;
        VIFIBN16.medium++ <--> DatarateChannel {  delay = 20ms; datarate = 80Mbps; ber = 0; } <--> VIFIBN23.medium++;
        VIFIBN16.medium++ <--> DatarateChannel {  delay = 13ms; datarate = 82Mbps; ber = 0; } <--> VIFIBN27.medium++;
        VIFIBN17.medium++ <--> DatarateChannel {  delay = 33ms; datarate = 96Mbps; ber = 0; } <--> VIFIBN2.medium++;
        VIFIBN17.medium++ <--> DatarateChannel {  delay = 36ms; datarate = 94Mbps; ber = 0; } <--> VIFIBN8.medium++;
        VIFIBN17.medium++ <--> DatarateChannel {  delay = 24ms; datarate = 90Mbps; ber = 0; } <--> VIFIBN9.medium++;
        VIFIBN17.medium++ <--> DatarateChannel {  delay = 18ms; datarate = 91Mbps; ber = 0; } <--> VIFIBN11.medium++;
        VIFIBN17.medium++ <--> DatarateChannel {  delay = 45ms; datarate = 80Mbps; ber = 0; } <--> VIFIBN12.medium++;
        VIFIBN17.medium++ <--> DatarateChannel {  delay = 15ms; datarate = 86Mbps; ber = 0; } <--> VIFIBN13.medium++;
        VIFIBN17.medium++ <--> DatarateChannel {  delay = 17ms; datarate = 91Mbps; ber = 0; } <--> VIFIBN14.medium++;
        VIFIBN18.medium++ <--> DatarateChannel {  delay = 30ms; datarate = 96Mbps; ber = 0; } <--> VIFIBN7.medium++;
        VIFIBN18.medium++ <--> DatarateChannel {  delay = 10ms; datarate = 94Mbps; ber = 0; } <--> VIFIBN8.medium++;
        VIFIBN18.medium++ <--> DatarateChannel {  delay = 37ms; datarate = 85Mbps; ber = 0; } <--> VIFIBN10.medium++;
        VIFIBN18.medium++ <--> DatarateChannel {  delay = 12ms; datarate = 96Mbps; ber = 0; } <--> VIFIBN11.medium++;
        VIFIBN18.medium++ <--> DatarateChannel {  delay = 46ms; datarate = 85Mbps; ber = 0; } <--> VIFIBN12.medium++;
        VIFIBN18.medium++ <--> DatarateChannel {  delay = 47ms; datarate = 90Mbps; ber = 0; } <--> VIFIBN16.medium++;
        VIFIBN18.medium++ <--> DatarateChannel {  delay = 20ms; datarate = 85Mbps; ber = 0; } <--> VIFIBN19.medium++;
        VIFIBN18.medium++ <--> DatarateChannel {  delay = 31ms; datarate = 80Mbps; ber = 0; } <--> VIFIBN21.medium++;
        VIFIBN18.medium++ <--> DatarateChannel {  delay = 53ms; datarate = 94Mbps; ber = 0; } <--> VIFIBN9.medium++;
        VIFIBN19.medium++ <--> DatarateChannel {  delay = 45ms; datarate = 86Mbps; ber = 0; } <--> VIFIBN8.medium++;
        VIFIBN19.medium++ <--> DatarateChannel {  delay = 34ms; datarate = 93Mbps; ber = 0; } <--> VIFIBN9.medium++;
        VIFIBN19.medium++ <--> DatarateChannel {  delay = 35ms; datarate = 89Mbps; ber = 0; } <--> VIFIBN23.medium++;
        VIFIBN19.medium++ <--> DatarateChannel {  delay = 35ms; datarate = 98Mbps; ber = 0; } <--> VIFIBN24.medium++;
        VIFIBN19.medium++ <--> DatarateChannel {  delay = 78ms; datarate = 89Mbps; ber = 0; } <--> VIFIBN40.medium++;
        VIFIBN20.medium++ <--> DatarateChannel {  delay = 13ms; datarate = 95Mbps; ber = 0; } <--> VIFIBN2.medium++;
        VIFIBN20.medium++ <--> DatarateChannel {  delay = 16ms; datarate = 95Mbps; ber = 0; } <--> VIFIBN7.medium++;
        VIFIBN20.medium++ <--> DatarateChannel {  delay = 27ms; datarate = 84Mbps; ber = 0; } <--> VIFIBN11.medium++;
        VIFIBN20.medium++ <--> DatarateChannel {  delay = 20ms; datarate = 99Mbps; ber = 0; } <--> VIFIBN21.medium++;
        VIFIBN20.medium++ <--> DatarateChannel {  delay = 45ms; datarate = 94Mbps; ber = 0; } <--> VIFIBN22.medium++;
        VIFIBN20.medium++ <--> DatarateChannel {  delay = 46ms; datarate = 84Mbps; ber = 0; } <--> VIFIBN24.medium++;
        VIFIBN20.medium++ <--> DatarateChannel {  delay = 20ms; datarate = 82Mbps; ber = 0; } <--> VIFIBN26.medium++;
        VIFIBN20.medium++ <--> DatarateChannel {  delay = 36ms; datarate = 83Mbps; ber = 0; } <--> VIFIBN28.medium++;
        VIFIBN20.medium++ <--> DatarateChannel {  delay = 49ms; datarate = 89Mbps; ber = 0; } <--> VIFIBN36.medium++;
        VIFIBN20.medium++ <--> DatarateChannel {  delay = 36ms; datarate = 87Mbps; ber = 0; } <--> VIFIBN42.medium++;
        VIFIBN21.medium++ <--> DatarateChannel {  delay = 13ms; datarate = 94Mbps; ber = 0; } <--> VIFIBN28.medium++;
        VIFIBN21.medium++ <--> DatarateChannel {  delay = 50ms; datarate = 84Mbps; ber = 0; } <--> VIFIBN30.medium++;
        VIFIBN21.medium++ <--> DatarateChannel {  delay = 24ms; datarate = 91Mbps; ber = 0; } <--> VIFIBN33.medium++;
        VIFIBN22.medium++ <--> DatarateChannel {  delay = 22ms; datarate = 96Mbps; ber = 0; } <--> VIFIBN10.medium++;
        VIFIBN22.medium++ <--> DatarateChannel {  delay = 31ms; datarate = 99Mbps; ber = 0; } <--> VIFIBN11.medium++;
        VIFIBN22.medium++ <--> DatarateChannel {  delay = 50ms; datarate = 99Mbps; ber = 0; } <--> VIFIBN16.medium++;
        VIFIBN22.medium++ <--> DatarateChannel {  delay = 13ms; datarate = 94Mbps; ber = 0; } <--> VIFIBN21.medium++;
        VIFIBN22.medium++ <--> DatarateChannel {  delay = 13ms; datarate = 90Mbps; ber = 0; } <--> VIFIBN23.medium++;
        VIFIBN22.medium++ <--> DatarateChannel {  delay = 49ms; datarate = 96Mbps; ber = 0; } <--> VIFIBN24.medium++;
        VIFIBN22.medium++ <--> DatarateChannel {  delay = 40ms; datarate = 89Mbps; ber = 0; } <--> VIFIBN25.medium++;
        VIFIBN22.medium++ <--> DatarateChannel {  delay = 36ms; datarate = 95Mbps; ber = 0; } <--> VIFIBN29.medium++;
        VIFIBN22.medium++ <--> DatarateChannel {  delay = 16ms; datarate = 88Mbps; ber = 0; } <--> VIFIBN30.medium++;
        VIFIBN22.medium++ <--> DatarateChannel {  delay = 20ms; datarate = 91Mbps; ber = 0; } <--> VIFIBN36.medium++;
        VIFIBN22.medium++ <--> DatarateChannel {  delay = 26ms; datarate = 93Mbps; ber = 0; } <--> VIFIBN2.medium++;
        VIFIBN23.medium++ <--> DatarateChannel {  delay = 26ms; datarate = 97Mbps; ber = 0; } <--> VIFIBN21.medium++;
        VIFIBN23.medium++ <--> DatarateChannel {  delay = 38ms; datarate = 92Mbps; ber = 0; } <--> VIFIBN28.medium++;
        VIFIBN24.medium++ <--> DatarateChannel {  delay = 10ms; datarate = 85Mbps; ber = 0; } <--> VIFIBN23.medium++;
        VIFIBN24.medium++ <--> DatarateChannel {  delay = 25ms; datarate = 82Mbps; ber = 0; } <--> VIFIBN26.medium++;
        VIFIBN24.medium++ <--> DatarateChannel {  delay = 14ms; datarate = 92Mbps; ber = 0; } <--> VIFIBN27.medium++;
        VIFIBN25.medium++ <--> DatarateChannel {  delay = 38ms; datarate = 97Mbps; ber = 0; } <--> VIFIBN23.medium++;
        VIFIBN25.medium++ <--> DatarateChannel {  delay = 14ms; datarate = 83Mbps; ber = 0; } <--> VIFIBN24.medium++;
        VIFIBN25.medium++ <--> DatarateChannel {  delay = 27ms; datarate = 93Mbps; ber = 0; } <--> VIFIBN26.medium++;
        VIFIBN25.medium++ <--> DatarateChannel {  delay = 39ms; datarate = 91Mbps; ber = 0; } <--> VIFIBN27.medium++;
        VIFIBN25.medium++ <--> DatarateChannel {  delay = 42ms; datarate = 99Mbps; ber = 0; } <--> VIFIBN34.medium++;
        VIFIBN25.medium++ <--> DatarateChannel {  delay = 35ms; datarate = 89Mbps; ber = 0; } <--> VIFIBN36.medium++;
        VIFIBN25.medium++ <--> DatarateChannel {  delay = 39ms; datarate = 86Mbps; ber = 0; } <--> VIFIBN37.medium++;
        VIFIBN25.medium++ <--> DatarateChannel {  delay = 41ms; datarate = 94Mbps; ber = 0; } <--> VIFIBN39.medium++;
        VIFIBN25.medium++ <--> DatarateChannel {  delay = 26ms; datarate = 98Mbps; ber = 0; } <--> VIFIBN41.medium++;
        VIFIBN25.medium++ <--> DatarateChannel {  delay = 34ms; datarate = 93Mbps; ber = 0; } <--> VIFIBN43.medium++;
        VIFIBN25.medium++ <--> DatarateChannel {  delay = 29ms; datarate = 87Mbps; ber = 0; } <--> VIFIBN12.medium++;
        VIFIBN26.medium++ <--> DatarateChannel {  delay = 32ms; datarate = 92Mbps; ber = 0; } <--> VIFIBN21.medium++;
        VIFIBN26.medium++ <--> DatarateChannel {  delay = 33ms; datarate = 90Mbps; ber = 0; } <--> VIFIBN23.medium++;
        VIFIBN26.medium++ <--> DatarateChannel {  delay = 18ms; datarate = 88Mbps; ber = 0; } <--> VIFIBN28.medium++;
        VIFIBN26.medium++ <--> DatarateChannel {  delay = 22ms; datarate = 88Mbps; ber = 0; } <--> VIFIBN29.medium++;
        VIFIBN27.medium++ <--> DatarateChannel {  delay = 26ms; datarate = 93Mbps; ber = 0; } <--> VIFIBN21.medium++;
        VIFIBN27.medium++ <--> DatarateChannel {  delay = 29ms; datarate = 97Mbps; ber = 0; } <--> VIFIBN23.medium++;
        VIFIBN27.medium++ <--> DatarateChannel {  delay = 49ms; datarate = 97Mbps; ber = 0; } <--> VIFIBN29.medium++;
        VIFIBN27.medium++ <--> DatarateChannel {  delay = 24ms; datarate = 94Mbps; ber = 0; } <--> VIFIBN30.medium++;
        VIFIBN27.medium++ <--> DatarateChannel {  delay = 10ms; datarate = 82Mbps; ber = 0; } <--> VIFIBN33.medium++;
        VIFIBN27.medium++ <--> DatarateChannel {  delay = 26ms; datarate = 81Mbps; ber = 0; } <--> VIFIBN36.medium++;
        VIFIBN27.medium++ <--> DatarateChannel {  delay = 44ms; datarate = 85Mbps; ber = 0; } <--> VIFIBN37.medium++;
        VIFIBN28.medium++ <--> DatarateChannel {  delay = 19ms; datarate = 87Mbps; ber = 0; } <--> VIFIBN30.medium++;
        VIFIBN28.medium++ <--> DatarateChannel {  delay = 39ms; datarate = 81Mbps; ber = 0; } <--> VIFIBN33.medium++;
        VIFIBN28.medium++ <--> DatarateChannel {  delay = 15ms; datarate = 88Mbps; ber = 0; } <--> VIFIBN37.medium++;
        VIFIBN28.medium++ <--> DatarateChannel {  delay = 31ms; datarate = 81Mbps; ber = 0; } <--> VIFIBN40.medium++;
        VIFIBN29.medium++ <--> DatarateChannel {  delay = 25ms; datarate = 91Mbps; ber = 0; } <--> VIFIBN37.medium++;
        VIFIBN29.medium++ <--> DatarateChannel {  delay = 29ms; datarate = 81Mbps; ber = 0; } <--> VIFIBN38.medium++;
        VIFIBN29.medium++ <--> DatarateChannel {  delay = 78ms; datarate = 94Mbps; ber = 0; } <--> VIFIBN44.medium++;
        VIFIBN29.medium++ <--> DatarateChannel {  delay = 17ms; datarate = 81Mbps; ber = 0; } <--> VIFIBN46.medium++;
        VIFIBN30.medium++ <--> DatarateChannel {  delay = 45ms; datarate = 83Mbps; ber = 0; } <--> VIFIBN33.medium++;
        VIFIBN30.medium++ <--> DatarateChannel {  delay = 46ms; datarate = 96Mbps; ber = 0; } <--> VIFIBN34.medium++;
        VIFIBN30.medium++ <--> DatarateChannel {  delay = 26ms; datarate = 95Mbps; ber = 0; } <--> VIFIBN38.medium++;
        VIFIBN31.medium++ <--> DatarateChannel {  delay = 12ms; datarate = 85Mbps; ber = 0; } <--> VIFIBN44.medium++;
        VIFIBN31.medium++ <--> DatarateChannel {  delay = 11ms; datarate = 80Mbps; ber = 0; } <--> VIFIBN45.medium++;
        VIFIBN31.medium++ <--> DatarateChannel {  delay = 48ms; datarate = 89Mbps; ber = 0; } <--> VIFIBN46.medium++;
        VIFIBN31.medium++ <--> DatarateChannel {  delay = 49ms; datarate = 94Mbps; ber = 0; } <--> VIFIBN50.medium++;
        VIFIBN32.medium++ <--> DatarateChannel {  delay = 33ms; datarate = 81Mbps; ber = 0; } <--> VIFIBN16.medium++;
        VIFIBN32.medium++ <--> DatarateChannel {  delay = 39ms; datarate = 92Mbps; ber = 0; } <--> VIFIBN24.medium++;
        VIFIBN32.medium++ <--> DatarateChannel {  delay = 14ms; datarate = 84Mbps; ber = 0; } <--> VIFIBN28.medium++;
        VIFIBN32.medium++ <--> DatarateChannel {  delay = 47ms; datarate = 93Mbps; ber = 0; } <--> VIFIBN30.medium++;
        VIFIBN32.medium++ <--> DatarateChannel {  delay = 50ms; datarate = 88Mbps; ber = 0; } <--> VIFIBN33.medium++;
        VIFIBN32.medium++ <--> DatarateChannel {  delay = 28ms; datarate = 86Mbps; ber = 0; } <--> VIFIBN36.medium++;
        VIFIBN32.medium++ <--> DatarateChannel {  delay = 41ms; datarate = 93Mbps; ber = 0; } <--> VIFIBN10.medium++;
        VIFIBN32.medium++ <--> DatarateChannel {  delay = 56ms; datarate = 96Mbps; ber = 0; } <--> VIFIBN14.medium++;
        VIFIBN32.medium++ <--> DatarateChannel {  delay = 94ms; datarate = 80Mbps; ber = 0; } <--> VIFIBN43.medium++;
        VIFIBN33.medium++ <--> DatarateChannel {  delay = 22ms; datarate = 99Mbps; ber = 0; } <--> VIFIBN29.medium++;
        VIFIBN33.medium++ <--> DatarateChannel {  delay = 28ms; datarate = 80Mbps; ber = 0; } <--> VIFIBN34.medium++;
        VIFIBN33.medium++ <--> DatarateChannel {  delay = 30ms; datarate = 80Mbps; ber = 0; } <--> VIFIBN37.medium++;
        VIFIBN33.medium++ <--> DatarateChannel {  delay = 32ms; datarate = 89Mbps; ber = 0; } <--> VIFIBN40.medium++;
        VIFIBN33.medium++ <--> DatarateChannel {  delay = 13ms; datarate = 84Mbps; ber = 0; } <--> VIFIBN45.medium++;
        VIFIBN34.medium++ <--> DatarateChannel {  delay = 16ms; datarate = 80Mbps; ber = 0; } <--> VIFIBN31.medium++;
        VIFIBN34.medium++ <--> DatarateChannel {  delay = 25ms; datarate = 98Mbps; ber = 0; } <--> VIFIBN37.medium++;
        VIFIBN34.medium++ <--> DatarateChannel {  delay = 25ms; datarate = 89Mbps; ber = 0; } <--> VIFIBN41.medium++;
        VIFIBN34.medium++ <--> DatarateChannel {  delay = 13ms; datarate = 92Mbps; ber = 0; } <--> VIFIBN43.medium++;
        VIFIBN34.medium++ <--> DatarateChannel {  delay = 99ms; datarate = 91Mbps; ber = 0; } <--> VIFIBN45.medium++;
        VIFIBN34.medium++ <--> DatarateChannel {  delay = 70ms; datarate = 84Mbps; ber = 0; } <--> VIFIBN38.medium++;
        VIFIBN35.medium++ <--> DatarateChannel {  delay = 33ms; datarate = 85Mbps; ber = 0; } <--> VIFIBN21.medium++;
        VIFIBN35.medium++ <--> DatarateChannel {  delay = 22ms; datarate = 96Mbps; ber = 0; } <--> VIFIBN29.medium++;
        VIFIBN35.medium++ <--> DatarateChannel {  delay = 29ms; datarate = 87Mbps; ber = 0; } <--> VIFIBN30.medium++;
        VIFIBN35.medium++ <--> DatarateChannel {  delay = 34ms; datarate = 80Mbps; ber = 0; } <--> VIFIBN36.medium++;
        VIFIBN35.medium++ <--> DatarateChannel {  delay = 23ms; datarate = 99Mbps; ber = 0; } <--> VIFIBN39.medium++;
        VIFIBN35.medium++ <--> DatarateChannel {  delay = 46ms; datarate = 83Mbps; ber = 0; } <--> VIFIBN42.medium++;
        VIFIBN35.medium++ <--> DatarateChannel {  delay = 20ms; datarate = 81Mbps; ber = 0; } <--> VIFIBN44.medium++;
        VIFIBN35.medium++ <--> DatarateChannel {  delay = 50ms; datarate = 84Mbps; ber = 0; } <--> VIFIBN47.medium++;
        VIFIBN35.medium++ <--> DatarateChannel {  delay = 44ms; datarate = 86Mbps; ber = 0; } <--> VIFIBN49.medium++;
        VIFIBN36.medium++ <--> DatarateChannel {  delay = 12ms; datarate = 98Mbps; ber = 0; } <--> VIFIBN31.medium++;
        VIFIBN36.medium++ <--> DatarateChannel {  delay = 35ms; datarate = 82Mbps; ber = 0; } <--> VIFIBN33.medium++;
        VIFIBN36.medium++ <--> DatarateChannel {  delay = 31ms; datarate = 89Mbps; ber = 0; } <--> VIFIBN43.medium++;
        VIFIBN36.medium++ <--> DatarateChannel {  delay = 17ms; datarate = 91Mbps; ber = 0; } <--> VIFIBN45.medium++;
        VIFIBN36.medium++ <--> DatarateChannel {  delay = 43ms; datarate = 93Mbps; ber = 0; } <--> VIFIBN46.medium++;
        VIFIBN36.medium++ <--> DatarateChannel {  delay = 17ms; datarate = 81Mbps; ber = 0; } <--> VIFIBN47.medium++;
        VIFIBN36.medium++ <--> DatarateChannel {  delay = 24ms; datarate = 84Mbps; ber = 0; } <--> VIFIBN48.medium++;
        VIFIBN37.medium++ <--> DatarateChannel {  delay = 34ms; datarate = 91Mbps; ber = 0; } <--> VIFIBN31.medium++;
        VIFIBN37.medium++ <--> DatarateChannel {  delay = 21ms; datarate = 83Mbps; ber = 0; } <--> VIFIBN38.medium++;
        VIFIBN37.medium++ <--> DatarateChannel {  delay = 31ms; datarate = 85Mbps; ber = 0; } <--> VIFIBN43.medium++;
        VIFIBN38.medium++ <--> DatarateChannel {  delay = 37ms; datarate = 97Mbps; ber = 0; } <--> VIFIBN45.medium++;
        VIFIBN38.medium++ <--> DatarateChannel {  delay = 41ms; datarate = 89Mbps; ber = 0; } <--> VIFIBN47.medium++;
        VIFIBN38.medium++ <--> DatarateChannel {  delay = 11ms; datarate = 96Mbps; ber = 0; } <--> VIFIBN50.medium++;
        VIFIBN38.medium++ <--> DatarateChannel {  delay = 62ms; datarate = 82Mbps; ber = 0; } <--> VIFIBN44.medium++;
        VIFIBN39.medium++ <--> DatarateChannel {  delay = 31ms; datarate = 99Mbps; ber = 0; } <--> VIFIBN28.medium++;
        VIFIBN39.medium++ <--> DatarateChannel {  delay = 11ms; datarate = 80Mbps; ber = 0; } <--> VIFIBN30.medium++;
        VIFIBN39.medium++ <--> DatarateChannel {  delay = 31ms; datarate = 81Mbps; ber = 0; } <--> VIFIBN31.medium++;
        VIFIBN39.medium++ <--> DatarateChannel {  delay = 42ms; datarate = 85Mbps; ber = 0; } <--> VIFIBN33.medium++;
        VIFIBN39.medium++ <--> DatarateChannel {  delay = 62ms; datarate = 93Mbps; ber = 0; } <--> VIFIBN50.medium++;
        VIFIBN40.medium++ <--> DatarateChannel {  delay = 14ms; datarate = 85Mbps; ber = 0; } <--> VIFIBN44.medium++;
        VIFIBN40.medium++ <--> DatarateChannel {  delay = 14ms; datarate = 88Mbps; ber = 0; } <--> VIFIBN45.medium++;
        VIFIBN40.medium++ <--> DatarateChannel {  delay = 24ms; datarate = 96Mbps; ber = 0; } <--> VIFIBN47.medium++;
        VIFIBN40.medium++ <--> DatarateChannel {  delay = 31ms; datarate = 99Mbps; ber = 0; } <--> VIFIBN50.medium++;
        VIFIBN41.medium++ <--> DatarateChannel {  delay = 48ms; datarate = 96Mbps; ber = 0; } <--> VIFIBN31.medium++;
        VIFIBN41.medium++ <--> DatarateChannel {  delay = 35ms; datarate = 80Mbps; ber = 0; } <--> VIFIBN38.medium++;
        VIFIBN41.medium++ <--> DatarateChannel {  delay = 46ms; datarate = 88Mbps; ber = 0; } <--> VIFIBN46.medium++;
        VIFIBN41.medium++ <--> DatarateChannel {  delay = 43ms; datarate = 93Mbps; ber = 0; } <--> VIFIBN47.medium++;
        VIFIBN41.medium++ <--> DatarateChannel {  delay = 16ms; datarate = 88Mbps; ber = 0; } <--> VIFIBN50.medium++;
        VIFIBN42.medium++ <--> DatarateChannel {  delay = 12ms; datarate = 83Mbps; ber = 0; } <--> VIFIBN34.medium++;
        VIFIBN42.medium++ <--> DatarateChannel {  delay = 17ms; datarate = 93Mbps; ber = 0; } <--> VIFIBN37.medium++;
        VIFIBN42.medium++ <--> DatarateChannel {  delay = 33ms; datarate = 90Mbps; ber = 0; } <--> VIFIBN38.medium++;
        VIFIBN42.medium++ <--> DatarateChannel {  delay = 15ms; datarate = 92Mbps; ber = 0; } <--> VIFIBN43.medium++;
        VIFIBN42.medium++ <--> DatarateChannel {  delay = 26ms; datarate = 92Mbps; ber = 0; } <--> VIFIBN44.medium++;
        VIFIBN42.medium++ <--> DatarateChannel {  delay = 21ms; datarate = 89Mbps; ber = 0; } <--> VIFIBN45.medium++;
        VIFIBN42.medium++ <--> DatarateChannel {  delay = 87ms; datarate = 92Mbps; ber = 0; } <--> VIFIBN40.medium++;
        VIFIBN42.medium++ <--> DatarateChannel {  delay = 38ms; datarate = 83Mbps; ber = 0; } <--> VIFIBN48.medium++;
        VIFIBN43.medium++ <--> DatarateChannel {  delay = 14ms; datarate = 87Mbps; ber = 0; } <--> VIFIBN44.medium++;
        VIFIBN43.medium++ <--> DatarateChannel {  delay = 15ms; datarate = 84Mbps; ber = 0; } <--> VIFIBN49.medium++;
        VIFIBN43.medium++ <--> DatarateChannel {  delay = 42ms; datarate = 89Mbps; ber = 0; } <--> VIFIBN50.medium++;
        VIFIBN44.medium++ <--> DatarateChannel {  delay = 49ms; datarate = 98Mbps; ber = 0; } <--> VIFIBN50.medium++;
        VIFIBN44.medium++ <--> DatarateChannel {  delay = 96ms; datarate = 96Mbps; ber = 0; } <--> VIFIBN46.medium++;
        VIFIBN45.medium++ <--> DatarateChannel {  delay = 11ms; datarate = 87Mbps; ber = 0; } <--> VIFIBN48.medium++;
        VIFIBN46.medium++ <--> DatarateChannel {  delay = 35ms; datarate = 82Mbps; ber = 0; } <--> VIFIBN47.medium++;
        VIFIBN50.medium++ <--> DatarateChannel {  delay = 27ms; datarate = 94Mbps; ber = 0; } <--> VIFIBN49.medium++;
        VIFIBN2.medium++ <--> DatarateChannel {  delay = 65ms; datarate = 100Mbps; ber = 0; } <--> VIFIBN9.medium++;
        VIFIBN2.medium++ <--> DatarateChannel {  delay = 66ms; datarate = 100Mbps; ber = 0; } <--> VIFIBN18.medium++;
        VIFIBN2.medium++ <--> DatarateChannel {  delay = 97ms; datarate = 100Mbps; ber = 0; } <--> VIFIBN28.medium++;
        VIFIBN2.medium++ <--> DatarateChannel {  delay = 70ms; datarate = 100Mbps; ber = 0; } <--> VIFIBN27.medium++;
        VIFIBN2.medium++ <--> DatarateChannel {  delay = 51ms; datarate = 100Mbps; ber = 0; } <--> VIFIBN35.medium++;
        VIFIBN2.medium++ <--> DatarateChannel {  delay = 50ms; datarate = 100Mbps; ber = 0; } <--> VIFIBN31.medium++;
        VIFIBN2.medium++ <--> DatarateChannel {  delay = 42ms; datarate = 100Mbps; ber = 0; } <--> VIFIBN25.medium++;
        VIFIBN2.medium++ <--> DatarateChannel {  delay = 87ms; datarate = 100Mbps; ber = 0; } <--> VIFIBN24.medium++;
        VIFIBN2.medium++ <--> DatarateChannel {  delay = 40ms; datarate = 100Mbps; ber = 0; } <--> VIFIBN34.medium++;
        VIFIBN2.medium++ <--> DatarateChannel {  delay = 89ms; datarate = 100Mbps; ber = 0; } <--> VIFIBN36.medium++;
        VIFIBN1.medium++ <--> DatarateChannel {  delay = 85ms; datarate = 100Mbps; ber = 0; } <--> VIFIBN2.medium++;
        VIFIBN1.medium++ <--> DatarateChannel {  delay = 63ms; datarate = 100Mbps; ber = 0; } <--> VIFIBN9.medium++;
        VIFIBN1.medium++ <--> DatarateChannel {  delay = 69ms; datarate = 100Mbps; ber = 0; } <--> VIFIBN14.medium++;
        VIFIBN1.medium++ <--> DatarateChannel {  delay = 92ms; datarate = 100Mbps; ber = 0; } <--> VIFIBN19.medium++;
        VIFIBN1.medium++ <--> DatarateChannel {  delay = 85ms; datarate = 100Mbps; ber = 0; } <--> VIFIBN28.medium++;
        VIFIBN1.medium++ <--> DatarateChannel {  delay = 94ms; datarate = 100Mbps; ber = 0; } <--> VIFIBN27.medium++;
        VIFIBN1.medium++ <--> DatarateChannel {  delay = 99ms; datarate = 100Mbps; ber = 0; } <--> VIFIBN31.medium++;
        VIFIBN1.medium++ <--> DatarateChannel {  delay = 81ms; datarate = 100Mbps; ber = 0; } <--> VIFIBN24.medium++;
        VIFIBN1.medium++ <--> DatarateChannel {  delay = 72ms; datarate = 100Mbps; ber = 0; } <--> VIFIBN34.medium++;
        VIFIBN1.medium++ <--> DatarateChannel {  delay = 62ms; datarate = 100Mbps; ber = 0; } <--> VIFIBN36.medium++;
        VIFIBN9.medium++ <--> DatarateChannel {  delay = 67ms; datarate = 100Mbps; ber = 0; } <--> VIFIBN14.medium++;
        VIFIBN9.medium++ <--> DatarateChannel {  delay = 70ms; datarate = 100Mbps; ber = 0; } <--> VIFIBN22.medium++;
        VIFIBN9.medium++ <--> DatarateChannel {  delay = 48ms; datarate = 100Mbps; ber = 0; } <--> VIFIBN28.medium++;
        VIFIBN9.medium++ <--> DatarateChannel {  delay = 12ms; datarate = 100Mbps; ber = 0; } <--> VIFIBN27.medium++;
        VIFIBN9.medium++ <--> DatarateChannel {  delay = 35ms; datarate = 100Mbps; ber = 0; } <--> VIFIBN35.medium++;
        VIFIBN9.medium++ <--> DatarateChannel {  delay = 53ms; datarate = 100Mbps; ber = 0; } <--> VIFIBN31.medium++;
        VIFIBN9.medium++ <--> DatarateChannel {  delay = 95ms; datarate = 100Mbps; ber = 0; } <--> VIFIBN25.medium++;
        VIFIBN9.medium++ <--> DatarateChannel {  delay = 84ms; datarate = 100Mbps; ber = 0; } <--> VIFIBN24.medium++;
        VIFIBN9.medium++ <--> DatarateChannel {  delay = 54ms; datarate = 100Mbps; ber = 0; } <--> VIFIBN34.medium++;
        VIFIBN9.medium++ <--> DatarateChannel {  delay = 54ms; datarate = 100Mbps; ber = 0; } <--> VIFIBN36.medium++;
        VIFIBN14.medium++ <--> DatarateChannel {  delay = 90ms; datarate = 100Mbps; ber = 0; } <--> VIFIBN22.medium++;
        VIFIBN14.medium++ <--> DatarateChannel {  delay = 64ms; datarate = 100Mbps; ber = 0; } <--> VIFIBN18.medium++;
        VIFIBN14.medium++ <--> DatarateChannel {  delay = 22ms; datarate = 100Mbps; ber = 0; } <--> VIFIBN19.medium++;
        VIFIBN14.medium++ <--> DatarateChannel {  delay = 50ms; datarate = 100Mbps; ber = 0; } <--> VIFIBN28.medium++;
        VIFIBN14.medium++ <--> DatarateChannel {  delay = 72ms; datarate = 100Mbps; ber = 0; } <--> VIFIBN27.medium++;
        VIFIBN14.medium++ <--> DatarateChannel {  delay = 17ms; datarate = 100Mbps; ber = 0; } <--> VIFIBN35.medium++;
        VIFIBN14.medium++ <--> DatarateChannel {  delay = 19ms; datarate = 100Mbps; ber = 0; } <--> VIFIBN31.medium++;
        VIFIBN14.medium++ <--> DatarateChannel {  delay = 50ms; datarate = 100Mbps; ber = 0; } <--> VIFIBN25.medium++;
        VIFIBN14.medium++ <--> DatarateChannel {  delay = 90ms; datarate = 100Mbps; ber = 0; } <--> VIFIBN24.medium++;
        VIFIBN14.medium++ <--> DatarateChannel {  delay = 44ms; datarate = 100Mbps; ber = 0; } <--> VIFIBN34.medium++;
        VIFIBN14.medium++ <--> DatarateChannel {  delay = 39ms; datarate = 100Mbps; ber = 0; } <--> VIFIBN36.medium++;
        VIFIBN22.medium++ <--> DatarateChannel {  delay = 80ms; datarate = 100Mbps; ber = 0; } <--> VIFIBN18.medium++;
        VIFIBN22.medium++ <--> DatarateChannel {  delay = 95ms; datarate = 100Mbps; ber = 0; } <--> VIFIBN19.medium++;
        VIFIBN22.medium++ <--> DatarateChannel {  delay = 97ms; datarate = 100Mbps; ber = 0; } <--> VIFIBN28.medium++;
        VIFIBN22.medium++ <--> DatarateChannel {  delay = 70ms; datarate = 100Mbps; ber = 0; } <--> VIFIBN27.medium++;
        VIFIBN22.medium++ <--> DatarateChannel {  delay = 84ms; datarate = 100Mbps; ber = 0; } <--> VIFIBN35.medium++;
        VIFIBN22.medium++ <--> DatarateChannel {  delay = 80ms; datarate = 100Mbps; ber = 0; } <--> VIFIBN31.medium++;
        VIFIBN22.medium++ <--> DatarateChannel {  delay = 64ms; datarate = 100Mbps; ber = 0; } <--> VIFIBN34.medium++;
        VIFIBN18.medium++ <--> DatarateChannel {  delay = 65ms; datarate = 100Mbps; ber = 0; } <--> VIFIBN28.medium++;
        VIFIBN18.medium++ <--> DatarateChannel {  delay = 58ms; datarate = 100Mbps; ber = 0; } <--> VIFIBN27.medium++;
        VIFIBN18.medium++ <--> DatarateChannel {  delay = 95ms; datarate = 100Mbps; ber = 0; } <--> VIFIBN35.medium++;
        VIFIBN18.medium++ <--> DatarateChannel {  delay = 69ms; datarate = 100Mbps; ber = 0; } <--> VIFIBN31.medium++;
        VIFIBN18.medium++ <--> DatarateChannel {  delay = 72ms; datarate = 100Mbps; ber = 0; } <--> VIFIBN25.medium++;
        VIFIBN18.medium++ <--> DatarateChannel {  delay = 74ms; datarate = 100Mbps; ber = 0; } <--> VIFIBN24.medium++;
        VIFIBN18.medium++ <--> DatarateChannel {  delay = 28ms; datarate = 100Mbps; ber = 0; } <--> VIFIBN34.medium++;
        VIFIBN18.medium++ <--> DatarateChannel {  delay = 59ms; datarate = 100Mbps; ber = 0; } <--> VIFIBN36.medium++;
        VIFIBN19.medium++ <--> DatarateChannel {  delay = 98ms; datarate = 100Mbps; ber = 0; } <--> VIFIBN28.medium++;
        VIFIBN19.medium++ <--> DatarateChannel {  delay = 15ms; datarate = 100Mbps; ber = 0; } <--> VIFIBN27.medium++;
        VIFIBN19.medium++ <--> DatarateChannel {  delay = 69ms; datarate = 100Mbps; ber = 0; } <--> VIFIBN35.medium++;
        VIFIBN19.medium++ <--> DatarateChannel {  delay = 42ms; datarate = 100Mbps; ber = 0; } <--> VIFIBN31.medium++;
        VIFIBN19.medium++ <--> DatarateChannel {  delay = 12ms; datarate = 100Mbps; ber = 0; } <--> VIFIBN25.medium++;
        VIFIBN19.medium++ <--> DatarateChannel {  delay = 98ms; datarate = 100Mbps; ber = 0; } <--> VIFIBN34.medium++;
        VIFIBN19.medium++ <--> DatarateChannel {  delay = 27ms; datarate = 100Mbps; ber = 0; } <--> VIFIBN36.medium++;
        VIFIBN28.medium++ <--> DatarateChannel {  delay = 66ms; datarate = 100Mbps; ber = 0; } <--> VIFIBN27.medium++;
        VIFIBN28.medium++ <--> DatarateChannel {  delay = 63ms; datarate = 100Mbps; ber = 0; } <--> VIFIBN35.medium++;
        VIFIBN28.medium++ <--> DatarateChannel {  delay = 51ms; datarate = 100Mbps; ber = 0; } <--> VIFIBN31.medium++;
        VIFIBN28.medium++ <--> DatarateChannel {  delay = 93ms; datarate = 100Mbps; ber = 0; } <--> VIFIBN25.medium++;
        VIFIBN28.medium++ <--> DatarateChannel {  delay = 89ms; datarate = 100Mbps; ber = 0; } <--> VIFIBN24.medium++;
        VIFIBN28.medium++ <--> DatarateChannel {  delay = 79ms; datarate = 100Mbps; ber = 0; } <--> VIFIBN34.medium++;
        VIFIBN28.medium++ <--> DatarateChannel {  delay = 67ms; datarate = 100Mbps; ber = 0; } <--> VIFIBN36.medium++;
        VIFIBN27.medium++ <--> DatarateChannel {  delay = 76ms; datarate = 100Mbps; ber = 0; } <--> VIFIBN35.medium++;
        VIFIBN27.medium++ <--> DatarateChannel {  delay = 98ms; datarate = 100Mbps; ber = 0; } <--> VIFIBN31.medium++;
        VIFIBN27.medium++ <--> DatarateChannel {  delay = 56ms; datarate = 100Mbps; ber = 0; } <--> VIFIBN34.medium++;
        VIFIBN35.medium++ <--> DatarateChannel {  delay = 63ms; datarate = 100Mbps; ber = 0; } <--> VIFIBN31.medium++;
        VIFIBN35.medium++ <--> DatarateChannel {  delay = 94ms; datarate = 100Mbps; ber = 0; } <--> VIFIBN25.medium++;
        VIFIBN35.medium++ <--> DatarateChannel {  delay = 86ms; datarate = 100Mbps; ber = 0; } <--> VIFIBN24.medium++;
        VIFIBN35.medium++ <--> DatarateChannel {  delay = 94ms; datarate = 100Mbps; ber = 0; } <--> VIFIBN34.medium++;
        VIFIBN31.medium++ <--> DatarateChannel {  delay = 76ms; datarate = 100Mbps; ber = 0; } <--> VIFIBN25.medium++;
        VIFIBN31.medium++ <--> DatarateChannel {  delay = 89ms; datarate = 100Mbps; ber = 0; } <--> VIFIBN24.medium++;
        VIFIBN24.medium++ <--> DatarateChannel {  delay = 99ms; datarate = 100Mbps; ber = 0; } <--> VIFIBN34.medium++;
        VIFIBN24.medium++ <--> DatarateChannel {  delay = 45ms; datarate = 100Mbps; ber = 0; } <--> VIFIBN36.medium++;
        VIFIBN34.medium++ <--> DatarateChannel {  delay = 90ms; datarate = 100Mbps; ber = 0; } <--> VIFIBN36.medium++;

}
