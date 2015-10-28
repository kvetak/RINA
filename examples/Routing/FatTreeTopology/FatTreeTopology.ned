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
// Author: Kewin Rausch <kewin.rausch@create-net.org>
// Description: Provides a small DC example using RINA.

package rina.examples.Routing.FatTreeTopology;

import rina.src.CS.Host1AP;
import rina.src.CS.InteriorRouter2Int;
import rina.src.CS.InteriorRouter4Int;


network FatTreeTopology
{
    @display("bgb=975,618");

    submodules:

        AS1: InteriorRouter2Int {
            @display("p=267,96");
        }
        AS2: InteriorRouter2Int {
            @display("p=667,96");
        }
        TOR1: InteriorRouter4Int {
            @display("p=267,268");
        }
        TOR2: InteriorRouter4Int {
            @display("p=667,268");
        }

        Server1: Host1AP {
            @display("p=185,441");
        }
        Server2: Host1AP {
            @display("p=349,441");
        }
        Server3: Host1AP {
            @display("p=585,441");
        }
        Server4: Host1AP {
            @display("p=749,441");
        }

    connections:

        AS1.medium[0] <--> TOR1.medium[0];
        AS1.medium[1] <--> TOR2.medium[0];

        AS2.medium[0] <--> TOR1.medium[1];
        AS2.medium[1] <--> TOR2.medium[1];

        Server1.medium <--> TOR1.medium[2];
        Server2.medium <--> TOR1.medium[3];

        Server3.medium <--> TOR2.medium[2];
        Server4.medium <--> TOR2.medium[3];
}
