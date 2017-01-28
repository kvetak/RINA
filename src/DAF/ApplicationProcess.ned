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

package rina.src.DAF;

import rina.src.Common.Test;
import rina.src.DAF.AEManagement.AEManagement;
import rina.src.DAF.CDAP.CommonDistributedApplicationProtocol;
import rina.src.DAF.DA.DIFAllocator;
import rina.src.DAF.IRM.ConnectionTable;
import rina.src.DAF.IRM.IRM;
import rina.src.DIF.RMT.RMT;
import rina.src.DAF.AP.APInst;
import rina.src.DAF.RIB.DAFRIBDaemon;
import rina.src.DAF.AE.ApplicationEntity;
import rina.src.DAF.Enrollment.DAFEnrollmentModule;

module ApplicationProcess
{
    parameters:
        @display("bgb=400,220;i=misc/node,yellow,30");
        string apName = default("App");
        string apInstance = default("0");
        string apType = default("AP");
    gates:
        inout southIo[];
    submodules:
        apInst: <apType> like APInst {
            @display("p=35,35");
        }

        ribDaemon: DAFRIBDaemon {
            @display("p=200,60;i=block/segm");
        }

        enrollment: DAFEnrollmentModule {
            @display("p=325,60");
        }

        aeManagement: ApplicationEntity {
            @display("p=200,150;i=block/cogwheel");
        }
    connections allowunconnected:
}
