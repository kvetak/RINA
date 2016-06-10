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

package rina.playground.UPC.OverTags.examples.ABCD;
import ned.DatarateChannel;
import rina.src.Other.OverTags.MA;
import rina.src.Other.OverTags.Relay;


network ABCD
{
    @display("bgb=388,221");
    submodules:
        A: Relay {
            @display("p=90,47");
        }
        B: Relay {
            @display("p=276,47");
        }
        C: Relay {
            @display("p=90,163");
        }
        D: Relay {
            @display("p=276,163");
        }
        Manager: MA {
            @display("p=190,105");
        }
    connections:
        A.maIo <--> DatarateChannel <--> Manager.maIo++;
        B.maIo <--> DatarateChannel <--> Manager.maIo++;
        C.maIo <--> DatarateChannel <--> Manager.maIo++;
        D.maIo <--> DatarateChannel <--> Manager.maIo++;
}
