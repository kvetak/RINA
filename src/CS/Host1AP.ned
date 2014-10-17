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

package rina.CS;

import rina.Common.Test;
import rina.DAF.ApplicationProcess;
import rina.DAF.DA.DIFAllocator;
import rina.DIF.IPCProcess;


module Host1AP
{
    parameters:
        @display("i=device/pc;bgb=255,271");
        @node;
        //int numOfDIFs = 1;
        //int numOfAPs = 1;

    gates:
        inout medium @loose;

    submodules:
        applicationProcess1: ApplicationProcess {
            @display("p=70,56");
            //numOfDIFs = numOfDIFs;            
        }

        difAllocator: DIFAllocator {
            @display("p=210,56");
        }

        ipcProcess0: IPCProcess {
            @display("p=133,212");
			//numOfAPs = numOfAPs;
        }

        ipcProcess1: IPCProcess {
            @display("p=133,130");
			//numOfAPs = numOfAPs;
        }

    connections allowunconnected:
        ipcProcess0.southIo++ <--> medium;
        ipcProcess0.northIo++ <--> ipcProcess1.southIo++;
}
