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

package rina.examples.Routing.MeshBWRT;


import rina.src.CS.InteriorRouterNInt;


network MeshBWRT
{
    @display("bgb=774,505");

    submodules:
        R0: InteriorRouterNInt {
            @display("p=92,248");
        }
        R1: InteriorRouterNInt {
            @display("p=193,164");
        }
        R2: InteriorRouterNInt {
            @display("p=181,363");
        }
        R3: InteriorRouterNInt {
            @display("p=282,279");
        }
        R4: InteriorRouterNInt {
            @display("p=282,112");
        }
        R5: InteriorRouterNInt {
            @display("p=405,96");
        }
        R6: InteriorRouterNInt {
            @display("p=405,388");
        }
        R7: InteriorRouterNInt {
            @display("p=554,248");
        }
    connections:
        R0.medium++ <--> R1.medium++;
        R0.medium++ <--> R2.medium++;
        R1.medium++ <--> R3.medium++;
        R1.medium++ <--> R4.medium++;
        R2.medium++ <--> R3.medium++;
        R2.medium++ <--> R6.medium++;
        R3.medium++ <--> R4.medium++;
        R3.medium++ <--> R5.medium++;
        R3.medium++ <--> R6.medium++;
        R4.medium++ <--> R5.medium++;
        R5.medium++ <--> R6.medium++;
        R5.medium++ <--> R7.medium++;
        R6.medium++ <--> R7.medium++;
}
