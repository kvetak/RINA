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

package rina.examples.Routing.SimpleMultipath;
import rina.src.CS.Host1AP;
import rina.src.CS.HostNAP;
import rina.src.CS.InteriorRouterNInt;


network SimpleMultipath
{
    @display("bgb=388,432");
    submodules:
        host1: HostNAP {
            @display("p=95,370");
        }
        host2: HostNAP {
            @display("p=253,370");
        }
        router1: InteriorRouterNInt {
            @display("p=95,223");
        }
        router2: InteriorRouterNInt {
            @display("p=253,42");
        }
        router3: InteriorRouterNInt {
            @display("p=95,42");
        }
        router4: InteriorRouterNInt {
            @display("p=253,223");
        }
    connections:
        host1.medium <--> router1.medium++;
        router1.medium++ <--> router2.medium++;
        router1.medium++ <--> router3.medium++;
        host2.medium <--> router4.medium++;
        router2.medium++ <--> router4.medium++;
        router3.medium++ <--> router4.medium++;
}
