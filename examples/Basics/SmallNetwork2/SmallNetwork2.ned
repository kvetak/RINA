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

package rina.examples.Basics.SmallNetwork2;
import ned.DatarateChannel;
import rina.src.CS.Host1AP;
import rina.src.CS.InteriorRouter2Int;
import rina.src.CS.InteriorRouter3Int;


network SmallNetwork2
{
    @display("bgb=586,372");
    submodules:
        host1: Host1AP {
            @display("p=92,83");
        }
        host2: Host1AP {
            @display("p=92,252");
        }
        //        host3: Host1AP {
        //            @display("p=275,83");
        //        }
        host4: Host1AP {
            @display("p=473,83");
        }
        host5: Host1AP {
            @display("p=473,252");
        }
        router1: InteriorRouter3Int {
            @display("p=166,165");
        }
        router2: InteriorRouter2Int {
            @display("p=275,165");
        }
        router3: InteriorRouter3Int {
            @display("p=388,165");
        }

    connections:
//        router1.medium[0] <--> host1.medium;
//        router1.medium[1] <--> host2.medium;
//        router1.medium[2] <--> router2.medium[0];
//        router2.medium[1] <--> router3.medium[0];
////        router2.medium[2] <--> host3.medium;
//        router3.medium[1] <--> host4.medium;
//        router3.medium[2] <--> host5.medium;

        router1.medium[0] <--> NormalPath <--> host1.medium;
        router1.medium[1] <--> NormalPath <--> host2.medium;
        router1.medium[2] <--> NormalPath <--> router2.medium[0];
        router2.medium[1] <--> NormalPath <--> router3.medium[0];
//        router2.medium[2] <--> host3.medium;
        router3.medium[1] <--> NormalPath <--> host4.medium;
        router3.medium[2] <--> ErroneousPath <--> host5.medium;
}

channel NormalPath extends DatarateChannel
{
    parameters:
        datarate = 1Mbps;
        delay = 1us; // 10m
        per = 0;
        ber = 0;
}

channel LongPath extends DatarateChannel
{
    parameters:
        datarate = 1Mbps;
        delay = 0.0565us; // 10m
        per = 0;
        ber = 0;
}

channel ErroneousPath extends DatarateChannel
{
    parameters:
        datarate = 1Mbps;
        delay = 1us; // 10m
        per = 0.00;
        ber = 0.0;
}
