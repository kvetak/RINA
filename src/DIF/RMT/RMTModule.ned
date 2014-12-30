//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
// 

import rina.DIF.RMT.policies.scheduler.IntRMTSchedulingPolicy;
import rina.DIF.RMT.policies.monitor.IntRMTQMonitorPolicy;
import rina.DIF.RMT.policies.maxqueue.IntRMTMaxQPolicy;

package rina.DIF.RMT;

module RMTModule
{
    parameters:
        @display("i=block/classifier;bgb=590,275");

        string schedPolicyName = default("LongestQFirst");
        string qMonitorPolicyName = default("SimpleMonitor");
        string maxQPolicyName = default("TailDrop");

        double TxQueuingTime @unit(ms) = default(0.0ms);
        double RxQueuingTime @unit(ms) = default(0.0ms);

        int queueSize = default(20);
        int queueThresh = default(10);

        string queueColorBusy = default("#80FF80");
        string queueColorWarn = default("#FF8000");
        string queueColorFull = default("#800000");

    gates:
        inout ribdIo;

    submodules:
        rmt: RMT {
            @display("p=55,55");
        }
        rmtQueueManager: RMTQueueManager {
            @display("p=535,49");
        }
        schedulingPolicy: <schedPolicyName> like IntRMTSchedulingPolicy {
            @display("p=165,55;is=s");
        }
        queueMonitorPolicy: <qMonitorPolicyName> like IntRMTQMonitorPolicy {
            @display("p=270,55;is=s");
        }
        maxQueuePolicy: <maxQPolicyName> like IntRMTMaxQPolicy {
            @display("p=375,55;is=s");
        }
    connections allowunconnected:
        ribdIo <--> rmt.ribdIo;
}
