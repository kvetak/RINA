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

import rina.src.DAF.ApplicationProcess;
import rina.src.DAF.DA.DIFAllocator;
import rina.src.DAF.IRM.IPCResourceManager;
import rina.src.DIF.IPCProcess;

module Host1APNInt
{
    parameters:
        @display("i=device/pc;bgb=695,400");
        @node;
        int numOfInterfaces = default(1);
        //int numOfDIFs = 1;
        //int numOfAPs = 1;

    gates:
        inout medium[numOfInterfaces] @loose;

    submodules:
        applicationProcess1: ApplicationProcess {
            @display("p=70,56");
            //numOfDIFs = numOfDIFs;            
        }

        difAllocator: DIFAllocator {
            @display("p=210,56");
        }

        ipcProcess0[numOfInterfaces]: IPCProcess {
            @display("p=133,323,r,150");
			//numOfAPs = numOfAPs;
        }

        ipcProcess1: IPCProcess {
            @display("p=133,241");
			//numOfAPs = numOfAPs;
        }

        ipcResourceManager: IPCResourceManager {
            @display("p=133,141");
        }
    connections allowunconnected:

        for i=0..sizeof(medium)-1 {
            ipcProcess0[i].southIo++ <--> medium[i];
            ipcProcess0[i].northIo++ <--> ipcProcess1.southIo++;
        }


}
