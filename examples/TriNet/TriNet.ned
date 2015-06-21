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

package rina.examples.TriNet;

import ned.DatarateChannel;
import rina.src.CS.HostNAP;
import rina.src.CS.InteriorRouter2Int;
import rina.src.CS.InteriorRouter3Int;


network TriNet
{
    @display("bgb=325,256");
    submodules:
        A: InteriorRouter2Int {
            @display("p=96,118");
        }
        B: InteriorRouter2Int {
            @display("p=170,45");
        }
        C: InteriorRouter2Int {
            @display("p=170,198");
        }
        D: InteriorRouter2Int {
            @display("p=239,118");
        }
    connections allowunconnected:
        A.medium[0] <--> B.medium[0];
        A.medium[1] <--> C.medium[0];
        
        B.medium[1] <--> D.medium[0];
        C.medium[1] <--> D.medium[1];

}
