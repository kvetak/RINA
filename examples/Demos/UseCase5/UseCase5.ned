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

package rina.examples.Demos.UseCase5;

import ned.DelayChannel;
import rina.src.CS.BorderRouter2n1nm;
import rina.src.CS.BorderRouter2n1nmLeft;
import rina.src.CS.Host1AP;
import rina.src.CS.InteriorRouter2Int;


network UseCase5
{
    submodules:
        BorderRouterA: BorderRouter2n1nm {
            @display("p=147,145");
        }
        BorderRouterB: BorderRouter2n1nmLeft {
            @display("p=379,145");
        }
        HostA: Host1AP {
            @display("p=41,50");
        }
        HostB: Host1AP {
            @display("p=482,50");
        }
        InteriorRouter: InteriorRouter2Int {
            @display("p=263,145");
        }
    connections:
        HostA.medium <--> DelayChannel {  delay = 1ms; } <--> BorderRouterA.medium[0];
        HostB.medium <--> DelayChannel {  delay = 1ms; } <--> BorderRouterB.medium[0];
        BorderRouterA.medium[1] <--> DelayChannel {  delay = 1ms; } <--> InteriorRouter.medium++;
        BorderRouterB.medium[1] <--> DelayChannel {  delay = 1ms; } <--> InteriorRouter.medium++;
}
