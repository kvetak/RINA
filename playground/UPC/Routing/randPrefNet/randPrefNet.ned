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

package rina.playground.UPC.Routing.randPrefNet;

import ned.DelayChannel;
import rina.src.CS.InteriorRouterNMInt;


network randPrefNet
{
    @display("bgb=1510,1265");
    submodules:
        R1I1: InteriorRouterNMInt {
            @display("p=670,140");
        }
        R1I2: InteriorRouterNMInt {
            @display("p=585,129");
        }
        R1I3: InteriorRouterNMInt {
            @display("p=524,280");
        }
        R1I4: InteriorRouterNMInt {
            @display("p=452,217");
        }
        R1I5: InteriorRouterNMInt {
            @display("p=452,168");
        }
        R1I6: InteriorRouterNMInt {
            @display("p=624,29");
        }
        R1I7: InteriorRouterNMInt {
            @display("p=423,113");
        }
        R1I8: InteriorRouterNMInt {
            @display("p=524,29");
        }
        R1I9: InteriorRouterNMInt {
            @display("p=624,256");
        }
        R2I1: InteriorRouterNMInt {
            @display("p=287,335");
        }
        R2I2: InteriorRouterNMInt {
            @display("p=353,215");
        }
        R2I3: InteriorRouterNMInt {
            @display("p=138,363");
        }
        R2I4: InteriorRouterNMInt {
            @display("p=55,405");
        }
        R2I5: InteriorRouterNMInt {
            @display("p=265,254");
        }
        R2I6: InteriorRouterNMInt {
            @display("p=121,288");
        }
        R2I7: InteriorRouterNMInt {
            @display("p=226,366");
        }
        R2I8: InteriorRouterNMInt {
            @display("p=353,391");
        }
        R2I9: InteriorRouterNMInt {
            @display("p=187,310");
        }
        R2Ia: InteriorRouterNMInt {
            @display("p=258,191");
        }
        R2Ib: InteriorRouterNMInt {
            @display("p=394,390");
        }
        R3I1: InteriorRouterNMInt {
            @display("p=193,437");
        }
        R3I2: InteriorRouterNMInt {
            @display("p=55,512");
        }
        R3I3: InteriorRouterNMInt {
            @display("p=94,711");
        }
        R3I4: InteriorRouterNMInt {
            @display("p=211,573");
        }
        R3I5: InteriorRouterNMInt {
            @display("p=332,612");
        }
        R3I6: InteriorRouterNMInt {
            @display("p=274,512");
        }
        R3I7: InteriorRouterNMInt {
            @display("p=246,690");
        }
        R3I8: InteriorRouterNMInt {
            @display("p=173,690");
        }
        R3I9: InteriorRouterNMInt {
            @display("p=154,557");
        }
        R3Ia: InteriorRouterNMInt {
            @display("p=81,651");
        }
        R4I1: InteriorRouterNMInt {
            @display("p=291,942");
        }
        R4I2: InteriorRouterNMInt {
            @display("p=210,958");
        }
        R4I3: InteriorRouterNMInt {
            @display("p=140,896");
        }
        R4I4: InteriorRouterNMInt {
            @display("p=330,842");
        }
        R4I5: InteriorRouterNMInt {
            @display("p=171,799");
        }
        R4I6: InteriorRouterNMInt {
            @display("p=101,825");
        }
        R4I7: InteriorRouterNMInt {
            @display("p=313,739");
        }
        R4I8: InteriorRouterNMInt {
            @display("p=235,881");
        }
        R5I1: InteriorRouterNMInt {
            @display("p=508,951");
        }
        R5I2: InteriorRouterNMInt {
            @display("p=284,1107");
        }
        R5I3: InteriorRouterNMInt {
            @display("p=442,1013");
        }
        R5I4: InteriorRouterNMInt {
            @display("p=403,1189");
        }
        R5I5: InteriorRouterNMInt {
            @display("p=387,1006");
        }
        R5I6: InteriorRouterNMInt {
            @display("p=547,1198");
        }
        R5I7: InteriorRouterNMInt {
            @display("p=481,1140");
        }
        R5I8: InteriorRouterNMInt {
            @display("p=606,991");
        }
        R5I9: InteriorRouterNMInt {
            @display("p=403,1077");
        }
        R5Ia: InteriorRouterNMInt {
            @display("p=547,1030");
        }
        R5Ib: InteriorRouterNMInt {
            @display("p=403,912");
        }
        R6I1: InteriorRouterNMInt {
            @display("p=888,996");
        }
        R6I2: InteriorRouterNMInt {
            @display("p=820,1090");
        }
        R6I3: InteriorRouterNMInt {
            @display("p=948,1123");
        }
        R6I4: InteriorRouterNMInt {
            @display("p=898,919");
        }
        R6I5: InteriorRouterNMInt {
            @display("p=1010,1188");
        }
        R6I6: InteriorRouterNMInt {
            @display("p=759,1013");
        }
        R6I7: InteriorRouterNMInt {
            @display("p=987,1035");
        }
        R6I8: InteriorRouterNMInt {
            @display("p=898,1204");
        }
        R6I9: InteriorRouterNMInt {
            @display("p=720,1149");
        }
        R6Ia: InteriorRouterNMInt {
            @display("p=664,1204");
        }
        R6Ib: InteriorRouterNMInt {
            @display("p=703,974");
        }
        R7I1: InteriorRouterNMInt {
            @display("p=1273,1021");
        }
        R7I2: InteriorRouterNMInt {
            @display("p=1082,857");
        }
        R7I3: InteriorRouterNMInt {
            @display("p=1149,1060");
        }
        R7I4: InteriorRouterNMInt {
            @display("p=1285,866");
        }
        R7I5: InteriorRouterNMInt {
            @display("p=1133,967");
        }
        R7I6: InteriorRouterNMInt {
            @display("p=1075,1013");
        }
        R7I7: InteriorRouterNMInt {
            @display("p=986,912");
        }
        R7I8: InteriorRouterNMInt {
            @display("p=1160,803");
        }
        R8I1: InteriorRouterNMInt {
            @display("p=1388,496");
        }
        R8I2: InteriorRouterNMInt {
            @display("p=1306,767");
        }
        R8I3: InteriorRouterNMInt {
            @display("p=1420,655");
        }
        R8I4: InteriorRouterNMInt {
            @display("p=1257,490");
        }
        R8I5: InteriorRouterNMInt {
            @display("p=1201,722");
        }
        R8I6: InteriorRouterNMInt {
            @display("p=1366,722");
        }
        R8I7: InteriorRouterNMInt {
            @display("p=1381,574");
        }
        R8I8: InteriorRouterNMInt {
            @display("p=1163,559");
        }
        R8I9: InteriorRouterNMInt {
            @display("p=1317,661");
        }
        R8Ia: InteriorRouterNMInt {
            @display("p=1162,667");
        }
        R8Ib: InteriorRouterNMInt {
            @display("p=1240,584");
        }
        R9I1: InteriorRouterNMInt {
            @display("p=1306,361");
        }
        R9I2: InteriorRouterNMInt {
            @display("p=1230,322");
        }
        R9I3: InteriorRouterNMInt {
            @display("p=1210,445");
        }
        R9I4: InteriorRouterNMInt {
            @display("p=1316,428");
        }
        R9I5: InteriorRouterNMInt {
            @display("p=1377,283");
        }
        R9I6: InteriorRouterNMInt {
            @display("p=1125,283");
        }
        R9I7: InteriorRouterNMInt {
            @display("p=1279,247");
        }
        R9I8: InteriorRouterNMInt {
            @display("p=1136,389");
        }
        R9I9: InteriorRouterNMInt {
            @display("p=1464,361");
        }
        RaI1: InteriorRouterNMInt {
            @display("p=980,90");
        }
        RaI2: InteriorRouterNMInt {
            @display("p=786,192");
        }
        RaI3: InteriorRouterNMInt {
            @display("p=961,219");
        }
        RaI4: InteriorRouterNMInt {
            @display("p=1085,146");
        }
        RaI5: InteriorRouterNMInt {
            @display("p=901,138");
        }
        RaI6: InteriorRouterNMInt {
            @display("p=1094,219");
        }
        RaI7: InteriorRouterNMInt {
            @display("p=817,107");
        }
        RaI8: InteriorRouterNMInt {
            @display("p=744,129");
        }
        RaI9: InteriorRouterNMInt {

            @display("p=1026,217");
        }
        
    connections:
        R1I1.mediumIntra++ <--> DelayChannel{delay=1us;} <-->  R1I9.mediumIntra++;
        R1I2.mediumIntra++ <--> DelayChannel{delay=1us;} <-->  R1I3.mediumIntra++;
        R1I2.mediumIntra++ <--> DelayChannel{delay=1us;} <-->  R1I4.mediumIntra++;
        R1I2.mediumIntra++ <--> DelayChannel{delay=1us;} <-->  R1I6.mediumIntra++;
        R1I2.mediumIntra++ <--> DelayChannel{delay=1us;} <-->  R1I7.mediumIntra++;
        R1I2.mediumIntra++ <--> DelayChannel{delay=1us;} <-->  R1I8.mediumIntra++;
        R1I3.mediumIntra++ <--> DelayChannel{delay=1us;} <-->  R1I4.mediumIntra++;
        R1I3.mediumIntra++ <--> DelayChannel{delay=1us;} <-->  R1I8.mediumIntra++;
        R1I3.mediumIntra++ <--> DelayChannel{delay=1us;} <-->  R1I9.mediumIntra++;
        R1I4.mediumIntra++ <--> DelayChannel{delay=1us;} <-->  R1I5.mediumIntra++;
        R1I5.mediumIntra++ <--> DelayChannel{delay=1us;} <-->  R1I7.mediumIntra++;
        R1I6.mediumIntra++ <--> DelayChannel{delay=1us;} <-->  R1I9.mediumIntra++;
        R1I7.mediumIntra++ <--> DelayChannel{delay=1us;} <-->  R1I8.mediumIntra++;
        R2I1.mediumIntra++ <--> DelayChannel{delay=1us;} <-->  R2I3.mediumIntra++;
        R2I1.mediumIntra++ <--> DelayChannel{delay=1us;} <-->  R2I5.mediumIntra++;
        R2I1.mediumIntra++ <--> DelayChannel{delay=1us;} <-->  R2I7.mediumIntra++;
        R2I1.mediumIntra++ <--> DelayChannel{delay=1us;} <-->  R2I8.mediumIntra++;
        R2I2.mediumIntra++ <--> DelayChannel{delay=1us;} <-->  R2I5.mediumIntra++;
        R2I2.mediumIntra++ <--> DelayChannel{delay=1us;} <-->  R2Ib.mediumIntra++;
        R2I3.mediumIntra++ <--> DelayChannel{delay=1us;} <-->  R2I6.mediumIntra++;
        R2I3.mediumIntra++ <--> DelayChannel{delay=1us;} <-->  R2I9.mediumIntra++;
        R2I4.mediumIntra++ <--> DelayChannel{delay=1us;} <-->  R2I6.mediumIntra++;
        R2I4.mediumIntra++ <--> DelayChannel{delay=1us;} <-->  R2I8.mediumIntra++;
        R2I5.mediumIntra++ <--> DelayChannel{delay=1us;} <-->  R2I6.mediumIntra++;
        R2I5.mediumIntra++ <--> DelayChannel{delay=1us;} <-->  R2Ib.mediumIntra++;
        R2I6.mediumIntra++ <--> DelayChannel{delay=1us;} <-->  R2Ia.mediumIntra++;
        R2I7.mediumIntra++ <--> DelayChannel{delay=1us;} <-->  R2I9.mediumIntra++;
        R2I9.mediumIntra++ <--> DelayChannel{delay=1us;} <-->  R2Ib.mediumIntra++;
        R2Ia.mediumIntra++ <--> DelayChannel{delay=1us;} <-->  R2Ib.mediumIntra++;
        R3I1.mediumIntra++ <--> DelayChannel{delay=1us;} <-->  R3I2.mediumIntra++;
        R3I1.mediumIntra++ <--> DelayChannel{delay=1us;} <-->  R3I6.mediumIntra++;
        R3I2.mediumIntra++ <--> DelayChannel{delay=1us;} <-->  R3I6.mediumIntra++;
        R3I2.mediumIntra++ <--> DelayChannel{delay=1us;} <-->  R3I8.mediumIntra++;
        R3I2.mediumIntra++ <--> DelayChannel{delay=1us;} <-->  R3I9.mediumIntra++;
        R3I2.mediumIntra++ <--> DelayChannel{delay=1us;} <-->  R3Ia.mediumIntra++;
        R3I3.mediumIntra++ <--> DelayChannel{delay=1us;} <-->  R3Ia.mediumIntra++;
        R3I4.mediumIntra++ <--> DelayChannel{delay=1us;} <-->  R3I5.mediumIntra++;
        R3I4.mediumIntra++ <--> DelayChannel{delay=1us;} <-->  R3I7.mediumIntra++;
        R3I4.mediumIntra++ <--> DelayChannel{delay=1us;} <-->  R3I9.mediumIntra++;
        R3I5.mediumIntra++ <--> DelayChannel{delay=1us;} <-->  R3I7.mediumIntra++;
        R3I5.mediumIntra++ <--> DelayChannel{delay=1us;} <-->  R3Ia.mediumIntra++;
        R3I7.mediumIntra++ <--> DelayChannel{delay=1us;} <-->  R3I8.mediumIntra++;
        R3I8.mediumIntra++ <--> DelayChannel{delay=1us;} <-->  R3I9.mediumIntra++;
        R3I9.mediumIntra++ <--> DelayChannel{delay=1us;} <-->  R3Ia.mediumIntra++;
        R4I1.mediumIntra++ <--> DelayChannel{delay=1us;} <-->  R4I2.mediumIntra++;
        R4I1.mediumIntra++ <--> DelayChannel{delay=1us;} <-->  R4I4.mediumIntra++;
        R4I1.mediumIntra++ <--> DelayChannel{delay=1us;} <-->  R4I8.mediumIntra++;
        R4I2.mediumIntra++ <--> DelayChannel{delay=1us;} <-->  R4I3.mediumIntra++;
        R4I2.mediumIntra++ <--> DelayChannel{delay=1us;} <-->  R4I5.mediumIntra++;
        R4I2.mediumIntra++ <--> DelayChannel{delay=1us;} <-->  R4I8.mediumIntra++;
        R4I3.mediumIntra++ <--> DelayChannel{delay=1us;} <-->  R4I5.mediumIntra++;
        R4I3.mediumIntra++ <--> DelayChannel{delay=1us;} <-->  R4I6.mediumIntra++;
        R4I4.mediumIntra++ <--> DelayChannel{delay=1us;} <-->  R4I5.mediumIntra++;
        R4I4.mediumIntra++ <--> DelayChannel{delay=1us;} <-->  R4I7.mediumIntra++;
        R4I5.mediumIntra++ <--> DelayChannel{delay=1us;} <-->  R4I7.mediumIntra++;
        R4I7.mediumIntra++ <--> DelayChannel{delay=1us;} <-->  R4I8.mediumIntra++;
        R5I1.mediumIntra++ <--> DelayChannel{delay=1us;} <-->  R5I3.mediumIntra++;
        R5I1.mediumIntra++ <--> DelayChannel{delay=1us;} <-->  R5I4.mediumIntra++;
        R5I1.mediumIntra++ <--> DelayChannel{delay=1us;} <-->  R5I7.mediumIntra++;
        R5I2.mediumIntra++ <--> DelayChannel{delay=1us;} <-->  R5I3.mediumIntra++;
        R5I2.mediumIntra++ <--> DelayChannel{delay=1us;} <-->  R5I4.mediumIntra++;
        R5I2.mediumIntra++ <--> DelayChannel{delay=1us;} <-->  R5I6.mediumIntra++;
        R5I2.mediumIntra++ <--> DelayChannel{delay=1us;} <-->  R5I7.mediumIntra++;
        R5I2.mediumIntra++ <--> DelayChannel{delay=1us;} <-->  R5Ib.mediumIntra++;
        R5I3.mediumIntra++ <--> DelayChannel{delay=1us;} <-->  R5I5.mediumIntra++;
        R5I3.mediumIntra++ <--> DelayChannel{delay=1us;} <-->  R5I9.mediumIntra++;
        R5I4.mediumIntra++ <--> DelayChannel{delay=1us;} <-->  R5I6.mediumIntra++;
        R5I4.mediumIntra++ <--> DelayChannel{delay=1us;} <-->  R5I9.mediumIntra++;
        R5I6.mediumIntra++ <--> DelayChannel{delay=1us;} <-->  R5I7.mediumIntra++;
        R5I6.mediumIntra++ <--> DelayChannel{delay=1us;} <-->  R5I8.mediumIntra++;
        R5I7.mediumIntra++ <--> DelayChannel{delay=1us;} <-->  R5Ia.mediumIntra++;
        R5I8.mediumIntra++ <--> DelayChannel{delay=1us;} <-->  R5Ia.mediumIntra++;
        R6I1.mediumIntra++ <--> DelayChannel{delay=1us;} <-->  R6I6.mediumIntra++;
        R6I1.mediumIntra++ <--> DelayChannel{delay=1us;} <-->  R6I8.mediumIntra++;
        R6I2.mediumIntra++ <--> DelayChannel{delay=1us;} <-->  R6I6.mediumIntra++;
        R6I2.mediumIntra++ <--> DelayChannel{delay=1us;} <-->  R6I9.mediumIntra++;
        R6I3.mediumIntra++ <--> DelayChannel{delay=1us;} <-->  R6I4.mediumIntra++;
        R6I3.mediumIntra++ <--> DelayChannel{delay=1us;} <-->  R6I5.mediumIntra++;
        R6I3.mediumIntra++ <--> DelayChannel{delay=1us;} <-->  R6I6.mediumIntra++;
        R6I3.mediumIntra++ <--> DelayChannel{delay=1us;} <-->  R6I9.mediumIntra++;
        R6I4.mediumIntra++ <--> DelayChannel{delay=1us;} <-->  R6I6.mediumIntra++;
        R6I4.mediumIntra++ <--> DelayChannel{delay=1us;} <-->  R6I7.mediumIntra++;
        R6I5.mediumIntra++ <--> DelayChannel{delay=1us;} <-->  R6I8.mediumIntra++;
        R6I6.mediumIntra++ <--> DelayChannel{delay=1us;} <-->  R6Ib.mediumIntra++;
        R6I8.mediumIntra++ <--> DelayChannel{delay=1us;} <-->  R6Ia.mediumIntra++;
        R6I9.mediumIntra++ <--> DelayChannel{delay=1us;} <-->  R6Ia.mediumIntra++;
        R6I9.mediumIntra++ <--> DelayChannel{delay=1us;} <-->  R6Ib.mediumIntra++;
        R6Ia.mediumIntra++ <--> DelayChannel{delay=1us;} <-->  R6Ib.mediumIntra++;
        R7I1.mediumIntra++ <--> DelayChannel{delay=1us;} <-->  R7I2.mediumIntra++;
        R7I1.mediumIntra++ <--> DelayChannel{delay=1us;} <-->  R7I3.mediumIntra++;
        R7I1.mediumIntra++ <--> DelayChannel{delay=1us;} <-->  R7I4.mediumIntra++;
        R7I1.mediumIntra++ <--> DelayChannel{delay=1us;} <-->  R7I5.mediumIntra++;
        R7I1.mediumIntra++ <--> DelayChannel{delay=1us;} <-->  R7I8.mediumIntra++;
        R7I2.mediumIntra++ <--> DelayChannel{delay=1us;} <-->  R7I5.mediumIntra++;
        R7I2.mediumIntra++ <--> DelayChannel{delay=1us;} <-->  R7I7.mediumIntra++;
        R7I3.mediumIntra++ <--> DelayChannel{delay=1us;} <-->  R7I6.mediumIntra++;
        R7I4.mediumIntra++ <--> DelayChannel{delay=1us;} <-->  R7I5.mediumIntra++;
        R7I5.mediumIntra++ <--> DelayChannel{delay=1us;} <-->  R7I7.mediumIntra++;
        R7I5.mediumIntra++ <--> DelayChannel{delay=1us;} <-->  R7I8.mediumIntra++;
        R7I6.mediumIntra++ <--> DelayChannel{delay=1us;} <-->  R7I7.mediumIntra++;
        R8I1.mediumIntra++ <--> DelayChannel{delay=1us;} <-->  R8I4.mediumIntra++;
        R8I1.mediumIntra++ <--> DelayChannel{delay=1us;} <-->  R8I7.mediumIntra++;
        R8I1.mediumIntra++ <--> DelayChannel{delay=1us;} <-->  R8I8.mediumIntra++;
        R8I1.mediumIntra++ <--> DelayChannel{delay=1us;} <-->  R8Ib.mediumIntra++;
        R8I2.mediumIntra++ <--> DelayChannel{delay=1us;} <-->  R8I5.mediumIntra++;
        R8I2.mediumIntra++ <--> DelayChannel{delay=1us;} <-->  R8I9.mediumIntra++;
        R8I3.mediumIntra++ <--> DelayChannel{delay=1us;} <-->  R8I7.mediumIntra++;
        R8I3.mediumIntra++ <--> DelayChannel{delay=1us;} <-->  R8I9.mediumIntra++;
        R8I4.mediumIntra++ <--> DelayChannel{delay=1us;} <-->  R8I8.mediumIntra++;
        R8I5.mediumIntra++ <--> DelayChannel{delay=1us;} <-->  R8I7.mediumIntra++;
        R8I5.mediumIntra++ <--> DelayChannel{delay=1us;} <-->  R8I9.mediumIntra++;
        R8I6.mediumIntra++ <--> DelayChannel{delay=1us;} <-->  R8I7.mediumIntra++;
        R8I6.mediumIntra++ <--> DelayChannel{delay=1us;} <-->  R8I9.mediumIntra++;
        R8I7.mediumIntra++ <--> DelayChannel{delay=1us;} <-->  R8Ia.mediumIntra++;
        R8I7.mediumIntra++ <--> DelayChannel{delay=1us;} <-->  R8Ib.mediumIntra++;
        R8Ia.mediumIntra++ <--> DelayChannel{delay=1us;} <-->  R8Ib.mediumIntra++;
        R9I1.mediumIntra++ <--> DelayChannel{delay=1us;} <-->  R9I2.mediumIntra++;
        R9I2.mediumIntra++ <--> DelayChannel{delay=1us;} <-->  R9I3.mediumIntra++;
        R9I2.mediumIntra++ <--> DelayChannel{delay=1us;} <-->  R9I6.mediumIntra++;
        R9I3.mediumIntra++ <--> DelayChannel{delay=1us;} <-->  R9I6.mediumIntra++;
        R9I3.mediumIntra++ <--> DelayChannel{delay=1us;} <-->  R9I9.mediumIntra++;
        R9I4.mediumIntra++ <--> DelayChannel{delay=1us;} <-->  R9I5.mediumIntra++;
        R9I4.mediumIntra++ <--> DelayChannel{delay=1us;} <-->  R9I7.mediumIntra++;
        R9I4.mediumIntra++ <--> DelayChannel{delay=1us;} <-->  R9I8.mediumIntra++;
        R9I5.mediumIntra++ <--> DelayChannel{delay=1us;} <-->  R9I6.mediumIntra++;
        R9I5.mediumIntra++ <--> DelayChannel{delay=1us;} <-->  R9I7.mediumIntra++;
        R9I6.mediumIntra++ <--> DelayChannel{delay=1us;} <-->  R9I8.mediumIntra++;
        R9I6.mediumIntra++ <--> DelayChannel{delay=1us;} <-->  R9I9.mediumIntra++;
        R9I7.mediumIntra++ <--> DelayChannel{delay=1us;} <-->  R9I8.mediumIntra++;
        RaI1.mediumIntra++ <--> DelayChannel{delay=1us;} <-->  RaI6.mediumIntra++;
        RaI1.mediumIntra++ <--> DelayChannel{delay=1us;} <-->  RaI7.mediumIntra++;
        RaI2.mediumIntra++ <--> DelayChannel{delay=1us;} <-->  RaI7.mediumIntra++;
        RaI2.mediumIntra++ <--> DelayChannel{delay=1us;} <-->  RaI8.mediumIntra++;
        RaI2.mediumIntra++ <--> DelayChannel{delay=1us;} <-->  RaI9.mediumIntra++;
        RaI3.mediumIntra++ <--> DelayChannel{delay=1us;} <-->  RaI5.mediumIntra++;
        RaI3.mediumIntra++ <--> DelayChannel{delay=1us;} <-->  RaI6.mediumIntra++;
        RaI3.mediumIntra++ <--> DelayChannel{delay=1us;} <-->  RaI9.mediumIntra++;
        RaI4.mediumIntra++ <--> DelayChannel{delay=1us;} <-->  RaI6.mediumIntra++;
        RaI5.mediumIntra++ <--> DelayChannel{delay=1us;} <-->  RaI6.mediumIntra++;
        RaI5.mediumIntra++ <--> DelayChannel{delay=1us;} <-->  RaI9.mediumIntra++;
        RaI6.mediumIntra++ <--> DelayChannel{delay=1us;} <-->  RaI9.mediumIntra++;
        RaI7.mediumIntra++ <--> DelayChannel{delay=1us;} <-->  RaI9.mediumIntra++;
        R1I3.mediumInter++ <--> DelayChannel{delay=1us;} <-->  R6I4.mediumInter++;
        R1I3.mediumInter++ <--> DelayChannel{delay=1us;} <-->  R6Ib.mediumInter++;
        R1I9.mediumInter++ <--> DelayChannel{delay=1us;} <-->  R6I4.mediumInter++;
        R2I8.mediumInter++ <--> DelayChannel{delay=1us;} <-->  R5Ib.mediumInter++;
        R2Ib.mediumInter++ <--> DelayChannel{delay=1us;} <-->  R5I1.mediumInter++;
        R2Ib.mediumInter++ <--> DelayChannel{delay=1us;} <-->  R5I8.mediumInter++;
        R3I5.mediumInter++ <--> DelayChannel{delay=1us;} <-->  R7I7.mediumInter++;
        R3I5.mediumInter++ <--> DelayChannel{delay=1us;} <-->  R9I8.mediumInter++;
        R3I6.mediumInter++ <--> DelayChannel{delay=1us;} <-->  R7I7.mediumInter++;
        R3I6.mediumInter++ <--> DelayChannel{delay=1us;} <-->  R7I8.mediumInter++;
        R3I6.mediumInter++ <--> DelayChannel{delay=1us;} <-->  R9I6.mediumInter++;
        R4I4.mediumInter++ <--> DelayChannel{delay=1us;} <-->  R5Ib.mediumInter++;
        R4I4.mediumInter++ <--> DelayChannel{delay=1us;} <-->  R6I4.mediumInter++;
        R4I4.mediumInter++ <--> DelayChannel{delay=1us;} <-->  R6Ib.mediumInter++;
        R4I7.mediumInter++ <--> DelayChannel{delay=1us;} <-->  R5Ib.mediumInter++;
        R5I1.mediumInter++ <--> DelayChannel{delay=1us;} <-->  R6I4.mediumInter++;
        R5I1.mediumInter++ <--> DelayChannel{delay=1us;} <-->  R8I8.mediumInter++;
        R5I1.mediumInter++ <--> DelayChannel{delay=1us;} <-->  R9I6.mediumInter++;
        R5I8.mediumInter++ <--> DelayChannel{delay=1us;} <-->  R8I8.mediumInter++;
        R5I8.mediumInter++ <--> DelayChannel{delay=1us;} <-->  R9I8.mediumInter++;
        R5Ib.mediumInter++ <--> DelayChannel{delay=1us;} <-->  R6I4.mediumInter++;
        R5Ib.mediumInter++ <--> DelayChannel{delay=1us;} <-->  R6Ib.mediumInter++;
        R5Ib.mediumInter++ <--> DelayChannel{delay=1us;} <-->  R9I8.mediumInter++;
        R6I4.mediumInter++ <--> DelayChannel{delay=1us;} <-->  R7I2.mediumInter++;
        R6I4.mediumInter++ <--> DelayChannel{delay=1us;} <-->  R7I7.mediumInter++;
        R6I4.mediumInter++ <--> DelayChannel{delay=1us;} <-->  R7I8.mediumInter++;
        R6I4.mediumInter++ <--> DelayChannel{delay=1us;} <-->  RaI2.mediumInter++;
        R6I4.mediumInter++ <--> DelayChannel{delay=1us;} <-->  RaI9.mediumInter++;
        R6Ib.mediumInter++ <--> DelayChannel{delay=1us;} <-->  R8I5.mediumInter++;
        R6Ib.mediumInter++ <--> DelayChannel{delay=1us;} <-->  R8I8.mediumInter++;
        R6Ib.mediumInter++ <--> DelayChannel{delay=1us;} <-->  R8Ia.mediumInter++;
        R6Ib.mediumInter++ <--> DelayChannel{delay=1us;} <-->  RaI9.mediumInter++;
        R7I2.mediumInter++ <--> DelayChannel{delay=1us;} <-->  R9I8.mediumInter++;
        R7I7.mediumInter++ <--> DelayChannel{delay=1us;} <-->  R9I8.mediumInter++;
        R7I8.mediumInter++ <--> DelayChannel{delay=1us;} <-->  R8I5.mediumInter++;
        R7I8.mediumInter++ <--> DelayChannel{delay=1us;} <-->  R8Ia.mediumInter++;
        R7I8.mediumInter++ <--> DelayChannel{delay=1us;} <-->  R9I3.mediumInter++;
        R9I3.mediumInter++ <--> DelayChannel{delay=1us;} <-->  RaI9.mediumInter++;
        R9I6.mediumInter++ <--> DelayChannel{delay=1us;} <-->  RaI2.mediumInter++;
        R9I8.mediumInter++ <--> DelayChannel{delay=1us;} <-->  RaI2.mediumInter++;

}
