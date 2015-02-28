//
// Copyright © 2014 PRISTINE Consortium (http://ict-pristine.eu)
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

import rina.policies.DIF.RMT.Scheduler.IntRMTSchedulingPolicy;
import rina.policies.DIF.RMT.Monitor.IntRMTQMonitorPolicy;
import rina.policies.DIF.RMT.MaxQueue.IntRMTMaxQPolicy;

package rina.DIF.RMT;

module RelayAndMux
{
    parameters:
        @display("i=block/classifier;bgb=645,230");

        string schedPolicyName = default("LongestQFirst");
        string qMonitorPolicyName = default("SimpleMonitor");
        string maxQPolicyName = default("TailDrop");

        int defaultMaxQLength = default(20);
        int defaultThreshQLength = default(10);

        string queueColorBusy = default("#80FF80");
        string queueColorWarn = default("#FF8000");
        string queueColorFull = default("#800000");

    gates:
        inout ribdIo;

    submodules:
        rmt: RMT {
            @display("p=55,55");
        }
        schedulingPolicy: <schedPolicyName> like IntRMTSchedulingPolicy {
            @display("p=200,55;is=s");
        }
        queueMonitorPolicy: <qMonitorPolicyName> like IntRMTQMonitorPolicy {
            @display("p=310,55;is=s");
        }
        maxQueuePolicy: <maxQPolicyName> like IntRMTMaxQPolicy {
            @display("p=420,55;is=s");
        }
        rmtModuleAllocator: RMTModuleAllocator {
            @display("p=575,55");
        }
    connections allowunconnected:
        ribdIo <--> rmt.ribdIo;
}
