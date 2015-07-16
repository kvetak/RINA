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

package rina.src.CS;

package rina.src.CS;

import rina.src.DAF.ApplicationProcessNAE;
import rina.src.DAF.DA.DIFAllocator;
import rina.src.DAF.IRM.IPCResourceManager;
import rina.src.DIF.IPCProcess;

module HostNAPNAE
{
    parameters:
        @display("i=device/pc;bgb=255,400");
        @node;

        int numOfAPs = default(1);
        int numOfAEs = default(1);

    gates:
        inout medium @loose;

    submodules:
        applicationProcess[numOfAPs]: ApplicationProcessNAE {            
            @display("p=70,56,r");
            numOfAE = numOfAEs;
        }

        difAllocator: DIFAllocator {
            @display("p=210,56");
        }

        ipcProcess0: IPCProcess {
            @display("p=133,323");
        }

        ipcProcess1: IPCProcess {
            @display("p=133,241");
        }

        ipcResourceManager: IPCResourceManager {
            @display("p=133,141");
        }
    connections allowunconnected:
        ipcProcess0.southIo++ <--> medium;
        ipcProcess0.northIo++ <--> ipcProcess1.southIo++;
}
