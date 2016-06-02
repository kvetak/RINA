//
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

import rina.policies.DIF.RMT.Scheduler.IntRMTSchedulingPolicy;
import rina.policies.DIF.RMT.Monitor.IntRMTQMonitorPolicy;
import rina.policies.DIF.RMT.MaxQueue.IntRMTMaxQPolicy;
import rina.policies.DIF.RMT.PDUForwarding.IntPDUForwarding;

package rina.src.DIF.RMT;

module RelayAndMux
{
    parameters:
        @display("i=block/classifier;bgb=700,230");

        string schedPolicyName = default("LongestQFirst");
        string qMonitorPolicyName = default("DummyMonitor");
        string maxQPolicyName = default("TailDrop");
        string ForwardingPolicyName = default("SimpleTable");
		string sdupPolicyName = default("DummyProtection");
		
		
        int defaultMaxQLength = default(20);
        int defaultThreshQLength = default(10);
        
        // PDU tracefile generation.
        // format: event time node ipcp pduType pduSize flags flow DIF srcAddr dstAddr seq id
        //
        // event: r (receive) / s (send) / + (enqueue) / - (dequeue) / d (drop)
        // time: event timestamp in seconds
        // node: node name
        // ipcp: IPC process name
        // pduType: PDU type
        // pduSize: PDU size in bits
        // flags: PDU flags
        // flow: flow-id (srcCEP + dstCEP + qosID)
        // DIF: DIF name
        // srcAddr: source address
        // dstAddr: destination address
        // seq: PDU sequence number
        // id: packet ID (unambiguous in scope of whole simulation)
        bool pduTracing = default(false);

    gates:
        inout ribdIo;

    submodules:
        rmt: RMT {
            @display("p=55,55");
        }
        schedulingPolicy: <schedPolicyName> like IntRMTSchedulingPolicy {
            @display("p=175,55;is=s");
        }
        queueMonitorPolicy: <qMonitorPolicyName> like IntRMTQMonitorPolicy {
            @display("p=295,55;is=s");
        }
        maxQueuePolicy: <maxQPolicyName> like IntRMTMaxQPolicy {
            @display("p=415,55;is=s");
        }
        pduForwardingPolicy: <ForwardingPolicyName> like IntPDUForwarding {
            @display("p=535,55;is=s");
        }
        allocator: RMTModuleAllocator {
            @display("p=655,55;i=block/cogwheel");
        }
    connections allowunconnected:
        ribdIo <--> rmt.ribdIo;
}
