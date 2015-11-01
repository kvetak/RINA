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

package rina.src.DIF.EFCP;
import rina.policies.DIF.EFCP.DTP.InitialSeqNum.IntInitialSeqNumPolicy;
import rina.policies.DIF.EFCP.DTP.RTTEstimator.IntRTTEstimatorPolicy;
import rina.policies.DIF.EFCP.DTP.RcvrInactivity.IntRcvrInactivityPolicy;
import rina.policies.DIF.EFCP.DTP.SenderInactivity.IntSenderInactivityPolicy;
import rina.src.DIF.EFCP.DTP.DTP;
import rina.src.DIF.EFCP.DTP.DTPState;
import rina.src.DIF.EFCP.DTP.DumbGate;


module EFCPI
{
    parameters:
        @display("i=block/layer;bgb=1045,333");
        string initialSeqNumPolicyName;
        string rcvrInactivityPolicyName;
        string senderInactivityPolicyName;
        string rttEstimatorPolicyName;
    gates:
        inout northIo; //to FAI
        inout southIo; //to RMT
    submodules:
        dtp: DTP {
            @display("p=41,92");
        }
        northG: DumbGate {
            @display("p=41,29;is=vs");
        }
        southG: DumbGate {
            @display("p=41,294;is=vs");
        }
        dtpState: DTPState {
            @display("p=131,41");
        }
        initialSeqNumPolicy: <initialSeqNumPolicyName> like IntInitialSeqNumPolicy {
            @display("p=387,25;is=vs");
        }
        rttEstimatorPolicy: <rttEstimatorPolicyName> like IntRTTEstimatorPolicy {
            @display("p=387,105;is=vs");
        }
        senderInactivityPolicy: <senderInactivityPolicyName> like IntSenderInactivityPolicy {
            @display("p=387,65;is=vs");
        }
        rcvrInactivityPolicy: <rcvrInactivityPolicyName> like IntRcvrInactivityPolicy {
            @display("p=387,145;is=vs");
        }
    connections allowunconnected:
        northG.northIo <--> northIo;
        dtp.northIo <--> northG.southIo;
        //        
        dtp.southIo <--> southG.northIo;
        southG.southIo <--> southIo;


}
