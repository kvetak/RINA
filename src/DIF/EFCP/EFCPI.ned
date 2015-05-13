//
// Copyright © 2014 PRISTINE Consortium (http://ict-pristine.eu)
// 
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
// 

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
        @display("i=block/layer;bgb=506,241");
        string initialSeqNumPolicyName;
        string rcvrInactivityPolicyName;
        string senderInactivityPolicyName;
        string rttEstimatorPolicyName;
    gates:
        inout northIo; //to FAI
        inout southIo; //to RMT
    submodules:
        dtp: DTP {
            @display("p=41,112");
        }
        northG: DumbGate {
            @display("p=41,29;is=vs");
        }
        southG: DumbGate {
            @display("p=41,201;is=vs");
        }
        dtpState: DTPState {
            @display("p=131,41");
        }
        initialSeqNumPolicy: <initialSeqNumPolicyName> like IntInitialSeqNumPolicy {
            @display("p=387,29;is=vs");
        }
        rttEstimatorPolicy: <rttEstimatorPolicyName> like IntRTTEstimatorPolicy {
            @display("p=387,100;is=vs");
        }
        senderInactivityPolicy: <senderInactivityPolicyName> like IntSenderInactivityPolicy {
            @display("p=387,68;is=vs");
        }
        rcvrInactivityPolicy: <rcvrInactivityPolicyName> like IntRcvrInactivityPolicy {
            @display("p=387,133;is=vs");
        }
    connections allowunconnected:
        northG.northIo <--> northIo;
        dtp.northIo <--> northG.southIo;
        //        
        dtp.southIo <--> southG.northIo;
        southG.southIo <--> southIo;


}
