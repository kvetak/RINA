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

import rina.DAF.AE.AEPing;
import rina.DAF.CDAP.CommonDistributedApplicationProtocol;
import rina.DAF.DA.DIFAllocator;
import rina.DAF.IRM.IRM;
import rina.DIF.RMT.RMT;


module ApplicationProcess
{
    parameters:
        @display("bgb=434,251;i=misc/node,yellow,30");
        //int numOfDIFs;
        string apName = default("App");
        string apInstance = default("0");

    gates:
        //inout southIo[numOfDIFs];

    submodules:
        irm: IRM {
            @display("p=125,178");
            //numOfDIFs = numOfDIFs;
        }
        difAllocator: DIFAllocator {
            @display("p=315,178");
        }
        commonDistributedApplicationProtocol: CommonDistributedApplicationProtocol {
            @display("p=315,56");
        }
        aePing: AEPing {
            @display("p=125,56");
        }

    connections allowunconnected:
        //for i = 0 .. numOfDIFs - 1 {
        //    irm.irmIo[i] <--> southIo[i];            
        //}        
        //commonDistributedApplicationProtocol.southIo++ <--> irm.cdapIo++;
}
