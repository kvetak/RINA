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
import rina.DAF.IRM.ConnectionTable;
import rina.DAF.IRM.IRM;
import rina.DIF.RMT.RMT;


module ApplicationProcess
{
    parameters:
        @display("bgb=386,251;i=misc/node,yellow,30");
        //int numOfDIFs;
        string apName = default("App");
        string apInstance = default("0");

    gates:
        //inout southIo[numOfDIFs];

    submodules:
        irm: IRM {
            @display("p=64,180");
            //numOfDIFs = numOfDIFs;
        }
        commonDistributedApplicationProtocol: CommonDistributedApplicationProtocol {
            @display("p=254,58");
        }
        aePing: AEPing {
            @display("p=64,58");
        }

        connectionTable: ConnectionTable {
            @display("p=254,180");
        }
    connections allowunconnected:
}
