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

package rina.DIF;


import rina.Common.Test;
import rina.DAF.CDAP.CommonDistributedApplicationProtocol;
import rina.DIF.EFCP.EFCPModule;
import rina.DIF.Enrollment.EnrollmentModule;
import rina.DIF.FA.FlowAllocator;
import rina.DIF.RA.ResourceAllocator;
import rina.DIF.RIB.RIBDaemon;
import rina.DIF.RMT.RelayAndMux;
import rina.policies.DIF.Routing.IntRouting;

module IPCProcess
{
    parameters:
        @display("bgb=457,307;i=misc/square,#FF8000,50");
        string ipcAddress;
        string difName;
        string apName = default(ipcAddress + "_" + difName);
        bool relay = default(false);
        string routingPolicyName = default("DummyRouting");
    gates:
        inout southIo[];
        inout northIo[];
    submodules:
        flowAllocator: FlowAllocator {
            @display("p=167,50");
        }
        relayAndMux: RelayAndMux {
            @display("p=79,249;i=block/dispatch");
        }
        ribDaemon: RIBDaemon {
            @display("p=229,153");
        }

        efcp: EFCPModule {
            @display("p=79,50");
        }
        enrollmentModule: EnrollmentModule {
            @display("p=390,50");
        }
        routingPolicy: <routingPolicyName> like IntRouting {
            @display("p=390,153");
        }
        resourceAllocator: ResourceAllocator {
            @display("p=390,249");
        }

    connections allowunconnected:
        relayAndMux.ribdIo <--> ribDaemon.rmtIo;
}
