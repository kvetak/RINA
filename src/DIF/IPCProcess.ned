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


import rina.DAF.CDAP.CommonDistributedApplicationProtocol;
import rina.DIF.EFCP.EFCP;
import rina.DIF.Enrollment.Enrollment;
import rina.DIF.FA.FlowAllocator;
import rina.DIF.RA.ResourceAllocator;
import rina.DIF.RIB.RIBDaemon;
import rina.DIF.RMT.RMT;


module IPCProcess
{
    parameters:
        @display("bgb=457,307;i=misc/square,#FF8000,50");
        int ipcAddress;
    gates:
        inout southIo[];
        inout northIo[];
    submodules:
        flowAllocator: FlowAllocator {
            @display("p=90,61");
        }
        rmt: RMT {
            @display("p=90,249");
        }
        ribDaemon: RIBDaemon {
            @display("p=238,147");
        }

        efcp: EFCP {
            @display("p=90,147");
        }
        resourceAllocator: ResourceAllocator {
            @display("p=390,195");
        }
        enrollment: Enrollment {
            @display("p=390,100");
        }
        commonDistributedApplicationProtocol: CommonDistributedApplicationProtocol {
            @display("p=238,249");
        }
    connections:
        rmt.rmtIo++ <--> southIo++;
        flowAllocator.appIo++ <--> northIo++;
        commonDistributedApplicationProtocol.southIo++ <--> rmt.rmtIo++;
}
