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

package rina.src.DAF.AE;

import rina.src.DAF.CDAP.CommonDistributedApplicationProtocol;
import rina.src.Common.Socket;


module ApplicationEntityInstance
{
    parameters:
        @display("i=block/socket;bgb=276,300");
        string aeType = default("AE");
    gates:
        inout aeIo[];
                
    submodules:
        commonDistributedApplicationProtocol: CommonDistributedApplicationProtocol {
            @display("p=135,145");
        }
        iae: <aeType> like IAE {
            @display("p=135,48");
        }
        socket: Socket {
            @display("p=135,230");
        }

    connections allowunconnected:
        socket.cdapIo <--> commonDistributedApplicationProtocol.southIo;
}
