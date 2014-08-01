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

import rina.DAF.ApplicationProcess;
import rina.DIF.IPCProcess;


module Host2AP
{
    parameters:
        @display("i=device/pc;bgb=289,221");
        @node;
        //int numOfDIFs = 1;
        //int numOfAPs = 2;

    gates:
        inout medium @loose;

    submodules:
        applicationProcess1: ApplicationProcess {
            @display("p=72,57");
            //numOfDIFs = numOfDIFs;
        }
        
        applicationProcess2: ApplicationProcess {
            @display("p=218,57");
            //numOfDIFs = numOfDIFs;
        }
        
        ipcProcess1: IPCProcess {
            @display("p=133,153");
            //numOfAPs = numOfAPs;
        }
        
    connections allowunconnected:
        ipcProcess1.southIo++ <--> medium;
        //ipcProcess1.northIo[0] <--> applicationProcess1.southIo[0];
        //ipcProcess1.northIo[1] <--> applicationProcess2.southIo[0];
}
