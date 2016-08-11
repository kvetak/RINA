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

package rina.examples.Routing.SWDCLS100;

import ned.DatarateChannel;
import rina.src.CS.*;
import rina.src.DAF.IRM.ConnectionTable;
import rina.src.DIF.EFCP.DTCP.*;

network SWDCLSScen100
{
    submodules:



        VIFIBN48: VIFIBNode26 {
        @display("p=100,92");
        }
        VIFIBN46: VIFIBNode15 {
        @display("p=100,55");
        }
        VIFIBN64: VIFIBNode13 {
        @display("p=109,76");
        }
        VIFIBN17: VIFIBNode19 {
        @display("p=105,65");
        }
        VIFIBN66: VIFIBNode8 {
        @display("p=104,4");
        }
        VIFIBN78: VIFIBNode8 {
        @display("p=106,74");
        }
        VIFIBN40: VIFIBNode17 {
        @display("p=102,40");
        }
        VIFIBN8: VIFIBNode15 {
        @display("p=108,56");
        }
        VIFIBN54: VIFIBNode15 {
        @display("p=107,58");
        }
        VIFIBN23: VIFIBNode24 {
        @display("p=606,599");
        }
        VIFIBN42: VIFIBNode17 {
        @display("p=604,598");
        }
        VIFIBN30: VIFIBNode11 {
        @display("p=605,522");
        }
        VIFIBN16: VIFIBNode16 {
        @display("p=604,583");
        }
        VIFIBN29: VIFIBNode14 {
        @display("p=601,511");
        }
        VIFIBN33: VIFIBNode12 {
        @display("p=609,585");
        }
        VIFIBN63: VIFIBNode15 {
        @display("p=608,529");
        }
        VIFIBN13: VIFIBNode29 {
        @display("p=306,80");
        }
        VIFIBN22: VIFIBNode14 {
        @display("p=308,48");
        }
        VIFIBN5: VIFIBNode16 {
        @display("p=305,7");
        }
        VIFIBN58: VIFIBNode12 {
        @display("p=301,33");
        }
        VIFIBN12: VIFIBNode17 {
        @display("p=309,81");
        }
        VIFIBN15: VIFIBNode16 {
        @display("p=302,89");
        }
        VIFIBN19: VIFIBNode28 {
        @display("p=1207,522");
        }
        VIFIBN52: VIFIBNode12 {
        @display("p=1202,582");
        }
        VIFIBN18: VIFIBNode16 {
        @display("p=1203,577");
        }
        VIFIBN38: VIFIBNode15 {
        @display("p=1205,569");
        }
        VIFIBN34: VIFIBNode16 {
        @display("p=1201,558");
        }
        VIFIBN56: VIFIBNode13 {
        @display("p=1203,532");
        }
        VIFIBN35: VIFIBNode14 {
        @display("p=1204,527");
        }
        VIFIBN53: VIFIBNode23 {
        @display("p=503,26");
        }
        VIFIBN25: VIFIBNode11 {
        @display("p=508,33");
        }
        VIFIBN24: VIFIBNode17 {
        @display("p=505,43");
        }
        VIFIBN6: VIFIBNode16 {
        @display("p=503,44");
        }
        VIFIBN10: VIFIBNode15 {
        @display("p=504,73");
        }
        VIFIBN31: VIFIBNode22 {
        @display("p=1809,508");
        }
        VIFIBN9: VIFIBNode17 {
        @display("p=1802,515");
        }
        VIFIBN60: VIFIBNode14 {
        @display("p=1807,518");
        }
        VIFIBN4: VIFIBNode19 {
        @display("p=1802,564");
        }
        VIFIBN2: VIFIBNode17 {
        @display("p=1808,554");
        }
        VIFIBN89: VIFIBNode10 {
        @display("p=1801,525");
        }
        VIFIBN20: VIFIBNode14 {
        @display("p=1804,532");
        }
        VIFIBN32: VIFIBNode24 {
        @display("p=702,59");
        }
        VIFIBN37: VIFIBNode14 {
        @display("p=701,37");
        }
        VIFIBN21: VIFIBNode18 {
        @display("p=707,35");
        }
        VIFIBN7: VIFIBNode17 {
        @display("p=703,35");
        }
        VIFIBN45: VIFIBNode11 {
        @display("p=701,82");
        }
        VIFIBN39: VIFIBNode15 {
        @display("p=705,21");
        }
        VIFIBN94: VIFIBNode22 {
        @display("p=2408,538");
        }
        VIFIBN43: VIFIBNode17 {
        @display("p=2402,520");
        }
        VIFIBN88: VIFIBNode12 {
        @display("p=2400,522");
        }
        VIFIBN75: VIFIBNode11 {
        @display("p=2409,523");
        }
        VIFIBN99: VIFIBNode7 {
        @display("p=2403,522");
        }
        VIFIBN55: VIFIBNode11 {
        @display("p=2408,546");
        }
        VIFIBN27: VIFIBNode10 {
        @display("p=2401,586");
        }
        VIFIBN28: VIFIBNode14 {
        @display("p=2403,537");
        }
        VIFIBN73: VIFIBNode9 {
        @display("p=2409,584");
        }
        VIFIBN95: VIFIBNode9 {
        @display("p=2403,509");
        }
        VIFIBN26: VIFIBNode13 {
        @display("p=2406,511");
        }
        VIFIBN14: VIFIBNode16 {
        @display("p=2408,587");
        }
        VIFIBN97: VIFIBNode7 {
        @display("p=2402,515");
        }
        VIFIBN74: VIFIBNode14 {
        @display("p=2407,511");
        }
        VIFIBN49: VIFIBNode11 {
        @display("p=2405,595");
        }
        VIFIBN51: VIFIBNode27 {
        @display("p=904,74");
        }
        VIFIBN50: VIFIBNode15 {
        @display("p=904,3");
        }
        VIFIBN41: VIFIBNode16 {
        @display("p=907,98");
        }
        VIFIBN70: VIFIBNode12 {
        @display("p=903,27");
        }
        VIFIBN61: VIFIBNode15 {
        @display("p=909,66");
        }
        VIFIBN84: VIFIBNode11 {
        @display("p=903,66");
        }
        VIFIBN62: VIFIBNode11 {
        @display("p=904,88");
        }
        VIFIBN47: VIFIBNode27 {
        @display("p=3005,566");
        }
        VIFIBN76: VIFIBNode7 {
        @display("p=3000,519");
        }
        VIFIBN65: VIFIBNode16 {
        @display("p=3008,546");
        }
        VIFIBN11: VIFIBNode17 {
        @display("p=3009,546");
        }
        VIFIBN67: VIFIBNode11 {
        @display("p=3003,527");
        }
        VIFIBN80: VIFIBNode11 {
        @display("p=3002,559");
        }
        VIFIBN96: VIFIBNode8 {
        @display("p=3002,507");
        }
        VIFIBN1: VIFIBNode18 {
        @display("p=3005,592");
        }
        VIFIBN77: VIFIBNode22 {
        @display("p=1108,7");
        }
        VIFIBN100: VIFIBNode7 {
        @display("p=1102,41");
        }
        VIFIBN86: VIFIBNode10 {
        @display("p=1101,65");
        }
        VIFIBN91: VIFIBNode21 {
        @display("p=3602,539");
        }
        VIFIBN82: VIFIBNode5 {
        @display("p=3606,564");
        }
        VIFIBN90: VIFIBNode8 {
        @display("p=3602,541");
        }
        VIFIBN92: VIFIBNode21 {
        @display("p=1301,71");
        }
        VIFIBN87: VIFIBNode10 {
        @display("p=1307,39");
        }
        VIFIBN71: VIFIBNode8 {
        @display("p=1308,58");
        }
        VIFIBN36: VIFIBNode23 {
        @display("p=4206,539");
        }
        VIFIBN69: VIFIBNode12 {
        @display("p=4207,539");
        }
        VIFIBN93: VIFIBNode6 {
        @display("p=4206,517");
        }
        VIFIBN81: VIFIBNode9 {
        @display("p=4206,522");
        }
        VIFIBN44: VIFIBNode13 {
        @display("p=4202,560");
        }
        VIFIBN3: VIFIBNode16 {
        @display("p=4202,599");
        }
        VIFIBN57: VIFIBNode13 {
        @display("p=4206,537");
        }
        VIFIBN59: VIFIBNode12 {
        @display("p=4200,523");
        }
        VIFIBN72: VIFIBNode11 {
        @display("p=4208,569");
        }
        VIFIBN68: VIFIBNode27 {
        @display("p=1500,21");
        }
        VIFIBN98: VIFIBNode7 {
        @display("p=1505,80");
        }
        VIFIBN85: VIFIBNode9 {
        @display("p=1503,66");
        }
        VIFIBN79: VIFIBNode10 {
        @display("p=1509,19");
        }
        VIFIBN83: VIFIBNode10 {
        @display("p=1508,7");
        }






      connections:
        VIFIBN1.medium++ <--> DatarateChannel {  delay = 19ms; datarate =83Mbps; ber = 0;} <--> VIFIBN14.medium++;
        VIFIBN1.medium++ <--> DatarateChannel {  delay = 25ms; datarate =94Mbps; ber = 0;} <--> VIFIBN15.medium++;
        VIFIBN1.medium++ <--> DatarateChannel {  delay = 23ms; datarate =87Mbps; ber = 0;} <--> VIFIBN25.medium++;
        VIFIBN1.medium++ <--> DatarateChannel {  delay = 27ms; datarate =88Mbps; ber = 0;} <--> VIFIBN38.medium++;
        VIFIBN1.medium++ <--> DatarateChannel {  delay = 21ms; datarate =86Mbps; ber = 0;} <--> VIFIBN39.medium++;
        VIFIBN1.medium++ <--> DatarateChannel {  delay = 26ms; datarate =88Mbps; ber = 0;} <--> VIFIBN42.medium++;
        VIFIBN1.medium++ <--> DatarateChannel {  delay = 13ms; datarate =86Mbps; ber = 0;} <--> VIFIBN43.medium++;
        VIFIBN1.medium++ <--> DatarateChannel {  delay = 28ms; datarate =84Mbps; ber = 0;} <--> VIFIBN46.medium++;
        VIFIBN1.medium++ <--> DatarateChannel {  delay = 14ms; datarate =88Mbps; ber = 0;} <--> VIFIBN47.medium++;
        VIFIBN1.medium++ <--> DatarateChannel {  delay = 30ms; datarate =97Mbps; ber = 0;} <--> VIFIBN49.medium++;
        VIFIBN1.medium++ <--> DatarateChannel {  delay = 15ms; datarate =95Mbps; ber = 0;} <--> VIFIBN51.medium++;
        VIFIBN1.medium++ <--> DatarateChannel {  delay = 21ms; datarate =96Mbps; ber = 0;} <--> VIFIBN55.medium++;
        VIFIBN1.medium++ <--> DatarateChannel {  delay = 18ms; datarate =99Mbps; ber = 0;} <--> VIFIBN61.medium++;
        VIFIBN1.medium++ <--> DatarateChannel {  delay = 34ms; datarate =87Mbps; ber = 0;} <--> VIFIBN13.medium++;
        VIFIBN1.medium++ <--> DatarateChannel {  delay = 49ms; datarate =89Mbps; ber = 0;} <--> VIFIBN18.medium++;
        VIFIBN1.medium++ <--> DatarateChannel {  delay = 35ms; datarate =96Mbps; ber = 0;} <--> VIFIBN22.medium++;
        VIFIBN1.medium++ <--> DatarateChannel {  delay = 49ms; datarate =82Mbps; ber = 0;} <--> VIFIBN24.medium++;
        VIFIBN2.medium++ <--> DatarateChannel {  delay = 14ms; datarate =92Mbps; ber = 0;} <--> VIFIBN4.medium++;
        VIFIBN2.medium++ <--> DatarateChannel {  delay = 20ms; datarate =93Mbps; ber = 0;} <--> VIFIBN5.medium++;
        VIFIBN2.medium++ <--> DatarateChannel {  delay = 21ms; datarate =95Mbps; ber = 0;} <--> VIFIBN7.medium++;
        VIFIBN2.medium++ <--> DatarateChannel {  delay = 12ms; datarate =88Mbps; ber = 0;} <--> VIFIBN20.medium++;
        VIFIBN2.medium++ <--> DatarateChannel {  delay = 23ms; datarate =95Mbps; ber = 0;} <--> VIFIBN26.medium++;
        VIFIBN2.medium++ <--> DatarateChannel {  delay = 17ms; datarate =82Mbps; ber = 0;} <--> VIFIBN28.medium++;
        VIFIBN2.medium++ <--> DatarateChannel {  delay = 16ms; datarate =94Mbps; ber = 0;} <--> VIFIBN29.medium++;
        VIFIBN2.medium++ <--> DatarateChannel {  delay = 20ms; datarate =84Mbps; ber = 0;} <--> VIFIBN36.medium++;
        VIFIBN2.medium++ <--> DatarateChannel {  delay = 15ms; datarate =93Mbps; ber = 0;} <--> VIFIBN37.medium++;
        VIFIBN2.medium++ <--> DatarateChannel {  delay = 33ms; datarate =96Mbps; ber = 0;} <--> VIFIBN10.medium++;
        VIFIBN2.medium++ <--> DatarateChannel {  delay = 34ms; datarate =90Mbps; ber = 0;} <--> VIFIBN16.medium++;
        VIFIBN3.medium++ <--> DatarateChannel {  delay = 16ms; datarate =99Mbps; ber = 0;} <--> VIFIBN2.medium++;
        VIFIBN3.medium++ <--> DatarateChannel {  delay = 30ms; datarate =93Mbps; ber = 0;} <--> VIFIBN6.medium++;
        VIFIBN3.medium++ <--> DatarateChannel {  delay = 15ms; datarate =97Mbps; ber = 0;} <--> VIFIBN16.medium++;
        VIFIBN3.medium++ <--> DatarateChannel {  delay = 18ms; datarate =98Mbps; ber = 0;} <--> VIFIBN24.medium++;
        VIFIBN3.medium++ <--> DatarateChannel {  delay = 20ms; datarate =82Mbps; ber = 0;} <--> VIFIBN33.medium++;
        VIFIBN3.medium++ <--> DatarateChannel {  delay = 11ms; datarate =94Mbps; ber = 0;} <--> VIFIBN36.medium++;
        VIFIBN3.medium++ <--> DatarateChannel {  delay = 26ms; datarate =81Mbps; ber = 0;} <--> VIFIBN41.medium++;
        VIFIBN3.medium++ <--> DatarateChannel {  delay = 10ms; datarate =89Mbps; ber = 0;} <--> VIFIBN44.medium++;
        VIFIBN3.medium++ <--> DatarateChannel {  delay = 28ms; datarate =89Mbps; ber = 0;} <--> VIFIBN63.medium++;
        VIFIBN3.medium++ <--> DatarateChannel {  delay = 14ms; datarate =87Mbps; ber = 0;} <--> VIFIBN72.medium++;
        VIFIBN3.medium++ <--> DatarateChannel {  delay = 38ms; datarate =86Mbps; ber = 0;} <--> VIFIBN5.medium++;
        VIFIBN3.medium++ <--> DatarateChannel {  delay = 32ms; datarate =90Mbps; ber = 0;} <--> VIFIBN10.medium++;
        VIFIBN3.medium++ <--> DatarateChannel {  delay = 46ms; datarate =86Mbps; ber = 0;} <--> VIFIBN11.medium++;
        VIFIBN3.medium++ <--> DatarateChannel {  delay = 32ms; datarate =84Mbps; ber = 0;} <--> VIFIBN13.medium++;
        VIFIBN4.medium++ <--> DatarateChannel {  delay = 30ms; datarate =81Mbps; ber = 0;} <--> VIFIBN5.medium++;
        VIFIBN4.medium++ <--> DatarateChannel {  delay = 28ms; datarate =91Mbps; ber = 0;} <--> VIFIBN23.medium++;
        VIFIBN4.medium++ <--> DatarateChannel {  delay = 11ms; datarate =97Mbps; ber = 0;} <--> VIFIBN28.medium++;
        VIFIBN4.medium++ <--> DatarateChannel {  delay = 14ms; datarate =98Mbps; ber = 0;} <--> VIFIBN40.medium++;
        VIFIBN4.medium++ <--> DatarateChannel {  delay = 30ms; datarate =96Mbps; ber = 0;} <--> VIFIBN57.medium++;
        VIFIBN4.medium++ <--> DatarateChannel {  delay = 20ms; datarate =98Mbps; ber = 0;} <--> VIFIBN64.medium++;
        VIFIBN4.medium++ <--> DatarateChannel {  delay = 11ms; datarate =90Mbps; ber = 0;} <--> VIFIBN69.medium++;
        VIFIBN4.medium++ <--> DatarateChannel {  delay = 23ms; datarate =89Mbps; ber = 0;} <--> VIFIBN79.medium++;
        VIFIBN4.medium++ <--> DatarateChannel {  delay = 12ms; datarate =85Mbps; ber = 0;} <--> VIFIBN80.medium++;
        VIFIBN4.medium++ <--> DatarateChannel {  delay = 22ms; datarate =98Mbps; ber = 0;} <--> VIFIBN81.medium++;
        VIFIBN4.medium++ <--> DatarateChannel {  delay = 26ms; datarate =93Mbps; ber = 0;} <--> VIFIBN91.medium++;
        VIFIBN4.medium++ <--> DatarateChannel {  delay = 20ms; datarate =80Mbps; ber = 0;} <--> VIFIBN93.medium++;
        VIFIBN4.medium++ <--> DatarateChannel {  delay = 21ms; datarate =93Mbps; ber = 0;} <--> VIFIBN94.medium++;
        VIFIBN4.medium++ <--> DatarateChannel {  delay = 39ms; datarate =85Mbps; ber = 0;} <--> VIFIBN7.medium++;
        VIFIBN4.medium++ <--> DatarateChannel {  delay = 35ms; datarate =86Mbps; ber = 0;} <--> VIFIBN11.medium++;
        VIFIBN5.medium++ <--> DatarateChannel {  delay = 17ms; datarate =99Mbps; ber = 0;} <--> VIFIBN22.medium++;
        VIFIBN5.medium++ <--> DatarateChannel {  delay = 29ms; datarate =99Mbps; ber = 0;} <--> VIFIBN29.medium++;
        VIFIBN5.medium++ <--> DatarateChannel {  delay = 30ms; datarate =96Mbps; ber = 0;} <--> VIFIBN35.medium++;
        VIFIBN5.medium++ <--> DatarateChannel {  delay = 42ms; datarate =89Mbps; ber = 0;} <--> VIFIBN6.medium++;
        VIFIBN5.medium++ <--> DatarateChannel {  delay = 39ms; datarate =96Mbps; ber = 0;} <--> VIFIBN16.medium++;
        VIFIBN5.medium++ <--> DatarateChannel {  delay = 46ms; datarate =99Mbps; ber = 0;} <--> VIFIBN17.medium++;
        VIFIBN5.medium++ <--> DatarateChannel {  delay = 37ms; datarate =87Mbps; ber = 0;} <--> VIFIBN21.medium++;
        VIFIBN6.medium++ <--> DatarateChannel {  delay = 21ms; datarate =82Mbps; ber = 0;} <--> VIFIBN12.medium++;
        VIFIBN6.medium++ <--> DatarateChannel {  delay = 24ms; datarate =82Mbps; ber = 0;} <--> VIFIBN19.medium++;
        VIFIBN6.medium++ <--> DatarateChannel {  delay = 13ms; datarate =80Mbps; ber = 0;} <--> VIFIBN34.medium++;
        VIFIBN6.medium++ <--> DatarateChannel {  delay = 12ms; datarate =81Mbps; ber = 0;} <--> VIFIBN53.medium++;
        VIFIBN6.medium++ <--> DatarateChannel {  delay = 15ms; datarate =98Mbps; ber = 0;} <--> VIFIBN63.medium++;
        VIFIBN6.medium++ <--> DatarateChannel {  delay = 21ms; datarate =97Mbps; ber = 0;} <--> VIFIBN68.medium++;
        VIFIBN6.medium++ <--> DatarateChannel {  delay = 29ms; datarate =80Mbps; ber = 0;} <--> VIFIBN71.medium++;
        VIFIBN6.medium++ <--> DatarateChannel {  delay = 42ms; datarate =94Mbps; ber = 0;} <--> VIFIBN11.medium++;
        VIFIBN7.medium++ <--> DatarateChannel {  delay = 16ms; datarate =94Mbps; ber = 0;} <--> VIFIBN10.medium++;
        VIFIBN7.medium++ <--> DatarateChannel {  delay = 28ms; datarate =90Mbps; ber = 0;} <--> VIFIBN24.medium++;
        VIFIBN7.medium++ <--> DatarateChannel {  delay = 11ms; datarate =99Mbps; ber = 0;} <--> VIFIBN32.medium++;
        VIFIBN7.medium++ <--> DatarateChannel {  delay = 10ms; datarate =95Mbps; ber = 0;} <--> VIFIBN37.medium++;
        VIFIBN7.medium++ <--> DatarateChannel {  delay = 17ms; datarate =98Mbps; ber = 0;} <--> VIFIBN40.medium++;
        VIFIBN7.medium++ <--> DatarateChannel {  delay = 25ms; datarate =88Mbps; ber = 0;} <--> VIFIBN41.medium++;
        VIFIBN7.medium++ <--> DatarateChannel {  delay = 17ms; datarate =95Mbps; ber = 0;} <--> VIFIBN44.medium++;
        VIFIBN7.medium++ <--> DatarateChannel {  delay = 20ms; datarate =83Mbps; ber = 0;} <--> VIFIBN45.medium++;
        VIFIBN7.medium++ <--> DatarateChannel {  delay = 12ms; datarate =92Mbps; ber = 0;} <--> VIFIBN56.medium++;
        VIFIBN7.medium++ <--> DatarateChannel {  delay = 18ms; datarate =89Mbps; ber = 0;} <--> VIFIBN60.medium++;
        VIFIBN7.medium++ <--> DatarateChannel {  delay = 47ms; datarate =98Mbps; ber = 0;} <--> VIFIBN6.medium++;
        VIFIBN8.medium++ <--> DatarateChannel {  delay = 27ms; datarate =87Mbps; ber = 0;} <--> VIFIBN11.medium++;
        VIFIBN8.medium++ <--> DatarateChannel {  delay = 20ms; datarate =89Mbps; ber = 0;} <--> VIFIBN31.medium++;
        VIFIBN8.medium++ <--> DatarateChannel {  delay = 11ms; datarate =98Mbps; ber = 0;} <--> VIFIBN48.medium++;
        VIFIBN8.medium++ <--> DatarateChannel {  delay = 46ms; datarate =99Mbps; ber = 0;} <--> VIFIBN18.medium++;
        VIFIBN9.medium++ <--> DatarateChannel {  delay = 28ms; datarate =97Mbps; ber = 0;} <--> VIFIBN1.medium++;
        VIFIBN9.medium++ <--> DatarateChannel {  delay = 12ms; datarate =88Mbps; ber = 0;} <--> VIFIBN4.medium++;
        VIFIBN9.medium++ <--> DatarateChannel {  delay = 20ms; datarate =87Mbps; ber = 0;} <--> VIFIBN5.medium++;
        VIFIBN9.medium++ <--> DatarateChannel {  delay = 16ms; datarate =97Mbps; ber = 0;} <--> VIFIBN7.medium++;
        VIFIBN9.medium++ <--> DatarateChannel {  delay = 16ms; datarate =91Mbps; ber = 0;} <--> VIFIBN8.medium++;
        VIFIBN9.medium++ <--> DatarateChannel {  delay = 17ms; datarate =96Mbps; ber = 0;} <--> VIFIBN11.medium++;
        VIFIBN9.medium++ <--> DatarateChannel {  delay = 23ms; datarate =98Mbps; ber = 0;} <--> VIFIBN15.medium++;
        VIFIBN9.medium++ <--> DatarateChannel {  delay = 29ms; datarate =99Mbps; ber = 0;} <--> VIFIBN16.medium++;
        VIFIBN9.medium++ <--> DatarateChannel {  delay = 22ms; datarate =95Mbps; ber = 0;} <--> VIFIBN19.medium++;
        VIFIBN9.medium++ <--> DatarateChannel {  delay = 16ms; datarate =88Mbps; ber = 0;} <--> VIFIBN21.medium++;
        VIFIBN9.medium++ <--> DatarateChannel {  delay = 23ms; datarate =92Mbps; ber = 0;} <--> VIFIBN23.medium++;
        VIFIBN9.medium++ <--> DatarateChannel {  delay = 15ms; datarate =84Mbps; ber = 0;} <--> VIFIBN25.medium++;
        VIFIBN9.medium++ <--> DatarateChannel {  delay = 12ms; datarate =82Mbps; ber = 0;} <--> VIFIBN31.medium++;
        VIFIBN9.medium++ <--> DatarateChannel {  delay = 15ms; datarate =82Mbps; ber = 0;} <--> VIFIBN36.medium++;
        VIFIBN9.medium++ <--> DatarateChannel {  delay = 22ms; datarate =83Mbps; ber = 0;} <--> VIFIBN38.medium++;
        VIFIBN9.medium++ <--> DatarateChannel {  delay = 49ms; datarate =99Mbps; ber = 0;} <--> VIFIBN12.medium++;
        VIFIBN9.medium++ <--> DatarateChannel {  delay = 50ms; datarate =89Mbps; ber = 0;} <--> VIFIBN18.medium++;
        VIFIBN10.medium++ <--> DatarateChannel {  delay = 14ms; datarate =80Mbps; ber = 0;} <--> VIFIBN8.medium++;
        VIFIBN10.medium++ <--> DatarateChannel {  delay = 24ms; datarate =89Mbps; ber = 0;} <--> VIFIBN13.medium++;
        VIFIBN10.medium++ <--> DatarateChannel {  delay = 20ms; datarate =90Mbps; ber = 0;} <--> VIFIBN17.medium++;
        VIFIBN10.medium++ <--> DatarateChannel {  delay = 15ms; datarate =93Mbps; ber = 0;} <--> VIFIBN21.medium++;
        VIFIBN11.medium++ <--> DatarateChannel {  delay = 23ms; datarate =99Mbps; ber = 0;} <--> VIFIBN58.medium++;
        VIFIBN11.medium++ <--> DatarateChannel {  delay = 23ms; datarate =93Mbps; ber = 0;} <--> VIFIBN59.medium++;
        VIFIBN11.medium++ <--> DatarateChannel {  delay = 18ms; datarate =97Mbps; ber = 0;} <--> VIFIBN62.medium++;
        VIFIBN11.medium++ <--> DatarateChannel {  delay = 15ms; datarate =97Mbps; ber = 0;} <--> VIFIBN66.medium++;
        VIFIBN11.medium++ <--> DatarateChannel {  delay = 19ms; datarate =88Mbps; ber = 0;} <--> VIFIBN77.medium++;
        VIFIBN12.medium++ <--> DatarateChannel {  delay = 25ms; datarate =96Mbps; ber = 0;} <--> VIFIBN17.medium++;
        VIFIBN12.medium++ <--> DatarateChannel {  delay = 18ms; datarate =90Mbps; ber = 0;} <--> VIFIBN31.medium++;
        VIFIBN12.medium++ <--> DatarateChannel {  delay = 12ms; datarate =95Mbps; ber = 0;} <--> VIFIBN32.medium++;
        VIFIBN12.medium++ <--> DatarateChannel {  delay = 18ms; datarate =99Mbps; ber = 0;} <--> VIFIBN50.medium++;
        VIFIBN12.medium++ <--> DatarateChannel {  delay = 19ms; datarate =85Mbps; ber = 0;} <--> VIFIBN53.medium++;
        VIFIBN12.medium++ <--> DatarateChannel {  delay = 20ms; datarate =81Mbps; ber = 0;} <--> VIFIBN56.medium++;
        VIFIBN12.medium++ <--> DatarateChannel {  delay = 11ms; datarate =89Mbps; ber = 0;} <--> VIFIBN58.medium++;
        VIFIBN12.medium++ <--> DatarateChannel {  delay = 31ms; datarate =99Mbps; ber = 0;} <--> VIFIBN18.medium++;
        VIFIBN13.medium++ <--> DatarateChannel {  delay = 10ms; datarate =87Mbps; ber = 0;} <--> VIFIBN58.medium++;
        VIFIBN13.medium++ <--> DatarateChannel {  delay = 29ms; datarate =90Mbps; ber = 0;} <--> VIFIBN59.medium++;
        VIFIBN13.medium++ <--> DatarateChannel {  delay = 25ms; datarate =84Mbps; ber = 0;} <--> VIFIBN67.medium++;
        VIFIBN14.medium++ <--> DatarateChannel {  delay = 28ms; datarate =84Mbps; ber = 0;} <--> VIFIBN5.medium++;
        VIFIBN14.medium++ <--> DatarateChannel {  delay = 24ms; datarate =88Mbps; ber = 0;} <--> VIFIBN8.medium++;
        VIFIBN14.medium++ <--> DatarateChannel {  delay = 29ms; datarate =92Mbps; ber = 0;} <--> VIFIBN15.medium++;
        VIFIBN14.medium++ <--> DatarateChannel {  delay = 25ms; datarate =81Mbps; ber = 0;} <--> VIFIBN17.medium++;
        VIFIBN14.medium++ <--> DatarateChannel {  delay = 20ms; datarate =92Mbps; ber = 0;} <--> VIFIBN20.medium++;
        VIFIBN14.medium++ <--> DatarateChannel {  delay = 25ms; datarate =88Mbps; ber = 0;} <--> VIFIBN22.medium++;
        VIFIBN14.medium++ <--> DatarateChannel {  delay = 19ms; datarate =89Mbps; ber = 0;} <--> VIFIBN26.medium++;
        VIFIBN14.medium++ <--> DatarateChannel {  delay = 18ms; datarate =93Mbps; ber = 0;} <--> VIFIBN27.medium++;
        VIFIBN14.medium++ <--> DatarateChannel {  delay = 30ms; datarate =81Mbps; ber = 0;} <--> VIFIBN35.medium++;
        VIFIBN14.medium++ <--> DatarateChannel {  delay = 19ms; datarate =91Mbps; ber = 0;} <--> VIFIBN43.medium++;
        VIFIBN14.medium++ <--> DatarateChannel {  delay = 11ms; datarate =88Mbps; ber = 0;} <--> VIFIBN45.medium++;
        VIFIBN14.medium++ <--> DatarateChannel {  delay = 26ms; datarate =97Mbps; ber = 0;} <--> VIFIBN48.medium++;
        VIFIBN14.medium++ <--> DatarateChannel {  delay = 25ms; datarate =91Mbps; ber = 0;} <--> VIFIBN52.medium++;
        VIFIBN14.medium++ <--> DatarateChannel {  delay = 40ms; datarate =90Mbps; ber = 0;} <--> VIFIBN2.medium++;
        VIFIBN14.medium++ <--> DatarateChannel {  delay = 39ms; datarate =97Mbps; ber = 0;} <--> VIFIBN3.medium++;
        VIFIBN15.medium++ <--> DatarateChannel {  delay = 16ms; datarate =86Mbps; ber = 0;} <--> VIFIBN5.medium++;
        VIFIBN15.medium++ <--> DatarateChannel {  delay = 11ms; datarate =98Mbps; ber = 0;} <--> VIFIBN6.medium++;
        VIFIBN15.medium++ <--> DatarateChannel {  delay = 13ms; datarate =96Mbps; ber = 0;} <--> VIFIBN12.medium++;
        VIFIBN15.medium++ <--> DatarateChannel {  delay = 12ms; datarate =87Mbps; ber = 0;} <--> VIFIBN13.medium++;
        VIFIBN15.medium++ <--> DatarateChannel {  delay = 24ms; datarate =85Mbps; ber = 0;} <--> VIFIBN19.medium++;
        VIFIBN15.medium++ <--> DatarateChannel {  delay = 21ms; datarate =98Mbps; ber = 0;} <--> VIFIBN30.medium++;
        VIFIBN15.medium++ <--> DatarateChannel {  delay = 26ms; datarate =92Mbps; ber = 0;} <--> VIFIBN33.medium++;
        VIFIBN15.medium++ <--> DatarateChannel {  delay = 15ms; datarate =87Mbps; ber = 0;} <--> VIFIBN36.medium++;
        VIFIBN15.medium++ <--> DatarateChannel {  delay = 19ms; datarate =88Mbps; ber = 0;} <--> VIFIBN41.medium++;
        VIFIBN15.medium++ <--> DatarateChannel {  delay = 28ms; datarate =92Mbps; ber = 0;} <--> VIFIBN52.medium++;
        VIFIBN15.medium++ <--> DatarateChannel {  delay = 27ms; datarate =91Mbps; ber = 0;} <--> VIFIBN53.medium++;
        VIFIBN15.medium++ <--> DatarateChannel {  delay = 49ms; datarate =90Mbps; ber = 0;} <--> VIFIBN2.medium++;
        VIFIBN15.medium++ <--> DatarateChannel {  delay = 38ms; datarate =94Mbps; ber = 0;} <--> VIFIBN16.medium++;
        VIFIBN16.medium++ <--> DatarateChannel {  delay = 20ms; datarate =88Mbps; ber = 0;} <--> VIFIBN32.medium++;
        VIFIBN16.medium++ <--> DatarateChannel {  delay = 12ms; datarate =81Mbps; ber = 0;} <--> VIFIBN40.medium++;
        VIFIBN16.medium++ <--> DatarateChannel {  delay = 11ms; datarate =89Mbps; ber = 0;} <--> VIFIBN60.medium++;
        VIFIBN16.medium++ <--> DatarateChannel {  delay = 22ms; datarate =90Mbps; ber = 0;} <--> VIFIBN62.medium++;
        VIFIBN16.medium++ <--> DatarateChannel {  delay = 21ms; datarate =97Mbps; ber = 0;} <--> VIFIBN63.medium++;
        VIFIBN16.medium++ <--> DatarateChannel {  delay = 10ms; datarate =96Mbps; ber = 0;} <--> VIFIBN68.medium++;
        VIFIBN17.medium++ <--> DatarateChannel {  delay = 23ms; datarate =90Mbps; ber = 0;} <--> VIFIBN27.medium++;
        VIFIBN17.medium++ <--> DatarateChannel {  delay = 12ms; datarate =84Mbps; ber = 0;} <--> VIFIBN50.medium++;
        VIFIBN17.medium++ <--> DatarateChannel {  delay = 21ms; datarate =93Mbps; ber = 0;} <--> VIFIBN52.medium++;
        VIFIBN17.medium++ <--> DatarateChannel {  delay = 22ms; datarate =85Mbps; ber = 0;} <--> VIFIBN88.medium++;
        VIFIBN17.medium++ <--> DatarateChannel {  delay = 38ms; datarate =89Mbps; ber = 0;} <--> VIFIBN30.medium++;
        VIFIBN18.medium++ <--> DatarateChannel {  delay = 24ms; datarate =82Mbps; ber = 0;} <--> VIFIBN54.medium++;
        VIFIBN19.medium++ <--> DatarateChannel {  delay = 18ms; datarate =91Mbps; ber = 0;} <--> VIFIBN31.medium++;
        VIFIBN19.medium++ <--> DatarateChannel {  delay = 18ms; datarate =82Mbps; ber = 0;} <--> VIFIBN52.medium++;
        VIFIBN19.medium++ <--> DatarateChannel {  delay = 26ms; datarate =92Mbps; ber = 0;} <--> VIFIBN53.medium++;
        VIFIBN19.medium++ <--> DatarateChannel {  delay = 12ms; datarate =80Mbps; ber = 0;} <--> VIFIBN54.medium++;
        VIFIBN19.medium++ <--> DatarateChannel {  delay = 13ms; datarate =80Mbps; ber = 0;} <--> VIFIBN56.medium++;
        VIFIBN19.medium++ <--> DatarateChannel {  delay = 41ms; datarate =97Mbps; ber = 0;} <--> VIFIBN8.medium++;
        VIFIBN20.medium++ <--> DatarateChannel {  delay = 14ms; datarate =96Mbps; ber = 0;} <--> VIFIBN16.medium++;
        VIFIBN20.medium++ <--> DatarateChannel {  delay = 27ms; datarate =82Mbps; ber = 0;} <--> VIFIBN23.medium++;
        VIFIBN20.medium++ <--> DatarateChannel {  delay = 25ms; datarate =92Mbps; ber = 0;} <--> VIFIBN34.medium++;
        VIFIBN20.medium++ <--> DatarateChannel {  delay = 17ms; datarate =90Mbps; ber = 0;} <--> VIFIBN36.medium++;
        VIFIBN20.medium++ <--> DatarateChannel {  delay = 16ms; datarate =86Mbps; ber = 0;} <--> VIFIBN41.medium++;
        VIFIBN20.medium++ <--> DatarateChannel {  delay = 16ms; datarate =97Mbps; ber = 0;} <--> VIFIBN45.medium++;
        VIFIBN20.medium++ <--> DatarateChannel {  delay = 28ms; datarate =91Mbps; ber = 0;} <--> VIFIBN62.medium++;
        VIFIBN20.medium++ <--> DatarateChannel {  delay = 27ms; datarate =86Mbps; ber = 0;} <--> VIFIBN72.medium++;
        VIFIBN20.medium++ <--> DatarateChannel {  delay = 10ms; datarate =90Mbps; ber = 0;} <--> VIFIBN73.medium++;
        VIFIBN20.medium++ <--> DatarateChannel {  delay = 21ms; datarate =88Mbps; ber = 0;} <--> VIFIBN75.medium++;
        VIFIBN20.medium++ <--> DatarateChannel {  delay = 17ms; datarate =96Mbps; ber = 0;} <--> VIFIBN76.medium++;
        VIFIBN21.medium++ <--> DatarateChannel {  delay = 11ms; datarate =90Mbps; ber = 0;} <--> VIFIBN54.medium++;
        VIFIBN21.medium++ <--> DatarateChannel {  delay = 21ms; datarate =89Mbps; ber = 0;} <--> VIFIBN58.medium++;
        VIFIBN21.medium++ <--> DatarateChannel {  delay = 27ms; datarate =81Mbps; ber = 0;} <--> VIFIBN62.medium++;
        VIFIBN21.medium++ <--> DatarateChannel {  delay = 23ms; datarate =86Mbps; ber = 0;} <--> VIFIBN66.medium++;
        VIFIBN21.medium++ <--> DatarateChannel {  delay = 27ms; datarate =99Mbps; ber = 0;} <--> VIFIBN78.medium++;
        VIFIBN21.medium++ <--> DatarateChannel {  delay = 21ms; datarate =92Mbps; ber = 0;} <--> VIFIBN89.medium++;
        VIFIBN21.medium++ <--> DatarateChannel {  delay = 46ms; datarate =97Mbps; ber = 0;} <--> VIFIBN18.medium++;
        VIFIBN22.medium++ <--> DatarateChannel {  delay = 11ms; datarate =96Mbps; ber = 0;} <--> VIFIBN12.medium++;
        VIFIBN22.medium++ <--> DatarateChannel {  delay = 24ms; datarate =94Mbps; ber = 0;} <--> VIFIBN27.medium++;
        VIFIBN22.medium++ <--> DatarateChannel {  delay = 13ms; datarate =97Mbps; ber = 0;} <--> VIFIBN52.medium++;
        VIFIBN22.medium++ <--> DatarateChannel {  delay = 10ms; datarate =82Mbps; ber = 0;} <--> VIFIBN58.medium++;
        VIFIBN22.medium++ <--> DatarateChannel {  delay = 23ms; datarate =90Mbps; ber = 0;} <--> VIFIBN66.medium++;
        VIFIBN22.medium++ <--> DatarateChannel {  delay = 47ms; datarate =89Mbps; ber = 0;} <--> VIFIBN8.medium++;
        VIFIBN22.medium++ <--> DatarateChannel {  delay = 39ms; datarate =99Mbps; ber = 0;} <--> VIFIBN19.medium++;
        VIFIBN23.medium++ <--> DatarateChannel {  delay = 25ms; datarate =93Mbps; ber = 0;} <--> VIFIBN17.medium++;
        VIFIBN23.medium++ <--> DatarateChannel {  delay = 12ms; datarate =97Mbps; ber = 0;} <--> VIFIBN18.medium++;
        VIFIBN23.medium++ <--> DatarateChannel {  delay = 16ms; datarate =97Mbps; ber = 0;} <--> VIFIBN19.medium++;
        VIFIBN23.medium++ <--> DatarateChannel {  delay = 22ms; datarate =93Mbps; ber = 0;} <--> VIFIBN31.medium++;
        VIFIBN23.medium++ <--> DatarateChannel {  delay = 11ms; datarate =99Mbps; ber = 0;} <--> VIFIBN34.medium++;
        VIFIBN23.medium++ <--> DatarateChannel {  delay = 26ms; datarate =97Mbps; ber = 0;} <--> VIFIBN50.medium++;
        VIFIBN24.medium++ <--> DatarateChannel {  delay = 30ms; datarate =80Mbps; ber = 0;} <--> VIFIBN12.medium++;
        VIFIBN24.medium++ <--> DatarateChannel {  delay = 14ms; datarate =92Mbps; ber = 0;} <--> VIFIBN13.medium++;
        VIFIBN24.medium++ <--> DatarateChannel {  delay = 27ms; datarate =83Mbps; ber = 0;} <--> VIFIBN18.medium++;
        VIFIBN24.medium++ <--> DatarateChannel {  delay = 21ms; datarate =97Mbps; ber = 0;} <--> VIFIBN35.medium++;
        VIFIBN24.medium++ <--> DatarateChannel {  delay = 23ms; datarate =93Mbps; ber = 0;} <--> VIFIBN40.medium++;
        VIFIBN24.medium++ <--> DatarateChannel {  delay = 18ms; datarate =98Mbps; ber = 0;} <--> VIFIBN44.medium++;
        VIFIBN24.medium++ <--> DatarateChannel {  delay = 12ms; datarate =93Mbps; ber = 0;} <--> VIFIBN53.medium++;
        VIFIBN24.medium++ <--> DatarateChannel {  delay = 15ms; datarate =91Mbps; ber = 0;} <--> VIFIBN56.medium++;
        VIFIBN24.medium++ <--> DatarateChannel {  delay = 38ms; datarate =92Mbps; ber = 0;} <--> VIFIBN8.medium++;
        VIFIBN24.medium++ <--> DatarateChannel {  delay = 36ms; datarate =86Mbps; ber = 0;} <--> VIFIBN17.medium++;
        VIFIBN24.medium++ <--> DatarateChannel {  delay = 50ms; datarate =99Mbps; ber = 0;} <--> VIFIBN19.medium++;
        VIFIBN25.medium++ <--> DatarateChannel {  delay = 28ms; datarate =91Mbps; ber = 0;} <--> VIFIBN2.medium++;
        VIFIBN25.medium++ <--> DatarateChannel {  delay = 22ms; datarate =90Mbps; ber = 0;} <--> VIFIBN4.medium++;
        VIFIBN25.medium++ <--> DatarateChannel {  delay = 28ms; datarate =87Mbps; ber = 0;} <--> VIFIBN5.medium++;
        VIFIBN25.medium++ <--> DatarateChannel {  delay = 12ms; datarate =98Mbps; ber = 0;} <--> VIFIBN10.medium++;
        VIFIBN25.medium++ <--> DatarateChannel {  delay = 13ms; datarate =87Mbps; ber = 0;} <--> VIFIBN13.medium++;
        VIFIBN25.medium++ <--> DatarateChannel {  delay = 12ms; datarate =99Mbps; ber = 0;} <--> VIFIBN24.medium++;
        VIFIBN25.medium++ <--> DatarateChannel {  delay = 30ms; datarate =96Mbps; ber = 0;} <--> VIFIBN30.medium++;
        VIFIBN25.medium++ <--> DatarateChannel {  delay = 14ms; datarate =84Mbps; ber = 0;} <--> VIFIBN31.medium++;
        VIFIBN25.medium++ <--> DatarateChannel {  delay = 38ms; datarate =94Mbps; ber = 0;} <--> VIFIBN16.medium++;
        VIFIBN26.medium++ <--> DatarateChannel {  delay = 19ms; datarate =93Mbps; ber = 0;} <--> VIFIBN8.medium++;
        VIFIBN26.medium++ <--> DatarateChannel {  delay = 28ms; datarate =85Mbps; ber = 0;} <--> VIFIBN10.medium++;
        VIFIBN26.medium++ <--> DatarateChannel {  delay = 16ms; datarate =89Mbps; ber = 0;} <--> VIFIBN19.medium++;
        VIFIBN26.medium++ <--> DatarateChannel {  delay = 15ms; datarate =80Mbps; ber = 0;} <--> VIFIBN28.medium++;
        VIFIBN26.medium++ <--> DatarateChannel {  delay = 11ms; datarate =85Mbps; ber = 0;} <--> VIFIBN45.medium++;
        VIFIBN26.medium++ <--> DatarateChannel {  delay = 15ms; datarate =86Mbps; ber = 0;} <--> VIFIBN50.medium++;
        VIFIBN26.medium++ <--> DatarateChannel {  delay = 23ms; datarate =95Mbps; ber = 0;} <--> VIFIBN57.medium++;
        VIFIBN26.medium++ <--> DatarateChannel {  delay = 23ms; datarate =92Mbps; ber = 0;} <--> VIFIBN67.medium++;
        VIFIBN27.medium++ <--> DatarateChannel {  delay = 25ms; datarate =86Mbps; ber = 0;} <--> VIFIBN52.medium++;
        VIFIBN28.medium++ <--> DatarateChannel {  delay = 24ms; datarate =92Mbps; ber = 0;} <--> VIFIBN17.medium++;
        VIFIBN28.medium++ <--> DatarateChannel {  delay = 25ms; datarate =92Mbps; ber = 0;} <--> VIFIBN32.medium++;
        VIFIBN28.medium++ <--> DatarateChannel {  delay = 19ms; datarate =90Mbps; ber = 0;} <--> VIFIBN33.medium++;
        VIFIBN28.medium++ <--> DatarateChannel {  delay = 16ms; datarate =85Mbps; ber = 0;} <--> VIFIBN35.medium++;
        VIFIBN28.medium++ <--> DatarateChannel {  delay = 22ms; datarate =81Mbps; ber = 0;} <--> VIFIBN37.medium++;
        VIFIBN28.medium++ <--> DatarateChannel {  delay = 12ms; datarate =82Mbps; ber = 0;} <--> VIFIBN45.medium++;
        VIFIBN28.medium++ <--> DatarateChannel {  delay = 27ms; datarate =89Mbps; ber = 0;} <--> VIFIBN52.medium++;
        VIFIBN28.medium++ <--> DatarateChannel {  delay = 28ms; datarate =84Mbps; ber = 0;} <--> VIFIBN53.medium++;
        VIFIBN28.medium++ <--> DatarateChannel {  delay = 29ms; datarate =98Mbps; ber = 0;} <--> VIFIBN59.medium++;
        VIFIBN29.medium++ <--> DatarateChannel {  delay = 16ms; datarate =95Mbps; ber = 0;} <--> VIFIBN6.medium++;
        VIFIBN29.medium++ <--> DatarateChannel {  delay = 12ms; datarate =80Mbps; ber = 0;} <--> VIFIBN12.medium++;
        VIFIBN29.medium++ <--> DatarateChannel {  delay = 19ms; datarate =96Mbps; ber = 0;} <--> VIFIBN13.medium++;
        VIFIBN29.medium++ <--> DatarateChannel {  delay = 29ms; datarate =88Mbps; ber = 0;} <--> VIFIBN18.medium++;
        VIFIBN29.medium++ <--> DatarateChannel {  delay = 24ms; datarate =87Mbps; ber = 0;} <--> VIFIBN31.medium++;
        VIFIBN29.medium++ <--> DatarateChannel {  delay = 14ms; datarate =88Mbps; ber = 0;} <--> VIFIBN33.medium++;
        VIFIBN29.medium++ <--> DatarateChannel {  delay = 19ms; datarate =91Mbps; ber = 0;} <--> VIFIBN35.medium++;
        VIFIBN29.medium++ <--> DatarateChannel {  delay = 21ms; datarate =90Mbps; ber = 0;} <--> VIFIBN37.medium++;
        VIFIBN29.medium++ <--> DatarateChannel {  delay = 28ms; datarate =96Mbps; ber = 0;} <--> VIFIBN54.medium++;
        VIFIBN29.medium++ <--> DatarateChannel {  delay = 19ms; datarate =87Mbps; ber = 0;} <--> VIFIBN60.medium++;
        VIFIBN29.medium++ <--> DatarateChannel {  delay = 31ms; datarate =97Mbps; ber = 0;} <--> VIFIBN19.medium++;
        VIFIBN32.medium++ <--> DatarateChannel {  delay = 19ms; datarate =97Mbps; ber = 0;} <--> VIFIBN11.medium++;
        VIFIBN32.medium++ <--> DatarateChannel {  delay = 27ms; datarate =84Mbps; ber = 0;} <--> VIFIBN13.medium++;
        VIFIBN32.medium++ <--> DatarateChannel {  delay = 10ms; datarate =94Mbps; ber = 0;} <--> VIFIBN21.medium++;
        VIFIBN32.medium++ <--> DatarateChannel {  delay = 16ms; datarate =83Mbps; ber = 0;} <--> VIFIBN30.medium++;
        VIFIBN32.medium++ <--> DatarateChannel {  delay = 23ms; datarate =91Mbps; ber = 0;} <--> VIFIBN48.medium++;
        VIFIBN33.medium++ <--> DatarateChannel {  delay = 22ms; datarate =96Mbps; ber = 0;} <--> VIFIBN12.medium++;
        VIFIBN33.medium++ <--> DatarateChannel {  delay = 11ms; datarate =85Mbps; ber = 0;} <--> VIFIBN13.medium++;
        VIFIBN33.medium++ <--> DatarateChannel {  delay = 29ms; datarate =88Mbps; ber = 0;} <--> VIFIBN21.medium++;
        VIFIBN33.medium++ <--> DatarateChannel {  delay = 21ms; datarate =85Mbps; ber = 0;} <--> VIFIBN23.medium++;
        VIFIBN33.medium++ <--> DatarateChannel {  delay = 11ms; datarate =92Mbps; ber = 0;} <--> VIFIBN30.medium++;
        VIFIBN33.medium++ <--> DatarateChannel {  delay = 30ms; datarate =85Mbps; ber = 0;} <--> VIFIBN41.medium++;
        VIFIBN33.medium++ <--> DatarateChannel {  delay = 14ms; datarate =94Mbps; ber = 0;} <--> VIFIBN50.medium++;
        VIFIBN34.medium++ <--> DatarateChannel {  delay = 29ms; datarate =96Mbps; ber = 0;} <--> VIFIBN10.medium++;
        VIFIBN34.medium++ <--> DatarateChannel {  delay = 11ms; datarate =94Mbps; ber = 0;} <--> VIFIBN18.medium++;
        VIFIBN34.medium++ <--> DatarateChannel {  delay = 26ms; datarate =81Mbps; ber = 0;} <--> VIFIBN31.medium++;
        VIFIBN34.medium++ <--> DatarateChannel {  delay = 29ms; datarate =98Mbps; ber = 0;} <--> VIFIBN58.medium++;
        VIFIBN34.medium++ <--> DatarateChannel {  delay = 27ms; datarate =91Mbps; ber = 0;} <--> VIFIBN59.medium++;
        VIFIBN34.medium++ <--> DatarateChannel {  delay = 23ms; datarate =94Mbps; ber = 0;} <--> VIFIBN62.medium++;
        VIFIBN34.medium++ <--> DatarateChannel {  delay = 11ms; datarate =99Mbps; ber = 0;} <--> VIFIBN65.medium++;
        VIFIBN35.medium++ <--> DatarateChannel {  delay = 23ms; datarate =86Mbps; ber = 0;} <--> VIFIBN27.medium++;
        VIFIBN35.medium++ <--> DatarateChannel {  delay = 22ms; datarate =95Mbps; ber = 0;} <--> VIFIBN65.medium++;
        VIFIBN36.medium++ <--> DatarateChannel {  delay = 28ms; datarate =98Mbps; ber = 0;} <--> VIFIBN10.medium++;
        VIFIBN36.medium++ <--> DatarateChannel {  delay = 10ms; datarate =90Mbps; ber = 0;} <--> VIFIBN21.medium++;
        VIFIBN36.medium++ <--> DatarateChannel {  delay = 25ms; datarate =97Mbps; ber = 0;} <--> VIFIBN22.medium++;
        VIFIBN36.medium++ <--> DatarateChannel {  delay = 21ms; datarate =87Mbps; ber = 0;} <--> VIFIBN32.medium++;
        VIFIBN36.medium++ <--> DatarateChannel {  delay = 18ms; datarate =82Mbps; ber = 0;} <--> VIFIBN37.medium++;
        VIFIBN37.medium++ <--> DatarateChannel {  delay = 23ms; datarate =90Mbps; ber = 0;} <--> VIFIBN6.medium++;
        VIFIBN37.medium++ <--> DatarateChannel {  delay = 17ms; datarate =89Mbps; ber = 0;} <--> VIFIBN10.medium++;
        VIFIBN37.medium++ <--> DatarateChannel {  delay = 17ms; datarate =84Mbps; ber = 0;} <--> VIFIBN11.medium++;
        VIFIBN37.medium++ <--> DatarateChannel {  delay = 11ms; datarate =89Mbps; ber = 0;} <--> VIFIBN30.medium++;
        VIFIBN37.medium++ <--> DatarateChannel {  delay = 28ms; datarate =90Mbps; ber = 0;} <--> VIFIBN53.medium++;
        VIFIBN37.medium++ <--> DatarateChannel {  delay = 18ms; datarate =86Mbps; ber = 0;} <--> VIFIBN54.medium++;
        VIFIBN37.medium++ <--> DatarateChannel {  delay = 29ms; datarate =85Mbps; ber = 0;} <--> VIFIBN56.medium++;
        VIFIBN38.medium++ <--> DatarateChannel {  delay = 28ms; datarate =99Mbps; ber = 0;} <--> VIFIBN4.medium++;
        VIFIBN38.medium++ <--> DatarateChannel {  delay = 19ms; datarate =95Mbps; ber = 0;} <--> VIFIBN7.medium++;
        VIFIBN38.medium++ <--> DatarateChannel {  delay = 10ms; datarate =98Mbps; ber = 0;} <--> VIFIBN8.medium++;
        VIFIBN38.medium++ <--> DatarateChannel {  delay = 24ms; datarate =96Mbps; ber = 0;} <--> VIFIBN16.medium++;
        VIFIBN38.medium++ <--> DatarateChannel {  delay = 26ms; datarate =82Mbps; ber = 0;} <--> VIFIBN18.medium++;
        VIFIBN38.medium++ <--> DatarateChannel {  delay = 28ms; datarate =97Mbps; ber = 0;} <--> VIFIBN22.medium++;
        VIFIBN38.medium++ <--> DatarateChannel {  delay = 26ms; datarate =84Mbps; ber = 0;} <--> VIFIBN27.medium++;
        VIFIBN38.medium++ <--> DatarateChannel {  delay = 20ms; datarate =86Mbps; ber = 0;} <--> VIFIBN32.medium++;
        VIFIBN38.medium++ <--> DatarateChannel {  delay = 13ms; datarate =94Mbps; ber = 0;} <--> VIFIBN35.medium++;
        VIFIBN38.medium++ <--> DatarateChannel {  delay = 13ms; datarate =97Mbps; ber = 0;} <--> VIFIBN48.medium++;
        VIFIBN38.medium++ <--> DatarateChannel {  delay = 24ms; datarate =99Mbps; ber = 0;} <--> VIFIBN51.medium++;
        VIFIBN38.medium++ <--> DatarateChannel {  delay = 11ms; datarate =95Mbps; ber = 0;} <--> VIFIBN52.medium++;
        VIFIBN38.medium++ <--> DatarateChannel {  delay = 28ms; datarate =80Mbps; ber = 0;} <--> VIFIBN53.medium++;
        VIFIBN39.medium++ <--> DatarateChannel {  delay = 27ms; datarate =97Mbps; ber = 0;} <--> VIFIBN10.medium++;
        VIFIBN39.medium++ <--> DatarateChannel {  delay = 16ms; datarate =80Mbps; ber = 0;} <--> VIFIBN13.medium++;
        VIFIBN39.medium++ <--> DatarateChannel {  delay = 15ms; datarate =81Mbps; ber = 0;} <--> VIFIBN16.medium++;
        VIFIBN39.medium++ <--> DatarateChannel {  delay = 20ms; datarate =81Mbps; ber = 0;} <--> VIFIBN24.medium++;
        VIFIBN39.medium++ <--> DatarateChannel {  delay = 15ms; datarate =81Mbps; ber = 0;} <--> VIFIBN30.medium++;
        VIFIBN39.medium++ <--> DatarateChannel {  delay = 19ms; datarate =90Mbps; ber = 0;} <--> VIFIBN34.medium++;
        VIFIBN39.medium++ <--> DatarateChannel {  delay = 10ms; datarate =94Mbps; ber = 0;} <--> VIFIBN37.medium++;
        VIFIBN39.medium++ <--> DatarateChannel {  delay = 15ms; datarate =96Mbps; ber = 0;} <--> VIFIBN42.medium++;
        VIFIBN39.medium++ <--> DatarateChannel {  delay = 20ms; datarate =89Mbps; ber = 0;} <--> VIFIBN43.medium++;
        VIFIBN39.medium++ <--> DatarateChannel {  delay = 13ms; datarate =94Mbps; ber = 0;} <--> VIFIBN50.medium++;
        VIFIBN39.medium++ <--> DatarateChannel {  delay = 27ms; datarate =86Mbps; ber = 0;} <--> VIFIBN54.medium++;
        VIFIBN39.medium++ <--> DatarateChannel {  delay = 12ms; datarate =91Mbps; ber = 0;} <--> VIFIBN57.medium++;
        VIFIBN39.medium++ <--> DatarateChannel {  delay = 25ms; datarate =96Mbps; ber = 0;} <--> VIFIBN58.medium++;
        VIFIBN39.medium++ <--> DatarateChannel {  delay = 36ms; datarate =92Mbps; ber = 0;} <--> VIFIBN17.medium++;
        VIFIBN40.medium++ <--> DatarateChannel {  delay = 15ms; datarate =85Mbps; ber = 0;} <--> VIFIBN17.medium++;
        VIFIBN40.medium++ <--> DatarateChannel {  delay = 30ms; datarate =94Mbps; ber = 0;} <--> VIFIBN30.medium++;
        VIFIBN40.medium++ <--> DatarateChannel {  delay = 30ms; datarate =90Mbps; ber = 0;} <--> VIFIBN31.medium++;
        VIFIBN40.medium++ <--> DatarateChannel {  delay = 22ms; datarate =89Mbps; ber = 0;} <--> VIFIBN35.medium++;
        VIFIBN40.medium++ <--> DatarateChannel {  delay = 16ms; datarate =86Mbps; ber = 0;} <--> VIFIBN50.medium++;
        VIFIBN40.medium++ <--> DatarateChannel {  delay = 23ms; datarate =84Mbps; ber = 0;} <--> VIFIBN53.medium++;
        VIFIBN40.medium++ <--> DatarateChannel {  delay = 12ms; datarate =81Mbps; ber = 0;} <--> VIFIBN54.medium++;
        VIFIBN40.medium++ <--> DatarateChannel {  delay = 10ms; datarate =98Mbps; ber = 0;} <--> VIFIBN78.medium++;
        VIFIBN40.medium++ <--> DatarateChannel {  delay = 16ms; datarate =82Mbps; ber = 0;} <--> VIFIBN81.medium++;
        VIFIBN41.medium++ <--> DatarateChannel {  delay = 14ms; datarate =96Mbps; ber = 0;} <--> VIFIBN8.medium++;
        VIFIBN41.medium++ <--> DatarateChannel {  delay = 24ms; datarate =82Mbps; ber = 0;} <--> VIFIBN34.medium++;
        VIFIBN41.medium++ <--> DatarateChannel {  delay = 23ms; datarate =83Mbps; ber = 0;} <--> VIFIBN35.medium++;
        VIFIBN41.medium++ <--> DatarateChannel {  delay = 26ms; datarate =80Mbps; ber = 0;} <--> VIFIBN53.medium++;
        VIFIBN41.medium++ <--> DatarateChannel {  delay = 22ms; datarate =86Mbps; ber = 0;} <--> VIFIBN60.medium++;
        VIFIBN41.medium++ <--> DatarateChannel {  delay = 22ms; datarate =93Mbps; ber = 0;} <--> VIFIBN62.medium++;
        VIFIBN41.medium++ <--> DatarateChannel {  delay = 11ms; datarate =90Mbps; ber = 0;} <--> VIFIBN65.medium++;
        VIFIBN41.medium++ <--> DatarateChannel {  delay = 11ms; datarate =98Mbps; ber = 0;} <--> VIFIBN70.medium++;
        VIFIBN41.medium++ <--> DatarateChannel {  delay = 22ms; datarate =88Mbps; ber = 0;} <--> VIFIBN84.medium++;
        VIFIBN41.medium++ <--> DatarateChannel {  delay = 28ms; datarate =92Mbps; ber = 0;} <--> VIFIBN86.medium++;
        VIFIBN41.medium++ <--> DatarateChannel {  delay = 37ms; datarate =99Mbps; ber = 0;} <--> VIFIBN17.medium++;
        VIFIBN42.medium++ <--> DatarateChannel {  delay = 18ms; datarate =91Mbps; ber = 0;} <--> VIFIBN2.medium++;
        VIFIBN42.medium++ <--> DatarateChannel {  delay = 29ms; datarate =88Mbps; ber = 0;} <--> VIFIBN6.medium++;
        VIFIBN42.medium++ <--> DatarateChannel {  delay = 23ms; datarate =97Mbps; ber = 0;} <--> VIFIBN10.medium++;
        VIFIBN42.medium++ <--> DatarateChannel {  delay = 10ms; datarate =81Mbps; ber = 0;} <--> VIFIBN16.medium++;
        VIFIBN42.medium++ <--> DatarateChannel {  delay = 10ms; datarate =89Mbps; ber = 0;} <--> VIFIBN23.medium++;
        VIFIBN42.medium++ <--> DatarateChannel {  delay = 16ms; datarate =86Mbps; ber = 0;} <--> VIFIBN26.medium++;
        VIFIBN42.medium++ <--> DatarateChannel {  delay = 19ms; datarate =99Mbps; ber = 0;} <--> VIFIBN28.medium++;
        VIFIBN42.medium++ <--> DatarateChannel {  delay = 10ms; datarate =97Mbps; ber = 0;} <--> VIFIBN30.medium++;
        VIFIBN42.medium++ <--> DatarateChannel {  delay = 13ms; datarate =81Mbps; ber = 0;} <--> VIFIBN33.medium++;
        VIFIBN42.medium++ <--> DatarateChannel {  delay = 25ms; datarate =90Mbps; ber = 0;} <--> VIFIBN34.medium++;
        VIFIBN42.medium++ <--> DatarateChannel {  delay = 14ms; datarate =95Mbps; ber = 0;} <--> VIFIBN35.medium++;
        VIFIBN42.medium++ <--> DatarateChannel {  delay = 18ms; datarate =86Mbps; ber = 0;} <--> VIFIBN40.medium++;
        VIFIBN42.medium++ <--> DatarateChannel {  delay = 15ms; datarate =84Mbps; ber = 0;} <--> VIFIBN50.medium++;
        VIFIBN42.medium++ <--> DatarateChannel {  delay = 19ms; datarate =86Mbps; ber = 0;} <--> VIFIBN54.medium++;
        VIFIBN42.medium++ <--> DatarateChannel {  delay = 30ms; datarate =94Mbps; ber = 0;} <--> VIFIBN58.medium++;
        VIFIBN43.medium++ <--> DatarateChannel {  delay = 18ms; datarate =82Mbps; ber = 0;} <--> VIFIBN2.medium++;
        VIFIBN43.medium++ <--> DatarateChannel {  delay = 22ms; datarate =85Mbps; ber = 0;} <--> VIFIBN5.medium++;
        VIFIBN43.medium++ <--> DatarateChannel {  delay = 30ms; datarate =80Mbps; ber = 0;} <--> VIFIBN6.medium++;
        VIFIBN43.medium++ <--> DatarateChannel {  delay = 15ms; datarate =92Mbps; ber = 0;} <--> VIFIBN18.medium++;
        VIFIBN43.medium++ <--> DatarateChannel {  delay = 17ms; datarate =93Mbps; ber = 0;} <--> VIFIBN30.medium++;
        VIFIBN43.medium++ <--> DatarateChannel {  delay = 22ms; datarate =92Mbps; ber = 0;} <--> VIFIBN32.medium++;
        VIFIBN43.medium++ <--> DatarateChannel {  delay = 11ms; datarate =91Mbps; ber = 0;} <--> VIFIBN52.medium++;
        VIFIBN43.medium++ <--> DatarateChannel {  delay = 10ms; datarate =92Mbps; ber = 0;} <--> VIFIBN55.medium++;
        VIFIBN43.medium++ <--> DatarateChannel {  delay = 28ms; datarate =91Mbps; ber = 0;} <--> VIFIBN56.medium++;
        VIFIBN43.medium++ <--> DatarateChannel {  delay = 22ms; datarate =82Mbps; ber = 0;} <--> VIFIBN57.medium++;
        VIFIBN43.medium++ <--> DatarateChannel {  delay = 21ms; datarate =99Mbps; ber = 0;} <--> VIFIBN63.medium++;
        VIFIBN43.medium++ <--> DatarateChannel {  delay = 28ms; datarate =92Mbps; ber = 0;} <--> VIFIBN67.medium++;
        VIFIBN43.medium++ <--> DatarateChannel {  delay = 12ms; datarate =98Mbps; ber = 0;} <--> VIFIBN70.medium++;
        VIFIBN43.medium++ <--> DatarateChannel {  delay = 13ms; datarate =88Mbps; ber = 0;} <--> VIFIBN72.medium++;
        VIFIBN44.medium++ <--> DatarateChannel {  delay = 14ms; datarate =80Mbps; ber = 0;} <--> VIFIBN10.medium++;
        VIFIBN44.medium++ <--> DatarateChannel {  delay = 18ms; datarate =80Mbps; ber = 0;} <--> VIFIBN11.medium++;
        VIFIBN44.medium++ <--> DatarateChannel {  delay = 15ms; datarate =90Mbps; ber = 0;} <--> VIFIBN19.medium++;
        VIFIBN44.medium++ <--> DatarateChannel {  delay = 19ms; datarate =90Mbps; ber = 0;} <--> VIFIBN35.medium++;
        VIFIBN44.medium++ <--> DatarateChannel {  delay = 12ms; datarate =97Mbps; ber = 0;} <--> VIFIBN57.medium++;
        VIFIBN44.medium++ <--> DatarateChannel {  delay = 10ms; datarate =80Mbps; ber = 0;} <--> VIFIBN59.medium++;
        VIFIBN44.medium++ <--> DatarateChannel {  delay = 18ms; datarate =83Mbps; ber = 0;} <--> VIFIBN63.medium++;
        VIFIBN44.medium++ <--> DatarateChannel {  delay = 14ms; datarate =93Mbps; ber = 0;} <--> VIFIBN65.medium++;
        VIFIBN45.medium++ <--> DatarateChannel {  delay = 12ms; datarate =96Mbps; ber = 0;} <--> VIFIBN8.medium++;
        VIFIBN45.medium++ <--> DatarateChannel {  delay = 30ms; datarate =85Mbps; ber = 0;} <--> VIFIBN13.medium++;
        VIFIBN45.medium++ <--> DatarateChannel {  delay = 11ms; datarate =88Mbps; ber = 0;} <--> VIFIBN21.medium++;
        VIFIBN45.medium++ <--> DatarateChannel {  delay = 24ms; datarate =92Mbps; ber = 0;} <--> VIFIBN30.medium++;
        VIFIBN45.medium++ <--> DatarateChannel {  delay = 28ms; datarate =88Mbps; ber = 0;} <--> VIFIBN31.medium++;
        VIFIBN45.medium++ <--> DatarateChannel {  delay = 15ms; datarate =93Mbps; ber = 0;} <--> VIFIBN56.medium++;
        VIFIBN46.medium++ <--> DatarateChannel {  delay = 19ms; datarate =93Mbps; ber = 0;} <--> VIFIBN3.medium++;
        VIFIBN46.medium++ <--> DatarateChannel {  delay = 28ms; datarate =93Mbps; ber = 0;} <--> VIFIBN5.medium++;
        VIFIBN46.medium++ <--> DatarateChannel {  delay = 26ms; datarate =98Mbps; ber = 0;} <--> VIFIBN8.medium++;
        VIFIBN46.medium++ <--> DatarateChannel {  delay = 15ms; datarate =84Mbps; ber = 0;} <--> VIFIBN17.medium++;
        VIFIBN46.medium++ <--> DatarateChannel {  delay = 13ms; datarate =93Mbps; ber = 0;} <--> VIFIBN21.medium++;
        VIFIBN46.medium++ <--> DatarateChannel {  delay = 17ms; datarate =85Mbps; ber = 0;} <--> VIFIBN22.medium++;
        VIFIBN46.medium++ <--> DatarateChannel {  delay = 12ms; datarate =97Mbps; ber = 0;} <--> VIFIBN27.medium++;
        VIFIBN46.medium++ <--> DatarateChannel {  delay = 17ms; datarate =90Mbps; ber = 0;} <--> VIFIBN32.medium++;
        VIFIBN46.medium++ <--> DatarateChannel {  delay = 20ms; datarate =97Mbps; ber = 0;} <--> VIFIBN35.medium++;
        VIFIBN46.medium++ <--> DatarateChannel {  delay = 25ms; datarate =81Mbps; ber = 0;} <--> VIFIBN55.medium++;
        VIFIBN46.medium++ <--> DatarateChannel {  delay = 17ms; datarate =89Mbps; ber = 0;} <--> VIFIBN59.medium++;
        VIFIBN46.medium++ <--> DatarateChannel {  delay = 16ms; datarate =86Mbps; ber = 0;} <--> VIFIBN67.medium++;
        VIFIBN46.medium++ <--> DatarateChannel {  delay = 26ms; datarate =98Mbps; ber = 0;} <--> VIFIBN68.medium++;
        VIFIBN46.medium++ <--> DatarateChannel {  delay = 26ms; datarate =80Mbps; ber = 0;} <--> VIFIBN73.medium++;
        VIFIBN47.medium++ <--> DatarateChannel {  delay = 12ms; datarate =91Mbps; ber = 0;} <--> VIFIBN11.medium++;
        VIFIBN47.medium++ <--> DatarateChannel {  delay = 12ms; datarate =96Mbps; ber = 0;} <--> VIFIBN13.medium++;
        VIFIBN47.medium++ <--> DatarateChannel {  delay = 12ms; datarate =92Mbps; ber = 0;} <--> VIFIBN21.medium++;
        VIFIBN47.medium++ <--> DatarateChannel {  delay = 28ms; datarate =92Mbps; ber = 0;} <--> VIFIBN24.medium++;
        VIFIBN47.medium++ <--> DatarateChannel {  delay = 13ms; datarate =86Mbps; ber = 0;} <--> VIFIBN37.medium++;
        VIFIBN47.medium++ <--> DatarateChannel {  delay = 29ms; datarate =89Mbps; ber = 0;} <--> VIFIBN54.medium++;
        VIFIBN47.medium++ <--> DatarateChannel {  delay = 18ms; datarate =91Mbps; ber = 0;} <--> VIFIBN63.medium++;
        VIFIBN47.medium++ <--> DatarateChannel {  delay = 25ms; datarate =86Mbps; ber = 0;} <--> VIFIBN67.medium++;
        VIFIBN47.medium++ <--> DatarateChannel {  delay = 16ms; datarate =82Mbps; ber = 0;} <--> VIFIBN69.medium++;
        VIFIBN47.medium++ <--> DatarateChannel {  delay = 12ms; datarate =81Mbps; ber = 0;} <--> VIFIBN74.medium++;
        VIFIBN47.medium++ <--> DatarateChannel {  delay = 11ms; datarate =84Mbps; ber = 0;} <--> VIFIBN76.medium++;
        VIFIBN47.medium++ <--> DatarateChannel {  delay = 10ms; datarate =82Mbps; ber = 0;} <--> VIFIBN80.medium++;
        VIFIBN47.medium++ <--> DatarateChannel {  delay = 19ms; datarate =85Mbps; ber = 0;} <--> VIFIBN81.medium++;
        VIFIBN48.medium++ <--> DatarateChannel {  delay = 24ms; datarate =96Mbps; ber = 0;} <--> VIFIBN27.medium++;
        VIFIBN48.medium++ <--> DatarateChannel {  delay = 13ms; datarate =81Mbps; ber = 0;} <--> VIFIBN59.medium++;
        VIFIBN48.medium++ <--> DatarateChannel {  delay = 13ms; datarate =92Mbps; ber = 0;} <--> VIFIBN74.medium++;
        VIFIBN48.medium++ <--> DatarateChannel {  delay = 19ms; datarate =83Mbps; ber = 0;} <--> VIFIBN84.medium++;
        VIFIBN48.medium++ <--> DatarateChannel {  delay = 17ms; datarate =94Mbps; ber = 0;} <--> VIFIBN88.medium++;
        VIFIBN48.medium++ <--> DatarateChannel {  delay = 27ms; datarate =84Mbps; ber = 0;} <--> VIFIBN89.medium++;
        VIFIBN49.medium++ <--> DatarateChannel {  delay = 22ms; datarate =88Mbps; ber = 0;} <--> VIFIBN7.medium++;
        VIFIBN49.medium++ <--> DatarateChannel {  delay = 18ms; datarate =84Mbps; ber = 0;} <--> VIFIBN20.medium++;
        VIFIBN49.medium++ <--> DatarateChannel {  delay = 21ms; datarate =87Mbps; ber = 0;} <--> VIFIBN26.medium++;
        VIFIBN49.medium++ <--> DatarateChannel {  delay = 22ms; datarate =87Mbps; ber = 0;} <--> VIFIBN27.medium++;
        VIFIBN49.medium++ <--> DatarateChannel {  delay = 12ms; datarate =92Mbps; ber = 0;} <--> VIFIBN28.medium++;
        VIFIBN49.medium++ <--> DatarateChannel {  delay = 13ms; datarate =93Mbps; ber = 0;} <--> VIFIBN40.medium++;
        VIFIBN49.medium++ <--> DatarateChannel {  delay = 28ms; datarate =87Mbps; ber = 0;} <--> VIFIBN50.medium++;
        VIFIBN49.medium++ <--> DatarateChannel {  delay = 17ms; datarate =84Mbps; ber = 0;} <--> VIFIBN62.medium++;
        VIFIBN49.medium++ <--> DatarateChannel {  delay = 17ms; datarate =85Mbps; ber = 0;} <--> VIFIBN63.medium++;
        VIFIBN49.medium++ <--> DatarateChannel {  delay = 30ms; datarate =85Mbps; ber = 0;} <--> VIFIBN64.medium++;
        VIFIBN50.medium++ <--> DatarateChannel {  delay = 16ms; datarate =81Mbps; ber = 0;} <--> VIFIBN52.medium++;
        VIFIBN50.medium++ <--> DatarateChannel {  delay = 29ms; datarate =97Mbps; ber = 0;} <--> VIFIBN54.medium++;
        VIFIBN50.medium++ <--> DatarateChannel {  delay = 11ms; datarate =98Mbps; ber = 0;} <--> VIFIBN70.medium++;
        VIFIBN51.medium++ <--> DatarateChannel {  delay = 22ms; datarate =85Mbps; ber = 0;} <--> VIFIBN27.medium++;
        VIFIBN51.medium++ <--> DatarateChannel {  delay = 16ms; datarate =88Mbps; ber = 0;} <--> VIFIBN34.medium++;
        VIFIBN51.medium++ <--> DatarateChannel {  delay = 28ms; datarate =98Mbps; ber = 0;} <--> VIFIBN40.medium++;
        VIFIBN51.medium++ <--> DatarateChannel {  delay = 27ms; datarate =98Mbps; ber = 0;} <--> VIFIBN57.medium++;
        VIFIBN51.medium++ <--> DatarateChannel {  delay = 19ms; datarate =91Mbps; ber = 0;} <--> VIFIBN59.medium++;
        VIFIBN51.medium++ <--> DatarateChannel {  delay = 12ms; datarate =84Mbps; ber = 0;} <--> VIFIBN62.medium++;
        VIFIBN51.medium++ <--> DatarateChannel {  delay = 23ms; datarate =89Mbps; ber = 0;} <--> VIFIBN63.medium++;
        VIFIBN51.medium++ <--> DatarateChannel {  delay = 14ms; datarate =91Mbps; ber = 0;} <--> VIFIBN69.medium++;
        VIFIBN51.medium++ <--> DatarateChannel {  delay = 27ms; datarate =93Mbps; ber = 0;} <--> VIFIBN73.medium++;
        VIFIBN51.medium++ <--> DatarateChannel {  delay = 13ms; datarate =92Mbps; ber = 0;} <--> VIFIBN75.medium++;
        VIFIBN51.medium++ <--> DatarateChannel {  delay = 16ms; datarate =97Mbps; ber = 0;} <--> VIFIBN79.medium++;
        VIFIBN52.medium++ <--> DatarateChannel {  delay = 10ms; datarate =82Mbps; ber = 0;} <--> VIFIBN18.medium++;
        VIFIBN53.medium++ <--> DatarateChannel {  delay = 20ms; datarate =97Mbps; ber = 0;} <--> VIFIBN13.medium++;
        VIFIBN53.medium++ <--> DatarateChannel {  delay = 29ms; datarate =80Mbps; ber = 0;} <--> VIFIBN31.medium++;
        VIFIBN54.medium++ <--> DatarateChannel {  delay = 19ms; datarate =90Mbps; ber = 0;} <--> VIFIBN65.medium++;
        VIFIBN55.medium++ <--> DatarateChannel {  delay = 20ms; datarate =85Mbps; ber = 0;} <--> VIFIBN11.medium++;
        VIFIBN55.medium++ <--> DatarateChannel {  delay = 27ms; datarate =96Mbps; ber = 0;} <--> VIFIBN18.medium++;
        VIFIBN55.medium++ <--> DatarateChannel {  delay = 20ms; datarate =99Mbps; ber = 0;} <--> VIFIBN19.medium++;
        VIFIBN55.medium++ <--> DatarateChannel {  delay = 13ms; datarate =85Mbps; ber = 0;} <--> VIFIBN23.medium++;
        VIFIBN55.medium++ <--> DatarateChannel {  delay = 15ms; datarate =89Mbps; ber = 0;} <--> VIFIBN26.medium++;
        VIFIBN55.medium++ <--> DatarateChannel {  delay = 13ms; datarate =81Mbps; ber = 0;} <--> VIFIBN34.medium++;
        VIFIBN55.medium++ <--> DatarateChannel {  delay = 15ms; datarate =97Mbps; ber = 0;} <--> VIFIBN40.medium++;
        VIFIBN55.medium++ <--> DatarateChannel {  delay = 18ms; datarate =98Mbps; ber = 0;} <--> VIFIBN44.medium++;
        VIFIBN56.medium++ <--> DatarateChannel {  delay = 28ms; datarate =93Mbps; ber = 0;} <--> VIFIBN17.medium++;
        VIFIBN56.medium++ <--> DatarateChannel {  delay = 27ms; datarate =83Mbps; ber = 0;} <--> VIFIBN59.medium++;
        VIFIBN56.medium++ <--> DatarateChannel {  delay = 13ms; datarate =99Mbps; ber = 0;} <--> VIFIBN67.medium++;
        VIFIBN56.medium++ <--> DatarateChannel {  delay = 24ms; datarate =80Mbps; ber = 0;} <--> VIFIBN70.medium++;
        VIFIBN56.medium++ <--> DatarateChannel {  delay = 30ms; datarate =84Mbps; ber = 0;} <--> VIFIBN74.medium++;
        VIFIBN57.medium++ <--> DatarateChannel {  delay = 22ms; datarate =99Mbps; ber = 0;} <--> VIFIBN11.medium++;
        VIFIBN57.medium++ <--> DatarateChannel {  delay = 19ms; datarate =84Mbps; ber = 0;} <--> VIFIBN13.medium++;
        VIFIBN57.medium++ <--> DatarateChannel {  delay = 18ms; datarate =93Mbps; ber = 0;} <--> VIFIBN19.medium++;
        VIFIBN57.medium++ <--> DatarateChannel {  delay = 29ms; datarate =84Mbps; ber = 0;} <--> VIFIBN50.medium++;
        VIFIBN57.medium++ <--> DatarateChannel {  delay = 20ms; datarate =87Mbps; ber = 0;} <--> VIFIBN52.medium++;
        VIFIBN57.medium++ <--> DatarateChannel {  delay = 10ms; datarate =85Mbps; ber = 0;} <--> VIFIBN54.medium++;
        VIFIBN57.medium++ <--> DatarateChannel {  delay = 12ms; datarate =85Mbps; ber = 0;} <--> VIFIBN58.medium++;
        VIFIBN58.medium++ <--> DatarateChannel {  delay = 15ms; datarate =93Mbps; ber = 0;} <--> VIFIBN18.medium++;
        VIFIBN58.medium++ <--> DatarateChannel {  delay = 20ms; datarate =94Mbps; ber = 0;} <--> VIFIBN54.medium++;
        VIFIBN59.medium++ <--> DatarateChannel {  delay = 17ms; datarate =91Mbps; ber = 0;} <--> VIFIBN62.medium++;
        VIFIBN59.medium++ <--> DatarateChannel {  delay = 19ms; datarate =81Mbps; ber = 0;} <--> VIFIBN75.medium++;
        VIFIBN60.medium++ <--> DatarateChannel {  delay = 28ms; datarate =93Mbps; ber = 0;} <--> VIFIBN13.medium++;
        VIFIBN60.medium++ <--> DatarateChannel {  delay = 17ms; datarate =93Mbps; ber = 0;} <--> VIFIBN75.medium++;
        VIFIBN60.medium++ <--> DatarateChannel {  delay = 24ms; datarate =82Mbps; ber = 0;} <--> VIFIBN87.medium++;
        VIFIBN60.medium++ <--> DatarateChannel {  delay = 18ms; datarate =92Mbps; ber = 0;} <--> VIFIBN89.medium++;
        VIFIBN61.medium++ <--> DatarateChannel {  delay = 27ms; datarate =99Mbps; ber = 0;} <--> VIFIBN7.medium++;
        VIFIBN61.medium++ <--> DatarateChannel {  delay = 12ms; datarate =97Mbps; ber = 0;} <--> VIFIBN17.medium++;
        VIFIBN61.medium++ <--> DatarateChannel {  delay = 22ms; datarate =98Mbps; ber = 0;} <--> VIFIBN21.medium++;
        VIFIBN61.medium++ <--> DatarateChannel {  delay = 13ms; datarate =87Mbps; ber = 0;} <--> VIFIBN22.medium++;
        VIFIBN61.medium++ <--> DatarateChannel {  delay = 24ms; datarate =90Mbps; ber = 0;} <--> VIFIBN29.medium++;
        VIFIBN61.medium++ <--> DatarateChannel {  delay = 29ms; datarate =91Mbps; ber = 0;} <--> VIFIBN34.medium++;
        VIFIBN61.medium++ <--> DatarateChannel {  delay = 18ms; datarate =87Mbps; ber = 0;} <--> VIFIBN44.medium++;
        VIFIBN61.medium++ <--> DatarateChannel {  delay = 21ms; datarate =81Mbps; ber = 0;} <--> VIFIBN48.medium++;
        VIFIBN61.medium++ <--> DatarateChannel {  delay = 10ms; datarate =97Mbps; ber = 0;} <--> VIFIBN50.medium++;
        VIFIBN61.medium++ <--> DatarateChannel {  delay = 17ms; datarate =88Mbps; ber = 0;} <--> VIFIBN63.medium++;
        VIFIBN61.medium++ <--> DatarateChannel {  delay = 29ms; datarate =83Mbps; ber = 0;} <--> VIFIBN65.medium++;
        VIFIBN61.medium++ <--> DatarateChannel {  delay = 21ms; datarate =83Mbps; ber = 0;} <--> VIFIBN67.medium++;
        VIFIBN61.medium++ <--> DatarateChannel {  delay = 15ms; datarate =81Mbps; ber = 0;} <--> VIFIBN68.medium++;
        VIFIBN61.medium++ <--> DatarateChannel {  delay = 30ms; datarate =95Mbps; ber = 0;} <--> VIFIBN71.medium++;
        VIFIBN62.medium++ <--> DatarateChannel {  delay = 13ms; datarate =93Mbps; ber = 0;} <--> VIFIBN65.medium++;
        VIFIBN62.medium++ <--> DatarateChannel {  delay = 25ms; datarate =81Mbps; ber = 0;} <--> VIFIBN66.medium++;
        VIFIBN63.medium++ <--> DatarateChannel {  delay = 14ms; datarate =82Mbps; ber = 0;} <--> VIFIBN12.medium++;
        VIFIBN63.medium++ <--> DatarateChannel {  delay = 23ms; datarate =90Mbps; ber = 0;} <--> VIFIBN50.medium++;
        VIFIBN63.medium++ <--> DatarateChannel {  delay = 15ms; datarate =82Mbps; ber = 0;} <--> VIFIBN54.medium++;
        VIFIBN63.medium++ <--> DatarateChannel {  delay = 18ms; datarate =96Mbps; ber = 0;} <--> VIFIBN58.medium++;
        VIFIBN63.medium++ <--> DatarateChannel {  delay = 20ms; datarate =80Mbps; ber = 0;} <--> VIFIBN76.medium++;
        VIFIBN63.medium++ <--> DatarateChannel {  delay = 15ms; datarate =99Mbps; ber = 0;} <--> VIFIBN80.medium++;
        VIFIBN64.medium++ <--> DatarateChannel {  delay = 23ms; datarate =92Mbps; ber = 0;} <--> VIFIBN35.medium++;
        VIFIBN64.medium++ <--> DatarateChannel {  delay = 13ms; datarate =99Mbps; ber = 0;} <--> VIFIBN48.medium++;
        VIFIBN64.medium++ <--> DatarateChannel {  delay = 18ms; datarate =81Mbps; ber = 0;} <--> VIFIBN56.medium++;
        VIFIBN64.medium++ <--> DatarateChannel {  delay = 28ms; datarate =83Mbps; ber = 0;} <--> VIFIBN65.medium++;
        VIFIBN64.medium++ <--> DatarateChannel {  delay = 18ms; datarate =82Mbps; ber = 0;} <--> VIFIBN69.medium++;
        VIFIBN64.medium++ <--> DatarateChannel {  delay = 23ms; datarate =86Mbps; ber = 0;} <--> VIFIBN70.medium++;
        VIFIBN64.medium++ <--> DatarateChannel {  delay = 27ms; datarate =98Mbps; ber = 0;} <--> VIFIBN90.medium++;
        VIFIBN64.medium++ <--> DatarateChannel {  delay = 28ms; datarate =84Mbps; ber = 0;} <--> VIFIBN91.medium++;
        VIFIBN64.medium++ <--> DatarateChannel {  delay = 14ms; datarate =97Mbps; ber = 0;} <--> VIFIBN93.medium++;
        VIFIBN64.medium++ <--> DatarateChannel {  delay = 20ms; datarate =98Mbps; ber = 0;} <--> VIFIBN95.medium++;
        VIFIBN64.medium++ <--> DatarateChannel {  delay = 23ms; datarate =88Mbps; ber = 0;} <--> VIFIBN97.medium++;
        VIFIBN65.medium++ <--> DatarateChannel {  delay = 18ms; datarate =94Mbps; ber = 0;} <--> VIFIBN70.medium++;
        VIFIBN65.medium++ <--> DatarateChannel {  delay = 23ms; datarate =88Mbps; ber = 0;} <--> VIFIBN82.medium++;
        VIFIBN65.medium++ <--> DatarateChannel {  delay = 24ms; datarate =81Mbps; ber = 0;} <--> VIFIBN84.medium++;
        VIFIBN65.medium++ <--> DatarateChannel {  delay = 24ms; datarate =90Mbps; ber = 0;} <--> VIFIBN86.medium++;
        VIFIBN65.medium++ <--> DatarateChannel {  delay = 24ms; datarate =86Mbps; ber = 0;} <--> VIFIBN92.medium++;
        VIFIBN66.medium++ <--> DatarateChannel {  delay = 26ms; datarate =98Mbps; ber = 0;} <--> VIFIBN18.medium++;
        VIFIBN66.medium++ <--> DatarateChannel {  delay = 22ms; datarate =94Mbps; ber = 0;} <--> VIFIBN65.medium++;
        VIFIBN66.medium++ <--> DatarateChannel {  delay = 14ms; datarate =94Mbps; ber = 0;} <--> VIFIBN78.medium++;
        VIFIBN67.medium++ <--> DatarateChannel {  delay = 23ms; datarate =87Mbps; ber = 0;} <--> VIFIBN70.medium++;
        VIFIBN67.medium++ <--> DatarateChannel {  delay = 19ms; datarate =97Mbps; ber = 0;} <--> VIFIBN74.medium++;
        VIFIBN68.medium++ <--> DatarateChannel {  delay = 22ms; datarate =81Mbps; ber = 0;} <--> VIFIBN59.medium++;
        VIFIBN68.medium++ <--> DatarateChannel {  delay = 29ms; datarate =89Mbps; ber = 0;} <--> VIFIBN60.medium++;
        VIFIBN68.medium++ <--> DatarateChannel {  delay = 27ms; datarate =86Mbps; ber = 0;} <--> VIFIBN66.medium++;
        VIFIBN68.medium++ <--> DatarateChannel {  delay = 18ms; datarate =80Mbps; ber = 0;} <--> VIFIBN70.medium++;
        VIFIBN68.medium++ <--> DatarateChannel {  delay = 30ms; datarate =86Mbps; ber = 0;} <--> VIFIBN75.medium++;
        VIFIBN68.medium++ <--> DatarateChannel {  delay = 14ms; datarate =91Mbps; ber = 0;} <--> VIFIBN77.medium++;
        VIFIBN68.medium++ <--> DatarateChannel {  delay = 20ms; datarate =91Mbps; ber = 0;} <--> VIFIBN84.medium++;
        VIFIBN68.medium++ <--> DatarateChannel {  delay = 13ms; datarate =92Mbps; ber = 0;} <--> VIFIBN85.medium++;
        VIFIBN69.medium++ <--> DatarateChannel {  delay = 14ms; datarate =89Mbps; ber = 0;} <--> VIFIBN11.medium++;
        VIFIBN69.medium++ <--> DatarateChannel {  delay = 16ms; datarate =87Mbps; ber = 0;} <--> VIFIBN54.medium++;
        VIFIBN69.medium++ <--> DatarateChannel {  delay = 21ms; datarate =95Mbps; ber = 0;} <--> VIFIBN60.medium++;
        VIFIBN69.medium++ <--> DatarateChannel {  delay = 12ms; datarate =98Mbps; ber = 0;} <--> VIFIBN68.medium++;
        VIFIBN69.medium++ <--> DatarateChannel {  delay = 28ms; datarate =90Mbps; ber = 0;} <--> VIFIBN74.medium++;
        VIFIBN69.medium++ <--> DatarateChannel {  delay = 29ms; datarate =87Mbps; ber = 0;} <--> VIFIBN80.medium++;
        VIFIBN69.medium++ <--> DatarateChannel {  delay = 15ms; datarate =91Mbps; ber = 0;} <--> VIFIBN81.medium++;
        VIFIBN70.medium++ <--> DatarateChannel {  delay = 18ms; datarate =95Mbps; ber = 0;} <--> VIFIBN82.medium++;
        VIFIBN70.medium++ <--> DatarateChannel {  delay = 17ms; datarate =85Mbps; ber = 0;} <--> VIFIBN84.medium++;
        VIFIBN71.medium++ <--> DatarateChannel {  delay = 22ms; datarate =80Mbps; ber = 0;} <--> VIFIBN65.medium++;
        VIFIBN71.medium++ <--> DatarateChannel {  delay = 20ms; datarate =90Mbps; ber = 0;} <--> VIFIBN67.medium++;
        VIFIBN71.medium++ <--> DatarateChannel {  delay = 26ms; datarate =95Mbps; ber = 0;} <--> VIFIBN84.medium++;
        VIFIBN71.medium++ <--> DatarateChannel {  delay = 19ms; datarate =95Mbps; ber = 0;} <--> VIFIBN87.medium++;
        VIFIBN71.medium++ <--> DatarateChannel {  delay = 26ms; datarate =91Mbps; ber = 0;} <--> VIFIBN95.medium++;
        VIFIBN71.medium++ <--> DatarateChannel {  delay = 35ms; datarate =81Mbps; ber = 0;} <--> VIFIBN77.medium++;
        VIFIBN72.medium++ <--> DatarateChannel {  delay = 20ms; datarate =98Mbps; ber = 0;} <--> VIFIBN12.medium++;
        VIFIBN72.medium++ <--> DatarateChannel {  delay = 24ms; datarate =98Mbps; ber = 0;} <--> VIFIBN60.medium++;
        VIFIBN72.medium++ <--> DatarateChannel {  delay = 12ms; datarate =88Mbps; ber = 0;} <--> VIFIBN69.medium++;
        VIFIBN72.medium++ <--> DatarateChannel {  delay = 19ms; datarate =82Mbps; ber = 0;} <--> VIFIBN75.medium++;
        VIFIBN72.medium++ <--> DatarateChannel {  delay = 19ms; datarate =87Mbps; ber = 0;} <--> VIFIBN83.medium++;
        VIFIBN72.medium++ <--> DatarateChannel {  delay = 13ms; datarate =87Mbps; ber = 0;} <--> VIFIBN85.medium++;
        VIFIBN72.medium++ <--> DatarateChannel {  delay = 29ms; datarate =90Mbps; ber = 0;} <--> VIFIBN87.medium++;
        VIFIBN72.medium++ <--> DatarateChannel {  delay = 10ms; datarate =88Mbps; ber = 0;} <--> VIFIBN93.medium++;
        VIFIBN73.medium++ <--> DatarateChannel {  delay = 10ms; datarate =97Mbps; ber = 0;} <--> VIFIBN74.medium++;
        VIFIBN73.medium++ <--> DatarateChannel {  delay = 30ms; datarate =95Mbps; ber = 0;} <--> VIFIBN83.medium++;
        VIFIBN73.medium++ <--> DatarateChannel {  delay = 28ms; datarate =92Mbps; ber = 0;} <--> VIFIBN90.medium++;
        VIFIBN74.medium++ <--> DatarateChannel {  delay = 20ms; datarate =93Mbps; ber = 0;} <--> VIFIBN82.medium++;
        VIFIBN74.medium++ <--> DatarateChannel {  delay = 23ms; datarate =85Mbps; ber = 0;} <--> VIFIBN83.medium++;
        VIFIBN74.medium++ <--> DatarateChannel {  delay = 20ms; datarate =81Mbps; ber = 0;} <--> VIFIBN90.medium++;
        VIFIBN75.medium++ <--> DatarateChannel {  delay = 12ms; datarate =81Mbps; ber = 0;} <--> VIFIBN74.medium++;
        VIFIBN75.medium++ <--> DatarateChannel {  delay = 13ms; datarate =99Mbps; ber = 0;} <--> VIFIBN84.medium++;
        VIFIBN75.medium++ <--> DatarateChannel {  delay = 19ms; datarate =86Mbps; ber = 0;} <--> VIFIBN98.medium++;
        VIFIBN76.medium++ <--> DatarateChannel {  delay = 22ms; datarate =93Mbps; ber = 0;} <--> VIFIBN78.medium++;
        VIFIBN76.medium++ <--> DatarateChannel {  delay = 13ms; datarate =87Mbps; ber = 0;} <--> VIFIBN83.medium++;
        VIFIBN76.medium++ <--> DatarateChannel {  delay = 20ms; datarate =84Mbps; ber = 0;} <--> VIFIBN86.medium++;
        VIFIBN76.medium++ <--> DatarateChannel {  delay = 16ms; datarate =88Mbps; ber = 0;} <--> VIFIBN96.medium++;
        VIFIBN77.medium++ <--> DatarateChannel {  delay = 20ms; datarate =96Mbps; ber = 0;} <--> VIFIBN73.medium++;
        VIFIBN77.medium++ <--> DatarateChannel {  delay = 14ms; datarate =86Mbps; ber = 0;} <--> VIFIBN74.medium++;
        VIFIBN77.medium++ <--> DatarateChannel {  delay = 14ms; datarate =99Mbps; ber = 0;} <--> VIFIBN88.medium++;
        VIFIBN77.medium++ <--> DatarateChannel {  delay = 13ms; datarate =96Mbps; ber = 0;} <--> VIFIBN100.medium++;
        VIFIBN78.medium++ <--> DatarateChannel {  delay = 30ms; datarate =88Mbps; ber = 0;} <--> VIFIBN70.medium++;
        VIFIBN78.medium++ <--> DatarateChannel {  delay = 20ms; datarate =81Mbps; ber = 0;} <--> VIFIBN85.medium++;
        VIFIBN78.medium++ <--> DatarateChannel {  delay = 24ms; datarate =95Mbps; ber = 0;} <--> VIFIBN95.medium++;
        VIFIBN79.medium++ <--> DatarateChannel {  delay = 26ms; datarate =94Mbps; ber = 0;} <--> VIFIBN17.medium++;
        VIFIBN79.medium++ <--> DatarateChannel {  delay = 22ms; datarate =92Mbps; ber = 0;} <--> VIFIBN60.medium++;
        VIFIBN79.medium++ <--> DatarateChannel {  delay = 14ms; datarate =88Mbps; ber = 0;} <--> VIFIBN68.medium++;
        VIFIBN79.medium++ <--> DatarateChannel {  delay = 29ms; datarate =91Mbps; ber = 0;} <--> VIFIBN80.medium++;
        VIFIBN79.medium++ <--> DatarateChannel {  delay = 23ms; datarate =91Mbps; ber = 0;} <--> VIFIBN84.medium++;
        VIFIBN79.medium++ <--> DatarateChannel {  delay = 17ms; datarate =93Mbps; ber = 0;} <--> VIFIBN89.medium++;
        VIFIBN79.medium++ <--> DatarateChannel {  delay = 26ms; datarate =80Mbps; ber = 0;} <--> VIFIBN95.medium++;
        VIFIBN79.medium++ <--> DatarateChannel {  delay = 18ms; datarate =98Mbps; ber = 0;} <--> VIFIBN97.medium++;
        VIFIBN80.medium++ <--> DatarateChannel {  delay = 17ms; datarate =85Mbps; ber = 0;} <--> VIFIBN48.medium++;
        VIFIBN80.medium++ <--> DatarateChannel {  delay = 30ms; datarate =80Mbps; ber = 0;} <--> VIFIBN60.medium++;
        VIFIBN80.medium++ <--> DatarateChannel {  delay = 13ms; datarate =95Mbps; ber = 0;} <--> VIFIBN65.medium++;
        VIFIBN80.medium++ <--> DatarateChannel {  delay = 10ms; datarate =91Mbps; ber = 0;} <--> VIFIBN67.medium++;
        VIFIBN80.medium++ <--> DatarateChannel {  delay = 26ms; datarate =85Mbps; ber = 0;} <--> VIFIBN77.medium++;
        VIFIBN80.medium++ <--> DatarateChannel {  delay = 15ms; datarate =97Mbps; ber = 0;} <--> VIFIBN88.medium++;
        VIFIBN81.medium++ <--> DatarateChannel {  delay = 19ms; datarate =91Mbps; ber = 0;} <--> VIFIBN60.medium++;
        VIFIBN81.medium++ <--> DatarateChannel {  delay = 24ms; datarate =85Mbps; ber = 0;} <--> VIFIBN70.medium++;
        VIFIBN81.medium++ <--> DatarateChannel {  delay = 14ms; datarate =95Mbps; ber = 0;} <--> VIFIBN74.medium++;
        VIFIBN81.medium++ <--> DatarateChannel {  delay = 22ms; datarate =87Mbps; ber = 0;} <--> VIFIBN85.medium++;
        VIFIBN81.medium++ <--> DatarateChannel {  delay = 26ms; datarate =95Mbps; ber = 0;} <--> VIFIBN99.medium++;
        VIFIBN82.medium++ <--> DatarateChannel {  delay = 85ms; datarate =90Mbps; ber = 0;} <--> VIFIBN85.medium++;
        VIFIBN83.medium++ <--> DatarateChannel {  delay = 11ms; datarate =91Mbps; ber = 0;} <--> VIFIBN98.medium++;
        VIFIBN83.medium++ <--> DatarateChannel {  delay = 12ms; datarate =97Mbps; ber = 0;} <--> VIFIBN99.medium++;
        VIFIBN84.medium++ <--> DatarateChannel {  delay = 18ms; datarate =87Mbps; ber = 0;} <--> VIFIBN90.medium++;
        VIFIBN84.medium++ <--> DatarateChannel {  delay = 21ms; datarate =88Mbps; ber = 0;} <--> VIFIBN99.medium++;
        VIFIBN85.medium++ <--> DatarateChannel {  delay = 19ms; datarate =88Mbps; ber = 0;} <--> VIFIBN100.medium++;
        VIFIBN86.medium++ <--> DatarateChannel {  delay = 25ms; datarate =94Mbps; ber = 0;} <--> VIFIBN83.medium++;
        VIFIBN86.medium++ <--> DatarateChannel {  delay = 13ms; datarate =86Mbps; ber = 0;} <--> VIFIBN87.medium++;
        VIFIBN86.medium++ <--> DatarateChannel {  delay = 29ms; datarate =88Mbps; ber = 0;} <--> VIFIBN98.medium++;
        VIFIBN86.medium++ <--> DatarateChannel {  delay = 18ms; datarate =83Mbps; ber = 0;} <--> VIFIBN100.medium++;
        VIFIBN86.medium++ <--> DatarateChannel {  delay = 88ms; datarate =81Mbps; ber = 0;} <--> VIFIBN92.medium++;
        VIFIBN86.medium++ <--> DatarateChannel {  delay = 68ms; datarate =98Mbps; ber = 0;} <--> VIFIBN96.medium++;
        VIFIBN87.medium++ <--> DatarateChannel {  delay = 28ms; datarate =82Mbps; ber = 0;} <--> VIFIBN90.medium++;
        VIFIBN87.medium++ <--> DatarateChannel {  delay = 10ms; datarate =83Mbps; ber = 0;} <--> VIFIBN92.medium++;
        VIFIBN87.medium++ <--> DatarateChannel {  delay = 24ms; datarate =99Mbps; ber = 0;} <--> VIFIBN95.medium++;
        VIFIBN87.medium++ <--> DatarateChannel {  delay = 22ms; datarate =95Mbps; ber = 0;} <--> VIFIBN99.medium++;
        VIFIBN87.medium++ <--> DatarateChannel {  delay = 12ms; datarate =98Mbps; ber = 0;} <--> VIFIBN100.medium++;
        VIFIBN87.medium++ <--> DatarateChannel {  delay = 86ms; datarate =90Mbps; ber = 0;} <--> VIFIBN96.medium++;
        VIFIBN88.medium++ <--> DatarateChannel {  delay = 22ms; datarate =86Mbps; ber = 0;} <--> VIFIBN74.medium++;
        VIFIBN88.medium++ <--> DatarateChannel {  delay = 12ms; datarate =90Mbps; ber = 0;} <--> VIFIBN75.medium++;
        VIFIBN88.medium++ <--> DatarateChannel {  delay = 19ms; datarate =90Mbps; ber = 0;} <--> VIFIBN83.medium++;
        VIFIBN88.medium++ <--> DatarateChannel {  delay = 11ms; datarate =93Mbps; ber = 0;} <--> VIFIBN84.medium++;
        VIFIBN88.medium++ <--> DatarateChannel {  delay = 19ms; datarate =95Mbps; ber = 0;} <--> VIFIBN85.medium++;
        VIFIBN88.medium++ <--> DatarateChannel {  delay = 20ms; datarate =95Mbps; ber = 0;} <--> VIFIBN97.medium++;
        VIFIBN88.medium++ <--> DatarateChannel {  delay = 23ms; datarate =99Mbps; ber = 0;} <--> VIFIBN98.medium++;
        VIFIBN88.medium++ <--> DatarateChannel {  delay = 12ms; datarate =82Mbps; ber = 0;} <--> VIFIBN99.medium++;
        VIFIBN89.medium++ <--> DatarateChannel {  delay = 20ms; datarate =99Mbps; ber = 0;} <--> VIFIBN92.medium++;
        VIFIBN89.medium++ <--> DatarateChannel {  delay = 29ms; datarate =89Mbps; ber = 0;} <--> VIFIBN96.medium++;
        VIFIBN89.medium++ <--> DatarateChannel {  delay = 18ms; datarate =86Mbps; ber = 0;} <--> VIFIBN98.medium++;
        VIFIBN89.medium++ <--> DatarateChannel {  delay = 19ms; datarate =88Mbps; ber = 0;} <--> VIFIBN100.medium++;
        VIFIBN90.medium++ <--> DatarateChannel {  delay = 23ms; datarate =92Mbps; ber = 0;} <--> VIFIBN95.medium++;
        VIFIBN90.medium++ <--> DatarateChannel {  delay = 48ms; datarate =93Mbps; ber = 0;} <--> VIFIBN97.medium++;
        VIFIBN91.medium++ <--> DatarateChannel {  delay = 21ms; datarate =96Mbps; ber = 0;} <--> VIFIBN21.medium++;
        VIFIBN91.medium++ <--> DatarateChannel {  delay = 16ms; datarate =95Mbps; ber = 0;} <--> VIFIBN77.medium++;
        VIFIBN91.medium++ <--> DatarateChannel {  delay = 16ms; datarate =98Mbps; ber = 0;} <--> VIFIBN82.medium++;
        VIFIBN91.medium++ <--> DatarateChannel {  delay = 20ms; datarate =91Mbps; ber = 0;} <--> VIFIBN83.medium++;
        VIFIBN91.medium++ <--> DatarateChannel {  delay = 19ms; datarate =80Mbps; ber = 0;} <--> VIFIBN89.medium++;
        VIFIBN91.medium++ <--> DatarateChannel {  delay = 15ms; datarate =99Mbps; ber = 0;} <--> VIFIBN90.medium++;
        VIFIBN91.medium++ <--> DatarateChannel {  delay = 27ms; datarate =90Mbps; ber = 0;} <--> VIFIBN92.medium++;
        VIFIBN91.medium++ <--> DatarateChannel {  delay = 20ms; datarate =90Mbps; ber = 0;} <--> VIFIBN94.medium++;
        VIFIBN92.medium++ <--> DatarateChannel {  delay = 23ms; datarate =86Mbps; ber = 0;} <--> VIFIBN85.medium++;
        VIFIBN92.medium++ <--> DatarateChannel {  delay = 16ms; datarate =83Mbps; ber = 0;} <--> VIFIBN96.medium++;
        VIFIBN92.medium++ <--> DatarateChannel {  delay = 21ms; datarate =87Mbps; ber = 0;} <--> VIFIBN100.medium++;
        VIFIBN93.medium++ <--> DatarateChannel {  delay = 25ms; datarate =95Mbps; ber = 0;} <--> VIFIBN73.medium++;
        VIFIBN93.medium++ <--> DatarateChannel {  delay = 23ms; datarate =99Mbps; ber = 0;} <--> VIFIBN75.medium++;
        VIFIBN93.medium++ <--> DatarateChannel {  delay = 42ms; datarate =97Mbps; ber = 0;} <--> VIFIBN77.medium++;
        VIFIBN94.medium++ <--> DatarateChannel {  delay = 19ms; datarate =85Mbps; ber = 0;} <--> VIFIBN73.medium++;
        VIFIBN94.medium++ <--> DatarateChannel {  delay = 11ms; datarate =96Mbps; ber = 0;} <--> VIFIBN74.medium++;
        VIFIBN94.medium++ <--> DatarateChannel {  delay = 19ms; datarate =83Mbps; ber = 0;} <--> VIFIBN78.medium++;
        VIFIBN94.medium++ <--> DatarateChannel {  delay = 28ms; datarate =86Mbps; ber = 0;} <--> VIFIBN85.medium++;
        VIFIBN94.medium++ <--> DatarateChannel {  delay = 20ms; datarate =90Mbps; ber = 0;} <--> VIFIBN86.medium++;
        VIFIBN94.medium++ <--> DatarateChannel {  delay = 26ms; datarate =80Mbps; ber = 0;} <--> VIFIBN89.medium++;
        VIFIBN94.medium++ <--> DatarateChannel {  delay = 92ms; datarate =84Mbps; ber = 0;} <--> VIFIBN83.medium++;
        VIFIBN95.medium++ <--> DatarateChannel {  delay = 22ms; datarate =95Mbps; ber = 0;} <--> VIFIBN96.medium++;
        VIFIBN95.medium++ <--> DatarateChannel {  delay = 16ms; datarate =83Mbps; ber = 0;} <--> VIFIBN97.medium++;
        VIFIBN95.medium++ <--> DatarateChannel {  delay = 16ms; datarate =87Mbps; ber = 0;} <--> VIFIBN99.medium++;
        VIFIBN97.medium++ <--> DatarateChannel {  delay = 29ms; datarate =82Mbps; ber = 0;} <--> VIFIBN96.medium++;
        VIFIBN97.medium++ <--> DatarateChannel {  delay = 13ms; datarate =94Mbps; ber = 0;} <--> VIFIBN99.medium++;
        VIFIBN98.medium++ <--> DatarateChannel {  delay = 30ms; datarate =89Mbps; ber = 0;} <--> VIFIBN96.medium++;
        VIFIBN98.medium++ <--> DatarateChannel {  delay = 18ms; datarate =82Mbps; ber = 0;} <--> VIFIBN100.medium++;
        VIFIBN23.medium++ <--> DatarateChannel {  delay = 55ms; datarate =100Mbps; ber = 0;} <--> VIFIBN13.medium++;
        VIFIBN23.medium++ <--> DatarateChannel {  delay = 40ms; datarate =100Mbps; ber = 0;} <--> VIFIBN53.medium++;
        VIFIBN23.medium++ <--> DatarateChannel {  delay = 83ms; datarate =100Mbps; ber = 0;} <--> VIFIBN32.medium++;
        VIFIBN23.medium++ <--> DatarateChannel {  delay = 46ms; datarate =100Mbps; ber = 0;} <--> VIFIBN94.medium++;
        VIFIBN23.medium++ <--> DatarateChannel {  delay = 65ms; datarate =100Mbps; ber = 0;} <--> VIFIBN51.medium++;
        VIFIBN23.medium++ <--> DatarateChannel {  delay = 89ms; datarate =100Mbps; ber = 0;} <--> VIFIBN47.medium++;
        VIFIBN23.medium++ <--> DatarateChannel {  delay = 64ms; datarate =100Mbps; ber = 0;} <--> VIFIBN77.medium++;
        VIFIBN23.medium++ <--> DatarateChannel {  delay = 20ms; datarate =100Mbps; ber = 0;} <--> VIFIBN91.medium++;
        VIFIBN23.medium++ <--> DatarateChannel {  delay = 18ms; datarate =100Mbps; ber = 0;} <--> VIFIBN92.medium++;
        VIFIBN23.medium++ <--> DatarateChannel {  delay = 53ms; datarate =100Mbps; ber = 0;} <--> VIFIBN36.medium++;
        VIFIBN23.medium++ <--> DatarateChannel {  delay = 49ms; datarate =100Mbps; ber = 0;} <--> VIFIBN68.medium++;
        VIFIBN48.medium++ <--> DatarateChannel {  delay = 40ms; datarate =100Mbps; ber = 0;} <--> VIFIBN23.medium++;
        VIFIBN48.medium++ <--> DatarateChannel {  delay = 82ms; datarate =100Mbps; ber = 0;} <--> VIFIBN13.medium++;
        VIFIBN48.medium++ <--> DatarateChannel {  delay = 52ms; datarate =100Mbps; ber = 0;} <--> VIFIBN19.medium++;
        VIFIBN48.medium++ <--> DatarateChannel {  delay = 24ms; datarate =100Mbps; ber = 0;} <--> VIFIBN53.medium++;
        VIFIBN48.medium++ <--> DatarateChannel {  delay = 33ms; datarate =100Mbps; ber = 0;} <--> VIFIBN31.medium++;
        VIFIBN48.medium++ <--> DatarateChannel {  delay = 28ms; datarate =100Mbps; ber = 0;} <--> VIFIBN94.medium++;
        VIFIBN48.medium++ <--> DatarateChannel {  delay = 31ms; datarate =100Mbps; ber = 0;} <--> VIFIBN51.medium++;
        VIFIBN48.medium++ <--> DatarateChannel {  delay = 65ms; datarate =100Mbps; ber = 0;} <--> VIFIBN47.medium++;
        VIFIBN48.medium++ <--> DatarateChannel {  delay = 72ms; datarate =100Mbps; ber = 0;} <--> VIFIBN77.medium++;
        VIFIBN48.medium++ <--> DatarateChannel {  delay = 91ms; datarate =100Mbps; ber = 0;} <--> VIFIBN91.medium++;
        VIFIBN48.medium++ <--> DatarateChannel {  delay = 90ms; datarate =100Mbps; ber = 0;} <--> VIFIBN92.medium++;
        VIFIBN48.medium++ <--> DatarateChannel {  delay = 83ms; datarate =100Mbps; ber = 0;} <--> VIFIBN36.medium++;
        VIFIBN48.medium++ <--> DatarateChannel {  delay = 72ms; datarate =100Mbps; ber = 0;} <--> VIFIBN68.medium++;
        VIFIBN13.medium++ <--> DatarateChannel {  delay = 61ms; datarate =100Mbps; ber = 0;} <--> VIFIBN19.medium++;
        VIFIBN13.medium++ <--> DatarateChannel {  delay = 91ms; datarate =100Mbps; ber = 0;} <--> VIFIBN31.medium++;
        VIFIBN13.medium++ <--> DatarateChannel {  delay = 72ms; datarate =100Mbps; ber = 0;} <--> VIFIBN94.medium++;
        VIFIBN13.medium++ <--> DatarateChannel {  delay = 72ms; datarate =100Mbps; ber = 0;} <--> VIFIBN51.medium++;
        VIFIBN13.medium++ <--> DatarateChannel {  delay = 37ms; datarate =100Mbps; ber = 0;} <--> VIFIBN77.medium++;
        VIFIBN13.medium++ <--> DatarateChannel {  delay = 75ms; datarate =100Mbps; ber = 0;} <--> VIFIBN91.medium++;
        VIFIBN13.medium++ <--> DatarateChannel {  delay = 68ms; datarate =100Mbps; ber = 0;} <--> VIFIBN92.medium++;
        VIFIBN13.medium++ <--> DatarateChannel {  delay = 34ms; datarate =100Mbps; ber = 0;} <--> VIFIBN36.medium++;
        VIFIBN13.medium++ <--> DatarateChannel {  delay = 11ms; datarate =100Mbps; ber = 0;} <--> VIFIBN68.medium++;
        VIFIBN19.medium++ <--> DatarateChannel {  delay = 93ms; datarate =100Mbps; ber = 0;} <--> VIFIBN32.medium++;
        VIFIBN19.medium++ <--> DatarateChannel {  delay = 64ms; datarate =100Mbps; ber = 0;} <--> VIFIBN94.medium++;
        VIFIBN19.medium++ <--> DatarateChannel {  delay = 43ms; datarate =100Mbps; ber = 0;} <--> VIFIBN51.medium++;
        VIFIBN19.medium++ <--> DatarateChannel {  delay = 40ms; datarate =100Mbps; ber = 0;} <--> VIFIBN47.medium++;
        VIFIBN19.medium++ <--> DatarateChannel {  delay = 75ms; datarate =100Mbps; ber = 0;} <--> VIFIBN77.medium++;
        VIFIBN19.medium++ <--> DatarateChannel {  delay = 27ms; datarate =100Mbps; ber = 0;} <--> VIFIBN91.medium++;
        VIFIBN19.medium++ <--> DatarateChannel {  delay = 22ms; datarate =100Mbps; ber = 0;} <--> VIFIBN92.medium++;
        VIFIBN19.medium++ <--> DatarateChannel {  delay = 72ms; datarate =100Mbps; ber = 0;} <--> VIFIBN36.medium++;
        VIFIBN19.medium++ <--> DatarateChannel {  delay = 64ms; datarate =100Mbps; ber = 0;} <--> VIFIBN68.medium++;
        VIFIBN53.medium++ <--> DatarateChannel {  delay = 68ms; datarate =100Mbps; ber = 0;} <--> VIFIBN32.medium++;
        VIFIBN53.medium++ <--> DatarateChannel {  delay = 71ms; datarate =100Mbps; ber = 0;} <--> VIFIBN94.medium++;
        VIFIBN53.medium++ <--> DatarateChannel {  delay = 39ms; datarate =100Mbps; ber = 0;} <--> VIFIBN51.medium++;
        VIFIBN53.medium++ <--> DatarateChannel {  delay = 83ms; datarate =100Mbps; ber = 0;} <--> VIFIBN47.medium++;
        VIFIBN53.medium++ <--> DatarateChannel {  delay = 84ms; datarate =100Mbps; ber = 0;} <--> VIFIBN77.medium++;
        VIFIBN53.medium++ <--> DatarateChannel {  delay = 77ms; datarate =100Mbps; ber = 0;} <--> VIFIBN91.medium++;
        VIFIBN53.medium++ <--> DatarateChannel {  delay = 42ms; datarate =100Mbps; ber = 0;} <--> VIFIBN92.medium++;
        VIFIBN53.medium++ <--> DatarateChannel {  delay = 50ms; datarate =100Mbps; ber = 0;} <--> VIFIBN36.medium++;
        VIFIBN53.medium++ <--> DatarateChannel {  delay = 67ms; datarate =100Mbps; ber = 0;} <--> VIFIBN68.medium++;
        VIFIBN31.medium++ <--> DatarateChannel {  delay = 93ms; datarate =100Mbps; ber = 0;} <--> VIFIBN32.medium++;
        VIFIBN31.medium++ <--> DatarateChannel {  delay = 87ms; datarate =100Mbps; ber = 0;} <--> VIFIBN94.medium++;
        VIFIBN31.medium++ <--> DatarateChannel {  delay = 38ms; datarate =100Mbps; ber = 0;} <--> VIFIBN51.medium++;
        VIFIBN31.medium++ <--> DatarateChannel {  delay = 40ms; datarate =100Mbps; ber = 0;} <--> VIFIBN47.medium++;
        VIFIBN31.medium++ <--> DatarateChannel {  delay = 30ms; datarate =100Mbps; ber = 0;} <--> VIFIBN77.medium++;
        VIFIBN31.medium++ <--> DatarateChannel {  delay = 38ms; datarate =100Mbps; ber = 0;} <--> VIFIBN91.medium++;
        VIFIBN31.medium++ <--> DatarateChannel {  delay = 36ms; datarate =100Mbps; ber = 0;} <--> VIFIBN92.medium++;
        VIFIBN31.medium++ <--> DatarateChannel {  delay = 75ms; datarate =100Mbps; ber = 0;} <--> VIFIBN36.medium++;
        VIFIBN31.medium++ <--> DatarateChannel {  delay = 31ms; datarate =100Mbps; ber = 0;} <--> VIFIBN68.medium++;
        VIFIBN32.medium++ <--> DatarateChannel {  delay = 63ms; datarate =100Mbps; ber = 0;} <--> VIFIBN94.medium++;
        VIFIBN32.medium++ <--> DatarateChannel {  delay = 28ms; datarate =100Mbps; ber = 0;} <--> VIFIBN51.medium++;
        VIFIBN32.medium++ <--> DatarateChannel {  delay = 42ms; datarate =100Mbps; ber = 0;} <--> VIFIBN47.medium++;
        VIFIBN32.medium++ <--> DatarateChannel {  delay = 35ms; datarate =100Mbps; ber = 0;} <--> VIFIBN77.medium++;
        VIFIBN32.medium++ <--> DatarateChannel {  delay = 29ms; datarate =100Mbps; ber = 0;} <--> VIFIBN91.medium++;
        VIFIBN32.medium++ <--> DatarateChannel {  delay = 39ms; datarate =100Mbps; ber = 0;} <--> VIFIBN92.medium++;
        VIFIBN32.medium++ <--> DatarateChannel {  delay = 14ms; datarate =100Mbps; ber = 0;} <--> VIFIBN68.medium++;
        VIFIBN94.medium++ <--> DatarateChannel {  delay = 15ms; datarate =100Mbps; ber = 0;} <--> VIFIBN51.medium++;
        VIFIBN94.medium++ <--> DatarateChannel {  delay = 44ms; datarate =100Mbps; ber = 0;} <--> VIFIBN47.medium++;
        VIFIBN94.medium++ <--> DatarateChannel {  delay = 83ms; datarate =100Mbps; ber = 0;} <--> VIFIBN77.medium++;
        VIFIBN94.medium++ <--> DatarateChannel {  delay = 65ms; datarate =100Mbps; ber = 0;} <--> VIFIBN92.medium++;
        VIFIBN94.medium++ <--> DatarateChannel {  delay = 81ms; datarate =100Mbps; ber = 0;} <--> VIFIBN36.medium++;
        VIFIBN94.medium++ <--> DatarateChannel {  delay = 41ms; datarate =100Mbps; ber = 0;} <--> VIFIBN68.medium++;
        VIFIBN51.medium++ <--> DatarateChannel {  delay = 99ms; datarate =100Mbps; ber = 0;} <--> VIFIBN47.medium++;
        VIFIBN51.medium++ <--> DatarateChannel {  delay = 41ms; datarate =100Mbps; ber = 0;} <--> VIFIBN77.medium++;
        VIFIBN51.medium++ <--> DatarateChannel {  delay = 40ms; datarate =100Mbps; ber = 0;} <--> VIFIBN91.medium++;
        VIFIBN51.medium++ <--> DatarateChannel {  delay = 42ms; datarate =100Mbps; ber = 0;} <--> VIFIBN92.medium++;
        VIFIBN51.medium++ <--> DatarateChannel {  delay = 18ms; datarate =100Mbps; ber = 0;} <--> VIFIBN36.medium++;
        VIFIBN51.medium++ <--> DatarateChannel {  delay = 57ms; datarate =100Mbps; ber = 0;} <--> VIFIBN68.medium++;
        VIFIBN47.medium++ <--> DatarateChannel {  delay = 31ms; datarate =100Mbps; ber = 0;} <--> VIFIBN77.medium++;
        VIFIBN47.medium++ <--> DatarateChannel {  delay = 35ms; datarate =100Mbps; ber = 0;} <--> VIFIBN91.medium++;
        VIFIBN47.medium++ <--> DatarateChannel {  delay = 12ms; datarate =100Mbps; ber = 0;} <--> VIFIBN92.medium++;
        VIFIBN47.medium++ <--> DatarateChannel {  delay = 23ms; datarate =100Mbps; ber = 0;} <--> VIFIBN36.medium++;
        VIFIBN47.medium++ <--> DatarateChannel {  delay = 65ms; datarate =100Mbps; ber = 0;} <--> VIFIBN68.medium++;
        VIFIBN77.medium++ <--> DatarateChannel {  delay = 49ms; datarate =100Mbps; ber = 0;} <--> VIFIBN92.medium++;
        VIFIBN77.medium++ <--> DatarateChannel {  delay = 99ms; datarate =100Mbps; ber = 0;} <--> VIFIBN36.medium++;
        VIFIBN91.medium++ <--> DatarateChannel {  delay = 44ms; datarate =100Mbps; ber = 0;} <--> VIFIBN36.medium++;
        VIFIBN91.medium++ <--> DatarateChannel {  delay = 11ms; datarate =100Mbps; ber = 0;} <--> VIFIBN68.medium++;
        VIFIBN92.medium++ <--> DatarateChannel {  delay = 41ms; datarate =100Mbps; ber = 0;} <--> VIFIBN36.medium++;
        VIFIBN92.medium++ <--> DatarateChannel {  delay = 66ms; datarate =100Mbps; ber = 0;} <--> VIFIBN68.medium++;
        VIFIBN36.medium++ <--> DatarateChannel {  delay = 60ms; datarate =100Mbps; ber = 0;} <--> VIFIBN68.medium++;

}
