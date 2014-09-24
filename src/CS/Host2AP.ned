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


module Host2AP
{
    parameters:
        @display("i=device/pc;bgb=340,271");
        @node;

    gates:
        inout medium @loose;

    submodules:
        applicationProcess1: ApplicationProcess {
            @display("p=72,57");
        }

        applicationProcess2: ApplicationProcess {
            @display("p=268,57");
        }

        difAllocator: DIFAllocator {
            @display("p=170,57");
        }

        ipcProcess0: IPCProcess {
            @display("p=170,212");
        }

        ipcProcess1: IPCProcess {
            @display("p=170,130");
        }

    connections allowunconnected:
        ipcProcess0.southIo++ <--> medium;
        ipcProcess1.southIo++ <--> ipcProcess0.northIo++;
}
