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

package rina.src.DIF.RIB;

import rina.src.DAF.CDAP.CommonDistributedApplicationProtocol;
import rina.src.DIF.Enrollment.EnrollmentNotifier;
import rina.src.DIF.FA.FANotifier;
module RIBDaemon
{
    parameters:
        @display("i=block/control;bgb=271,360");

    gates:
        inout rmtIo;
        inout efcpIo;

    submodules:
        commonDistributedApplicationProtocol: CommonDistributedApplicationProtocol {
            parameters:
                @display("p=147,211");
            gates:
                southIo;
        }
        ribd: RIBd {
            parameters:
                @display("p=147,118");
        }

        ribdSplitter: RIBdSplitter {
            @display("p=147,304");
        }
        faNotifier: FANotifier {
            @display("p=60,31");
        }
        enrollmentNotifier: EnrollmentNotifier {
            @display("p=60,144");
        }
        routingNotifier: RoutingNotifier {
            @display("p=60,85");
        }
    connections allowunconnected:
        commonDistributedApplicationProtocol.southIo <--> ribdSplitter.cdapIo;
        ribdSplitter.rmtIo <--> rmtIo;
        ribdSplitter.efcpIo <--> efcpIo;
}
import rina.src.DIF.Routing.RoutingNotifier;


