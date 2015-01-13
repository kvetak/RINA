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

//
// <h1>Host with two Application Processes</h1> 
//
// This models simulates host node that has two different rank DIFs:
//  * 1x (N)-DIF <i>ipcProcess1</i> is used by AP for communication 
//  * 1x (N-1)-DIF <i>ipcProcess0</i> underlaying DIF for <i>ipcProcess1</i>   
//
// It contains two distinct APs - <i>applicationProcces1/2</i>
// It also contains <i>DIFAllocator</i> module as NameSpaceManager interface
//
// @author Vladimir Vesely (ivesely@fit.vutbr.cz)
// @date Last refactorized and documented on 2015-01-12


package rina.CS;

import rina.Common.Test;
import rina.DAF.ApplicationProcess;
import rina.DAF.DA.DIFAllocator;
import rina.DAF.IRM.IPCResourceManager;
import rina.DIF.IPCProcess;

module Host2AP
{
    parameters:
        @display("i=device/pc;bgb=340,422");
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
            @display("p=170,342");
        }

        ipcProcess1: IPCProcess {
            @display("p=170,260");
        }

        ipcResourceManager: IPCResourceManager {
            @display("p=170,168");
        }
    connections allowunconnected:
        ipcProcess0.southIo++ <--> medium;
        ipcProcess1.southIo++ <--> ipcProcess0.northIo++;
}
