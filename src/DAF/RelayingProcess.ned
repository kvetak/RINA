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

package rina.DAF;

import rina.DAF.CDAP.CommonDistributedApplicationProtocol;
import rina.DAF.DA.DIFAllocator;
import rina.DAF.IRM.IRM;
import rina.DIF.RMT.RMT;


module RelayingProcess
{
    @display("bgb=487,266;i=misc/node,#FF80FF,30");
    gates:
        inout southIo[];
    submodules:
        irm: IRM {
            @display("p=100,64");
        }
        difAllocator: DIFAllocator {
            @display("p=220,64");
        }
        rmt: RMT {
            @display("p=152,171");
        }
        commonDistributedApplicationProtocol: CommonDistributedApplicationProtocol {
            @display("p=346,171");
        }
    connections:
        rmt.rmtIo <--> southIo++;
}
