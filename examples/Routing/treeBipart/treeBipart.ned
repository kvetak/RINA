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

package rina.examples.Routing.treeBipart;
import rina.src.CS.HostNAP;
import rina.src.CS.InteriorRouterNInt;


network treeBipart
{
    submodules:
        N0: InteriorRouterNInt {
            @display("p=450,1000");
        }
        N0_0: InteriorRouterNInt {
            @display("p=350.0,50.0");
        }
        N0_0_0: InteriorRouterNInt {
            @display("p=250.0,-266.6666666666667");
        }
        S0_0_0: HostNAP {
            @display("p=150.0,-266.6666666666667");
        }
        N0_0_1: InteriorRouterNInt {
            @display("p=250.0,-55.55555555555557");
        }
        S0_0_1: HostNAP {
            @display("p=150.0,-55.55555555555557");
        }
        N0_0_2: InteriorRouterNInt {
            @display("p=250.0,155.55555555555554");
        }
        S0_0_2: HostNAP {
            @display("p=150.0,155.55555555555554");
        }
        N0_1: InteriorRouterNInt {
            @display("p=350.0,683.3333333333334");
        }
        N0_1_0: InteriorRouterNInt {
            @display("p=250.0,366.6666666666667");
        }
        S0_1_0: HostNAP {
            @display("p=150.0,366.6666666666667");
        }
        N0_1_1: InteriorRouterNInt {
            @display("p=250.0,577.7777777777778");
        }
        S0_1_1: HostNAP {
            @display("p=150.0,577.7777777777778");
        }
        N0_1_2: InteriorRouterNInt {
            @display("p=250.0,788.8888888888889");
        }
        S0_1_2: HostNAP {
            @display("p=150.0,788.8888888888889");
        }
        N0_2: InteriorRouterNInt {
            @display("p=350.0,1316.6666666666667");
        }
        N0_2_0: InteriorRouterNInt {
            @display("p=250.0,1000.0");
        }
        S0_2_0: HostNAP {
            @display("p=150.0,1000.0");
        }
        N0_2_1: InteriorRouterNInt {
            @display("p=250.0,1211.111111111111");
        }
        S0_2_1: HostNAP {
            @display("p=150.0,1211.111111111111");
        }
        N0_2_2: InteriorRouterNInt {
            @display("p=250.0,1422.2222222222222");
        }
        S0_2_2: HostNAP {
            @display("p=150.0,1422.2222222222222");
        }
        N1: InteriorRouterNInt {
            @display("p=550,1000");
        }
        N1_0: InteriorRouterNInt {
            @display("p=650.0,50.0");
        }
        N1_0_0: InteriorRouterNInt {
            @display("p=750.0,-266.6666666666667");
        }
        S1_0_0: HostNAP {
            @display("p=850.0,-266.6666666666667");
        }
        N1_0_1: InteriorRouterNInt {
            @display("p=750.0,-55.55555555555557");
        }
        S1_0_1: HostNAP {
            @display("p=850.0,-55.55555555555557");
        }
        N1_0_2: InteriorRouterNInt {
            @display("p=750.0,155.55555555555554");
        }
        S1_0_2: HostNAP {
            @display("p=850.0,155.55555555555554");
        }
        N1_1: InteriorRouterNInt {
            @display("p=650.0,683.3333333333334");
        }
        N1_1_0: InteriorRouterNInt {
            @display("p=750.0,366.6666666666667");
        }
        S1_1_0: HostNAP {
            @display("p=850.0,366.6666666666667");
        }
        N1_1_1: InteriorRouterNInt {
            @display("p=750.0,577.7777777777778");
        }
        S1_1_1: HostNAP {
            @display("p=850.0,577.7777777777778");
        }
        N1_1_2: InteriorRouterNInt {
            @display("p=750.0,788.8888888888889");
        }
        S1_1_2: HostNAP {
            @display("p=850.0,788.8888888888889");
        }
        N1_2: InteriorRouterNInt {
            @display("p=650.0,1316.6666666666667");
        }
        N1_2_0: InteriorRouterNInt {
            @display("p=750.0,1000.0");
        }
        S1_2_0: HostNAP {
            @display("p=850.0,1000.0");
        }
        N1_2_1: InteriorRouterNInt {
            @display("p=750.0,1211.111111111111");
        }
        S1_2_1: HostNAP {
            @display("p=850.0,1211.111111111111");
        }
        N1_2_2: InteriorRouterNInt {
            @display("p=750.0,1422.2222222222222");
        }
        S1_2_2: HostNAP {
            @display("p=850.0,1422.2222222222222");
        }
    connections:
        N0.medium++ <--> N1.medium++;
        N0_0.medium++ <--> N0.medium++;
        N0_0_0.medium++ <--> N0_0.medium++;
        S0_0_0.medium <--> N0_0_0.medium++;
        N0_0_1.medium++ <--> N0_0.medium++;
        S0_0_1.medium <--> N0_0_1.medium++;
        N0_0_2.medium++ <--> N0_0.medium++;
        S0_0_2.medium <--> N0_0_2.medium++;
        N0_1.medium++ <--> N0.medium++;
        N0_1_0.medium++ <--> N0_1.medium++;
        S0_1_0.medium <--> N0_1_0.medium++;
        N0_1_1.medium++ <--> N0_1.medium++;
        S0_1_1.medium <--> N0_1_1.medium++;
        N0_1_2.medium++ <--> N0_1.medium++;
        S0_1_2.medium <--> N0_1_2.medium++;
        N0_2.medium++ <--> N0.medium++;
        N0_2_0.medium++ <--> N0_2.medium++;
        S0_2_0.medium <--> N0_2_0.medium++;
        N0_2_1.medium++ <--> N0_2.medium++;
        S0_2_1.medium <--> N0_2_1.medium++;
        N0_2_2.medium++ <--> N0_2.medium++;
        S0_2_2.medium <--> N0_2_2.medium++;
        N1_0.medium++ <--> N1.medium++;
        N1_0_0.medium++ <--> N1_0.medium++;
        S1_0_0.medium <--> N1_0_0.medium++;
        N1_0_1.medium++ <--> N1_0.medium++;
        S1_0_1.medium <--> N1_0_1.medium++;
        N1_0_2.medium++ <--> N1_0.medium++;
        S1_0_2.medium <--> N1_0_2.medium++;
        N1_1.medium++ <--> N1.medium++;
        N1_1_0.medium++ <--> N1_1.medium++;
        S1_1_0.medium <--> N1_1_0.medium++;
        N1_1_1.medium++ <--> N1_1.medium++;
        S1_1_1.medium <--> N1_1_1.medium++;
        N1_1_2.medium++ <--> N1_1.medium++;
        S1_1_2.medium <--> N1_1_2.medium++;
        N1_2.medium++ <--> N1.medium++;
        N1_2_0.medium++ <--> N1_2.medium++;
        S1_2_0.medium <--> N1_2_0.medium++;
        N1_2_1.medium++ <--> N1_2.medium++;
        S1_2_1.medium <--> N1_2_1.medium++;
        N1_2_2.medium++ <--> N1_2.medium++;
        S1_2_2.medium <--> N1_2_2.medium++;
        
        N1_2_2.medium++ <--> N1_2_1.medium++;
}
